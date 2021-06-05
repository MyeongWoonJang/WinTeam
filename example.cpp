#include <Windows.h>
#include <math.h>

#define PI 3.141592654   

HBITMAP GetRotatedBitmap(HDC hdc, HBITMAP hBitmap, int source_x, int source_y, int dest_width, int dest_height, float angle, COLORREF bkColor)
{
	HDC sourceDC = CreateCompatibleDC(hdc);                                      // ȸ���� ��Ʈ�� ������ ������ DC   
	HDC destDC = CreateCompatibleDC(hdc);                                      // ȸ���� ��Ʈ���� ��¹��� DC   
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, dest_width, dest_height);       // ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� �ڵ�   

	HBITMAP hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);                   // ȸ���� ��Ʈ�� ������ DC�� ����   
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);                   // ȸ���� ��Ʈ���� ��¹��� DC��, ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� ����   

	HBRUSH hbrBack = CreateSolidBrush(bkColor);                                  // ȸ������ ����, ���鿵���� ĥ�� �귯���ڵ� ����   
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);                      // �귯���ڵ� ����   
	PatBlt(destDC, 0, 0, dest_width, dest_height, PATCOPY);                           // ���õ� �귯�÷�, ȸ���� ��Ʈ���� ��¹��� DC��, �̸� ������ ä�� ����   
	DeleteObject(SelectObject(destDC, hbrOld));                                     // �귯�� ����   

	angle = (float)(angle * PI / 180);                                      // ȸ���� ����(360�й�)��, ���ȴ����� ������ ����   
	float cosine = (float)cos(angle);                                              // ȸ���̵���ȯ ��Ŀ� �� cos��Ÿ ���� ����          
	float sine = (float)sin(angle);                                              // ȸ���̵���ȯ ��Ŀ� �� sin��Ÿ ���� ����   
	SetGraphicsMode(destDC, GM_ADVANCED);                                               // ������ ��ǥ���� ȸ���� ���Ͽ�, �׷��ȸ�带 Ȯ����� ����



	XFORM xform;                                                                        // �������� ǥ���ϴ� 3��3���� ��� ����   
	xform.eM11 = cosine;                                                                // 1�� 1�� ���� ���� (ȸ������)   
	xform.eM12 = sine;                                                                  // 1�� 2�� ���� ���� (ȸ������)   
	xform.eM21 = -sine;                                                                 // 2�� 1�� ���� ���� (ȸ������)   
	xform.eM22 = cosine;                                                                // 2�� 2�� ���� ���� (ȸ������)   
	xform.eDx = (FLOAT)dest_width / 2.0f;                                               // 3�� 1�� ���� ���� (X�� �̵� ����)   
	xform.eDy = (FLOAT)dest_height / 2.0f;                                              // 3�� 2�� ���� ���� (Y�� �̵� ����)   
																						// ������ ��ķ�, �μ�DC�� �������� ��ǥ�踦 ��ȯ.   
																						// �μ�DC�� ��´������ �޸𸮺�Ʈ���� �����Ƿ�,
																						// �����ϰ� �ִ� �޸𸮺�Ʈ���� ��ǥü�谡 ȸ���ȴ�.   
	SetWorldTransform(destDC, &xform);
	// ȸ���� �޸�DC��, ȸ���� �̹����� ���   
	BitBlt(destDC, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, sourceDC, source_x, source_y, SRCCOPY);
	// ���� �ڿ� ����   
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteObject(sourceDC);
	DeleteObject(destDC);
	// ȸ���� ��Ʈ�� �ڵ� ����   
	return hbmResult;
}



void RotateBlt(HDC hdc, HDC hOffScreen, int dest_x, int dest_y, int dest_width, int dest_height,
	HBITMAP hBit, int source_x, int source_y, DWORD dFlag, float angle, COLORREF bkColor)
{
	static HDC hTempMemDC;              // ȸ���� ��Ʈ���� ������ �޸�DC   
	HBITMAP hTempBitmap, hOldBitmap;    // ȸ���� ��Ʈ���� ������, ��Ʈ�� �ڵ�   
										// ���� �ѹ��� ��Ʈ��DC�� �����մϴ�.   
	if (!hTempMemDC) hTempMemDC = CreateCompatibleDC(hdc);
	// ��Ʈ���� ȸ���ϴ� �Լ��� ȣ���Ͽ�, ���ϵǴ� ȸ���� ��Ʈ�� �ڵ��� ����   
	hTempBitmap = GetRotatedBitmap(hdc, hBit, source_x, source_y, dest_width, dest_height, angle, bkColor);
	// ȸ���� ��Ʈ�� �ڵ��� �����ϰ�,
	hOldBitmap = (HBITMAP)SelectObject(hTempMemDC, hTempBitmap);
	// ������ũ��DC��, ȸ���� ��Ʈ�� �ڵ��� ������, �޸�DC�� �̹����� ����մϴ�.   
	// ���� �ּ��� �����ϸ�, �����ǥ�� �߽����� �ϴ� ȸ���̹����� �˴ϴ�.   
	TransparentBlt(hOffScreen, dest_x/* - dest_width/2*/, dest_y/* - dest_height/2*/, dest_width, dest_height, hTempMemDC, 0, 0, dest_width, dest_height, RGB(255, 255, 255));
	SelectObject(hTempMemDC, hOldBitmap);
	DeleteObject(hTempBitmap);
}