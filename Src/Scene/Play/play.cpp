#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"

Map CMap;                     
Player player;

//初期化
void InitPlay() {
	
	CMap.Init();

	player.Init();

	scene = SCENE_LOOP_PLAY;
}



//通常処理
void StepPlay() {


	player.Step();
}



//描画処理
void DrawPlay() {

	

	CMap.Draw();
	player.Draw();
	
}



//破棄処理
void FinPlay() {




}