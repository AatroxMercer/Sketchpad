
// SketchpadDlg.h: 头文件
//

#pragma once


struct Data_Line {
	int sx, sy;
	int ex, ey;
	int type;
};

struct Data_Circle {
	int x, y, r;
	int type;
};

struct Data_Ellipse
{
	int x, y;
	int a, b;
	int type;
};

// CSketchpadDlg 对话框
class CSketchpadDlg : public CDialogEx
{
// 构造
public:
	CSketchpadDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SKETCHPAD_DIALOG };
#endif

public:
	HDC hdc;
	Data_Line m_line;
	Data_Circle m_circle;
	Data_Ellipse m_ellipse;

	const void moveTo(int x, int y);
	const void lineTo(int x, int y);
	const void setPixel(double x, double y);
	const void drawStars(int originX, int originY, int x, int y);

	const void drawDDA();
	const void drawBresenham();
	const void drawCircle();
	const void drawEllipse();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuLine();
	afx_msg void OnMenuEllipse();
	afx_msg void OnMenuCircle();
};