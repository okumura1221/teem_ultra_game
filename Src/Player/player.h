#include "../Common.h"


class Player {

protected:
	int playerHandle;
	float playerX;
	float playerY;
	float playerSpeed;
	float grav;

	int playerSizeX;
	int playerSizeY;

	bool jump;

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

	//プレイヤーのx座標をセット
	float GetPlayerPosX(float new_pos_x) {  playerX= new_pos_x; }

	//プレイヤーのｙ座標をセット
	float GetPlayerPosY(float new_pos_y) {  playerY= new_pos_y; }

	//プレイヤーのＸサイズ
	int GetPlayerSizeX() { return playerSizeX; }

	//プレイヤーのＹサイズ
	int GetPlayerSizeY() { return playerSizeY; }
};