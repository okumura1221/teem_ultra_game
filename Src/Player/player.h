#include "../Common.h"


enum Animation {
	WALK_R,
	WALK_L

};


class Player {

protected:
	int playerHandle[2][6];
	float playerX;
	float playerNextX;
	float playerY;
	float playerNextY;
	float playerSpeed;//�v���C���[�ړ����x
	float grav;//�d�͂̂�������
	float jumpPower;//�W�����v��

	int playerSizeX;
	int playerSizeY;
	int animState;
	int animIndex;
	int changeAnimFlame;
	int animFlameCount;

	bool jump;//�W�����v�\���ǂ���

public:

	//������
	void Init();

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

	//�v���C���[�̂w�T�C�Y
	int GetPlayerSizeX() { return playerSizeX; }

	//�v���C���[�̂x�T�C�Y
	int GetPlayerSizeY() { return playerSizeY; }

	//�v���C���[���W�����v�\�ɂ���
	void SetJump() { jump = false; }

	// �i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);
};