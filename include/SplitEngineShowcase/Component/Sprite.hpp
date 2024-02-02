#pragma once
#include <SplitEngine/AssetDatabase.hpp>
#include <SplitEngine/Rendering/Sprite.hpp>

using namespace SplitEngine;

namespace SplitEngineShowcase::Component
{
	struct Sprite
	{
		AssetHandle<Rendering::Sprite> SpriteAsset;
		float                          AnimationSpeed    = 0;
		float                          CurrentFrame      = 0;
		uint32_t                       PreviousTextureID = 0;
	};
}
