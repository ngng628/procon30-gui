# pragma once
# include "FieldForSearch.h"
# include <vector>

/// <summary>
/// 盤面情報からタイルポイントを計算します
/// </summary>
/// <param name="points">
/// 盤面の得点情報
/// </param>
/// <param name="tiles">
/// 塗られているタイルの場所
/// 塗られている   -> true
/// 塗られていない -> false
/// </param>
/// <returns>
/// タイルポイント
/// </returns>
int32 TileCalculate(const Array<Array<int>>& points, const Array<Array<int>>& tiled);

/// <summary>
/// 盤面情報から領域ポイントを計算します
/// </summary>
/// <param name="points">
/// 盤面の得点情報
/// </param>
/// <param name="tiles">
/// 塗られているタイルの場所
/// 塗られている   -> true
/// 塗られていない -> false
/// </param>
/// <returns>
/// 領域ポイント
/// </returns>
int32 AreaCalculate(const Array<Array<int32>>& points, Array<Array<int32>> tiled);

/// <summary>
/// 盤面情報から得点を計算します
/// </summary>
/// <param name="points">
/// 盤面の得点情報
/// </param>
/// <param name="tiles">
/// 塗られているタイルの場所
/// 塗られている   -> true
/// 塗られていない -> false
/// </param>
/// <returns>
/// 合計得点
/// </returns>
int32 ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled);

int32 ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled,
                          int32 PointWeight, int32 AreaWeight);

/// <summary>
/// 盤面情報から敵との得点差を計算します(味方-敵)
/// </summary>
/// <param name="field">
/// 盤面情報
/// <\param>
/// <returns>
/// 得点差
/// 味方が優勢 -> 正
/// 敵が優勢   -> 負
/// </returns>
int32 LeadScoreCalculate(const FFS& field);
int32 LeadScoreCalculate(const FFS& field,
                       int32 allyPointWeight, int32 allyAreaWeight,
                       int32 enemyPointWeight, int32 enemyAreaWeight);

void setupTiles(const FFS& field,
                Array<Array<int32>>& allyTiles, Array<Array<int32>>& enemyTiles);
