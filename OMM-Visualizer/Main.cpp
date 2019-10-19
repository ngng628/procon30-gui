# include <Siv3D.hpp> // OpenSiv3D v0.4.1
# include <iostream>
# include "FieldReader.h"
# include "AssetManager.h"

void Main()
{
	AssetLoader::Audio();
	AssetLoader::Texture();
	AssetLoader::Font();
	
	FilePath path = U"public-field/C-1.json";
	Window::Resize(1024, 768);

	Field field;
	FieldReader reader(path);
	reader.copyTo(field);

	while (System::Update())
	{
		field.draw();
	}
}
