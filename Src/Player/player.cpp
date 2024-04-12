#include "player.h"



void Player::Init(int player_no) {

	LoadDivGraph("Data/Player/player_R.png", 14, 3, 5, 64, 64, playerHandle[0]);
	LoadDivGraph("Data/Player/player_L.png", 14, 3, 5, 64, 64, playerHandle[1]);
	
	animIndex = 0;
	animFlag = 0;
	animFlameCount = 0;
	

	//１Pと２Pの分け
	if (player_no == 1) {
		animState = R;
		
		button[0]= KEY_INPUT_A;
		button[1]=KEY_INPUT_D;
		button[2]= KEY_INPUT_W;
		button[3]= KEY_INPUT_SPACE;
		playerNextX = 50;
		playerNextY = 400;
	}
	else {
		animState = L;
		button[0] = KEY_INPUT_NUMPAD4;
		button[1] = KEY_INPUT_NUMPAD6;
		button[2] = KEY_INPUT_NUMPAD8;
		button[3] = KEY_INPUT_NUMPADENTER;
		playerNextX =1150;
		playerNextY = 400;
	}
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
		
	//座標を決定
	playerX = playerNextX;
	playerY = playerNextY;

	//移動処理
	if(Input::Keep(button[0])) {//左
		playerNextX -= playerSpeed;
		animState = L;
		if (animFlag != 2&&animFlag != 3) {
			animFlag = 1;
		}
	}else 
		if (Input::Keep(button[1])) {//右
		playerNextX += playerSpeed;
		animState = R;
		if (animFlag != 2 && animFlag != 3) {
			animFlag = 1;
		}
	}

	//ジャンプ処理
	if (!jump) {
		jumpPower = 40;
		if (Input::Push(button[2])) {
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
	//重力
	playerNextY += grav;

}

void Player::Draw() {

	if (animFlag == 0) {
		animIndex = 9;
	}

	if (animFlag == 1) {
		changeAnimFlame = 7;
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
	
}


// 進んでいる方向をチェック
// 上下左右の順になっている
void Player::GetMoveDirection(bool* _dirArray) {
	// 右方向のチェック
	if (GetNextPlayerPosX() > GetPlayerPosX()) {
		_dirArray[3] = true;
	}

	// 左方向のチェック
	if (GetNextPlayerPosX() <GetPlayerPosX()) {
		_dirArray[2] = true;
	}
	// 下方向のチェック
	if (GetNextPlayerPosY() > GetPlayerPosY()) {
		_dirArray[1] = true;
	}

	// 上方向のチェック
	if (GetNextPlayerPosY() < GetPlayerPosY()) {
		_dirArray[0] = true;
	}
}