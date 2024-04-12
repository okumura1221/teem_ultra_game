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
		hpHandle = LoadGraph("Data/Player/hp.png");
		for (int index = 0;index < 10;index++) {
			bulletHandle[0][index] = LoadGraph("Data/Player/attack_R.png");
			bulletHandle[1][index] = LoadGraph("Data/Player/attack_L.png");
		}
		button[0]= KEY_INPUT_A;
		button[1]=KEY_INPUT_D;
		button[2]= KEY_INPUT_W;
		button[3]= KEY_INPUT_SPACE;
		playerNextX = 50;
		playerNextY = 400;
	}
	else {
		animState = L;
		hpHandle = LoadGraph("Data/Player/hp2.png");
		for (int index = 0;index < 10;index++) {
			bulletHandle[0][index] = LoadGraph("Data/Player/attack2_R.png");
			bulletHandle[1][index] = LoadGraph("Data/Player/attack2_L.png");
		}
		button[0] = KEY_INPUT_NUMPAD4;
		button[1] = KEY_INPUT_NUMPAD6;
		button[2] = KEY_INPUT_NUMPAD8;
		button[3] = KEY_INPUT_NUMPADENTER;
		playerNextX =1150;
		playerNextY = 400;
	}

	hp = 100;
	playerSizeX = 64;
	playerSizeY = 64;
	playerSpeed = 5;
	jump = false;
	grav = 15.0;
	jumpPower = 20;
	

	for (int index = 0;index < 10;index++) {
		bulletX[index] = 0;
		bulletY[index] = 0;
		isUse[index] = false;
	}
	bulletinterval = 20;
	bulletintervalCount = 20;
	bulletSizeX = 80;
	bulletSizeY = 40;
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
	if (bulletintervalCount < 10) {
		animFlag = 4;
		if (!jump) {
			playerNextX = playerX;
		}
	}

		
	//座標を決定
	playerX = playerNextX;
	playerY = playerNextY;

	//移動処理
		if (Input::Keep(button[0])) {//左
			playerNextX -= playerSpeed;
			animState = L;
			if (animFlag == 1 || animFlag == 0) {
				animFlag = 1;
			}
		}
		else
			if (Input::Keep(button[1])) {//右
				playerNextX += playerSpeed;
				animState = R;
				if (animFlag == 1 || animFlag == 0) {
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


	//弾の発射
	if (Input::Push(button[3])) {
	
		if (bulletintervalCount == bulletinterval) {
			bulletintervalCount = 0;
			for (int index = 0;index < 10;index++) {
				if (isUse[index]) { continue; }

				bulletX[index] = playerX;
				bulletY[index] = playerY;
				bulletState[index] = animState;
				isUse[index] = true;
				break;
			}

		}
	}

	//弾の移動
	for (int index = 0;index < 10;index++) {
		if (!isUse[index]) { continue; }

		if (bulletState[index] == L) {
			bulletX[index] -= 10;
		}
		if (bulletState[index] == R) {
			bulletX[index] += 10;
		}
		if (bulletX[index] >= 1200 || bulletX[index] <= 0) {
			isUse[index] = false;
		}
	}


	bulletintervalCount++;
		if (bulletintervalCount >= bulletinterval) {
			bulletintervalCount = bulletinterval;
		}

}

void Player::Draw() {

	//アニメーション
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
	if (animFlag == 4) {
		if (!jump) {
			animIndex = 12;
		}
		else {
			animIndex = 8;
		}
	}

	//プレイヤー描画
	DrawGraph(playerX, playerY, playerHandle[animState][animIndex], true);

	//弾画像
	for (int index = 0;index < 10;index++) {
		if (!isUse[index]) { continue; }
	
		DrawGraph(bulletX[index], bulletY[index], bulletHandle[bulletState[index]][index], true);
	}
	
	DrawCircleGauge(playerX + 32, playerY - 20, hp,hpHandle, 0.0);

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