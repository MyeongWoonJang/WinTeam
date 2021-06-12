﻿#include "Weapon.h"

Weapon::Weapon(const Camera* camera, const Player* player, const Crosshair* crosshair)
{
	image = new Image(L"sword\\RustyGreatSword00-resources.assets-1011.png");
	width = camera->x_half_range / 3;
	height = camera->y_half_range / 2;
	Update(player, crosshair);
}

void Weapon::Init(const Camera* camera, const Player* player, const Crosshair* crosshair)
{
	width = camera->x_half_range / 3;
	height = camera->y_half_range / 2;
	Update(player, crosshair);
}

float Degree(const POINT& point1, const POINT& point2)
{
	float degree;
	if (point1.x < point2.x) {
		degree = atan2(point2.y - point1.y, point2.x - point1.x);
	}
	else {
		degree = -atan2(point1.y - point2.y, point1.x - point2.x);
	}

	return -degree;
}

void Weapon::Update(const Player* player, const Crosshair* crosshair)
{
	pos = player->pos;
	pos.x -= player->width;
	POINT player_center = { player->pos.x + (player->width / 2), player->pos.y + (player->height / 2) };

	if (player_center.x <= crosshair->pos.x) {
		looking_direction = TRUE;
	}
	else {
		looking_direction = FALSE;
	}

	angle = Degree(player_center, crosshair->pos);
}

void Weapon::Render(HDC scene_dc, const RECT& bit_rect)
{
	int image_width = image->GetWidth();
	int image_height = image->GetHeight();

	HBITMAP hbm_rotate = RotateImage(scene_dc, image, angle);
	Image* rotate_image = new Image();
	rotate_image->Attach(hbm_rotate);
	rotate_image->SetTransparentColor(RGB(0, 0, 0));

	if (looking_direction) {
		FlipImage(scene_dc, bit_rect, rotate_image, pos.x, pos.y, width, height);
	}
	else {
		rotate_image->Draw(scene_dc, pos.x, pos.y, width, height, 0, 0, image_width, image_height);
	}
}