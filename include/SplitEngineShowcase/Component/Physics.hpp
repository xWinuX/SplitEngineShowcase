#pragma once
#include <glm/vec3.hpp>

namespace SplitEngineShowcase::Component
{
	struct Physics
	{
		bool      HasGravity = false;
		glm::vec3 Velocity{};
	};
}
