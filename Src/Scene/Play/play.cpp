#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"

Map CMap;                     
Player player;

//‰Šú‰»
void InitPlay() {
	
	CMap.Init();

	player.Init();

	scene = SCENE_LOOP_PLAY;
}



//’Êíˆ—
void StepPlay() {


	player.Step();
}



//•`‰æˆ—
void DrawPlay() {

	

	CMap.Draw();
	player.Draw();
	
}



//”jŠüˆ—
void FinPlay() {




}