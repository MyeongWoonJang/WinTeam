#pragma once
#ifndef _crosshair
#define _crosshair
#include <windows.h>
#include "Camera.h"
#include "FileUtility.h"
#include "InstantDCset.h"

class Crosshair
{
private:
	POINT pos;
	int half_size;
public:
	inline const POINT GetPos() { return pos; };

	Crosshair(const RECT camera_rect, const Dungeon* dungeon, const RECT& client);

	void Update(const RECT camera_rect, const Dungeon* dungeon, const RECT& client);
	void Render(HDC scene_dc, const RECT& bit_rect);
	
	BOOL LookingDirection(const POINT* player);	// TRUE�� ������ ���� ����, FALSE�� ���� ���� �ִ� ����
};
#endif