#include "player.h"



void Player::Init() {

	LoadDivGraph("Data/Player/playerRun_R.png", 6, 3, 2, 64, 64, playerHandle[0]);
	LoadDivGraph("Data/Player/playerRun_L.png", 6, 3, 2, 64, 64, playerHandle[1]);
	animState = 0;
	animIndex = 0;
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

	//���W������
	playerX = playerNextX;
	playerY = playerNextY;

	//�ړ�����
	if(Input::Keep(KEY_INPUT_A)) {//��
		playerNextX -= playerSpeed;
		animState = WALK_L;
		animFlameCount++;
	}

	if (Input::Keep(KEY_INPUT_D)) {//�E
		playerNextX += playerSpeed;
		animState = WALK_R;
		animFlameCount++;
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



	if (animFlameCount >= changeAnimFlame) {
		animFlameCount = 0;
		animIndex++;
		if (animIndex == 6) {
			animIndex = 0;
		}
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