# include <Siv3D.hpp>
# include "FieldReader.h"
# include "AssetManager.h"
# include "ScoreCalculate.h"
# include "ScoreBar.h"
# include "Greedy.h"
# include "Simulator.h"
# include "beamsearch2.h"
# include <future>
# include <thread>

String ListenMessage(TCPClient& client)
{
	std::string message;
	while (true)
	{
		char character;

		if (!client.read(character))
		{
			return Unicode::Widen(message);
		}

		if (character == '\n')
		{
			return Unicode::Widen(message);
		}
		else
		{
			std::string tmpch;
			tmpch += character;
			message.push_back(character);
		}
	}
}

void Main()
{
	TOMLReader toml(U"config.toml");

	/* Windowの設定 */
	Window::Resize(1024, 768);
	Window::SetStyle(WindowStyle::Sizable);
	String windowMainTitle = U"踊って舞って回って - Visualizer";
	Window::SetTitle(windowMainTitle);

	/* アセットのロード */
	AssetLoader::Audios();
	AssetLoader::Textures();
	AssetLoader::Fonts();

	/* FieldとMatchの生成 */
	FilePath path = toml[U"Field.name"].get<String>();
	Field field;
	FieldReader reader(path);
	reader.copyTo(field);

	int32 turnMillis = toml[U"Match.turnMillis"].get<int32>();
	int32 max_turn = toml[U"Match.turns"].get<int32>();
	Match red_match(0, 0, U"null", field.teams[0].teamID, turnMillis, max_turn);
	Array<Match> blue_matches = {{ 0, 0, U"null", field.teams[1].teamID, turnMillis, max_turn }};

	ScoreBar scoreBar(RectF(Window::ClientSize().x - 250 - 50, 90, 250, 30));

	/* TCPサーバー */
	// IPv4 ip = IPv4::Localhost();
	// TCPClient client;
	// bool connected = false;
	// constexpr uint16 port = 50000;
	
	// client.connect(ip, port);
	// Window::SetTitle(windowMainTitle + U" | 接続待機中...");
	// std::string message;

	Array<Action> blue_actions;
	std::future<Array<Action>> result;
	std::thread th_blue = std::thread(solve_beam2, std::ref(blue_actions), field, blue_matches[0]);
	bool match_end = false;
	while (System::Update())
	{
		field.draw();
		field.update();

		FontAsset(U"30")(U"ターン : {}/{}"_fmt(field.turn, red_match.turns)).draw(Window::ClientSize().x - 250 - 50, 30);
		scoreBar.draw(FontAsset(U"25"), field);

		if (!match_end)
		{
			// ClearPrint();


			// if (client.isConnected())
			// {
			// 	if (!connected)
			// 	{
			// 		connected = true;
			// 		Window::SetTitle(windowMainTitle + U" | 接続完了！");
			// 	}

			// 	// const auto match_data = ToJson(blue_matches).toUTF8();
			// 	// client.send(match_data.data(), sizeof(char) * match_data.length());
			// }


			if (field.allActionWasDecided())
			{
				ClearPrint();
				th_blue.join();
				Array<Action> red_actions = field.getPlayerAction();

				Exec(field, red_actions, blue_actions);
				field.turn++;
				AudioAsset(U"遷移").playOneShot();
				th_blue = std::thread(solve_beam2, std::ref(blue_actions), field, blue_matches[0]);
			}
			if (field.turn >= red_match.turns)
			{
				match_end = true;
			}
		}
	}
	th_blue.join();
}

