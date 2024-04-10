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

	void Init();

	void Step();

	void Draw();
	
};