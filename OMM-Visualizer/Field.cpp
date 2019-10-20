# include "Field.h"

Field::Field(int32 _height, int32 _width, 
	const Array<Array<int32>>& _points,
	UnixTime _startedAtUnixTime,
	int32 _turn,
	const Array<Array<int32>>& _tiled,
	const Array<Team>& _teams,
	const Array<Action>& _actions)
    : height(_height)
    , width(_width)
    , points(_points)
    , startedAtUnixTime(_startedAtUnixTime)
    , turn(_turn)
    , tiled(_tiled)
    , teams(_teams)
    , actions(_actions)
{
	m_redIndex = 0;
	m_redID = teams[0].teamID;
	m_blueIndex = 1;
	m_blueID = teams[1].teamID;
}

void Field::draw() const
{
	for (int32 y : step(height))
	{
		for (int32 x : step(height))
		{
			const int32 GridSize = 46;
			int32 margin = 20;
			if (tiled[y][x] == m_redID)
			{
				Rect dot(margin + x * GridSize, margin + y * GridSize, GridSize);
				dot.draw(Color(U"#E2421F")).drawFrame(1.0, 1.0, Palette::Gray);
				TextureAsset(U"Cat").resized(GridSize).drawAt(margin + x * GridSize + GridSize / 2, margin + y * GridSize + GridSize / 2, Alpha(130));
			}
			else if (tiled[y][x] == m_blueID)
			{
				Rect dot(margin + x * GridSize, margin + y * GridSize, GridSize);
				dot.draw(Color(U"#205EE3")).drawFrame(1.0, 1.0, Palette::Gray);
				TextureAsset(U"Rabbit").resized(GridSize).drawAt(margin + x * GridSize + GridSize / 2, margin + y * GridSize + GridSize / 2, Alpha(130));
			}
			else
			{
				Rect dot(margin + x * GridSize, margin + y * GridSize, GridSize);
				dot.draw(Palette::Black).drawFrame(1.0, 1.0, Palette::Gray);
			}
			FontAsset(U"25")(points[y][x]).drawAt(margin + x * GridSize + GridSize/2, margin + y * GridSize + GridSize/2);
		}
	}
}

Array<Array<int32>> Field::normalizedTiled(int32 team_index) const
{
	Array<Array<int32>> normalizeTiled(height, Array<int32>(width, 0));
	int32 teamID = teams[team_index].teamID;

	for (int32 y = 0; y < height; ++y)
	{
		for (int32 x = 0; x < width; ++x)
		{
			normalizeTiled[y][x] = (tiled[y][x] == teamID);
		}
	}

	return normalizeTiled;
}

std::pair<int32, int32> Field::getIndex(const Match& match) const
{
    if (teams.at(0).teamID == match.teamID)
    {
        return std::pair<int32, int32>(0, 1);
    }
    else
    {
        return std::pair<int32, int32>(1, 0);
    }
}

