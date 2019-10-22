# include "Field.h"
# include "Point.h"

Field::Field(int32 _height, int32 _width, 
	const Array<Array<int32>>& _points,
	UnixTime _startedAtUnixTime,
	int32 _turn,
	const Array<Array<int32>>& _tiled,
	const Array<Team>& _teams,
	const Array<Action>& _actions)
    : height(_height) , width(_width)
    , points(_points)
    , startedAtUnixTime(_startedAtUnixTime)
    , turn(_turn)
    , tiled(_tiled)
    , teams(_teams)
    , actions(_actions)
	, m_gridSize(46)
	, m_margin(20)
	, m_arrowFlag(height, Array<bool>(width, false))
	, m_typeFlag(height, Array<bool>(width, false))
	, m_playerActions(teams[0].agents.size(), {-1, U"stay", 0, 0})
{
	m_redIndex = 0;
	m_redID = teams[0].teamID;
	m_blueIndex = 1;
	m_blueID = teams[1].teamID;


	m_cells.resize(height);
	for (int32 y : step(height))
	{
		m_cells[y].resize(width);
		for (int32 x : step(width))
		{
			m_cells[y][x] = Rect(m_margin + (x+1) * m_gridSize, m_margin + (y+1) * m_gridSize, m_gridSize);
		}
	}

	m_tmpBigCells.resize(height+2);
	for (int32 y : step(height+2))
	{
		m_tmpBigCells[y].resize(width+2);
		for (int32 x : step(width+2))
		{
			m_tmpBigCells[y][x] = Rect(m_margin + x * m_gridSize, m_margin + y * m_gridSize, m_gridSize);
		}
	}
}

void Field::draw() const
{
	auto GridCenterPos = [&](int32 x, int32 y)
	{
		return s3d::Point(m_margin + (x+1) * m_gridSize + m_gridSize / 2, m_margin + (y+1) * m_gridSize + m_gridSize / 2);
	};

	for (auto y : step(height))
	{
		for (auto x : step(width))
		{
			if (tiled[y][x] == m_redID)
			{
				m_cells[y][x].draw(Color(U"#E2421F")).drawFrame(1.0, 1.0, Palette::Gray);

			}
			else if (tiled[y][x] == m_blueID)
			{
				m_cells[y][x].draw(Color(U"#205EE3")).drawFrame(1.0, 1.0, Palette::Gray);
				if (ExistAgent(1, y, x))
				{
					TextureAsset(U"Rabbit").resized(m_gridSize).drawAt(GridCenterPos(x, y), Alpha(130));
				}
			}
			else
			{
				m_cells[y][x].draw(Palette::Black).drawFrame(1.0, 1.0, Palette::Gray);
			}
			FontAsset(U"25")(points[y][x]).drawAt(GridCenterPos(x, y));
		}
	}

	for (auto y : step(height))
	{
		for (auto x : step(width))
		{
			if (m_arrowFlag[y][x])
			{
				TextureAsset(U"矢印.上").drawAt(GridCenterPos(x, y - 1), Alpha(130));
				TextureAsset(U"矢印.右上").drawAt(GridCenterPos(x + 1, y - 1), Alpha(130));
				TextureAsset(U"矢印.右").drawAt(GridCenterPos(x + 1, y), Alpha(130));
				TextureAsset(U"矢印.右下").drawAt(GridCenterPos(x + 1, y + 1), Alpha(130));
				TextureAsset(U"矢印.下").drawAt(GridCenterPos(x, y + 1), Alpha(130));
				TextureAsset(U"矢印.左下").drawAt(GridCenterPos(x - 1, y + 1), Alpha(130));
				TextureAsset(U"矢印.左").drawAt(GridCenterPos(x - 1, y), Alpha(130));
				TextureAsset(U"矢印.左上").drawAt(GridCenterPos(x - 1, y - 1), Alpha(130));
			}
			if (m_typeFlag[y][x] and !m_arrowFlag[y][x])
			{
				TextureAsset(U"en.move").drawAt(GridCenterPos(x - 1, y + 1), Alpha(200));
				TextureAsset(U"en.remove").drawAt(GridCenterPos(x, y + 1), Alpha(200));
				TextureAsset(U"en.stay").drawAt(GridCenterPos(x + 1, y + 1), Alpha(200));
			}
			if (ExistAgent(0, y, x))
			{
				TextureAsset(U"Cat").resized(m_gridSize).drawAt(GridCenterPos(x, y), Alpha(130));
				Agent agent = GetAgent(0, y, x);
				for (auto& act : m_playerActions)
				{
					if (act.agentID == agent.agentID)
					{
						if (act.apply == 2)
						{
							Point pos = GridCenterPos(x, y) - Point(m_gridSize / 2, m_gridSize / 2);
							TextureAsset(U"heavy_check_mark").resized(m_gridSize/1.8).draw(pos);
						}
					}
				}
			}
		}
	}

}

