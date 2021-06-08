#include "Character.h"
#include <iostream>

void Character::ForceGravity(const Dungeon* dungeon)	// ĳ���� ����(LANDING, DOWN, DOWNJUMP, UP)�� ���� ������
{
	InstantDCSet dc_set(RECT{ 0, 0, dungeon->dungeon_width, dungeon->dungeon_height });

	dungeon->dungeon_terrain_image->Draw(dc_set.buf_dc, dc_set.bit_rect);

	// ĳ���� �� ��ġ�� ����� ��� DOWN���·� �ٲٱ�
	if ((state == State::LANDING || state == State::DOWNJUMP) && MapPixelCollision(dc_set.buf_dc, RGB(255, 0, 255), POINT{ pos.x + width / 2, pos.y + height })) {
		state = State::DOWN;
		if (MapPixelCollision(dc_set.buf_dc, !RGB(255, 0, 255), POINT{ pos.x + width / 2, pos.y + height + 5 })) {	// ���������� ���
			state = State::LANDING;
			MovePos(dungeon, Direction::DOWN, 5);
		}
	}
	// ���� �� �� ��� �Ǹ� LANDING ���·� �ٲٱ�
	else if (state == State::DOWN && (MapPixelCollision(dc_set.buf_dc, RGB(255, 0, 0), POINT{ pos.x + width / 2, pos.y + height }) || MapPixelCollision(dc_set.buf_dc, RGB(0, 255, 0), POINT{ pos.x + width / 2, pos.y + height }))) {
		state = State::LANDING;
	}

	if (state == State::LANDING) {	// ������ or DOWN���� LANDING���� �ٲ���� �� ĳ���Ͱ� �� �ٷ� ���� ���� �Ϸ� ���� but ���ڿ������� 
		while (!MapPixelCollision(dc_set.buf_dc, RGB(255, 0, 255), POINT{ pos.x + width / 2, pos.y + height - 1 })) {
			MovePos(dungeon, Direction::UP, 1);
		}
	}

	if (state == State::UP) {	// JUMP���� �ö󰡰� �ִ� ���� jump_power�� 0�� �Ǹ� ���°� DOWN���� �ٲ��
		MovePos(dungeon, Direction::UP, jump_power);
		jump_power -= 2;
		if (jump_power <= 0) {
			state = State::DOWN;
		}
	}
	else if (state == State::DOWN || state == State::DOWNJUMP) {
		MovePos(dungeon, Direction::DOWN, jump_power);
		if (jump_power < 10) {
			jump_power += 2;
		}
	}
}

void Character::MovePos(const Dungeon* dungeon, Direction direction, const int px)
{
	switch (direction) {
	case Direction::LEFT:
		if (pos.x - px > 0)
			pos.x -= px;
		break;
	case Direction::UP:
		if (pos.y - px > 0)
			pos.y -= px;
		break;
	case Direction::RIGHT:
		if (pos.x + px < dungeon->dungeon_width)
			pos.x += px;
		break;
	case Direction::DOWN:
		if (pos.y + px < dungeon->dungeon_height)
			pos.y += px;
		break;
	}
}

void FlipImage(HDC scene_dc, const RECT& bit_rect, Image* image, int x, int y, int width, int height)
{
	int image_width = image->GetWidth();
	int image_height = image->GetHeight();

	HDC dest_dc = CreateCompatibleDC(scene_dc);
	HBITMAP hbitmap = CreateCompatibleBitmap(scene_dc, image_width, image_height);
	HBITMAP hbm_old_dest = (HBITMAP)SelectObject(dest_dc, hbitmap);

	HDC source_dc = CreateCompatibleDC(scene_dc);
	HBITMAP hbm_result = CreateCompatibleBitmap(scene_dc, image_width, image_height);
	HBITMAP hbm_old_source = (HBITMAP)SelectObject(source_dc, hbm_result);

	image->Draw(dest_dc, 0, 0, image_width, image_height, 0, 0, image_width, image_height);
	StretchBlt(source_dc, image_width, 0, -image_width, image_height, dest_dc, 0, 0, image_width, image_height, SRCCOPY);
	TransparentBlt(scene_dc, x, y, width, height, source_dc, 0, 0, image_width, image_height, RGB(0, 0, 0));	// RGB(34, 32, 52)

	SelectObject(source_dc, hbm_old_source);
	DeleteObject(source_dc);
	SelectObject(dest_dc, hbm_old_dest);
	DeleteObject(dest_dc);
}

void Character::Render(HDC scene_dc, const RECT& bit_rect, BOOL looking_direction)
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

void Character::Update()
{

}

bool Character::MapPixelCollision(HDC terrain_dc, COLORREF val, POINT pt)	// ���� ǥ�� �̹����� ����� �浹 Ȯ��, ���� ����
{
	if (pt.x < client.left || pt.y > client.right)
		return true;
	if (pt.y < client.top || pt.y > client.bottom)
		return true;

	COLORREF pixel_color = GetPixel(terrain_dc, pt.x, pt.y);
	if (pixel_color == val)
		return true;
	else
		return false;
}

