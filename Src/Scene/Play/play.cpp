#include "play.h"
#include "../../Map/Map.h"  

Map CMap;                     


//������
void InitPlay() {
	
	CMap.Init();

	scene = SCENE_LOOP_PLAY;
}



//�ʏ폈��
void StepPlay() {


	
}



//�`�揈��
void DrawPlay() {

	DrawCircle(100, 630, 32, GetColor(255, 0, 0), true);

	CMap.Draw();
	
}



//�j������
void FinPlay() {




}