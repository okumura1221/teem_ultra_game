#include "player.h"

#define  RUN_PATH "Data/Sound/����{�^��������38.mp3"
#define  JUMP_PATH "Data/Sound/�W�����v�̒��n.mp3"
#define  JUMP_PATH_2 "Data/Sound/�L�b�N�̑f�U��2.mp3"
#define  ATTACK_PATH "Data/Sound/�Ή����@1.mp3"
#define  ATTACK_PATH_2 "Data_/Sound/�u���炦�I�v.mp3"
#define  JUMP_PATH_3 "Data/Sound/�u�Ƃ��I�v.mp3"
#define  GUARD_PATH "Data/Sound/�u�����I�v.mp3"
#define  GUARD_PATH_2 "Data/Sound/�u���������I�v.mp3"
#define  GUARD_PATH_3 "Data/Sound/�u�����Ȃ����I�v.mp3"


//������
void Player::Init(int player_no) {
	
	//�v���C���[�摜�ǂݍ���

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
	//�PP�ƂQP�̕���
	if (player_no == 1) {//1P������
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
	else {//�Q��������
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
	//�e�̏�����
	for (int index = 0;index < 10;index++) {
		bulletX[index] = 0;
		bulletY[index] = 0;
		damage[index] = 8;//�_���[�W�͒n�W�A��T�i�ύX�̉\������j
		isUse[index] = false;
	}
	bulletinterval = 20;
	bulletintervalCount = 20;
	bulletSizeX = 80;
	bulletSizeY = 40;
}

void Player::Step() {

	//�A�j���[�V����������
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

		
	//���W������
	playerX = playerNextX;
	playerY = playerNextY;

	if (startCount >= 200&&hp>0) {
		//�ړ�����
		if (Input::Keep(button[0])) {//��
			playerNextX -= playerSpeed;
			animState = L;
			if (animFlag == 1 || animFlag == 0) {
				animFlag = 1;
			}
		}
		else
			if (Input::Keep(button[1])) {//�E
				playerNextX += playerSpeed;
				animState = R;
				if (animFlag == 1 || animFlag == 0) {
					animFlag = 1;
				}
			}


		//�W�����v����
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
		//�d��
		playerNextY += grav;

		
		//�_���[�W���󂯂����̐�����я���(��)
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
		

		//�e�̔���
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

	//�e�̈ړ�
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

	//�A�j���[�V�����ɂ���ď�����ς���
	if (animFlag == 0) {//����
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

	if (animFlag == 1) {//����
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

	if (animFlag == 2) {//��
		animIndex = 7;
	}

	if (animFlag == 3) {//��
		animIndex = 6;
	}
	if (animFlag == 4) {//�ˌ�
		if (!jump) {
			animIndex = 12;
		}
		else {
			animIndex = 8;
		}
	}

	if(hp<=0)animIndex = 11;//���S

	//�v���C���[�`��
	//if (alphaFlag)
	//	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 5);
	DrawGraph(playerX, playerY, playerHandle[animState][animIndex], true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�e�摜
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
	
	//�g�o�\���B�����m���ɂȂ�Ɠ_�ł���B
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