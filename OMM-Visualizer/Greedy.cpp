# include "Greedy.h"
# include "ScoreCalculate.h"
# include "Point.h"

using namespace std;

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }

Array<Action> Greedy(const Field& _field,  const Match& match)
{
    Field field = _field;
    Array<Action> actions;

    int32 team_index = field.getIndex(match).first;
    Team team = field.teams[team_index];
    const int32 h = field.height;
    const int32 w = field.width;
    const int32 allyID = team.teamID;
    const int32 enemyID = field.teams[!team_index].teamID;

    for (const auto& agent : team.agents)
    {
        int32 max_score = -114514;
        Action interestingAction = Action(agent.agentID, U"stay", 0, 0);
        omm::Point interestiongPos = { 0, 0 };

        Action unhappyAction = Action(agent.agentID, U"stay", 0, 0);
        omm::Point unhappyPos = { 0, 0 };
        for (auto dy : Range(-1, 1))
        {
            for (auto dx : Range(-1, 1))
            {
                omm::Point p = omm::Point(agent.y, agent.x) + omm::Point(dy, dx);

                if (!p.isOver(h, w))
                {
                    if (field.tiled[p.y][p.x] == enemyID)
                    {
                        field.tiled[p.y][p.x] = 0;
                        int32 score = ScoreCalculate(field.points, field.normalizedTiled(team_index));
                        if (chmax(max_score, score))
                        {
                            interestiongPos = p;
                            interestingAction = Action(agent.agentID, U"remove", dy, dx);
                        }
                        field.tiled[p.y][p.x] = enemyID;
                    }
                    if (field.tiled[p.y][p.x] == allyID)
                    {
                        std::random_device rnd;
                        std::mt19937 mt(rnd());
                        std::uniform_int_distribution<> randdr(-1, 1);
                        array<String, 2> type_str = { U"move", U"remove" };
                        int32 _dy = randdr(mt);
                        int32 _dx = randdr(mt);
                        unhappyAction = Action(agent.agentID, type_str[abs(randdr(mt))], _dy, _dx);
                        unhappyPos = p - omm::Point(dy, dx) + omm::Point(_dy, _dx);

                    }
                    if (field.tiled[p.y][p.x] == 0)
                    {
                        field.tiled[p.y][p.x] = allyID;
                        int32 score = ScoreCalculate(field.points, field.normalizedTiled(team_index));
                        if (chmax(max_score, score))
                        {
                            interestiongPos = p;
                            interestingAction = Action(agent.agentID, U"move", dy, dx);
                        }
                        field.tiled[p.y][p.x] = 0;
                    }
                }
            }
        }
        if (interestingAction.type != U"stay")
        {
            actions.push_back(interestingAction);
            if (interestingAction.type == U"move")
            {
                field.tiled[interestiongPos.y][interestiongPos.x] = allyID;
            }
            else // "remove"
            {
                field.tiled[interestiongPos.y][interestiongPos.x] = 0;
            }
        }
        else //stay
        {
            actions.push_back(unhappyAction);
        }
    }

    return actions;
}

