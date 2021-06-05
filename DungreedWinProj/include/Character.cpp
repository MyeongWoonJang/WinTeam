
void Character::Init()
{
	// �׽�Ʈ��
	pos = { 60, 500 };
	state = DOWN;
	jump_power = 0;
	width = 60;
	height = 60;
}

void Character::Move(HDC h_dc, const TCHAR* map_name)	// ĳ���� ����(LANDING, DOWN, DOWNJUMP, UP)�� ���� ������
{
	// ĳ���� �� ��ġ�� ����� ��� DOWN���·� �ٲٱ�
	if ((state == LANDING || state == DOWNJUMP) && MapPixelCollision(map_name, RGB(255, 0, 255), pos.x + width / 2, pos.y + height, h_dc)) {
		state = DOWN;
		if (MapPixelCollision(map_name, !RGB(255, 0, 255), pos.x + width / 2, pos.y + height + 5, h_dc)) {	// ���������� ���
			state = LANDING;
			pos.y += 5;
		}
	}
	// ���� �� �� ��� �Ǹ� LANDING ���·� �ٲٱ�
	else if (state == DOWN && (MapPixelCollision(map_name, RGB(255, 0, 0), pos.x + width / 2, pos.y + height, h_dc)) || MapPixelCollision(L"map_png\\map1-����.png", RGB(0, 255, 0), pos.x + width / 2, pos.y + height, h_dc)) {
		state = LANDING;
	}

	if (state == LANDING) {	// ������ or DOWN���� LANDING���� �ٲ���� �� ĳ���Ͱ� �� �ٷ� ���� ���� �Ϸ� ���� but ���ڿ������� 
		while (!MapPixelCollision(map_name, RGB(255, 0, 255), pos.x + width / 2, pos.y + height - 1, h_dc)) {
			pos.y--;
		}
	}

	if (state == UP) {	// JUMP���� �ö󰡰� �ִ� ���� jump_power�� 0�� �Ǹ� ���°� DOWN���� �ٲ��
		pos.y -= jump_power;
		jump_power -= 2;
		if (jump_power <= 0) {
			state = DOWN;
		}
	}
	else if (state == DOWN || state == DOWNJUMP) {
		pos.y += jump_power;
		if (jump_power < 10) {
			jump_power += 2;
		}
	}

}

BOOL Character::MapPixelCollision(const TCHAR* map_name, COLORREF color, int x, int y, HDC h_dc)	// ���� ǥ�� �̹����� ����� �浹 Ȯ��, ���� ����
{
	Image map_collision;
	map_collision.Load(map_name);

	int map_width = map_collision.GetWidth();
	int map_height = map_collision.GetHeight();

	HDC map_dc = CreateCompatibleDC(h_dc);
	HBITMAP h_bit = CreateCompatibleBitmap(h_dc, 1280, 800);
	HBITMAP old_bit = (HBITMAP)SelectObject(map_dc, h_bit);

	map_collision.Draw(map_dc, 0, 0, 1280, 800, 0, 0, map_width, map_height);

	COLORREF c = GetPixel(map_dc, x, y);

	map_collision.Destroy();
	SelectObject(h_dc, old_bit);
	DeleteObject(h_bit);
	DeleteDC(map_dc);

	if (color == c) { return TRUE; }
	return FALSE;
}

void Character::Render(HDC& buf_m_dc)
{
	Image image;
	image.Load(L"player - dungreed\\CharIdle0-resources.assets-2445.png");	// �׽�Ʈ��
	int image_width = image.GetWidth();
	int image_height = image.GetHeight();
	image.Draw(buf_m_dc, pos.x, pos.y, width, height, 0, 0, image_width, image_height);
	image.Destroy();
}

void Character::Update()
{

}
