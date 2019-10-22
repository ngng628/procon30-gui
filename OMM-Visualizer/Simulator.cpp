# include "Simulator.h"
# include "ScoreCalculate.h"
# include "Point.h"
using namespace std;

bool Exec(Field& field, Array<Action> ally_actions, Array<Action> enemy_actions)
{
    int index = 0;

    // 無駄な処理だけど計算量そんなにないので確実に処理するために書いとくよ
    // 一旦Actionはすべて有効であるものとする
    for (auto& act : ally_actions)
    {
        act.apply = 1;
    }
    for (auto& act : enemy_actions)
    {
        act.apply = 1;
    }

    assert(ally_actions.size() == field.teams[index].agents.size());
    assert(enemy_actions.size() == field.teams[!index].agents.size());

    // 「無効」や「競合」そして「有効」な行動を順次格納
    Array<Action> actions_buff;

    // 「無効」な行動をAction配列から排除する
    ExcludeInvalidActions(field, 0, ally_actions, actions_buff);
    ExcludeInvalidActions(field, 1, enemy_actions, actions_buff);

    // 指定先がかぶった場合、その行動は競合となる
    map<int, int> mp;
    for (auto& act : ally_actions)
    {
        Team team = field.teams[index];
        for (auto i : step(team.agents.size()))
        {
            if (team.agents[i].agentID == act.agentID)
            {
                int32 ty = team.agents[i].y + act.dy;
                int32 tx = team.agents[i].x + act.dx;
                mp[1000*ty + tx]++;
            }
        }
    }
    for (auto& act : enemy_actions)
    {
        Team team = field.teams[!index];
        for (auto i : step(team.agents.size()))
        {
            if (team.agents[i].agentID == act.agentID)
            {
                int32 ty = team.agents[i].y + act.dy;
                int32 tx = team.agents[i].x + act.dx;
                mp[1000*ty + tx]++;
            }
        }
    }

    auto conflict = [&](auto& act){ 
        for (const auto& team : field.teams)
        {
            for (const auto& agent : team.agents)
            {
                if (agent.agentID == act.agentID)
                {
                    int32 ty = agent.y + act.dy;
                    int32 tx = agent.x + act.dx;
                    if (mp[1000*ty + tx] >= 2)
                    {
                        act.apply = 0;
                        actions_buff.push_back(act);

                        return true;
                    }
                }
            }
        }
        return false;
    };

    auto it = find_if(ally_actions.begin(), ally_actions.end(), conflict);
    while(it != ally_actions.end())
    {
        int64 index_ = std::distance(ally_actions.begin(), it);
        ally_actions[index_].apply = 0;
        it = find_if(++it, ally_actions.end(), conflict);
    }

    it = find_if(enemy_actions.begin(), enemy_actions.end(), conflict);
    while(it != enemy_actions.end())
    {
        int64 index_ = std::distance(enemy_actions.begin(), it);
        enemy_actions[index_].apply = 0;
        it = find_if(++it, enemy_actions.end(), conflict);
    }

    // 競合した行動を排除
    auto result = remove_if(ally_actions.begin(), ally_actions.end(), [](auto& act){
        return act.apply == 0;
    });
    ally_actions.erase(result, ally_actions.end());
    ally_actions.shrink_to_fit();
    result = remove_if(enemy_actions.begin(), enemy_actions.end(), [](auto& act){
        return act.apply == 0;
    });
    enemy_actions.erase(result, enemy_actions.end());
    enemy_actions.shrink_to_fit();

    // 一旦 move だけ行う
    Move(field, index, ally_actions, actions_buff);
    Move(field, !index, enemy_actions, actions_buff);

    // removeの処理
    Remove(field, index, ally_actions, actions_buff);
    Remove(field, !index, enemy_actions, actions_buff);

    field.actions = actions_buff;

    return true;
}

bool Exec(Field& field, int32 index, Array<Action> ally_actions, Array<Action> enemy_actions)
{
    // 無駄な処理だけど計算量そんなにないので確実に処理するために書いとくよ
    // 一旦Actionはすべて有効であるものとする
    for (auto& act : ally_actions)
    {
        act.apply = 1;
    }
    for (auto& act : enemy_actions)
    {
        act.apply = 1;
    }

    assert(ally_actions.size() == field.teams[index].agents.size());
    assert(enemy_actions.size() == field.teams[!index].agents.size());

    // 「無効」や「競合」そして「有効」な行動を順次格納
    Array<Action> actions_buff;

    // 「無効」な行動をAction配列から排除する
    ExcludeInvalidActions(field, index, ally_actions, actions_buff);
    ExcludeInvalidActions(field, !index, enemy_actions, actions_buff);

    // 指定先がかぶった場合、その行動は競合となる
    map<int32, int32> mp;
    for (auto& act : ally_actions)
    {
        Team team = field.teams[index];
        for (auto i : step(team.agents.size()))
        {
            if (team.agents[i].agentID == act.agentID)
            {
                int32 ty = team.agents[i].y + act.dy;
                int32 tx = team.agents[i].x + act.dx;
                mp[1000*ty + tx]++;
            }
        }
    }
    for (auto& act : enemy_actions)
    {
        Team team = field.teams[!index];
        for (int32 i = 0; i < team.agents.size(); ++i)
        {
            if (team.agents[i].agentID == act.agentID)
            {
                int32 ty = team.agents[i].y + act.dy;
                int32 tx = team.agents[i].x + act.dx;
                mp[1000*ty + tx]++;
            }
        }
    }

    auto conflict = [&](auto& act){ 
        for (const auto& team : field.teams)
        {
            for (const auto& agent : team.agents)
            {
                if (agent.agentID == act.agentID)
                {
                    int32 ty = agent.y + act.dy;
                    int32 tx = agent.x + act.dx;
                    if (mp[1000*ty + tx] >= 2)
                    {
                        act.apply = 0;
                        actions_buff.push_back(act);

                        return true;
                    }
                }
            }
        }
        return false;
    };

    auto it = find_if(ally_actions.begin(), ally_actions.end(), conflict);
    while(it != ally_actions.end())
    {
        int64 i = std::distance(ally_actions.begin(), it);
        ally_actions[i].apply = 0;
        it = find_if(++it, ally_actions.end(), conflict);
    }

    it = find_if(enemy_actions.begin(), enemy_actions.end(), conflict);
    while(it != enemy_actions.end())
    {
        int64 i = std::distance(enemy_actions.begin(), it);
        enemy_actions[i].apply = 0;
        it = find_if(++it, enemy_actions.end(), conflict);
    }

    // 競合した行動を排除
    auto result = remove_if(ally_actions.begin(), ally_actions.end(), [](auto& act){
        return act.apply == 0;
    });
    ally_actions.erase(result, ally_actions.end());
    ally_actions.shrink_to_fit();
    result = remove_if(enemy_actions.begin(), enemy_actions.end(), [](auto& act){
        return act.apply == 0;
    });
    enemy_actions.erase(result, enemy_actions.end());
    enemy_actions.shrink_to_fit();

    // 一旦 move だけ行う
    Move(field, index, ally_actions, actions_buff);
    Move(field, !index, enemy_actions, actions_buff);

    // removeの処理
    Remove(field, index, ally_actions, actions_buff);
    Remove(field, !index, enemy_actions, actions_buff);

    field.actions = actions_buff;

    return true;
}

