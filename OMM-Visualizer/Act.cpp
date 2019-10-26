# include "Act.h"

String ActToString(const Act a)
{
    if(a == Act::Move)
    {
        return U"move";
    }
    else if(a == Act::Remove)
    {
        return U"remove";
    }
    else
    {
        return U"stay";
    }
    
}