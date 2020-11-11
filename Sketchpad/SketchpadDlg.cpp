
// SketchpadDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Sketchpad.h"
#include "SketchpadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Inputbox_Line.h"
#include "Inputbox_Circle.h"
#include "Inputbox_Ellipse.h"


// CSketchpadDlg 对话框



CSketchpadDlg::CSketchpadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SKETCHPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSketchpadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

const void CSketchpadDlg::moveTo(int x, int y)
{
	MoveToEx(hdc, x + _ORIGIN_X_, _ORIGIN_Y_ - y, NULL);
}

const void CSketchpadDlg::lineTo(int x, int y)
{
	LineTo(hdc, x + _ORIGIN_X_, _ORIGIN_Y_ - y);
}

const void CSketchpadDlg::setPixel(double x, double y)
{
	Sleep(1);
	SetPixel(hdc, round(x) + _ORIGIN_X_, _ORIGIN_Y_ - round(y), COLORREF("black"));
}

const void CSketchpadDlg::drawStars(int originX, int originY, int x, int y)
{
	setPixel(originX + x, originY + y);
	setPixel(originX + x, originY - y);
	setPixel(originX - x, originY + y);
	setPixel(originX - x, originY - y);
}

const void CSketchpadDlg::drawDDA()
{
	int dx = m_line.ex - m_line.sx;
	int dy = m_line.ey - m_line.sy;
	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	double xStep = double(dx) / double(steps);
	double yStep = double(dy) / double(steps);

	double curr_x = m_line.sx;
	double curr_y = m_line.sy;

	do {
		setPixel(curr_x, curr_y);
		curr_x += xStep;
		curr_y += yStep;
	} while (steps--);
}

const void CSketchpadDlg::drawBresenham()
{
	int dx = m_line.ex - m_line.sx;
	int dy = m_line.ey - m_line.sy;

	int double_dx = dx * 2;
	int double_dy = dy * 2;
	int double_dyMinusDx = (dy - dx) * 2;

	int p = double_dy - dx;
	int curr_x = m_line.sx;
	int curr_y = m_line.sy;
	double m = (double)(m_line.ey - m_line.sy) / (double)(m_line.ex - m_line.sx);

	int target = max(m_line.ex, m_line.sx);
	do {
		setPixel(curr_x++, curr_y);
		if (m > 0)
			if (p < 0) p += double_dy;
			else {
				curr_y++;
				p += double_dyMinusDx;
			}
		else
			if (p > 0) p += double_dyMinusDx;
			else {
				curr_y--;
				p += double_dy;
			}
	} while (curr_x < target && abs(m) < 1);

	target = max(m_line.ey, m_line.sy);
	do {
		setPixel(curr_x, curr_y++);
		if (m > 0)
			if (p < 0) p += double_dx;
			else {
				curr_x++;
				p -= double_dyMinusDx;
			}
		else
			if (p > 0) p -= double_dyMinusDx;
			else {
				curr_x--;
				p += double_dx;
			}
	} while (curr_y < target && abs(m) > 1);
}

const void CSketchpadDlg::drawCircle()
{
	int p = 1 - m_circle.r;

	int x = m_circle.x;
	int y = m_circle.y;
	int curr_x = 0;
	int curr_y = m_circle.r;

	do {
		drawStars(x, y, curr_x, curr_y);
		drawStars(x, y, curr_y, curr_x);

		curr_x++;
		if (p < 0) p += 2 * curr_x + 1;
		else
			p += 2 * (curr_x - (--curr_y)) + 1;
	} while (curr_x < curr_y);

}

const void CSketchpadDlg::drawEllipse()
{
	INT64 a = m_ellipse.a;
	INT64 b = m_ellipse.b;
	INT64 x = m_ellipse.x;
	INT64 y = m_ellipse.y;
	INT64 a2 = a * a; // squared a
	INT64 b2 = b * b; // squared b
	INT64 da2 = 2 * a2; // double squared a
	INT64 db2 = 2 * b2; // double squared b

	INT64 curr_x = 0;
	INT64 curr_y = b;
	INT64 px = 0;
	INT64 py = da2 * b;
	INT64 p1 = round(b2 - a2 * b + a2 * 0.25);
	do {
		drawStars(x, y, curr_x++, curr_y);
		px += db2;
		if (p1 < 0) p1 += b2 + px;
		else {
			curr_y--; py -= da2;
			p1 += b2 + px - py;
		}
	} while (px < py);

	INT64 p2 = round(b2 * (curr_x + 0.5) * (curr_x + 0.5) + a2 * (curr_y - 1) * (curr_y - 1) - a2 * b2);
	while (curr_y > 0) {
		curr_y--;
		py -= da2;
		if (p2 > 0) p2 += a2 - py;
		else {
			curr_x++; px += db2;
			p2 += a2 - py + px;
		}
		drawStars(x, y, curr_x, curr_y);
	}
}

BEGIN_MESSAGE_MAP(CSketchpadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_Line, &CSketchpadDlg::OnMenuLine)
	ON_COMMAND(ID_MENU_Ellipse, &CSketchpadDlg::OnMenuEllipse)
	ON_COMMAND(ID_MENU_Circle, &CSketchpadDlg::OnMenuCircle)
END_MESSAGE_MAP()


// CSketchpadDlg 消息处理程序

BOOL CSketchpadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	hdc = ::GetDC(m_hWnd);
	m_line.type = m_circle.type = m_ellipse.type = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSketchpadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	// draw coordinate
	moveTo(0, -_ORIGIN_Y_);
	lineTo(0, +_ORIGIN_Y_);
	moveTo(-_ORIGIN_X_, 0);
	lineTo(+_ORIGIN_X_, 0);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSketchpadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CSketchpadDlg::OnMenuLine()
{
	m_line.type = 0;
	Inputbox_Line* input = new Inputbox_Line(this);
	input->DoModal();

	moveTo(m_line.sx, m_line.sy);
	// straight line
	if (m_line.sx == m_line.ex || m_line.sy == m_line.ey) {
		::ReleaseDC(m_hWnd, hdc);
		lineTo(m_line.ex, m_line.ey);
		return;
	}

	switch (m_line.type) {
	case 1:
		drawDDA();
		break;
	case 2:
		drawBresenham();
		break;
	default:
		break;
	}
}

void CSketchpadDlg::OnMenuCircle()
{
	m_circle.type = 0;
	Inputbox_Circle* input = new Inputbox_Circle(this);
	input->DoModal();

	if (m_circle.type && m_circle.r > 0)
		drawCircle();
}

void CSketchpadDlg::OnMenuEllipse()
{
	m_ellipse.type = 0;
	Inputbox_Ellipse* input = new Inputbox_Ellipse(this);
	input->DoModal();

	if (m_ellipse.type && m_ellipse.a > 0 && m_ellipse.b > 0)
		drawEllipse();
}


