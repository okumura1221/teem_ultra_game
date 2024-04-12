#include "../Common.h"


enum Animation {
	R,
	L
};


class Player {

protected:
	//プレイヤー変数
	int playerHandle[2][14];//プレイヤー画像
	int button[4];//入力キー
	int playerSizeX;//プレイヤー画像のXサイズ
	int playerSizeY;//プレイヤー画像のYサイズ
	int HP;//プレイヤーのHP

	float playerX;//ｘ座標
	float playerNextX;//次のフレームのｘ座標
	float playerY;//y座標
	float playerNextY;//次のフレームのy座標
	float playerSpeed;//プレイヤー移動速度
	float grav;//重力のおおきさ
	float jumpPower;//ジャンプ力
	
	int animState;//右向きか左向きか
	int animFlag;//アニメーションの種類
	int animIndex;//アニメーションの添え字
	int changeAnimFlame;//アニメーション切り替え時間
	int animFlameCount;//切り替え時間カウント

	bool jump;//ジャンプ中かどうか

	//弾変数
	int bulletHandle[2][10];//弾の画像
	int bulletState[10];//弾の向き
	int bulletinterval;//弾の発射間隔
	int bulletintervalCount;//弾の発射カウント
	
	float bulletX[10];//弾のX座標
	float bulletY[10];//弾のY座標

	bool isUse[10];//弾使用中かどうか

public:

	//初期化
	void Init(int player_no);

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

	//プレイヤーのＸサイズを得る
	int GetPlayerSizeX() { return playerSizeX; }

	//プレイヤーのＹサイズを得る
	int GetPlayerSizeY() { return playerSizeY; }

	//プレイヤーがジャンプ可能にする
	void SetJump() { jump = false; }

	//プレイヤーの進んでいる方向をチェック
	void GetMoveDirection(bool* _dirArray);
};