#include "DxLib.h"
#include"title.h"
#include "../../Common.h"
#include "../../Input/input.h"

#define TITLE_PATH "Data/Title/タイトル（tanku）.png"

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
		//BGM流したいとき
	}

	//Enterキー押されたなら
	if (Input::Push(KEY_INPUT_RETURN) == 1)
	{
		//SE入れる用 & BGM止める用//
		titleflag = true;   //フラグON
	}
	if (titleflag == true) {
		nextstopcount++;
		if (nextstopcount == 255 / 5 + 30) {   //nextstopcountが一定数達したとき
			//プレイシーンへ移動
			titlebgmcount = 0;
			nextstopcount = 0;
			//SEデリート用
			titleflag = false;
			scene = SCENE_FIN_TITLE;
		}
	}
	titlebgmcount++;
}

void DrawTitle()
{
	//タイトル描画
	DrawGraph(0, 0, TitleHandle, true);
}

void FinTitle()
{
	scene = SCENE_INIT_PLAY;
}