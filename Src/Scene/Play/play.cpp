#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"
#include "../../Collision/Collision.h"

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

/*// マップの当たり判定
void MAPCollision::MapCollision() {
	// Y方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// ブロック以外は処理しない
			if (CMap.m_MapData[mapIndexY][mapIndexX] == 0)
				continue;

			// どの方向に進んでいたかチェック
			bool dirArray[4] = { false,false,false,false };
			playerInfo.GetMoveDirection(dirArray);

			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = playerX;
			int Ay = playerY;
			int Aw = playerSizeX;
			int Ah = playerSizeY;

			// オブジェクトの情報
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ※Y方向のみに移動したと仮定した座標で当たり判定をチェックします
			Ay = playerInfo.GetNextPosY();
			Ax = playerInfo.GetPosX();

			// 当たっているかチェック
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// 上方向の修正
				if (dirArray[0]) {
					// めり込み量を計算する
					int overlap = By + Bh - Ay;
					playerInfo.SetNextPosY(Ay + overlap);
				}

				// 下方向の修正
				if (dirArray[1]) {
					// めり込み量を計算する
					int overlap = Ay + Ah - By;
					playerInfo.SetNextPosY(Ay - overlap);
					playerInfo.Yspeed = 0.0f;    //戻す
					playerInfo.isFly = false;    //ついたとき切り替え
				}
			}
		}
	}
	// X方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// ブロック以外は処理しない
			if (CMap.m_MapData[mapIndexY][mapIndexX] == 0)
				continue;

			// どの方向に進んでいたかチェック
			// ※Playerクラスに進む方向をチェックする関数を準備しています。
			bool dirArray[4] = { false,false,false,false };
			playerInfo.GetMoveDirection(dirArray);

			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = playerX;
			int Ay = playerY;
			int Aw = playerSizeX;
			int Ah = playerSizeY;

			// オブジェクトの情報
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// 矩形の当たり判定用のデータを準備
			// ※X方向のみに移動したと仮定した座標で当たり判定をチェックします
			Ay = playerInfo.GetNextPosY();
			Ax = playerInfo.GetNextPosX();

			// 当たっているかチェック
			if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// 左方向の修正
				if (dirArray[2]) {
					// めり込み量を計算する
					int overlap = Bx + Bw - Ax;
					playerInfo.SetNextPosX(Ax + overlap);
				}

				// 右方向の修正
				if (dirArray[3]) {
					// めり込み量を計算する
					int overlap = Ax + Aw - Bx;
					playerInfo.SetNextPosX(Ax - overlap);
				}
			}
		}
	}
}

// 2つの座標がか重なっている量を取得
int MAPCollision::GetOverlap(int posA, int posB) {
	int ret = posA - posB;
	return abs(ret);
}*/