bool ExcludeInvalidActions(const Field& field, int32 team_index, Array<Action>& actions, Array<Action>& actions_buff)
{
    // 敵のタイルがおかれている場所か
    auto onEnemyTile = [](const Array<Array<int32>>& tiled, int32 enemyTeamID, int32 y, int32 x)
    {
        if (tiled[y][x] == enemyTeamID)
        {
            return true;
        }
        return false;
    };
    // タイルが存在しないか
    auto noTile = [](const Array<Array<int32>>& tiled, int32 y, int32 x)
    {
        if (tiled[y][x] == 0)
        {
            return true;
        }
        return false;
    };

    auto result = remove_if(actions.begin(), actions.end(), [&](auto& act){
        if (act.type == U"move")
        {
            Team team = field.teams[team_index];
            for (auto i : step(team.agents.size()))
            {
                if (team.agents[i].agentID == act.agentID)
                {
                    int32 Yed = team.agents[i].y + act.dy;
                    int32 Xed = team.agents[i].x + act.dx;
                    if (omm::Point(Yed, Xed).isOver(field.height, field.width))
                    {
                        act.apply = -1;
                        actions_buff.push_back(act);
                        return true;
                    }
                    int32 rebirth = (team_index == 0) ? 1 : 0;  // 敵チームのインデックス
                    if (onEnemyTile(field.tiled, field.teams[rebirth].teamID, Yed, Xed))
                    {
                        act.apply = -1;
                        actions_buff.push_back(act);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        else if (act.type == U"remove")
        {
            Team team = field.teams[team_index];
            for (auto i : step(team.agents.size()))
            {
                if (team.agents[i].agentID == act.agentID)
                {
                    int32 Yed = field.teams[team_index].agents[i].y + act.dy;
                    int32 Xed = field.teams[team_index].agents[i].x + act.dx;
                    if (omm::Point(Yed, Xed).isOver(field.height, field.width))
                    {
                        act.apply = -1;
                        actions_buff.push_back(act);
                        return true;
                    }
                    if (noTile(field.tiled, Yed, Xed))
                    {
                        act.apply = -1;
                        actions_buff.push_back(act);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    });
    actions.erase(result, actions.end());
    actions.shrink_to_fit();

    return true;
}

bool Move(Field& field, int32 team_index, Array<Action>& actions, Array<Action>& actions_buff)
{
    for (auto& act : actions)
    {
        if (act.type == U"move")
        {
            Team team = field.teams[team_index];
            for (auto i : step(team.agents.size()))
            {
                if (team.agents[i].agentID == act.agentID)
                {
                    field.teams[team_index].agents[i].y += act.dy;
                    field.teams[team_index].agents[i].x += act.dx;
                    int32 ty = field.teams[team_index].agents[i].y;
                    int32 tx = field.teams[team_index].agents[i].x;
                    field.tiled[ty][tx] = team.teamID;

                    act.apply = 1;
                    actions_buff.push_back(act);
                }
            }
        }
    }
    return true;
}

bool Remove(Field& field, int32 team_index, Array<Action>& actions, Array<Action>& actions_buff)
{
    for (auto& act : actions)
    {
        if (act.type == U"remove")
        {
            Team team = field.teams[team_index];
            for (auto i : step(team.agents.size()))
            {
                if (team.agents[i].agentID == act.agentID)
                {
                    int32 ty = field.teams[team_index].agents[i].y + act.dy;
                    int32 tx = field.teams[team_index].agents[i].x + act.dx;
                    // 敵のエージェントが除去先に存在しないかの判定
                    for (auto& agent : field.teams[!team_index].agents)
                    {
                        if (agent.y == ty && agent.x == tx)
                        {
                            act.apply = 0;
                            actions_buff.push_back(act);
                        }
                    }
                    // †除去†
                    if (act.apply != 0)
                    {
                        act.apply = 1;
                        actions_buff.push_back(act);
                        field.tiled[ty][tx] = 0;
                    }
                }
            }
        }
    }
    
    return true;
}
