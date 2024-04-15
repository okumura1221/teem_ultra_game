#include "player.h"

#define  RUN_PATH "Data/Sound/決定ボタンを押す38.mp3"
#define  JUMP_PATH "Data/Sound/ジャンプの着地.mp3"
#define  JUMP_PATH_2 "Data/Sound/キックの素振り2.mp3"
#define  ATTACK_PATH "Data/Sound/火炎魔法1.mp3"
#define  ATTACK_PATH_2 "Data_/Sound/「くらえ！」.mp3"
#define  JUMP_PATH_3 "Data/Sound/「とう！」.mp3"
#define  GUARD_PATH "Data/Sound/「ぐっ！」.mp3"
#define  GUARD_PATH_2 "Data/Sound/「ぐああっ！」.mp3"
#define  GUARD_PATH_3 "Data/Sound/「効かないぞ！」.mp3"


//初期化
void Player::Init(int player_no) {
	
	//プレイヤー画像読み込み

	LoadDivGraph("Data/Player/player_R.png", 18, 3, 6, 64, 64, playerHandle[0]);
	LoadDivGraph("Data/Player/player_L.png", 18, 3, 6, 64, 64, playerHandle[1]);
	
	animIndex = 0;
	animFlag = 0;
	animFlameCount = 0;

	//runsounnd = LoadGraph(RUN_PATH);
	//damagevoice[0] = LoadSoundMem(ATTACK_PATH);
	//damagevoice[1] = LoadSoundMem(ATTACK_PATH_2);
	//damagevoice[2] = LoadSoundMem(JUMP_PATH);
	//	titlebgmhandle = LoadSoundMem(JUMP_PATH_2);
	//	jumpvoice[] = LoadSoundMem(JUMP_PATH_3);
	//	jumpvoice[0] = LoadSoundMem(GUARD_PATH);
	//	jumpvoice[1] = LoadSoundMem(GUARD_PATH_2);
	//	jumpvoice[2] = LoadSoundMem(GUARD_PATH_3);

	// damagevoice[3];
	// Attackvoice[2];
	// jumpvoice[3];
	//１Pと２Pの分け
	if (player_no == 1) {//1P初期化
		animState = R;
		hpHandle[0] = LoadGraph("Data/Player/hp_green.png");
		hpHandle[1] = LoadGraph("Data/Player/hp_yellow.png");
		hpHandle[2] = LoadGraph("Data/Player/hp_red.png");
		hpBaseHandle = LoadGraph("Data/Player/hp_base.png");
		for (int index = 0;index < 10;index++) {
			bulletHandle[0][index] = LoadGraph("Data/Player/attack_R.png");
			bulletHandle[1][index] = LoadGraph("Data/Player/attack_L.png");
		}
		button[0]= KEY_INPUT_A;
		button[1]=KEY_INPUT_D;
		button[2]= KEY_INPUT_W;
		button[3]= KEY_INPUT_SPACE;
		playerNextX = 50;
		playerNextY = 608;
	}
	else {//２ｐ初期化
		animState = L;
		hpHandle[0] = LoadGraph("Data/Player/hp_green.png");
		hpHandle[1] = LoadGraph("Data/Player/hp_yellow.png");
		hpHandle[2] = LoadGraph("Data/Player/hp_red.png");
		hpBaseHandle = LoadGraph("Data/Player/hp_base.png");
		for (int index = 0;index < 10;index++) {
			bulletHandle[0][index] = LoadGraph("Data/Player/attack2_R.png");
			bulletHandle[1][index] = LoadGraph("Data/Player/attack2_L.png");
		}
		button[0] = KEY_INPUT_NUMPAD4;
		button[1] = KEY_INPUT_NUMPAD6;
		button[2] = KEY_INPUT_NUMPAD8;
		button[3] = KEY_INPUT_NUMPADENTER;
		playerNextX =1150;
		playerNextY = 608;
	}

	hp = 100;
	alphaCount = 0;
	danger = false;
	alphaFlag = false;
	hpColorFlag = 0;
	playerSizeX = 64;
	playerSizeY = 64;
	playerSpeed = 5;
	jump = false;
	grav = 15.0;
	jumpPower = 20;
	HitPlayerDamage = false;
	HitJunpflmcnt = 0;
	HitFly_x=20;
	HitFly_y=20;
	//弾の初期化
	for (int index = 0;index < 10;index++) {
		bulletX[index] = 0;
		bulletY[index] = 0;
		damage[index] = 8;//ダメージは地８、空５（変更の可能性あり）
		isUse[index] = false;
	}
	bulletinterval = 20;
	bulletintervalCount = 20;
	bulletSizeX = 80;
	bulletSizeY = 40;
}

