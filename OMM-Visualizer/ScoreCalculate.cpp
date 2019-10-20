# include "ScoreCalculate.h"

bool OverField(const Array<Array<int32>>& tiled, int32 y, int32 x)
{
    if (y < 0 || tiled.size() - 1 < y)
    {
        return true;
    }
    if (x < 0 || tiled[0].size() - 1 < x)
    {
        return true;
    }
    return false;
}

// notSearchedNum
// 未探索とする数字
// 例えば初めての段階では 0 が未探索を示すため notSearchedNum は 0
void areaSearch(Array<Array<int32>>& tiled, int32 y, int32 x, int32 index, int32 notSearchedNum = 0)
{
    int32 dx[4] = { 1, -1, 0,  0 };
    int32 dy[4] = { 0,  0, 1, -1 };
    tiled[y][x] = index;
    for (int32 i = 0; i < 4; ++i)
    {
        if (!OverField(tiled, y + dy[i], x + dx[i]))
        {
            if (tiled[y + dy[i]][x + dx[i]] == notSearchedNum /*&& !(tiled[y+dy[i]][x+dx[i]] < index)*/)
            {
                tiled[y + dy[i]][x + dx[i]] = index;
                areaSearch(tiled, y + dy[i], x + dx[i], index, notSearchedNum);
            }
        }
    }
}

// タイルポイントの計算
int32 TileCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled)
{
    int32 sum = 0;
	for (int32 y : step(points.size()))
    {
        for (int32 x : step(points[0].size()))
        {
            if (tiled[y][x] == true)
            {
                sum += points[y][x];
            }
        }
    }

    return sum;
}

int32 AreaCalculate(const Array<Array<int32>>& points, Array<Array<int32>> tiled)
{
    // 領域ポイントの計算
    // イメージ : 4近傍に水を流す
    int32 index = 2;
	for (int32 y : step(points.size()))
    {
        for (int32 x : step(points[0].size()))
        {
            if (tiled[y][x] == 0)
            {
                areaSearch(tiled, y, x, index);
                index++;
            }
        }
    }

    // 角および辺は囲い判定対象外なので、それを除外する。
	for (int32 y : step(points.size()))
    {
        if (tiled[y][0] != 1 && tiled[y][0] != 0)
        {
            areaSearch(tiled, y, 0, 0, tiled[y][0]);
        }
        if (tiled[y][tiled[0].size() - 1] != 1 && tiled[y][tiled[0].size() - 1] != 0)
        {
            areaSearch(tiled, y, tiled[0].size() - 1, 0, tiled[y][tiled[0].size() - 1]);
        }
    }
	for (int32 x : step(points[0].size()))
    {
        if (tiled[0][x] != 1 && tiled[0][x] != 0)
        {
            areaSearch(tiled, 0, x, 0, tiled[0][x]);
        }
        if (tiled[tiled.size() - 1][x] != 1 && tiled[tiled.size() - 1][x] != 0)
        {
            areaSearch(tiled, tiled.size() - 1, x, 0, tiled[tiled.size() - 1][x]);
        }
    }

    // 囲われているところ = 数字が 1 を超えている(2 以上の)タイル
    int32 sum = 0;
	for (int32 y : step(points.size()))
    {
        for (int32 x : step(points[0].size()))
        {
            if (tiled[y][x] >= 2)
            {
                sum += Abs(points[y][x]);
            }
        }
    }

    return sum;
}

int32 ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled)
{
    return TileCalculate(points, tiled) + AreaCalculate(points, tiled);
}
