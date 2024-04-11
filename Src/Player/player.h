#include "../Common.h"


class Player {

protected:
	int playerHandle;
	float playerX;
	float playerNextX;
	float playerY;
	float playerNextY;
	float playerSpeed;
	float grav;

	int playerSizeX;
	int playerSizeY;

	bool jump;

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

	//�v���C���[��x���W���Z�b�g
	float GetPlayerNextPosX(float new_pos_x) {  playerNextX= new_pos_x; }

	//�v���C���[�̂����W���Z�b�g
	float GetPlayerNextPosY(float new_pos_y) {  playerNextY= new_pos_y; }

	//�v���C���[�̂w�T�C�Y
	int GetPlayerSizeX() { return playerSizeX; }

	//�v���C���[�̂x�T�C�Y
	int GetPlayerSizeY() { return playerSizeY; }
};