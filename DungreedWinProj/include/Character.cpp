#include "Character.h"

void Character::ForceGravity(const Dungeon* dungeon)	// ĳ���� ����(LANDING, DOWN, DOWNJUMP, UP)�� ���� ������
{
	InstantDCSet dc_set(RECT{ 0, 0, dungeon->dungeon_width, dungeon->dungeon_height });

	dungeon->dungeon_terrain_image->Draw(dc_set.buf_dc, dc_set.bit_rect);

	// ĳ���� �� ��ġ�� ����� ��� DOWN���·� �ٲٱ�
	if ((state == State::LANDING || state == State::DOWNJUMP) && MapPixelCollision(dc_set.buf_dc, RGB(255, 0, 255), POINT{ pos.x + width / 2, pos.y + height })) {
		state = State::DOWN;
	}
	// ���� �� �� ��� �Ǹ� LANDING ���·� �ٲٱ�
	else if (state == State::DOWN && (MapPixelCollision(dc_set.buf_dc, RGB(255, 0, 0), POINT{ pos.x + width / 2, pos.y + height }) || MapPixelCollision(dc_set.buf_dc, RGB(0, 255, 0), POINT{ pos.x + width / 2, pos.y + height }))) {
		state = State::LANDING;
		jump_power = 0;
	}

	if (state == State::LANDING) {	// ������ or DOWN���� LANDING���� �ٲ���� �� ĳ���Ͱ� �� �ٷ� ���� ���� �Ϸ� ����
		while (MapPixelCollision(dc_set.buf_dc, RGB(255, 0, 0), POINT{ pos.x + width / 2, pos.y + height - 1 })
			|| MapPixelCollision(dc_set.buf_dc, RGB(0, 255, 0), POINT{ pos.x + width / 2, pos.y + height - 1 })) {
			MovePos(dungeon, Direction::UP, 1);
		}
	}

	if (state == State::UP) {	// JUMP���� �ö󰡰� �ִ� ���� jump_power�� 0�� �Ǹ� ���°� DOWN���� �ٲ��
		MovePos(dungeon, Direction::UP, jump_power);
		// jump_power�� ������ �и� Ű��� �߷��� �� �ް� Ƣ������� ������ ��������.
		// �ڿ������� �������� ������� �� �и��� ���� �ִ��� �����Ѵ�. ex) 50.0f : 2000.0f, 250.0f : 4000.0f
		jump_power -= jump_power / 50.0f + dungeon->camera_y_half_range / 2000.0f;
		if (jump_power <= 0) {
			state = State::DOWN;
		}
	}
	else if (state == State::DOWN || state == State::DOWNJUMP) {
		MovePos(dungeon, Direction::DOWN, jump_power);
		if (jump_power < dungeon->camera_y_half_range / 20.0f) {
			// jump_power�� ������ �и� Ű��� �߷��� ���� ������ ��������.
			// �ڿ������� �������� ���ؼ� ������ �и� 500~1500 ���̷� �����Ѵ�. ���ڴ� �������Դ� �ϱ� ���� �ּ����� ��ġ��.
			// �� ������ �߷� ���� ������ �����ϸ� �� ���� �ٸ� �߷� ������ ������ ���߸ʵ� ������ ������ ���̴�.
			jump_power += jump_power / 500.0f + dungeon->camera_y_half_range / 1500.0f;
		}
	}
}

void Character::MovePos(const Dungeon* dungeon, Direction direction, const int px)
{
	switch (direction) {
	case Direction::LEFT:
		pos.x -= px;
		break;
	case Direction::UP:
		pos.y -= px;
		break;
	case Direction::RIGHT:
		pos.x += px;
		break;
	case Direction::DOWN:
		pos.y += px;
		break;
	}
}

bool Character::MapPixelCollision(HDC terrain_dc, const COLORREF& val, const POINT& pt)	// ���� ǥ�� �̹����� ����� �浹 Ȯ��, ���� ����
{
	if (pt.x < client.left || pt.y > client.right)
		return false;
	if (pt.y < client.top || pt.y > client.bottom)
		return false;

	if (GetPixel(terrain_dc, pt.x, pt.y) == val)
		return true;
	else
		return false;
}

void Character::Render(HDC scene_dc, const RECT& bit_rect) const
{
	Image image(L"player - dungreed\\CharIdle0-resources.assets-2445.png");
	int image_width = image.GetWidth();
	int image_height = image.GetHeight();
	if (looking_direction) {
		image.Draw(scene_dc, pos.x, pos.y, width, height, 0, 0, image_width, image_height);
	}
	else {
		FlipImage(scene_dc, bit_rect, &image, pos.x, pos.y, width, height);
	}
}

void Character::Look(const POINT& target)
{
	if (pos.x < target.x)
		looking_direction = TRUE;
	else
		looking_direction = FALSE;
}