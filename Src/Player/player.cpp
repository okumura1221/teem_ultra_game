#include "player.h"



void Player::Init() {

	playerHandle = LoadGraph("Data/Player/player.png");
	playerNextX = 40;
	playerNextY =400;
	playerSizeX = 64;
	playerSizeY = 64;
	playerSpeed = 5;
	jump = false;

}

void Player::Step() {

	
	playerX = playerNextX;
	playerY = playerNextY;

	//移動処理
	if(Input::Keep(KEY_INPUT_A)) {
		playerNextX -= playerSpeed;
	}

	if (Input::Keep(KEY_INPUT_D)) {
		playerNextX += playerSpeed;
	}

	//ジャンプ処理
	if (!jump) {
		grav = 0;
		if (Input::Push(KEY_INPUT_W)) {
			jump = true;
		}
	}
	if (jump) {
		playerNextY -= 20;
		grav += 0.9;
		playerNextY += grav;
	}

	//一時的な当たり判定
	if (playerNextY >= 720 - 64) {
		playerNextY = 720 - 64;
		jump = false;
	}

}

void Player::Draw() {

	DrawGraph(playerX, playerY, playerHandle, true);
	
	DrawFormatString(32, 0, GetColor(255, 0, 0), "%d", playerHandle, true);
}