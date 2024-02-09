#pragma once
#include <SplitEngine/AssetDatabase.hpp>
#include <SplitEngineShowcase/SpriteTexture.hpp>

using namespace SplitEngine;

namespace SplitEngineShowcase::Component
{
	struct SpriteRenderer
	{
		AssetHandle<SpriteTexture> SpriteTexture;
		float                      AnimationSpeed    = 0;
		float                      CurrentFrame      = 0;
		uint32_t                   PreviousTextureID = 0;
	};
}
