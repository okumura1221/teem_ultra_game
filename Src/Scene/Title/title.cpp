#include "DxLib.h"
#include"title.h"
#include "../../Common.h"
#include "../../Input/input.h"

#define TITLE_PATH "Data/Title/title.png"
#define MOUSE_PATH "Data/Player/mouse.png"
#define TITLE_CLICK_BEFORE_PATH "Data/Title/title_click_before.png"
#define TITLE_CLICK_AFTER_PATH "Data/Title/title_click_after.png"
#define  TITLE_BGM_PATH "Data/Sound/title_bgm.ogg"
#define  TITLE_CRICK_PATH_1 "Data/Sound/ビープ音4.mp3"
#define  TITLE_CRICK_PATH_2 "Data/Sound/決定ボタンを押す18.mp3"
#define  TITLE_CURSOR_PATH "Data/Sound/カーソル移動4.mp3"


int TitleHandle;
int TitleclickHandle[2];
int Titleclickindex = 0;;
int titlebgmcount = 0;
int nextstopcount = 0;
bool titleflag = false;
int MouseHandle;

int titlebgmhandle;
int titleclicksoundhandle[2];
int titlecursorhandle;
int mousex, mousey = 0;
bool pushflag;
bool cursorflag;
int shadowcolor;
double mouseradian;

void InitTitle()
{
	mouseradian=0.0;
	titlebgmhandle = LoadSoundMem(TITLE_BGM_PATH);
	titleclicksoundhandle[0] = LoadSoundMem(TITLE_CRICK_PATH_1);
	titleclicksoundhandle[1] = LoadSoundMem(TITLE_CRICK_PATH_2);
	titlecursorhandle = LoadSoundMem(TITLE_CURSOR_PATH);

	TitleHandle = LoadGraph(TITLE_PATH);
	TitleclickHandle[0] = LoadGraph(TITLE_CLICK_BEFORE_PATH);
	TitleclickHandle[1] = LoadGraph(TITLE_CLICK_AFTER_PATH);
	shadowcolor = 255;

	MouseHandle = LoadGraph(MOUSE_PATH);
	pushflag = false;
	cursorflag = false;
	scene = SCENE_LOOP_TITLE;
	PlaySoundMem(titlebgmhandle, DX_PLAYTYPE_LOOP, true);
}

void StepTitle()
{
	mouseradian+=0.05;
	if (titlebgmcount == 0) {
		//BGM流したいとき
	}

	GetMousePoint(&mousex, &mousey);
	if (335 <= mousex&& mousex <= 935&& 460 <= mousey && mousey <= 535)
	{ 
		if(!cursorflag)
		PlaySoundMem(titlecursorhandle, DX_PLAYTYPE_BACK, true);
		cursorflag = true;
		Titleclickindex = 1;
		//マウス押されたなら
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			if (!pushflag)
			PlaySoundMem(titleclicksoundhandle[1], DX_PLAYTYPE_BACK, true);
			Titleclickindex = 0;
			pushflag = true;
			//SE入れる用 & BGM止める用//
			titleflag = true;   //フラグON
		}
		else
		{
			pushflag = false;
		}
	}	
	else
	{
		Titleclickindex = 0;
		cursorflag = false;

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			if(!cursorflag)
			PlaySoundMem(titleclicksoundhandle[0], DX_PLAYTYPE_BACK, true);
			cursorflag = true;
		}
		else cursorflag = false;
	}
		
	
	if (titleflag == true) {
		shadowcolor-=10;
		if (shadowcolor<=0) {   //nextstopcountが一定数達したとき
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
//335,460  935,535
void DrawTitle()
{
	//タイトル描画
	DrawGraph(0, 0, TitleHandle, true);
	if(pushflag)
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawGraph(0, 0, TitleclickHandle[Titleclickindex], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaGraph(mousex, mousey,2.0, mouseradian,MouseHandle, true);
	DrawFormatString(1155, 680, GetColor(255, 255, 255), "BGM:OtoLogic様");
	SetDrawBright(shadowcolor, shadowcolor, shadowcolor);

}

void FinTitle()
{
	DeleteSoundMem(titlebgmhandle);
	DeleteSoundMem(titleclicksoundhandle[0]);
	DeleteSoundMem(titleclicksoundhandle[1]);
	DeleteSoundMem(titlecursorhandle);
	scene = SCENE_INIT_PLAY;
}