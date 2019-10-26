# pragma once
# include <string>

enum class Act:int32
{
    Stay,
    Move,
    Remove,
};

String ActToString(const Act a);