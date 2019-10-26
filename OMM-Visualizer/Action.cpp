# include "Action.h"

Action::Action(int32 _agentID, String _type, int32 _dy, int32 _dx, int32 _turn, int32 _apply)
    : agentID(_agentID)
    , type(_type)
    , dy(_dy), dx(_dx)
    , turn(_turn)
    , apply(_apply)
{}

String ToJson(const Array<Action>& actions)
{
    picojson::object actionsObj;
    picojson::array datalist;

    for (const auto& action : actions)
    {
        picojson::object data;
        data.insert(std::make_pair("agentID", picojson::value((double)action.agentID)));
        data.insert(std::make_pair("dy", picojson::value((double)action.dy)));
        data.insert(std::make_pair("dx", picojson::value((double)action.dx)));
        data.insert(std::make_pair("type", picojson::value(action.type.narrow())));
        datalist.push_back(picojson::value(data));
    }

    actionsObj.insert(std::make_pair("actions", picojson::value(datalist)));

    return Unicode::Widen(picojson::value(actionsObj).serialize());
}