void Field::update()
{
	for (auto y : step(height))
	{
		for (auto x : step(width))
		{
			if (m_typeFlag[y][x])
			{
				for (auto dx : Range(-1, 1))
				{
					int32 ty = y + 1;
					int32 tx = x + dx;
					if (m_tmpBigCells[ty+1][tx+1].leftClicked())
					{
						std::array<String, 3> types = { U"move", U"remove", U"stay" };
						m_typeFlag[y][x] = false;
						AddActionType(y, x, types[dx + 1]);
						AudioAsset(U"decision").playOneShot(0.3);
					}
				}
			}

			if (tiled[y][x] == m_redID and ExistAgent(0, y, x) and m_cells[y][x].leftClicked())
			{
				m_arrowFlag[y][x] = !m_arrowFlag[y][x];
			}
			if (m_arrowFlag[y][x] == true)
			{
				for (auto dy : Range(-1, 1))
				{
					for (auto dx : Range(-1, 1))
					{
						if (Point(dy, dx).isZero()) { continue; }

						int32 ty = y + dy;
						int32 tx = x + dx;
						if (!omm::Point(ty, tx).isOver(height, width) and m_cells[ty][tx].leftClicked())
						{
							m_typeFlag[y][x] = true;
							m_arrowFlag[y][x] = false;
							AddActionDirection(y, x, dy, dx);
						}
					}
				}
			}
		}
	}
}

bool Field::allActionWasDecided()
{
	for (const auto& act : m_playerActions)
	{
		if (act.apply != 2)
		{
			return false;
		}
	}

	m_playerActions.each([](auto& x) { x.apply = 0; });
	return true;
}

Array<Action> Field::getPlayerAction() const
{
	return m_playerActions;
}

Array<Array<int32>> Field::normalizedTiled(int32 team_index) const
{
	Array<Array<int32>> normalizeTiled(height, Array<int32>(width, 0));
	int32 teamID = teams[team_index].teamID;

	for (auto y : step(height))
	{
		for (auto x : step(width))
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

void Field::AddAction(int32 y, int32 x, int32 dy, int32 dx, String type)
{
	for (auto i : step(teams[0].agents.size()))
	{
		if (teams[0].agents[i].y == y and teams[0].agents[i].x == x)
		{
			m_playerActions[i].agentID = teams[0].agents[i].agentID;
			m_playerActions[i].dy = dy;
			m_playerActions[i].dx = dx;
		}
	}
}

void Field::AddActionDirection(int32 y, int32 x, int32 dy, int32 dx)
{
	for (auto i : step(teams[0].agents.size()))
	{
		if (teams[0].agents[i].y == y and teams[0].agents[i].x == x)
		{
			m_playerActions[i].agentID = teams[0].agents[i].agentID;
			m_playerActions[i].dy = dy;
			m_playerActions[i].dx = dx;
		}
	}
}

void Field::AddActionType(int32 y, int32 x, String type)
{
	for (auto i : step(teams[0].agents.size()))
	{
		if (teams[0].agents[i].y == y and teams[0].agents[i].x == x)
		{
			m_playerActions[i].agentID = teams[0].agents[i].agentID;
			m_playerActions[i].type = type;
			
			// 汚いコード
			m_playerActions[i].apply = 2;
		}
	}
}

bool Field::ExistAgent(int32 team_index, int32 y, int32 x) const
{
	for (const auto& agent : teams[team_index].agents)
	{
		if (agent.y == y and agent.x == x)
		{
			return true;
		}
	}
	return false;
}

Agent Field::GetAgent(int32 team_index, int32 y, int32 x) const
{
	for (const auto& agent : teams[team_index].agents)
	{
		if (agent.y == y and agent.x == x)
		{
			return agent;
		}
	}
	return Agent();
}

