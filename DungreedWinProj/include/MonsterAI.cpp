#include "MonsterAI.h"

void MonsterAI::Stand()
{
	monster->Stand();
	monster->cur_animation_name = monster->stand_animation_name;
}

void MonsterAI::MoveToPlayer(const Dungeon* dungeon, const Player* player)
{
	InstantDCSet dc_set(RECT{ 0, 0, dungeon->dungeon_width, dungeon->dungeon_height });

	dungeon->dungeon_terrain_image->Draw(dc_set.buf_dc, dc_set.bit_rect);

	monster->Look(player->pos);

	if (!monster->is_floating) {						// ���ٴ��� �ʴ� ������ �̵�
		if (monster->looking_direction) {
			if (monster->CanGoRight(dc_set.buf_dc))
				monster->RunRight();
			else if (monster->CanJump(monster->state))
				monster->Jump();
		}
		else {
			if (monster->CanGoLeft(dc_set.buf_dc))
				monster->RunLeft();
			else if (monster->CanJump(monster->state))
				monster->Jump();
		}
	}
	else {												// ���ٴϴ� ������ �̵�

	}


	if (!monster->move_animation_name.empty())
		monster->cur_animation_name = monster->move_animation_name;
	else
		monster->cur_animation_name = monster->stand_animation_name;
}

void MonsterAI::MoveFromPlayer(const Dungeon* dungeon, const Player* player)
{
	InstantDCSet dc_set(RECT{ 0, 0, dungeon->dungeon_width, dungeon->dungeon_height });

	dungeon->dungeon_terrain_image->Draw(dc_set.buf_dc, dc_set.bit_rect);

	monster->Look(player->pos);
	monster->looking_direction = (monster->looking_direction == TRUE) ? FALSE : TRUE;

	if (!monster->is_floating) {						// ���ٴ��� �ʴ� ������ �̵�
		if (monster->looking_direction) {
			if (monster->CanGoRight(dc_set.buf_dc) && !CanGoToPos(dc_set.buf_dc,
				POINT {monster->pos.x + monster->width / 2 + monster->x_move_px, monster->pos.y + monster->height + dungeon->dungeon_height / 50}))
				monster->RunRight();
		}
		else {
			if (monster->CanGoLeft(dc_set.buf_dc) && !CanGoToPos(dc_set.buf_dc,
				POINT{ monster->pos.x + monster->width / 2 - monster->x_move_px, monster->pos.y + monster->height + dungeon->dungeon_height / 50 }))
				monster->RunLeft();
		}
	}
	else {												// ���ٴϴ� ������ �̵�

	}

	if (!monster->move_animation_name.empty())
		monster->cur_animation_name = monster->move_animation_name;
	else
		monster->cur_animation_name = monster->stand_animation_name;

	// �̵��Ϸ��µ� ������ ���������� ����
}

void MonsterAI::Attack(const Dungeon* dungeon, const Player* player)
{
	if (!monster->attack_animation_name.empty())
		monster->cur_animation_name = monster->attack_animation_name;
	else
		monster->cur_animation_name = monster->stand_animation_name;
}
