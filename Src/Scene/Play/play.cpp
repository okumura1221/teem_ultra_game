#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"

Map CMap;                     
Player player;

//������
void InitPlay() {
	
	CMap.Init();

	player.Init();

	scene = SCENE_LOOP_PLAY;
}



//�ʏ폈��
void StepPlay() {


	player.Step();
}



//�`�揈��
void DrawPlay() {

	

	CMap.Draw();
	player.Draw();
	
}



//�j������
void FinPlay() {




}