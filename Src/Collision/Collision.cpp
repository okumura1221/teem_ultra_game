
#include "Collision.h"

//IsHitRect‚Ì’è‹`
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
	if (Ax<Bx + Bw &&
		Ax + Aw>Bx &&
		Ay + Ah > By &&
		Ay < By + Bh)
	{
		return true;
	}
	return false;
}

//IsHitCircle‚Ì’è‹`
bool IsHitCircle(int Ax, int Ay, int Ar, int Bx, int By, int Br) {
	if ((Ar + Br) * (Ar + Br) >
		(Ax - Bx) * (Ax - Bx) + (Ay - By) * (Ay - By))
	{
		return true;
	}
	return false;
}