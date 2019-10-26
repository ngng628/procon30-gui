# include "FieldForSearch.h"
using namespace std;

Array<Array<int32>> FieldForSearch::points;

FieldForSearch::FieldForSearch()
{
}

FieldForSearch::FieldForSearch(int w, int h,
             int mt, int t,
             std::vector<std::vector<Cell>> b,
             std::vector<Player> e, std::vector<Player> a)
             : width(w), height(h)
             , maxturn(mt), turn(t)
             , Board(b)
             , Enemies(e), Allies(a)
{
    teamnum = (int)Allies.size();
}

FieldForSearch::FieldForSearch(int w, int h, int n)
     : width(w), height(h)
     , maxturn(30), turn(1)
     , teamnum(n)
{
    Board.resize(h,std::vector<Cell>(w));
    Enemies.resize(n);
    Allies.resize(n);
}

FieldForSearch::FieldForSearch(int w, int h, int n, int mt, int t)
     : width(w), height(h)
     , maxturn(mt), turn(t)
     , teamnum(n)
{
    Board.resize(h,std::vector<Cell>(w));
    Enemies.resize(n);
    Allies.resize(n);
}

void FieldForSearch::reset(){
    for(int i=0;i<points.size();i++){
        points[i].clear();
        points[i].shrink_to_fit();
    }
    points.clear();
    points.shrink_to_fit();
}

FFS toFFS(const Field& field, const int turns, const int team_index, const int allyID, const int enemyID)
{
    FieldForSearch ffs
    (
        field.width,
        field.height,
        field.teams[0].agents.size(),
        turns,
        field.turn
    );
    ffs.points = field.points;
    for(int y=0;y<ffs.height;y++)
    {
        for(int x=0;x<ffs.width;x++)
        {
            if(field.tiled[y][x] == allyID)
                ffs.Board[y][x].type = ATP::ally;
            else if(field.tiled[y][x] == enemyID)
                ffs.Board[y][x].type = ATP::enemy;
            else
                ffs.Board[y][x].type = ATP::newtral;
        }
    }
    for(int i=0;i<ffs.teamnum;i++){
        ffs.Allies[i].pos = {field.teams[team_index].agents[i].y, field.teams[team_index].agents[i].x};
        ffs.Enemies[i].pos = {field.teams[!team_index].agents[i].y, field.teams[!team_index].agents[i].x};
    }
    return ffs;
}

