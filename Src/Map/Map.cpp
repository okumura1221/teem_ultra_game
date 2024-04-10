#include "map.h"
#include "DxLib.h"
#include "../Player/player.h"
#include "../Collision/Collision.h"
//マップ処理

// 初期化リストでconstのメンバ変数を初期化
//ステージ構成
Map::Map() :m_MapData{
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} }
{
	mapHundle1 = -1;
	mapHundle2 = -1;
	mapHundle3 = -1;
}

Map::~Map() {}

void Map::Init() {
	// 画像の読み込み
	mapHundle1 = LoadGraph("Data/Maptail/床（鉄）.png");
	mapHundle2 = LoadGraph("Data/Maptail/金網.png");
	mapHundle3 = LoadGraph("Data/Maptail/床（鉄暗）.png");
}



void Map::Draw() {

	//ごめん、うちのPCだと見ずらいので一時的に白い背景おく。後で消していいよ
	DrawBox(0, 0, 1280, 720, GetColor(200, 200, 200), true);
	//-------

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// ブロックを描画
			if (m_MapData[y][x] == 1) {
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHundle1, true);
			}
		}
	}
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