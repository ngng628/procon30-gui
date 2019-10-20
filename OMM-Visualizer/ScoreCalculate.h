# pragma once

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
int AreaCalculate(const Array<Array<int32>>& points, Array<Array<int32>> tiled);

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
int ScoreCalculate(const Array<Array<int32>>& points, const Array<Array<int32>>& tiled);

