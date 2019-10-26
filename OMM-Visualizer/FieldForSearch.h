#pragma once
# include "Player.h"
# include "Cell.h"
# include "Match.h"
# include "Team.h"
# include "Action.h"
# include "Point.h"
# include "Field.h"
# define  FieldForSearch FFS


struct FieldForSearch
{
    int width,height;
    int maxturn;
    int turn;
    std::vector<std::vector<Cell>> Board;
    static Array<Array<int32>> points;
    std::vector<Player> Enemies;
    std::vector<Player> Allies;
    int teamnum;

    FieldForSearch();
    FieldForSearch(int,int,int,int,std::vector<std::vector<Cell>>,
          std::vector<Player>, std::vector<Player>);
    FieldForSearch(int,int,int);
    FieldForSearch(int,int,int,int,int);
    static void reset();
};


/// <summary>
/// Field‚ðFFS‚É•ÏŠ·‚µ‚Ü‚·
/// </summary>
FFS toFFS(const Field& field, const int turns, const int team_index, const int allyID, const int enemyID);
