#include "map.h"
#include "DxLib.h"
#include "../Player/player.h"
#include "../Collision/Collision.h"
//�}�b�v����

// ���������X�g��const�̃����o�ϐ���������
//�X�e�[�W�\��
Map::Map() :m_MapData{
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} }
{
	mapHundle1 = -1;
	mapHundle2 = -1;
	mapHundle3 = -1;
}

Map::~Map() {}

void Map::Init() {
	// �摜�̓ǂݍ���
	mapHundle1 = LoadGraph("Data/Maptail/���i�S�j.png");
	mapHundle2 = LoadGraph("Data/Maptail/����.png");
	mapHundle3 = LoadGraph("Data/Maptail/���i�S�Áj.png");
}



void Map::Draw() {

	//���߂�A������PC���ƌ����炢�̂ňꎞ�I�ɔ����w�i�����B��ŏ����Ă�����
	DrawBox(0, 0, 1280, 720, GetColor(200, 200, 200), true);
	//-------

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// �u���b�N��`��
			if (m_MapData[y][x] == 1) {
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHundle1, true);
			}
		}
	}
}

/*// �}�b�v�̓����蔻��
void MAPCollision::MapCollision() {
	// Y�����̂ݓ����蔻����`�F�b�N����
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// �u���b�N�ȊO�͏������Ȃ�
			if (CMap.m_MapData[mapIndexY][mapIndexX] == 0)
				continue;

			// �ǂ̕����ɐi��ł������`�F�b�N
			bool dirArray[4] = { false,false,false,false };
			playerInfo.GetMoveDirection(dirArray);

			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = playerX;
			int Ay = playerY;
			int Aw = playerSizeX;
			int Ah = playerSizeY;

			// �I�u�W�F�N�g�̏��
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ��Y�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
			Ay = playerInfo.GetNextPosY();
			Ax = playerInfo.GetPosX();

			// �������Ă��邩�`�F�b�N
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// ������̏C��
				if (dirArray[0]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = By + Bh - Ay;
					playerInfo.SetNextPosY(Ay + overlap);
				}

				// �������̏C��
				if (dirArray[1]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = Ay + Ah - By;
					playerInfo.SetNextPosY(Ay - overlap);
					playerInfo.Yspeed = 0.0f;    //�߂�
					playerInfo.isFly = false;    //�����Ƃ��؂�ւ�
				}
			}
		}
	}
	// X�����̂ݓ����蔻����`�F�b�N����
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// �u���b�N�ȊO�͏������Ȃ�
			if (CMap.m_MapData[mapIndexY][mapIndexX] == 0)
				continue;

			// �ǂ̕����ɐi��ł������`�F�b�N
			// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B
			bool dirArray[4] = { false,false,false,false };
			playerInfo.GetMoveDirection(dirArray);

			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = playerX;
			int Ay = playerY;
			int Aw = playerSizeX;
			int Ah = playerSizeY;

			// �I�u�W�F�N�g�̏��
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ��`�̓����蔻��p�̃f�[�^������
			// ��X�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
			Ay = playerInfo.GetNextPosY();
			Ax = playerInfo.GetNextPosX();

			// �������Ă��邩�`�F�b�N
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// �������̏C��
				if (dirArray[2]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = Bx + Bw - Ax;
					playerInfo.SetNextPosX(Ax + overlap);
				}

				// �E�����̏C��
				if (dirArray[3]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = Ax + Aw - Bx;
					playerInfo.SetNextPosX(Ax - overlap);
				}
			}
		}
	}
}

// 2�̍��W�����d�Ȃ��Ă���ʂ��擾
int MAPCollision::GetOverlap(int posA, int posB) {
	int ret = posA - posB;
	return abs(ret);
}*/