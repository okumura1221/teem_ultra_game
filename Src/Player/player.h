#include "../Common.h"


enum Animation {
	R,
	L
};


class Player {

protected:
	//�v���C���[�ϐ�
	int playerHandle[2][14];//�v���C���[�摜
	int button[4];//���̓L�[
	int playerSizeX;//�v���C���[�摜��X�T�C�Y
	int playerSizeY;//�v���C���[�摜��Y�T�C�Y
	int HP;//�v���C���[��HP

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

	//�e�ϐ�
	int bulletHandle[2][10];//�e�̉摜
	int bulletState[10];//�e�̌���
	int bulletinterval;//�e�̔��ˊԊu
	int bulletintervalCount;//�e�̔��˃J�E���g
	
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

	//�v���C���[���W�����v�\�ɂ���
	void SetJump() { jump = false; }

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);
};