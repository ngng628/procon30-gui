# include "AssetManager.h"

bool AssetLoader::Audios()
{
	AudioAsset::Register(U"decision", U"asset/se/決定-木琴.mp3");
	AudioAsset::Preload(U"decision");
	AudioAsset::Register(U"遷移", U"asset/se/遷移.mp3");
	AudioAsset::Preload(U"遷移");

	return false;
}

bool AssetLoader::Textures()
{
	TextureAsset::Register(U"Cat", Emoji(U"🐈"));
	TextureAsset::Register(U"Rabbit", Emoji(U"🐇"));
	TextureAsset::Register(U"heavy_check_mark", Emoji(U"✔"));

	TextureAsset::Register(U"矢印.上", U"asset/矢印/上.png");
	TextureAsset::Register(U"矢印.右上", U"asset/矢印/右上.png");
	TextureAsset::Register(U"矢印.右", U"asset/矢印/右.png");
	TextureAsset::Register(U"矢印.右下", U"asset/矢印/右下.png");
	TextureAsset::Register(U"矢印.下", U"asset/矢印/下.png");
	TextureAsset::Register(U"矢印.左下", U"asset/矢印/左下.png");
	TextureAsset::Register(U"矢印.左", U"asset/矢印/左.png");
	TextureAsset::Register(U"矢印.左上", U"asset/矢印/左上.png");

	TextureAsset::Register(U"en.move", U"asset/en/move.png");
	TextureAsset::Register(U"en.remove", U"asset/en/remove.png");
	TextureAsset::Register(U"en.stay", U"asset/en/stay.png");

	TextureAsset::Register(U"ja.move", U"asset/ja/move.png");
	TextureAsset::Register(U"ja.remove", U"asset/ja/remove.png");
	TextureAsset::Register(U"ja.stay", U"asset/ja/stay.png");

	return false;
}

bool AssetLoader::Fonts()
{
	for (auto& size : Range(5, 50, 5))
	{
		FontAsset::Register(ToString(size), size);
	}
	return false;
}
