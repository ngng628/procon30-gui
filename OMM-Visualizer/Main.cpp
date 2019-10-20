# include <Siv3D.hpp> // OpenSiv3D v0.4.1
# include <iostream>
# include "FieldReader.h"
# include "AssetManager.h"
# include "ScoreCalculate.h"
# include "ScoreBar.h"


void Main()
{
	Window::SetTitle(U"踊って舞って回って - Visualizer");
	Window::SetStyle(WindowStyle::Sizable);
	AssetLoader::Audio();
	AssetLoader::Texture();
	AssetLoader::Font();
	
	FilePath path = U"public-field/testcase1.json";
	Window::Resize(1024, 768);


	Field field;
	FieldReader reader(path);
	reader.copyTo(field);

	int32 turnMillis = 10000;
	int32 max_turn = 50;
    Match match(0, 0, U"ヌル高専", field.teams[0].teamID, turnMillis, max_turn);

	const ScoreBar scoreBar(RectF(Window::ClientSize().x - 250 - 50, 90, 250, 30));


	while (System::Update())
	{
		ClearPrint();
		field.draw();

		int32 red_score = ScoreCalculate(field.points, field.normalizedTiled(0));
		int32 blue_score = ScoreCalculate(field.points, field.normalizedTiled(1));

		FontAsset(U"30")(U"ターン : {}/{}"_fmt(field.turn, match.turns)).draw(Window::ClientSize().x - 250 - 50, 30);
		scoreBar.draw(FontAsset(U"25"), red_score, blue_score);

		Print << Profiler::FPS() << U" FPS";
	}
}

