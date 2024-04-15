#include "play.h"
#include "../../Map/Map.h"  
#include "../../Player/player.h"
#include "../../Collision/Collision.h"

#define  BATTLE_START_BGM_PATH "Data/Sound/battle_start.ogg"
#define  BATTLE_EARLY_BGM_PATH "Data/Sound/battle_bgm_early.ogg"
#define  BATTLE_FINAL_BGM_PATH "Data/Sound/battle_bgm_final.ogg"
#define  BATTLE_WIN_BGM_PATH "Data/Sound/battle_winner.ogg"
#define  BATTLE_WIN_VOICE_PATH "Data/Sound/「やった！」.mp3"
#define  BATTLE_LOSS_VOICE_PATH "Data/Sound/「ぐああーーっ！」.mp3"
#define BATTLR_HIT_ATTACK "Data/Sound/パンチの衣擦れ2.mp3"

Player* player;
Map* CMap;
MAPCollision mapcollision;

//始まるまでの時間
int startCount;

int winHandle[2];
int finishCount;

int hitInterval[2];

int shadowcolor_2;

int battlestartbgm;

int battlebgm[2];

int battlewinbgm;

int hitSE;

int bgmindex;

bool bgmflag;

bool winbgmflag;

int mountainHandle;
int mountainbackHandle;

int cloudHandle[2][3];
int cloud_x[2][3];
int cloud_y[2][3];
int lastvoise[2];

//初期化
void InitPlay() {
	
	//ステージの処理に使う
	mountainHandle = LoadGraph("Data/fuji.png");//山画像
	mountainbackHandle = LoadGraph("Data/fuji_back.png");//背景画像
	for (int i = 0;i < 2;i++)//曇画像
	{
			cloudHandle[i][0] = LoadGraph("Data/cloud_1.png");
			cloudHandle[i][1] = LoadGraph("Data/cloud_2.png");
			cloudHandle[i][2] = LoadGraph("Data/cloud_3.png");	
			for (int j = 0;j < 3;j++)
			{
				cloud_y[0][j] = GetRand(300);
				cloud_y[1][j] = GetRand(200)+150;
			}
	}
	cloud_x[0][0] = 0;
	cloud_x[0][1] = (1280 / 2) - 126;
	cloud_x[0][2] = 1280 - 270;
	for (int i = 0;i < 3;i++)
	{
		cloud_x[1][i] = cloud_x[0][i]-1280;
	}
	startCount = 0;//移動可能までの時間
	winHandle[0] = LoadGraph("Data/1p_win.png");//勝利画像
	winHandle[1] = LoadGraph("Data/2p_win.png");//勝利画像
	finishCount = 0;//決着がついた後の自由時間
	hitInterval[0] = 0;
	hitInterval[1] = 0;

	player = new Player[2];
	CMap =new Map;

	CMap->Init();

	player[0].Init(1);
	player[1].Init(2);

	battlestartbgm= LoadSoundMem(BATTLE_START_BGM_PATH);
	battlebgm[0] = LoadSoundMem(BATTLE_EARLY_BGM_PATH);
	battlebgm[1] = LoadSoundMem(BATTLE_FINAL_BGM_PATH);
	battlewinbgm = LoadSoundMem(BATTLE_WIN_BGM_PATH);
	lastvoise[0] = LoadSoundMem(BATTLE_WIN_VOICE_PATH);
	lastvoise[1] = LoadSoundMem(BATTLE_LOSS_VOICE_PATH);
	hitSE = LoadSoundMem(BATTLR_HIT_ATTACK);

	shadowcolor_2 = 0;
	bgmindex = 0;
	bgmflag = false;
	winbgmflag = false;

	PlaySoundMem(battlestartbgm, DX_PLAYTYPE_BACK, true);

	scene = SCENE_LOOP_PLAY;
}



