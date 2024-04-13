#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"
#include "../../Collision/Collision.h"

                    
Player* player;
Map* CMap;
MAPCollision mapcollision;

int startCount;

int winHandle[2];
int finishCount;

//������
void InitPlay() {
	
	//�X�e�[�W�̏����Ɏg��
	startCount = 0;//�ړ��\�܂ł̎���
	winHandle[0] = LoadGraph("Data/1p_win.png");//�����摜
	winHandle[1] = LoadGraph("Data/2p_win.png");//�����摜
	finishCount = 0;//������������̎��R����

	player = new Player[2];
	CMap =new Map;

	CMap->Init();

	player[0].Init(1);
	player[1].Init(2);

	scene = SCENE_LOOP_PLAY;
}



//�ʏ폈��
void StepPlay() {

	//�v���C���[����
	player[0].Step();
	player[1].Step();

		//�v���C���[�P�̒e�ƃv���C���[�Q�̓����蔻��
	for (int index = 0;index < 10;index++) {

		if (!player[0].GetBulletIsUse(index)) { continue; }
		if (IsHitRect(player[1].GetPlayerPosX(), player[1].GetPlayerPosY(), player[1].GetPlayerSizeX(), player[1].GetPlayerSizeY(),
			player[0].GetBulletPosX(index), player[0].GetBulletPosY(index), player[0].GetBulletSizeX(), player[0].GetBulletSizeY())) {
			player[1].InDamage(player[0].GetBulletDamage(index));//������������_���[�W���󂯂�
			player[0].SetBulletIsUse(index);//�e������
		}
	}

		//�v���C���[2�̒e�ƃv���C���[1�̓����蔻��
	for (int index = 0;index < 10;index++) {

		if (!player[1].GetBulletIsUse(index)) { continue; }
		if (IsHitRect(player[0].GetPlayerPosX(), player[0].GetPlayerPosY(), player[0].GetPlayerSizeX(), player[0].GetPlayerSizeY(),
			player[1].GetBulletPosX(index), player[1].GetBulletPosY(index), player[1].GetBulletSizeX(), player[1].GetBulletSizeY())) {
			player[0].InDamage(player[1].GetBulletDamage(index));//������������_���[�W���󂯂�
			player[1].SetBulletIsUse(index);//�e������
		}
	}

	//�}�b�v�Ƃ̓����蔻��
	mapcollision.MapCollision();
	
	//�����摜����
	if (player[0].GetPlayerHP() <= 0 || player[1].GetPlayerHP() <= 0) {
		finishCount++;
		if (finishCount >= 600) {
			scene = SCENE_FIN_PLAY;
		}
	}

}



//�`�揈��
void DrawPlay() {

	int Color;

	if (startCount < 200) {
		startCount++;
		Color = GetColor(0, 0, 0);
	}
	else {
		Color = GetColor(250, 250, 250);
	}
	DrawCircle(600, 300, 1200, Color, true);


	CMap->Draw();
	player[0].Draw();
	player[1].Draw();
	
	//�����摜�`��
	if (player[0].GetPlayerHP() <= 0) {
		DrawGraph(0, 0, winHandle[1],true);
	}else
		if(player[1].GetPlayerHP() <= 0) {
		DrawGraph(0, 0, winHandle[0], true);
	}

}



//�j������
void FinPlay() {

	delete []player;
	player = nullptr;
	delete CMap;
	CMap = nullptr;
	DeleteGraph(winHandle[0]);
	DeleteGraph(winHandle[1]);
	scene = SCENE_INIT_TITLE;

}




// �}�b�v�̓����蔻��
void MAPCollision::MapCollision() {


	for (int index = 0;index < 2;index++) {
		// Y�����̂ݓ����蔻����`�F�b�N����
		for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
		{
			for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
			{
				// �u���b�N�ȊO�͏������Ȃ�
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
					continue;

				// �ǂ̕����ɐi��ł������`�F�b�N
				bool dirArray[4] = { false,false,false,false };
				player[index].GetMoveDirection(dirArray);

				// ��`�̓����蔻��p�̃f�[�^������
				// �v���C���[�̏��
				int Ax = player[index].GetPlayerPosX();
				int Ay = player[index].GetPlayerPosY();
				int Aw = player[index].GetPlayerSizeX();
				int Ah = player[index].GetPlayerSizeY();

				// �I�u�W�F�N�g�̏��
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// ��Y�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
				Ay = player[index].GetNextPlayerPosY();
				Ax = player[index].GetPlayerPosX();

				// �������Ă��邩�`�F�b�N
				if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// ������̏C��
					if (dirArray[0]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = By + Bh - Ay;
						player[index].SetPlayerNextPosY(Ay + overlap);
					}

					// �������̏C��
					if (dirArray[1]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = Ay + Ah - By;
						player[index].SetPlayerNextPosY(Ay - overlap);
						
						player[index].SetJump();    //�����Ƃ��؂�ւ�
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
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
					continue;

				// �ǂ̕����ɐi��ł������`�F�b�N
				// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B
				bool dirArray[4] = { false,false,false,false };
				player[index].GetMoveDirection(dirArray);

				// ��`�̓����蔻��p�̃f�[�^������
				// �v���C���[�̏��
				int Ax = player[index].GetPlayerPosX();
				int Ay = player[index].GetPlayerPosY();
				int Aw = player[index].GetPlayerSizeX();
				int Ah = player[index].GetPlayerSizeY();

				// �I�u�W�F�N�g�̏��
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// ��`�̓����蔻��p�̃f�[�^������
				// ��X�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
				Ay = player[index].GetNextPlayerPosY();
				Ax = player[index].GetNextPlayerPosX();

				// �������Ă��邩�`�F�b�N
				if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// �������̏C��
					if (dirArray[2]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = Bx + Bw - Ax;
						player[index].SetPlayerNextPosX(Ax + overlap);
					}

					// �E�����̏C��
					if (dirArray[3]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = Ax + Aw - Bx;
						player[index].SetPlayerNextPosX(Ax - overlap);
					}
				}
			}
		}
	}
}