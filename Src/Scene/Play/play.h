#include "../../Common.h"


//������
void InitPlay();

//�ʏ폈��
void StepPlay();

//�`�揈��
void DrawPlay();

//�j������
void FinPlay();

struct MAPCollision
{
	// �}�b�v�̓����蔻��
	void MapCollision();
	// 2�̍��W�����d�Ȃ��Ă���ʂ��擾
	int GetOverlap(int posA, int posB);
};