void Player::Step() {

	//アニメーションを決定
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

	if (startCount >= 200&&hp>0) {
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

		
		//ダメージを受けた時の吹っ飛び処理(左)
		if (HitPlayerDamage)
		{
			for (int index = 0; index < 10; index++) {
				if (bulletX[index] < playerX + playerSizeX) {
					playerNextX -= HitFly_x;
					if (HitFly_x <= 0) HitFly_x = 0;
					HitFly_x -= 1.2;
					playerNextY -= HitFly_y;
					HitFly_y -= 1.2;

					if (HitFly_y <= 0) HitFly_y = 0;

					HitJunpflmcnt++;
					if (HitJunpflmcnt >= 15)HitPlayerDamage = false;
				}
				break;
			}
		}
		if (HitPlayerDamage)
		{
			for (int index = 0; index < 10; index++) {
				if (bulletX[index] + bulletSizeX > playerX) {
					playerNextX += HitFly_x;
					if (HitFly_x <= 0) HitFly_x = 0;
					HitFly_x += 1.2;
					playerNextY -= HitFly_y;
					HitFly_y -= 1.2;

					if (HitFly_y <= 0) HitFly_y = 0;

					HitJunpflmcnt++;
					if (HitJunpflmcnt >= 15)HitPlayerDamage = false;
				}
				break;
			}
		}
		else
		{
			HitFly_x = 20;
			HitFly_y = 20;
			HitJunpflmcnt = 0;
		}
		

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
					if (!jump) {
						damage[index] = 8;
					}
					else {
						damage[index] = 5;
					}
					break;
				}

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

	//アニメーションによって処理を変える
	if (animFlag == 0) {//立ち
		changeAnimFlame = 7;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 18) {
				animIndex = 14;
			}
			else if (animIndex <= 14) {
				animIndex = 17;
			}
		}
	}

	if (animFlag == 1) {//歩き
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

	if (animFlag == 2) {//空中
		animIndex = 7;
	}

	if (animFlag == 3) {//空中
		animIndex = 6;
	}
	if (animFlag == 4) {//射撃
		if (!jump) {
			animIndex = 12;
		}
		else {
			animIndex = 8;
		}
	}

	if(hp<=0)animIndex = 11;//死亡

	//プレイヤー描画
	//if (alphaFlag)
	//	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 5);
	DrawGraph(playerX, playerY, playerHandle[animState][animIndex], true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//弾画像
	for (int index = 0;index < 10;index++) {
		if (!isUse[index]) { continue; }
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(bulletX[index], bulletY[index], bulletHandle[bulletState[index]][index], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
	if (hp < 30) {
		danger = true;
	}

	if (hp <= 50)hpColorFlag = 1;
	if (hp <= 30)hpColorFlag = 2;
	
	//ＨＰ表示。処理瀕死になると点滅する。
	int alpha;
	if (danger) {
		alphaCount++;
		if (alphaCount > 30) {
			alphaCount = 0;
			if (alphaFlag) {
				alphaFlag = false;
			}
			else {
				alphaFlag = true;
			}
		}
	}
	if (!alphaFlag) {
		alpha = 255;
	}
	else {
		alpha = 0;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawCircleGauge(playerX + 32, playerY - 20, 100, hpBaseHandle, 0.0);
	DrawCircleGauge(playerX + 32, playerY - 20, hp,hpHandle[hpColorFlag], 0.0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 1);
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

void Player::GetHitPlayerDamage()
{
	HitPlayerDamage = true;
}

void Player::HitFlyDirection(int Direction_1, int Direction_2)
{
	if (HitPlayerDamage)
	{
		if (Direction_1 != Direction_2)animIndex = 13;
		else animIndex = 9;
	}
}

int Player::GetDirection()
{
	return animState;
}

int Player::GetHP()
{
	return hp;
}