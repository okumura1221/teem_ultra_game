#include "DxLib.h"
#include "Common.h"
#include "Scene/Play/play.h"
#include "Scene/Title/title.h"


//設定フレームレート
#define FRAME_RATE (60)

//１フレームの時間(ミリ秒)
#define FRAME_TIME (1000/FRAME_RATE)

//フレームレート情報
struct FrameRateInfo {
	int currentTime;//現在の時間
	int lastFrameTime;//前回のフレーム実行時の時間
	int count;//フレームカウント用
	int calcFpsTime;//FPSを計算した時間
	float fps;//計測したFPS
};
//フレームレート情報変数
FrameRateInfo frameRateInfo;

//FPS計算
void CalcFps();

//FPS表示
void DrawCalc();


//最初のシーン
SCENE scene=SCENE_INIT_PLAY;


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(false);

	//DXライブラリの初期化
	if(DxLib_Init() == -1)
	{
		return -1;
	}

	//ウィンドウサイズを変更
	SetGraphMode(1280, 720, 32);

	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);


	Input::Init();
	
	//=====================================
	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);

		frameRateInfo.currentTime = GetNowCount();

		if (frameRateInfo.calcFpsTime == 0.0f) {
			frameRateInfo.fps = (float)FRAME_RATE;
		}


		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME) {

			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();

			Input::Step();

			//シーン遷移
			switch (scene) {

			case SCENE_INIT_TITLE:
				
				InitTitle();

				break;

			case SCENE_LOOP_TITLE:

				StepTitle();

				DrawTitle();

				break;

			case SCENE_FIN_TITLE:

				FinTitle();

				break;

			case SCENE_INIT_PLAY:
					
				InitPlay();

				break;

			case SCENE_LOOP_PLAY:
					
				StepPlay();

				DrawPlay();

				break;

			case SCENE_FIN_PLAY:

				FinPlay();

				break;
			}
			
			CalcFps();
			DrawCalc();
			
			
			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
		}
	}
	//最後に１回だけやる処理をここに書く
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}


void CalcFps() {
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;


	if (difTime > 1000) {
		float frameCount = (float)(frameRateInfo.count * 1000.0f);


		frameRateInfo.fps = frameCount / difTime;

		frameRateInfo.count = 0;
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

void DrawCalc() {
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1190, 700, color, "FPS[%.2f]", frameRateInfo.fps);
}
