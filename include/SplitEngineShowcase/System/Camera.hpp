#pragma once
#include <SplitEngine/ECS/System.hpp>
#include <SplitEngine/Rendering/Vulkan/Instance.hpp>

#include "SplitEngineShowcase/Component/Camera.hpp"
#include "SplitEngineShowcase/Component/Transform.hpp"

using namespace SplitEngine;

namespace SplitEngineShowcase::System
{
	class Camera final : public ECS::System<Component::Transform, Component::Camera>
	{
		public:
			Camera() = default;

			void Execute(Component::Transform* transformComponents, Component::Camera* cameraComponents, std::vector<uint64_t>& entities, ECS::Context& context) override;

		private:
			struct CameraUBO
			{
				glm::mat4 view;
				glm::mat4 proj;
				glm::mat4 viewProj;
			};
	};
}
