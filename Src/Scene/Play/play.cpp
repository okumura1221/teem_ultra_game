#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"
#include "../../Collision/Collision.h"

Map CMap;                     
Player player;
MAPCollision mapcollision;

//������
void InitPlay() {
	
	CMap.Init();

	player.Init();

	scene = SCENE_LOOP_PLAY;
}



//�ʏ폈��
void StepPlay() {
	mapcollision.MapCollision();

	player.Step();
}



//�`�揈��
void DrawPlay() {

	

	CMap.Draw();
	player.Draw();
	
}



//�j������
void FinPlay() {




}



// �}�b�v�̓����蔻��
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
			player.GetMoveDirection(dirArray);

			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = player.GetPlayerPosX();
			int Ay = player.GetPlayerPosY();
			int Aw = player.GetPlayerSizeX();
			int Ah = player.GetPlayerSizeY();

			// �I�u�W�F�N�g�̏��
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ��Y�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
			Ay = player.GetNextPlayerPosY();
			Ax = player.GetPlayerPosX();

			// �������Ă��邩�`�F�b�N
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// ������̏C��
				if (dirArray[0]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = By + Bh - Ay;
					player.SetPlayerNextPosY(Ay + overlap);
				}

				// �������̏C��
				if (dirArray[1]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = Ay + Ah - By;
					player.SetPlayerNextPosY(Ay - overlap);
					//playerInfo.Yspeed = 0.0f;    //�߂�
					player.SetJump();    //�����Ƃ��؂�ւ�
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
			player.GetMoveDirection(dirArray);

			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = player.GetPlayerPosX();
			int Ay = player.GetPlayerPosY();
			int Aw = player.GetPlayerSizeX();
			int Ah = player.GetPlayerSizeY();

			// �I�u�W�F�N�g�̏��
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ��`�̓����蔻��p�̃f�[�^������
			// ��X�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
			Ay = player.GetNextPlayerPosY();
			Ax = player.GetNextPlayerPosX();

			// �������Ă��邩�`�F�b�N
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// �������̏C��
				if (dirArray[2]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = Bx + Bw - Ax;
					player.SetPlayerNextPosX(Ax + overlap);
				}

				// �E�����̏C��
				if (dirArray[3]) {
					// �߂荞�ݗʂ��v�Z����
					int overlap = Ax + Aw - Bx;
					player.SetPlayerNextPosX(Ax - overlap);
				}
			}
		}
	}
}