# pragma once
# include <vector>
# include <utility>
# include "FieldForSearch.h"
# include "Command.h"
# include "Point.h"
# include "ScoreCalculate.h"

struct State2
{
    FFS field;
    int32 score;
    Array<std::pair<Command, std::pair<omm::Point, omm::Point>>> via;
    bool operator<(const State2& another) const
    {
        return score < another.score;
    }
    State2();
    State2(FFS);
    void calcScore();
};


/// <summary>
/// ある時点から特定ターン後に味方一人が行動した後の状態を返します
/// </summary>
/// <param name="state">
/// 元の状態
/// </param>
/// <param name="id">
/// 行動するPlayerのインデックス
/// </param>
/// <param name="dir">
/// 行動対象の方向
/// </param>
/// <param name="conflictAllyPos">
/// 味方と行動対象が競合する座標の集合
/// </param>
/// <param name="d">
/// 基点からのターン数競合を参照するターン
/// </param>
/// <returns>
/// 行動した次の状態
/// </returns>
State2 transition(const State2& state, const int32 id, const omm::Point dir,
                  const Array<Array<Array<omm::Point>>>& conflictAllyPos,
                  Array<std::pair<int32, omm::Point>>& deletedTiles,
                  const int32 d);