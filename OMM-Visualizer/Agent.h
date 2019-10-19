# pragma once

struct Agent
{
    Agent() = default;
    Agent(int32 _agentID, int32 _y, int32 _x);

    int32 agentID;
    int32 y, x;
};

