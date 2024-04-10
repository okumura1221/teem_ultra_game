#include "player.h"



void Player::Init() {

	playerHandle = LoadGraph("Data/Player/player.png");
	playerX = 40;
	playerY =400;
	playerSizeX = 64;
	playerSizeY = 64;
	playerSpeed = 5;
	jump = false;

}

void Player::Step() {

	
	//�ړ�����
	if(Input::Keep(KEY_INPUT_A)) {
		playerX -= playerSpeed;
	}

	if (Input::Keep(KEY_INPUT_D)) {
		playerX += playerSpeed;
	}

	//�W�����v����
	if (!jump) {
		grav = 0;
		if (Input::Push(KEY_INPUT_W)) {
			jump = true;
		}
	}
	if (jump) {
		playerY -= 20;
		grav += 0.9;
		playerY += grav;
	}

	//�ꎞ�I�ȓ����蔻��
	if (playerY >= 720 - 64) {
		playerY = 720 - 64;
		jump = false;
	}
}

void Player::Draw() {

	DrawGraph(playerX, playerY, playerHandle, true);
	
	DrawFormatString(32, 0, GetColor(255, 0, 0), "%d", playerHandle, true);
}