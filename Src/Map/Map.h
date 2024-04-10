#pragma once

// 各マップのデータ数
const int MAP_DATA_Y = 25;
const int MAP_DATA_X = 40;

// マップサイズ
const int MAP_SIZE = 32;

// マップクラス
class Map
{
private:
	// マップチップハンドル
	int mapHundle1;
	int mapHundle2;
	int mapHundle3;

public:
	Map();
	~Map();

	// マップデータ
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };
	int mposX;  //マップ座標

	// 初期化
	void Init();

	// 描画
	void Draw();
};

struct MAPCollision
{
	// マップの当たり判定
	void MapCollision();
	// 2つの座標がか重なっている量を取得
	int GetOverlap(int posA, int posB);
};