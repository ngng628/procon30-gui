# include "Command.h"

Command::Command()
       : to({0,0})
       , a(Act::Stay)
{
}

Command::Command(Act _a, omm::Point _to)
       : a(_a)
       , to(_to)
{
}

Commands::Commands(int32 sz)
{
    cmds.reserve(sz);
    cmds.resize(sz);
}