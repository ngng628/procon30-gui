# pragma once

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
int AreaCalculate(const Array<Array<int32>>& points, Array<Array<int32>> tiled);

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
int ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled);

