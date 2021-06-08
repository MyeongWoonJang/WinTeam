#pragma once
#ifndef _dungeon
#define _dungeon
#include <windows.h>
#include "FileUtility.h"
#include "Uncopyable.h"

extern HDC buf_dc;
extern RECT client;
extern HWND h_wnd;

class Dungeon : private Uncopyable
{
private:
	int dungeon_id;
	bool is_loaded;

	void LoadData(std::ifstream& in);
	void InterpretLine(const std::string& line);
	void InputDataAtField(const std::string& data, const std::string& field);
	void FetchFitArg(const std::string& data, int int_arg[], TCHAR str_arg[]);

public:
	Image* dungeon_image;
	Image* dungeon_terrain_image;

	POINT left_start_pos;
	POINT right_start_pos;
	POINT prev_dungeon_portal_pos;
	POINT next_dungeon_portal_pos;

	int dungeon_width;
	int dungeon_height;

	int next_dungeon_id;
	int prev_dungeon_id;

	int camera_x_half_range;
	int camera_y_half_range;

	Dungeon(const int dungeon_id);
	~Dungeon();

	void Render(HDC scene_dc, const RECT& bit_rect);
};
#endif