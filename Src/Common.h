#pragma once

#include "DxLib.h"
#include "Input/input.h"
#include "Collision/Collision.h"


enum SCENE {
	SCENE_INIT_TITLE,
	SCENE_LOOP_TITLE,
	SCENE_FIN_TITLE,
	SCENE_INIT_PLAY,
	SCENE_LOOP_PLAY,
	SCENE_FIN_PLAY,
};
extern SCENE scene;


