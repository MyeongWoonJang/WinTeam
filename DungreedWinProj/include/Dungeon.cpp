#include "Dungeon.h"

Dungeon::Dungeon(const int dungeon_id, int& camera_x_half_range, int& camera_y_half_range) : dungeon_id{ dungeon_id }
{
	CheckFileNameValidity(L"DungeonData.txt");
	// �����ͺ��̽��� �ִ� ������� ���� �ε�
}