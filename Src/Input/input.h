#pragma once

class Input {

	public:

	//������
	static void Init();

	//�O�t���ƌ��t�����L�^(�V�[���Ǘ��̑O�ɌĂԕK�v����)
	static void Step();

	//�������ꂽ
	static bool Push(int key_code);

	//�����ꑱ���Ă���
	static bool Keep(int key_code);

	//�����ꂽ
	static bool Release(int key_code);

};