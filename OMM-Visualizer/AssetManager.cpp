# include "AssetManager.h"

bool AssetLoader::Audio()
{
	return false;
}

bool AssetLoader::Texture()
{
	TextureAsset::Register(U"Cat", Emoji(U"🐈"));
	TextureAsset::Register(U"Rabbit", Emoji(U"🐇"));
	return false;
}

bool AssetLoader::Font()
{
	for (auto& size : Range(5, 50, 5))
	{
		FontAsset::Register(ToString(size), size);
	}
	return false;
}
