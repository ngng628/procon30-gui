# pragma once
# include "Field.h"

bool Exec(Field& field, Array<Action> ally_actions, Array<Action> enemy_actions);
bool Exec(Field& field, int32 ally_index, Array<Action> ally_actions, Array<Action> enemy_actions);
bool ExcludeInvalidActions(const Field&, int32, Array<Action>&, Array<Action>& actions_buff);
bool Move(Field& field, int32 team_index, Array<Action>& actions, Array<Action>& actions_buff);
bool Remove(Field& field, int32 team_index, Array<Action>& actions, Array<Action>& actions_buff);

