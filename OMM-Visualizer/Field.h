# pragma once
# include "Team.h"
# include "Action.h"
# include "Match.h"

using UnixTime = long;

struct Field
{
	Field() = default;
    Field(int32 _height, int32 _width, 
        const Array<Array<int32>>& _points,
        UnixTime _startedAtUnixTime,
        int32 _turn,
        const Array<Array<int32>>& _tiled,
        const Array<Team>& _teams,
        const Array<Action>& _actions
    );

	void draw() const;
	void update();
	bool allActionWasDecided();
	Array<Action> getPlayerAction() const;

	int32 height;
	int32 width;
	Array<Array<int32>> points;
	UnixTime startedAtUnixTime;
	int32 turn;
	Array<Array<int32>> tiled;
	Array<Team> teams;
	Array<Action> actions;

    /// <summary>
    /// 正規化したフィールドを返します
    /// </summary>
    Array<Array<int32>> normalizedTiled(int32 team_index) const;

    /// <summar>
    /// Ally と Enemy の team_index を返します
    /// </summar>
    /// <param name="match">
    /// 試合情報
    /// </summar>
    /// <returns>
    /// first : ally_index  ( 0 | 1 )
    /// second: enemy_index ( 1 | 0 )
    /// </return>
    std::pair<int32, int32> getIndex(const Match& match) const;

private:
	int32 m_redIndex;
	int32 m_redID;
	int32 m_blueIndex;
	int32 m_blueID;

	int32 m_gridSize;
	int32 m_margin;

	Array<Array<bool>> m_arrowFlag;

	Array<Texture> m_typeTexture;
	Array<Array<bool>> m_typeFlag;
	
	Array<Array<Rect>> m_cells;
	Array<Array<Rect>> m_tmpBigCells;

	Array<Action> m_playerActions;

	void AddAction(int32 y, int32 x, int32 dy, int32 dx, String type);
	void AddActionDirection(int32 y, int32 x, int32 dy, int32 dx);
	void AddActionType(int32 y, int32 x, String type);
	bool ExistAgent(int32 team_index, int32 y, int32 x) const;
	Agent GetAgent(int32 team_index, int32 y, int32 x) const;
};

