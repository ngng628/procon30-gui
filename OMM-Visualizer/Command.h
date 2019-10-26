# pragma once
# include <vector>
# include "Point.h"
# include "Act.h"

struct Command
{
    Act a;
    omm::Point to;
    Command();
    Command(Act, omm::Point);
};

struct Commands
{
    std::vector<Command> cmds;
	Commands() = default;
    Commands(int32);
};