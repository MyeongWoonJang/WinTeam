#include "Dungeon.h"

Dungeon::Dungeon(const int dungeon_id) : dungeon_id{ dungeon_id }
{
	CheckFileNameValidity(L"DungeonData.txt");
	std::ifstream in;
	// �����ͺ��̽��� �ִ� ������� ���� �ε�
}