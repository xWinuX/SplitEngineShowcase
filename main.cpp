#include "SplitEngine/Application.hpp"
#include "SplitEngine/AssetDatabase.hpp"
#include "SplitEngine/Input.hpp"
#include "SplitEngine/Debug/Performance.hpp"
#include "SplitEngine/ECS/System.hpp"
#include "SplitEngine/Rendering/Sprite.hpp"
#include "SplitEngine/Tools/ImagePacker.hpp"
#include "SplitEngine/Tools/ImageSlicer.hpp"

#include <glm/gtc/random.hpp>

#include "SplitEngineShowcase/Assets.hpp"
#include "SplitEngineShowcase/Component/AudioSource.hpp"
#include "SplitEngineShowcase/Component/Camera.hpp"
#include "SplitEngineShowcase/Component/Physics.hpp"
#include "SplitEngineShowcase/Component/Player.hpp"
#include "SplitEngineShowcase/Component/Sprite.hpp"
#include "SplitEngineShowcase/Component/Transform.hpp"
#include "SplitEngineShowcase/System/AudioSourcePlayer.hpp"
#include "SplitEngineShowcase/System/Camera.hpp"
#include "SplitEngineShowcase/System/Physics.hpp"
#include "SplitEngineShowcase/System/PlayerController.hpp"
#include "SplitEngineShowcase/System/SpriteRendering.hpp"

using namespace SplitEngine;
using namespace SplitEngineShowcase;

int main()
{
	Application application = Application({});
	application.Initialize();

	Input::RegisterAxis2D(InputAction::Move, { KeyCode::A, KeyCode::D }, { KeyCode::S, KeyCode::W });
	Input::RegisterButtonAction(InputAction::Fire, KeyCode::MOUSE_LEFT);

	AssetDatabase& assetDatabase = application.GetAssetDatabase();

	/**
	 * You can create an Asset with every type that has a public struct named CreateInfo!
	 * That means you can also create custom assets
	 * The key can be anything as long as it can be cast into an int, so no magic strings!
	 */
	AssetHandle<Rendering::Shader>   shader   = assetDatabase.CreateAsset<Rendering::Shader>(Shader::Sprite, { "res/shaders/debug" });
	AssetHandle<Rendering::Material> material = assetDatabase.CreateAsset<Rendering::Material>(Material::Sprite, { shader });

	// Create texture page and sprite assets
	Tools::ImagePacker texturePacker = Tools::ImagePacker();

	uint64_t floppaPackerID = texturePacker.AddImage("res/textures/Floppa.png");
	uint64_t blueBulletPackerID = texturePacker.AddRelatedImages(Tools::ImageSlicer::Slice("res/textures/BlueBullet.png", {3}));

	Tools::ImagePacker::PackingData packingData = texturePacker.Pack(2048);

	AssetHandle<Rendering::Sprite> floppaSprite = assetDatabase.CreateAsset<Rendering::Sprite>(Sprite::Floppa, { floppaPackerID, packingData });
	AssetHandle<Rendering::Sprite> blueBulletSprite = assetDatabase.CreateAsset<Rendering::Sprite>(Sprite::BlueBullet, { blueBulletPackerID, packingData });

	// Setup ECS
	ECS::Registry& ecs = application.GetECSRegistry();

	/**
	 * 	Each component that is used needs to be registered
	 * 	It's important that every Component, that will be used, is registered before any Entities are created or else the ECS will not work or likely crash the app
	 */
	ecs.RegisterComponent<Component::Transform>();
	ecs.RegisterComponent<Component::Sprite>();
	ecs.RegisterComponent<Component::Physics>();
	ecs.RegisterComponent<Component::AudioSource>();
	ecs.RegisterComponent<Component::Player>();
	ecs.RegisterComponent<Component::Camera>();

	/**
	 * 	Each system can either be registered as a gameplay system or as a render system
	 * 	Gameplay systems execute before rendering systems and don't have any special context
	 * 	Render systems execute after gameplay systems and run in a vulkan context so draw calls/binds etc... can be made
	 * 	Systems can be registered multiple times and parameters get forwarded to the systems constructor
	 * 	Systems can be registered as the game is running, so no need to preregister all at the start if you don't want to
	 */
	ecs.AddSystem<System::Physics>(ECS::Stage::Gameplay, 0);
	ecs.AddSystem<System::AudioSourcePlayer>(ECS::Stage::Gameplay, 0);
	ecs.AddSystem<System::PlayerController>(ECS::Stage::Gameplay, 0, blueBulletSprite);
	ecs.AddSystem<System::Camera>(ECS::Stage::Gameplay, 1);
	ecs.AddSystem<System::SpriteRenderer>(ECS::Stage::Rendering, 0, material, packingData);

	// Create entities
	for (int i = 0; i < 1'000'000; ++i) { ecs.CreateEntity<Component::Transform, Component::Sprite>({ glm::ballRand(100.0f), 0.0f }, { floppaSprite, 1.0f, 0 }); }

	uint64_t playerEntity = ecs.CreateEntity<Component::Transform, Component::Physics, Component::Player, Component::Sprite>({}, {}, {}, { floppaSprite, 1.0f });

	ecs.CreateEntity<Component::Transform, Component::Camera>({}, { playerEntity });

	// Run Game
	application.Run();

	return 0;
}
