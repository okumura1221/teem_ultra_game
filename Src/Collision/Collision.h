#ifndef __COLLISION_H__
#define __COLLISION_H__

//IsHitRect�̃v���g�^�C�v�錾
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);

//IsHitCircle�̃v���g�^�C�v�錾
bool IsHitCircle(int Ax, int Ay, int Ar, int Bx, int By, int Br);

#endif