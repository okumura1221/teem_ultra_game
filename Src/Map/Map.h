#pragma once

// �e�}�b�v�̃f�[�^��
const int MAP_DATA_Y = 25;
const int MAP_DATA_X = 40;

// �}�b�v�T�C�Y
const int MAP_SIZE = 32;

// �}�b�v�N���X
class Map
{
private:
	// �}�b�v�`�b�v�n���h��
	int mapHandle[4];

public:
	Map();
	~Map();

	// �}�b�v�f�[�^
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };
	int mposX;  //�}�b�v���W

	// ������
	void Init();

	// �`��
	void Draw();
};

