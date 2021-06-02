#include "Dungeon.h"

Dungeon::Dungeon(const int dungeon_id) : dungeon_id{ dungeon_id }
{
	CheckFileNameValidity(L"DungeonData.txt");
	std::ifstream in{ "DungoenData.txt" };
	std::string line;

	while (std::getline(in, line))
		if (IsID(line))
			LoadData(in);
}

void Dungeon::LoadData(std::ifstream& in)
{
	std::string line;

	while (std::getline(in, line))
		if (IsLineTypeWithData(line))
			InterpretLine(line);
}

void Dungeon::InterpretLine(const std::string& line)
{
	std::string field;
	std::string data;

	field = GetHeadString(line);
	data = GetRestString(line);
	InputDataAtField(data, field);
}

// �Ʒ� �Լ��� ¡�׷����ϴ�.
// �ڵ� 1�� �� ���� �� �Ƿ����� ���� ��....
// ������ : 1. ���ϵ� DungeonData Ÿ������ ������ �� ���� ������
//		   2. data�� � �Լ��� ������ �츮�� ���ϴ� �ڷ����� ���� �� ���ϵǴ� ������ ���� ���� ������
void Dungeon::InputDataAtField(const std::string& data, const std::string& field)
{
	int int_arg[2];
	TCHAR str_arg[200];

	FetchFitArg(data, int_arg, str_arg);

	if (field == "map_path")
		dungeon_image.Load(str_arg);
	else if (field == "map_terrain_path")
		dungeon_terrain_image.Load(str_arg);
	else if (field == "left_start_pos")
		left_start_pos = { int_arg[0], int_arg[1] };
	else if (field == "right_start_pos")
		right_start_pos = { int_arg[0], int_arg[1] };
	else if (field == "prev_dungeon_portal_pos")
		prev_dungeon_portal_pos = { int_arg[0], int_arg[1] };
	else if (field == "next_dungeon_portal_pos")
		next_dungeon_portal_pos = { int_arg[0], int_arg[1] };
	else if (field == "dungeon_width")
		dungeon_width = int_arg[0];
	else if (field == "dungeon_height")
		dungeon_height = int_arg[0];
	else if (field == "next_dungeon_id")
		next_dungeon_id = int_arg[0];
	else if (field == "prev_dungeon_id")
		prev_dungeon_id = int_arg[0];
	else if (field == "camera_x_half_range")
		camera_x_half_range = int_arg[0];
	else if (field == "camera_y_half_range")
		camera_y_half_range = int_arg[0];
	else
		throw L"Wrong Field Found In Dungeon DB";
}

void Dungeon::FetchFitArg(const std::string& data, int int_arg[], TCHAR str_arg[])
{
	std::string args_origin[2];
	try {
		args_origin[1] = GetRestString(data);
		// GetRestString�� �Ű����� string�� ���Ⱑ ������ ������ ����, ���� ������ ���� ���� ����
		args_origin[0] = GetHeadString(data);
		int_arg[0] = std::stoi(args_origin[0]);
		int_arg[1] = std::stoi(args_origin[1]);
	}
	catch (const TCHAR* error_message) {
		if (IsStringInt(data))
			int_arg[0] = std::stoi(data);
		else
			wsprintf(str_arg, L"%s", data);
	}
}

Dungeon::~Dungeon()
{
	dungeon_image.Destroy();
	dungeon_terrain_image.Destroy();
}