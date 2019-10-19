# pragma once

struct Action
{
    Action() = default;
    Action(int32 _agentID, String _type, int32 _dy, int32 _dx, int32 _turn = 0, int32 _apply = 1);
    int32 agentID;
    String type;
    int32 dy, dx;
    int32 turn;
    int32 apply;
};

/// <summary>
/// Action‚ÌArray”z—ñ‚ðJsonŒ`Ž®‚Ì•¶Žš—ñ‚É•ÏŠ·‚µ‚Ü‚·
/// </summary>
// String ToJson(const Array<Action>& actions);
