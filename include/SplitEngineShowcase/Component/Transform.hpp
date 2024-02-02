#pragma once
#include <glm/vec3.hpp>

namespace SplitEngineShowcase::Component
{
	struct Transform
	{
		glm::vec3 Position{};
		float     Rotation = 0;
	};
}
