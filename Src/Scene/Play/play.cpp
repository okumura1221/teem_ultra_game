#include "play.h"
#include "../../Map/Map.h"  

Map CMap;                     


//初期化
void InitPlay() {
	
	CMap.Init();

	scene = SCENE_LOOP_PLAY;
}



//通常処理
void StepPlay() {


	
}



//描画処理
void DrawPlay() {

	DrawCircle(100, 630, 32, GetColor(255, 0, 0), true);

	CMap.Draw();
	
}



//破棄処理
void FinPlay() {




}