# include "Match.h"

Match::Match(int32 _id, int32 _intervalMillis, const String& _matchTo, int32 _teamID, int32 _turnMillis, int32 _turns)
    : id(_id)
    , intervalMillis(_intervalMillis)
    , matchTo(_matchTo)
    , teamID(_teamID)
    , turnMillis(_turnMillis)
    , turns(_turns)
{}

String ToJson(const Array<Match>& matches)
{
	picojson::array matchList;

	for (const auto& match : matches)
	{
		picojson::object data;
		data.insert(std::make_pair("id", picojson::value((double)match.id)));
		data.insert(std::make_pair("intervalMillis", picojson::value((double)match.intervalMillis)));
		data.insert(std::make_pair("matchTo", picojson::value(match.matchTo.narrow())));
		data.insert(std::make_pair("teamID", picojson::value((double)match.teamID)));
		data.insert(std::make_pair("turnMillis", picojson::value((double)match.turnMillis)));
		data.insert(std::make_pair("turns", picojson::value((double)match.turns)));
		matchList.push_back(picojson::value(data));
	}

	return Unicode::Widen(picojson::value(matchList).serialize());
}
