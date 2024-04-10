#include "play.h"
#include "../../Map/Map.h"  

Map CMap;                     


//‰Šú‰»
void InitPlay() {
	
	CMap.Init();

	scene = SCENE_LOOP_PLAY;
}



//’Êíˆ—
void StepPlay() {


	
}



//•`‰æˆ—
void DrawPlay() {

	DrawCircle(100, 630, 32, GetColor(255, 0, 0), true);

	CMap.Draw();
	
}



//”jŠüˆ—
void FinPlay() {




}