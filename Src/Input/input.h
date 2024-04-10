#pragma once

class Input {

	public:

	//初期化
	static void Init();

	//前フレと現フレを記録(シーン管理の前に呼ぶ必要あり)
	static void Step();

	//今押された
	static bool Push(int key_code);

	//押され続けている
	static bool Keep(int key_code);

	//離された
	static bool Release(int key_code);

};