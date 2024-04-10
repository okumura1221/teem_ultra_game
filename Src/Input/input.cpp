#include "DxLib.h"
#include "input.h"

#define KEY_BUF_LEN (256)


char currentKeyBuf[KEY_BUF_LEN] = { 0 };

char preKeyBuf[KEY_BUF_LEN] = { 0 };


//初期化
void Input::Init(){

	for(int index = 0; index < KEY_BUF_LEN; index++) {
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}


//前フレと現フレを記録(シーン管理の前に呼ぶ必要あり)
void Input::Step() {
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		preKeyBuf[index] = currentKeyBuf[index];
	}
	GetHitKeyStateAll(currentKeyBuf);
}


//今押された
bool Input::Push(int key_code){
	//前フレで押されていないかつ、現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		//押されていないので false
		return false;
	}
}


//押され続けている
bool Input::Keep(int key_code) {
	//現フレで押されている
	if (currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		return false;
	}
}


//離された
bool Input::Release(int key_code) {
	//前フレで押されているかつ、現フレで押されていない。
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0) {
		return true;
	}
	else {
		return false;
	}
}