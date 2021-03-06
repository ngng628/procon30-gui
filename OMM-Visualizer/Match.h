# pragma once

struct Match
{
    Match() = default;
    Match(int32 _id, int32 _intervalMillis, const String& _matchTo, int32 _teamID, int32 _turnMillis, int32 _turns);

    int32 id;
    int32 intervalMillis;
    String matchTo;
    int32 teamID;
    int32 turnMillis;
    int32 turns;
};

/// <summary>
/// MatchをJson形式の文字列に変換します
/// </summary>
String ToJson(const Array<Match>& matches);
