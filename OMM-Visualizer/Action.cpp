# include "Action.h"

Action::Action(int32 _agentID, String _type, int32 _dy, int32 _dx, int32 _turn, int32 _apply)
    : agentID(_agentID)
    , type(_type)
    , dy(_dy), dx(_dx)
    , turn(_turn)
    , apply(_apply)
{}
