#include "../Common.h"


enum Animation {
	R,//�E
	L//��
};


class Player {

protected:
	//�v���C���[�ϐ�
	int playerHandle[2][18];//�v���C���[�摜
	int button[4];//���̓L�[
	int playerSizeX;//�v���C���[�摜��X�T�C�Y
	int playerSizeY;//�v���C���[�摜��Y�T�C�Y
	int hpBaseHandle;//�v���C���[HP�y��摜
	int hpHandle[3];//�v���C���[HP�摜
	int hp;//�v���C���[��HP
	int alphaCount;//
	int hpColorFlag;//HP�̐F�ϓ��ϐ�

	float playerX;//�����W
	float playerNextX;//���̃t���[���̂����W
	float playerY;//y���W
	float playerNextY;//���̃t���[����y���W
	float playerSpeed;//�v���C���[�ړ����x
	float grav;//�d�͂̂�������
	float jumpPower;//�W�����v��
	
	int animState;//�E��������������
	int animFlag;//�A�j���[�V�����̎��
	int animIndex;//�A�j���[�V�����̓Y����
	int changeAnimFlame;//�A�j���[�V�����؂�ւ�����
	int animFlameCount;//�؂�ւ����ԃJ�E���g

	bool jump;//�W�����v�����ǂ���
	bool alphaFlag;
	bool danger;//�������s���`���ǂ���

	bool HitPlayerDamage;//�v���C���[���U�����󂯂��ꍇ
	int hitArea;//�ǂ����瓖��������
	int HitJunpflmcnt;
	float HitFly_x;
	float HitFly_y;

	int runsounnd;
	int damagevoice[3];
	int Attackvoice[2];
	int jumpvoice[3];

	//�e�ϐ�
	int bulletHandle[2][10];//�e�̉摜
	int bulletState[10];//�e�̌���
	int bulletinterval;//�e�̔��ˊԊu
	int bulletintervalCount;//�e�̔��˃J�E���g
	int bulletSizeX;//�e��X�傫��
	int bulletSizeY;//�e��Y�傫��
	int damage[10];//�e�̍U����

	float bulletX[10];//�e��X���W
	float bulletY[10];//�e��Y���W

	bool isUse[10];//�e�g�p�����ǂ���

public:

	//������
	void Init(int player_no);

	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�v���C���[

	//�v���C���[�̂����W�𓾂�
	float GetPlayerPosX() { return playerX; }

	//�v���C���[�̂����W�𓾂�
	float GetPlayerPosY() { return playerY; }

	//�v���C���[�̂����W�𓾂�
	float GetNextPlayerPosX() { return playerNextX; }

	//�v���C���[�̂����W�𓾂�
	float GetNextPlayerPosY() { return playerNextY; }

	//�v���C���[��x���W���Z�b�g
	void SetPlayerNextPosX(float new_pos_x) {  playerNextX= new_pos_x; }

	//�v���C���[�̂����W���Z�b�g
	void SetPlayerNextPosY(float new_pos_y) {  playerNextY= new_pos_y; }

	//�v���C���[�̂w�T�C�Y�𓾂�
	int GetPlayerSizeX() { return playerSizeX; }

	//�v���C���[�̂x�T�C�Y�𓾂�
	int GetPlayerSizeY() { return playerSizeY; }

	//�v���C���[�̗̑͂𓾂�
	int GetPlayerHP() { return hp; }

	//�v���C���[���W�����v�\�ɂ���
	void SetJump() { jump = false; }

	//�v���C���[���_���[�W���󂯁A�m�b�N�o�b�N
	void InDamage(int damage, int bullet_state) {
		hp -= damage;
		hitArea = bullet_state;
		HitPlayerDamage = true;
	}

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);


	//�e

	//�e��x���W�𓾂�
	float GetBulletPosX(int bullet_index) { return bulletX[bullet_index]; }

	//�e��y���W�𓾂�
	float GetBulletPosY(int bullet_index) { return bulletY[bullet_index]+10; }

	//�e��x�T�C�Y�𓾂�
	float GetBulletSizeX() { return bulletSizeX-40; }

	//�e��y�T�C�Y�𓾂�
	float GetBulletSizeY() { return bulletSizeY-10; }

	//�e�̍U���͂𓾂�
	int GetBulletDamage(int bullet_index) { return damage[bullet_index]; }

	//�e�̌����𓾂�
	int GetBulletState(int bullet_index) { return bulletState[bullet_index]; }

	//�e�̎g�p��Ԃ𓾂�
	bool GetBulletIsUse(int bullet_index) { return isUse[bullet_index]; }

	//�e�̎g�p��Ԃ��I�t�ɂ���
	void SetBulletIsUse(int bullet_index) { isUse[bullet_index] = false;; }

};