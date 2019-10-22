# include <Siv3D.hpp>
# include "FieldReader.h"
# include "AssetManager.h"
# include "ScoreCalculate.h"
# include "ScoreBar.h"
# include "Greedy.h"
# include "Simulator.h"

void Main()
{
	TOMLReader toml(U"config.toml");

	Window::Resize(1024, 768);
	Window::SetStyle(WindowStyle::Sizable);
	Window::SetTitle(U"踊って舞って回って - Visualizer");

	AssetLoader::Audios();
	AssetLoader::Textures();
	AssetLoader::Fonts();

	FilePath path = toml[U"Field.name"].get<String>();

	Field field;
	FieldReader reader(path);
	reader.copyTo(field);

	int32 turnMillis = toml[U"Match.turnMillis"].get<int32>();
	int32 max_turn = toml[U"Match.turns"].get<int32>();
    Match red_match(0, 0, U"ヌル高専", field.teams[0].teamID, turnMillis, max_turn);
    Match blue_match(0, 0, U"ヌル高専", field.teams[1].teamID, turnMillis, max_turn);

	const ScoreBar scoreBar(RectF(Window::ClientSize().x - 250 - 50, 90, 250, 30));

	while (System::Update())
	{
		field.draw();
		field.update();

		// int32 red_score = ScoreCalculate(field.points, field.normalizedTiled(0));
		// int32 blue_score = ScoreCalculate(field.points, field.normalizedTiled(1));

		FontAsset(U"30")(U"ターン : {}/{}"_fmt(field.turn, red_match.turns)).draw(Window::ClientSize().x - 250 - 50, 30);
		scoreBar.draw(FontAsset(U"25"), field);

		if (field.allActionWasDecided())
		{
			Array<Action> red_actions = field.getPlayerAction();
			Array<Action> blue_actions = Greedy(field, blue_match);

			Exec(field, red_actions, blue_actions);
			field.turn++;
			AudioAsset(U"遷移").playOneShot();
		}
	}
}

