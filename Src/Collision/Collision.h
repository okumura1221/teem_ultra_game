#ifndef __COLLISION_H__
#define __COLLISION_H__

//IsHitRectのプロトタイプ宣言
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);

//IsHitCircleのプロトタイプ宣言
bool IsHitCircle(int Ax, int Ay, int Ar, int Bx, int By, int Br);

#endif