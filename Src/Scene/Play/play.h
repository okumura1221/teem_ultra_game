#include "../../Common.h"


//初期化
void InitPlay();

//通常処理
void StepPlay();

//描画処理
void DrawPlay();

//破棄処理
void FinPlay();

struct MAPCollision
{
	// マップの当たり判定
	void MapCollision();
	// 2つの座標がか重なっている量を取得
	int GetOverlap(int posA, int posB);
};