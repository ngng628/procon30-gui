# include "Match.h"

Match::Match(int32 _id, int32 _intervalMillis, const String& _matchTo, int32 _teamID, int32 _turnMillis, int32 _turns)
    : id(_id)
    , intervalMillis(_intervalMillis)
    , matchTo(_matchTo)
    , teamID(_teamID)
    , turnMillis(_turnMillis)
    , turns(_turns)
{}

