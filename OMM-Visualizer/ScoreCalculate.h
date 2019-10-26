# pragma once
# include "FieldForSearch.h"
# include <vector>

/// <summary>
/// �Ֆʏ�񂩂�^�C���|�C���g���v�Z���܂�
/// </summary>
/// <param name="points">
/// �Ֆʂ̓��_���
/// </param>
/// <param name="tiles">
/// �h���Ă���^�C���̏ꏊ
/// �h���Ă���   -> true
/// �h���Ă��Ȃ� -> false
/// </param>
/// <returns>
/// �^�C���|�C���g
/// </returns>
int32 TileCalculate(const Array<Array<int>>& points, const Array<Array<int>>& tiled);

/// <summary>
/// �Ֆʏ�񂩂�̈�|�C���g���v�Z���܂�
/// </summary>
/// <param name="points">
/// �Ֆʂ̓��_���
/// </param>
/// <param name="tiles">
/// �h���Ă���^�C���̏ꏊ
/// �h���Ă���   -> true
/// �h���Ă��Ȃ� -> false
/// </param>
/// <returns>
/// �̈�|�C���g
/// </returns>
int32 AreaCalculate(const Array<Array<int32>>& points, Array<Array<int32>> tiled);

/// <summary>
/// �Ֆʏ�񂩂瓾�_���v�Z���܂�
/// </summary>
/// <param name="points">
/// �Ֆʂ̓��_���
/// </param>
/// <param name="tiles">
/// �h���Ă���^�C���̏ꏊ
/// �h���Ă���   -> true
/// �h���Ă��Ȃ� -> false
/// </param>
/// <returns>
/// ���v���_
/// </returns>
int32 ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled);

int32 ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled,
                          int32 PointWeight, int32 AreaWeight);

/// <summary>
/// �Ֆʏ�񂩂�G�Ƃ̓��_�����v�Z���܂�(����-�G)
/// </summary>
/// <param name="field">
/// �Ֆʏ��
/// <\param>
/// <returns>
/// ���_��
/// �������D�� -> ��
/// �G���D��   -> ��
/// </returns>
int32 LeadScoreCalculate(const FFS& field);
int32 LeadScoreCalculate(const FFS& field,
                       int32 allyPointWeight, int32 allyAreaWeight,
                       int32 enemyPointWeight, int32 enemyAreaWeight);

void setupTiles(const FFS& field,
                Array<Array<int32>>& allyTiles, Array<Array<int32>>& enemyTiles);
