#pragma once
#include <ranges>
#include <SplitEngine/ECS/System.hpp>

#include "SplitEngineShowcase/Component/Physics.hpp"
#include "SplitEngineShowcase/Component/Transform.hpp"

using namespace SplitEngine;

namespace SplitEngineShowcase::System
{
	class Physics final : public ECS::System<Component::Transform, Component::Physics>
	{
		public:
		Physics() = default;

		/**
		 * The execute function contains a pointer to each component array used by the system
		 * This function can run multiple times and is called for each archetype contains all components needed by this system
		 */
		void Execute(Component::Transform* transformComponents, Component::Physics* physicsComponents, std::vector<uint64_t>& entities, ECS::Context& context) final;

		std::ranges::iota_view<size_t, size_t> _indexes;
	};
}
