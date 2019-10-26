# include "beamsearch2.h"

Commands beamSearch2(const FFS field, const int timelimit_ms)
{
    std::chrono::system_clock::time_point start;
    start = std::chrono::system_clock::now();
    const int32 margin_ms = 500; //猶予時間
    const int32 looseLimit_ms = timelimit_ms - margin_ms; //猶予のある探索可能時間
    
    const int32 depth = std::min(10,field.maxturn-field.turn+1); //depth手先まで見る(相手は考えない)

    Commands Cs(field.teamnum);
    // max8人全員同時に動かすと遷移先が爆発するので一人ずつ考える
    // 最初の人の最適解を見つける->そう動いた時の盤面をもとに次の人の最適解を見つける
    const int32 oneLimit = looseLimit_ms / field.teamnum; // 一人当たりの時間
    int32 time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
    State2 tmpState(field);
    Array<Array<Array<omm::Point>>> conflictAllyPos
        (depth+2, Array<Array<omm::Point>>(field.teamnum,Array<omm::Point>(2, {-1,-1}))); //危ない初期化
    Array<std::pair<int32, omm::Point>> deletedTiles;
    for (int32 i=0;i<field.teamnum;i++)
    {
        conflictAllyPos[0][i][0] = (field.Allies[i].pos);
    }

    for (int32 i=0;i<field.teamnum;i++) //i人目の手
    {   
        Array<std::priority_queue<State2>> States(depth+2);
        States[0].push(tmpState);
        Command c;
        int32 whilecounter = 0;
        while(time < oneLimit*(i+1))
        {
            for(int32 d=0;d<depth;d++)
            {
                if(States[d].empty()) continue;
                State2 now = States[d].top(); States[d].pop();
                //9通りの方向を与える(行動は一意に定まるので向こうで考える)
                States[d+1].push(transition(now, i, {-1,-1}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, {-1, 0}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, {-1, 1}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, { 0,-1}, conflictAllyPos, deletedTiles, d));
                // States[d+1].push(transition(now, i, { 0, 0}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, { 0, 1}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, { 1,-1}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, { 1, 0}, conflictAllyPos, deletedTiles, d));
                States[d+1].push(transition(now, i, { 1, 1}, conflictAllyPos, deletedTiles, d));
            }
            time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
            whilecounter++;
        }
        tmpState = States[depth].top(); //状態遷移
        // 味方が使うので干渉させたくないマスを記録する
        for(int32 d = 0; d < depth; d++)
        {
            if(tmpState.via[d].first.a == Act::Move)
            {
                conflictAllyPos[d][i][0] = {-1, -1}; //危ない
                conflictAllyPos[d][i][1] = tmpState.via[d].second.second;
            }
            else
            {
                conflictAllyPos[d][i][0] = tmpState.via[d].second.first;
                conflictAllyPos[d][i][1] = tmpState.via[d].second.second;
            }
        }
        c = tmpState.via.at(0).first;
    
        //戻り値
        Cs.cmds[i] = c;
    }
    return Cs;
}

Array<Action> solve_beam2(Array<Action>& actions, const Field& field, const Match& match)
{
	Array<Action> acts;
	int32 actsSize = (int32)field.teams[0].agents.size();
	int32 team_index;

	if(field.teams[0].teamID == match.teamID) team_index = 0;
	else team_index = 1;
	Commands commands = beamSearch2(toFFS(field, match.turns, team_index, 
						  field.teams[team_index].teamID, field.teams[!team_index].teamID),
						  match.turnMillis);
	
	assert(field.points.size() == field.height && field.points[0].size() == field.width);
	
	for(int32 i = 0; i < actsSize; i++)
	{
		acts.emplace_back(field.teams[team_index].agents[i].agentID, ActToString(commands.cmds[i].a),
						  commands.cmds[i].to.y, commands.cmds[i].to.x, 0, 1);
	}
	
	actions = acts;

    return acts;
}
