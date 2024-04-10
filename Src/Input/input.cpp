#include "DxLib.h"
#include "input.h"

#define KEY_BUF_LEN (256)


char currentKeyBuf[KEY_BUF_LEN] = { 0 };

char preKeyBuf[KEY_BUF_LEN] = { 0 };


//������
void Input::Init(){

	for(int index = 0; index < KEY_BUF_LEN; index++) {
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}


//�O�t���ƌ��t�����L�^(�V�[���Ǘ��̑O�ɌĂԕK�v����)
void Input::Step() {
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		preKeyBuf[index] = currentKeyBuf[index];
	}
	GetHitKeyStateAll(currentKeyBuf);
}


//�������ꂽ
bool Input::Push(int key_code){
	//�O�t���ŉ�����Ă��Ȃ����A���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		//������Ă��Ȃ��̂� false
		return false;
	}
}


//�����ꑱ���Ă���
bool Input::Keep(int key_code) {
	//���t���ŉ�����Ă���
	if (currentKeyBuf[key_code] == 1) {
		return true;
	}
	else {
		return false;
	}
}


//�����ꂽ
bool Input::Release(int key_code) {
	//�O�t���ŉ�����Ă��邩�A���t���ŉ�����Ă��Ȃ��B
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0) {
		return true;
	}
	else {
		return false;
	}
}