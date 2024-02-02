#pragma once
#include <SplitEngine/AssetDatabase.hpp>
#include <SplitEngine/ECS/System.hpp>
#include <SplitEngine/Rendering/Sprite.hpp>

#include "SplitEngineShowcase/Component/Physics.hpp"
#include "SplitEngineShowcase/Component/Player.hpp"
#include "SplitEngineShowcase/Component/Transform.hpp"

using namespace SplitEngine;

namespace SplitEngineShowcase::System
{
	class PlayerController final : public ECS::System<Component::Transform, Component::Player, Component::Physics>
	{
		public:
			PlayerController(AssetHandle<Rendering::Sprite> bulletSprite);

			void Execute(Component::Transform*  transformComponents,
			             Component::Player*     playerComponents,
			             Component::Physics*    physicsComponents,
			             std::vector<uint64_t>& entities,
			             ECS::Context&          context) override;

		private:
			AssetHandle<Rendering::Sprite> _bulletSprite;
	};
}
