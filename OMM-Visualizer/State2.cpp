# include "State2.h"

State2::State2()
     : via(10)
{
}

State2::State2(FFS _field)
     : field(_field)
     , via(10)
{
    calcScore();
}
 
void State2::calcScore()
{
    score = LeadScoreCalculate(field, 3, 1, 2, 2);
}

State2 transition(const State2& state, const int32 id, const omm::Point dir,
                  const Array<Array<Array<omm::Point>>>& conflictAllyPos,
                  Array<std::pair<int32, omm::Point>>& deletedTiles,
                  const int d)
{
    State2 next = state;
    const omm::Point here = next.field.Allies[id].pos;
    const int32 width = next.field.width;
    const int32 height = next.field.height;
    const omm::Point targetPos = here+dir;
    // 停留措置
    if(dir.isZero())
    {
        Command tmpc;
        next.via[d] = std::make_pair(tmpc,std::make_pair(here,here));
        return next;
    }
    // 場外 // 停留措置
    if(targetPos.isOver(height, width))
    {
        Command tmpc;
        next.via[d] = std::make_pair(tmpc,std::make_pair(here,here));
        return next; 
    }
    // 他人ゾーン // 停留措置
    for(int32 i=0; i<(int32)conflictAllyPos[d].size(); i++)
    {
        if(i==id) continue;
        if(conflictAllyPos[d][i][0] == targetPos || conflictAllyPos[d][i][1] == targetPos)
        {
            Command tmpc;
            next.via[d] = std::make_pair(tmpc,std::make_pair(here,here));
            return next;
        }
    }
    
    ATP& targetType = next.field.Board[targetPos.y][targetPos.x].type;
    // それほんとに消えてますか
    if(targetType != ATP::enemy)
    {
        for(auto p:deletedTiles)
        {
            if(p.second == targetPos && p.first > d)
            {
                targetType = ATP::enemy;
                p.first = d;
            }
        }
    }

    // タイルの色によって行動を決めて返す（本編）
    if(targetType == ATP::enemy)
    {
        deletedTiles.emplace_back(d,targetPos);
        targetType = ATP::newtral;
        Command tmpc(Act::Remove, dir);
        next.via[d] = std::make_pair(tmpc,std::make_pair(here,targetPos));
    }
    else
    {
        targetType = ATP::ally;
        Command tmpc(Act::Move, dir);
        next.via[d] = std::make_pair(tmpc,std::make_pair(here,targetPos));
        next.field.Allies[id] = targetPos;
    }
    next.calcScore();
    return next;
}