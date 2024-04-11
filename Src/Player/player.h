#include "../Common.h"


enum Animation {
	WALK_R,
	WALK_L

};


class Player {

protected:
	int playerHandle[2][6];
	float playerX;
	float playerNextX;
	float playerY;
	float playerNextY;
	float playerSpeed;//プレイヤー移動速度
	float grav;//重力のおおきさ
	float jumpPower;//ジャンプ力

	int playerSizeX;
	int playerSizeY;
	int animState;
	int animIndex;
	int changeAnimFlame;
	int animFlameCount;

	bool jump;//ジャンプ可能かどうか

public:

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	void Draw();


	//プレイヤーのｘ座標を得る
	float GetPlayerPosX() { return playerX; }

	//プレイヤーのｙ座標を得る
	float GetPlayerPosY() { return playerY; }

	//プレイヤーのｘ座標を得る
	float GetNextPlayerPosX() { return playerNextX; }

	//プレイヤーのｙ座標を得る
	float GetNextPlayerPosY() { return playerNextY; }

	//プレイヤーのx座標をセット
	void SetPlayerNextPosX(float new_pos_x) {  playerNextX= new_pos_x; }

	//プレイヤーのｙ座標をセット
	void SetPlayerNextPosY(float new_pos_y) {  playerNextY= new_pos_y; }

	//プレイヤーのＸサイズ
	int GetPlayerSizeX() { return playerSizeX; }

	//プレイヤーのＹサイズ
	int GetPlayerSizeY() { return playerSizeY; }

	//プレイヤーがジャンプ可能にする
	void SetJump() { jump = false; }

	// 進んでいる方向をチェック
	void GetMoveDirection(bool* _dirArray);
};