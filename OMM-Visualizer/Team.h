# pragma once
# include "Agent.h"

struct Team
{
	Team() = default;
	Team(int32 _teamID, const Array<Agent>& _agents, int32 _tilePoint, int32 _areaPoint);
	int32 teamID;
	Array<Agent> agents;
	int32 tilePoint;
	int32 areaPoint;
};

