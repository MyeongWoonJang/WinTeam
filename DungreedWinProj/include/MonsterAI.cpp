#include "MonsterAI.h"

void MonsterAI::Stand()
{
	monster->cur_animation_name = monster->stand_animation_name;
}

void MonsterAI::MoveToPlayer(const Player* player)
{
	if (!monster->move_animation_name.empty())
		monster->cur_animation_name = monster->move_animation_name;
	else
		monster->cur_animation_name = monster->stand_animation_name;

	// �÷��̾ ����, �ٷ� ���� �ö� �� �ִ� ����� �ִٸ� ����

	// �̵��Ϸ��µ� ������ ���������� ����
}

void MonsterAI::MoveFromPlayer(const Player* player)
{
	if (!monster->move_animation_name.empty())
		monster->cur_animation_name = monster->move_animation_name;
	else
		monster->cur_animation_name = monster->stand_animation_name;

	// �̵��Ϸ��µ� ������ ���������� ����
}

void MonsterAI::Attack()
{
	if (!monster->attack_animation_name.empty())
		monster->cur_animation_name = monster->attack_animation_name;
	else
		monster->cur_animation_name = monster->stand_animation_name;
}
