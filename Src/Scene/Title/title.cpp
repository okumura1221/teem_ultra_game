#include "DxLib.h"
#include"title.h"
#include "../../Common.h"
#include "../../Input/input.h"

#define TITLE_PATH "Data/Title/�^�C�g���itanku�j.png"

int TitleHandle;
int titlebgmcount = 0;
int nextstopcount = 0;
bool titleflag = false;

void InitTitle()
{
	TitleHandle = LoadGraph(TITLE_PATH);

	scene = SCENE_LOOP_TITLE;
}

void StepTitle()
{
	if (titlebgmcount == 0) {
		//BGM���������Ƃ�
	}

	//Enter�L�[�����ꂽ�Ȃ�
	if (Input::Push(KEY_INPUT_RETURN) == 1)
	{
		//SE�����p & BGM�~�߂�p//
		titleflag = true;   //�t���OON
	}
	if (titleflag == true) {
		nextstopcount++;
		if (nextstopcount == 255 / 5 + 30) {   //nextstopcount����萔�B�����Ƃ�
			//�v���C�V�[���ֈړ�
			titlebgmcount = 0;
			nextstopcount = 0;
			//SE�f���[�g�p
			titleflag = false;
			scene = SCENE_FIN_TITLE;
		}
	}
	titlebgmcount++;
}

void DrawTitle()
{
	//�^�C�g���`��
	DrawGraph(0, 0, TitleHandle, true);
}

void FinTitle()
{
	scene = SCENE_INIT_PLAY;
}