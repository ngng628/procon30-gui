# include "Team.h"

Team::Team(int32 _teamID, const Array<Agent>& _agents, int32 _tilePoint, int32 _areaPoint)
    : teamID(_teamID)
    , agents(_agents)
    , tilePoint(_tilePoint)
    , areaPoint(_areaPoint)
{}