//通常処理
void StepPlay() {

	//音
	if (shadowcolor_2 <= 255)shadowcolor_2 += 10;
	SetDrawBright(shadowcolor_2, shadowcolor_2, shadowcolor_2);

	if (player[0].GetPlayerHP() <= 50 || player[1].GetPlayerHP() <= 50)
	{
		StopSoundMem(battlebgm[0]);
		if (CheckSoundMem(battlebgm[0]) == 0 && CheckSoundMem(battlebgm[1]) == 0)
			PlaySoundMem(battlebgm[1], DX_PLAYTYPE_LOOP, true);
	}
	if (player[0].GetPlayerHP() <= 0 || player[1].GetPlayerHP() <= 0)
	{
		

		StopSoundMem(battlebgm[1]);
		if (CheckSoundMem(battlebgm[0]) == 0 && CheckSoundMem(battlewinbgm) == 0 && !winbgmflag)
		{
			PlaySoundMem(battlewinbgm, DX_PLAYTYPE_BACK, true);
			winbgmflag = true;
		}
	}



	//プレイヤー処理
	player[0].Step();
	player[1].Step();

	if (!bgmflag&& startCount >= 200)
	{
		PlaySoundMem(battlebgm[0], DX_PLAYTYPE_LOOP, true);
		bgmflag = true;
	}

		//プレイヤー１の弾とプレイヤー２の当たり判定
	if (hitInterval[1] == 40) {
		for (int index = 0;index < 10;index++) {

			if (!player[0].GetBulletIsUse(index)) { continue; }
			if (IsHitRect(player[1].GetPlayerPosX(), player[1].GetPlayerPosY(), player[1].GetPlayerSizeX(), player[1].GetPlayerSizeY(),
				player[0].GetBulletPosX(index), player[0].GetBulletPosY(index), player[0].GetBulletSizeX(), player[0].GetBulletSizeY())) {
				player[1].InDamage(player[0].GetBulletDamage(index), player[0].GetBulletState(index));//あったったらダメージを受ける
				player[0].SetBulletIsUse(index);//弾を消す
				hitInterval[1] = 0;
				PlaySoundMem(hitSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}

	//プレイヤー2の弾とプレイヤー1の当たり判定
	if (hitInterval[0] == 40) {
		
		for (int index = 0;index < 10;index++) {

			if (!player[1].GetBulletIsUse(index)) { continue; }
			if (IsHitRect(player[0].GetPlayerPosX(), player[0].GetPlayerPosY(), player[0].GetPlayerSizeX(), player[0].GetPlayerSizeY(),
				player[1].GetBulletPosX(index), player[1].GetBulletPosY(index), player[1].GetBulletSizeX(), player[1].GetBulletSizeY())) {
				player[0].InDamage(player[1].GetBulletDamage(index), player[1].GetBulletState(index));//あったったらダメージを受ける
				player[1].SetBulletIsUse(index);//弾を消す
				hitInterval[0] = 0;
				PlaySoundMem(hitSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}

	//マップとの当たり判定
	mapcollision.MapCollision();
	

	//勝利画像処理
	if (player[0].GetPlayerHP() <= 0 || player[1].GetPlayerHP() <= 0) {
		finishCount++;
		if (finishCount == 1)
		PlaySoundMem(lastvoise[1], DX_PLAYTYPE_BACK, true);
		if (finishCount == 400)
		PlaySoundMem(lastvoise[0], DX_PLAYTYPE_BACK, true);
		if (finishCount >= 600) {
			scene = SCENE_FIN_PLAY;
		}
	}

	//試合開始までのカウント
	if (startCount < 200) {
		startCount++;
	}

	
	for (int index = 0;index < 2;index++) {
		hitInterval[index]++;
		if (hitInterval[index] >= 40) {
			hitInterval[index] = 40;
		}
	}

	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			cloud_x[i][j] += 3*(i+j+1);
			if (cloud_x[i][0] >= (1280 + 484))cloud_x[i][0] = - 484;
			if (cloud_x[i][1] >= (1280 + 252))cloud_x[i][1] = - 252;
			if (cloud_x[i][2] >= (1280 + 541))cloud_x[i][2] = - 541;
		}
	}
}



//描画処理
void DrawPlay() {


	DrawGraph(0, 0, mountainbackHandle, true);


		for (int j = 0;j < 3;j++)
		{
			DrawGraph(cloud_x[0][j], cloud_y[0][j], cloudHandle[0][j], true);
		}
	
	DrawGraph(0, 0, mountainHandle, true);
	for (int j = 0;j < 3;j++)
	{
		DrawGraph(cloud_x[1][j], cloud_y[1][j], cloudHandle[1][j], true);
	}

	CMap->Draw();
	player[0].Draw();
	//2Pは色を反転する
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	player[1].Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//勝利画像描画
	if (player[0].GetPlayerHP() <= 0) {
		DrawGraph(0, 0, winHandle[1],true);
	}else
		if(player[1].GetPlayerHP() <= 0) {
		DrawGraph(0, 0, winHandle[0], true);
	}


}



//破棄処理
void FinPlay() {

	delete []player;
	player = nullptr;
	delete CMap;
	CMap = nullptr;
	DeleteGraph(mountainHandle);
	DeleteGraph(mountainbackHandle);
	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			DeleteGraph(cloudHandle[i][j]);
		}
	}
	DeleteGraph(winHandle[0]);
	DeleteGraph(winHandle[1]);
	DeleteSoundMem(battlestartbgm);
	DeleteSoundMem(battlebgm[0]);
	DeleteSoundMem(battlebgm[1]);
	DeleteSoundMem(battlewinbgm);
	DeleteSoundMem(mountainHandle);
	DeleteSoundMem(lastvoise[0]);
	DeleteSoundMem(lastvoise[1]);
	scene = SCENE_INIT_TITLE;

}




// マップの当たり判定
void MAPCollision::MapCollision() {


	for (int index = 0;index < 2;index++) {
		// Y方向のみ当たり判定をチェックする
		for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
		{
			for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
			{
				// ブロック以外は処理しない
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
					continue;

				// どの方向に進んでいたかチェック
				bool dirArray[4] = { false,false,false,false };
				player[index].GetMoveDirection(dirArray);

				// 矩形の当たり判定用のデータを準備
				// プレイヤーの情報
				int Ax = player[index].GetPlayerPosX();
				int Ay = player[index].GetPlayerPosY();
				int Aw = player[index].GetPlayerSizeX();
				int Ah = player[index].GetPlayerSizeY();

				// オブジェクトの情報
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// ※Y方向のみに移動したと仮定した座標で当たり判定をチェックします
				Ay = player[index].GetNextPlayerPosY();
				Ax = player[index].GetPlayerPosX();

				// 当たっているかチェック
				if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// 上方向の修正
					if (dirArray[0]) {
						// めり込み量を計算する
						int overlap = By + Bh - Ay;
						player[index].SetPlayerNextPosY(Ay + overlap);
					}

					// 下方向の修正
					if (dirArray[1]) {
						// めり込み量を計算する
						int overlap = Ay + Ah - By;
						player[index].SetPlayerNextPosY(Ay - overlap);
						
						player[index].SetJump();    //ついたとき切り替え
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
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
					continue;

				// どの方向に進んでいたかチェック
				// ※Playerクラスに進む方向をチェックする関数を準備しています。
				bool dirArray[4] = { false,false,false,false };
				player[index].GetMoveDirection(dirArray);

				// 矩形の当たり判定用のデータを準備
				// プレイヤーの情報
				int Ax = player[index].GetPlayerPosX();
				int Ay = player[index].GetPlayerPosY();
				int Aw = player[index].GetPlayerSizeX();
				int Ah = player[index].GetPlayerSizeY();

				// オブジェクトの情報
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// 矩形の当たり判定用のデータを準備
				// ※X方向のみに移動したと仮定した座標で当たり判定をチェックします
				Ay = player[index].GetNextPlayerPosY();
				Ax = player[index].GetNextPlayerPosX();

				// 当たっているかチェック
				if (IsHitRect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// 左方向の修正
					if (dirArray[2]) {
						// めり込み量を計算する
						int overlap = Bx + Bw - Ax;
						player[index].SetPlayerNextPosX(Ax + overlap);
					}

					// 右方向の修正
					if (dirArray[3]) {
						// めり込み量を計算する
						int overlap = Ax + Aw - Bx;
						player[index].SetPlayerNextPosX(Ax - overlap);
					}
				}
			}
		}
	}
}