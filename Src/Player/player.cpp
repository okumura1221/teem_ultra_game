#include "player.h"



void Player::Init() {

	LoadDivGraph("Data/Player/player_R.png", 14, 3, 5, 64, 64, playerHandle[0]);
	LoadDivGraph("Data/Player/player_L.png", 14, 3, 5, 64, 64, playerHandle[1]);
	animState = 0;
	animIndex = 0;
	animFlag = 0;
	animFlameCount = 0;
	changeAnimFlame = 7;
	playerNextX = 40;
	playerNextY =400;
	playerSizeX = 64;
	playerSizeY = 64;
	playerSpeed = 5;
	jump = false;
	grav = 15.0;
	jumpPower = 20;
	

}

void Player::Step() {

	if (playerX == playerNextX&&!jump) {
		animFlag = 0;
	}
	if (playerY < playerNextY) {
		animFlag = 2;
	}
	if (playerY > playerNextY) {
		animFlag = 3;
	}
	if (playerY == playerNextY && !jump) {
		animFlag = 0;
	}
		
	//���W������
	playerX = playerNextX;
	playerY = playerNextY;

	//�ړ�����
	if(Input::Keep(KEY_INPUT_A)) {//��
		playerNextX -= playerSpeed;
		animState = L;
		if (animFlag != 2&&animFlag != 3) {
			animFlag = 1;
		}
	}else 
		if (Input::Keep(KEY_INPUT_D)) {//�E
		playerNextX += playerSpeed;
		animState = R;
		if (animFlag != 2 &&animFlag != 3) {
			animFlag = 1;
		}
	}

	//�W�����v����
	if (!jump) {
		jumpPower = 40;
		if (Input::Push(KEY_INPUT_W)) {
			jump = true;
		}
	}
	if (jump) {
		playerNextY -= jumpPower;
		jumpPower -= 1.2;
		if (jumpPower <= 0) {
			jumpPower = 0;
		}
	}
	//�d��
	playerNextY += grav;

}

void Player::Draw() {

	if (animFlag == 0) {
		animIndex = 9;
	}

	if (animFlag == 1) {
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 6) {
				animIndex = 0;
			}
		}
	}

	if (animFlag == 2) {
		animIndex = 7;
	}

	if (animFlag == 3) {
		animIndex = 6;
	}


	DrawGraph(playerX, playerY, playerHandle[animState][animIndex], true);
	
	DrawFormatString(32, 0, GetColor(255, 0, 0), "%d", playerHandle, true);
}


// �i��ł���������`�F�b�N
// �㉺���E�̏��ɂȂ��Ă���
void Player::GetMoveDirection(bool* _dirArray) {
	// �E�����̃`�F�b�N
	if (GetNextPlayerPosX() > GetPlayerPosX()) {
		_dirArray[3] = true;
	}

	// �������̃`�F�b�N
	if (GetNextPlayerPosX() <GetPlayerPosX()) {
		_dirArray[2] = true;
	}
	// �������̃`�F�b�N
	if (GetNextPlayerPosY() > GetPlayerPosY()) {
		_dirArray[1] = true;
	}

	// ������̃`�F�b�N
	if (GetNextPlayerPosY() < GetPlayerPosY()) {
		_dirArray[0] = true;
	}
}