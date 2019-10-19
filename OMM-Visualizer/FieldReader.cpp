# include "FieldReader.h"
# include <fstream>

FieldReader::FieldReader(const FilePath& path)
{
	std::ifstream ifs;
	ifs.open(path.narrow());
	assert(ifs);
	ifs >> init_value;
}

bool FieldReader::copyTo(Field& field)
{
    picojson::object& obj = init_value.get<picojson::object>();

    int32 height = (int32)obj["height"].get<double>();
    int32 width = (int32)obj["width"].get<double>();

    Array<Array<int32>> points(height, Array<int32>(width, 0));
    int32 y, x;
    y = 0;
    for (auto& ps : obj["points"].get<picojson::array>())
    {
        x = 0;
        for (auto& p : ps.get<picojson::array>())
        {
            points[y][x] = (int32)p.get<double>();
            ++x;
        }
        ++y;
    }

    int32 startedAtUnixTime = (int32)obj["startedAtUnixTime"].get<double>();
    int32 turn = (int32)obj["turn"].get<double>();

    Array<Array<int32>> tiled(height, Array<int32>(width, 0));
    y = 0;
    for (auto& tiles : obj["tiled"].get<picojson::array>())
    {
        x = 0;
        for (auto& tile : tiles.get<picojson::array>())
        {
            tiled[y][x] = (int32)tile.get<double>();
            ++x;
        }
        ++y;
    }

    Array<Team> teams;
    for (auto& team : obj["teams"].get<picojson::array>())
    {
        picojson::object teamObj = team.get<picojson::object>();
        int32 teamID = (int32)teamObj["teamID"].get<double>();
        Array<Agent> agents;
        for (auto& agent : teamObj["agents"].get<picojson::array>())
        {
            picojson::object agentObj = agent.get<picojson::object>();
            int32 agentID = (int32)agentObj["agentID"].get<double>();
            int32 ay = (int32)agentObj["y"].get<double>() - 1;
            int32 ax = (int32)agentObj["x"].get<double>() - 1;
            agents.push_back(Agent(agentID, ay, ax));
        }
        int32 tilePoint = (int32)teamObj["tilePoint"].get<double>();
        int32 areaPoint = (int32)teamObj["areaPoint"].get<double>();
        teams.push_back(Team(teamID, agents, tilePoint, areaPoint));
    }

    Array<Action> actions;
    for (auto& action : obj["actions"].get<picojson::array>())
    {
        picojson::object actionObj = action.get<picojson::object>();
        int32 agentID = (int32)actionObj["agentID"].get<double>();
		String type = Unicode::Widen(actionObj["type"].get<std::string>());
        int32 dy = (int32)actionObj["dy"].get<double>();
        int32 dx = (int32)actionObj["dx"].get<double>();
        int32 aturn = (int32)actionObj["turn"].get<double>();
        int32 apply = (int32)actionObj["apply"].get<double>();
        actions.push_back(Action(agentID, type, dy, dx, aturn, apply));
    }

    field = m_field = Field(height, width, points, startedAtUnixTime, turn, tiled, teams, actions);

    return true;
}
