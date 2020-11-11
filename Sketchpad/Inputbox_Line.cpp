// Inputbox_Line.cpp: 实现文件
//

#include "pch.h"
#include "Sketchpad.h"
#include "Inputbox_Line.h"
#include "afxdialogex.h"
#include "SketchpadDlg.h"


// Inputbox_Line 对话框

IMPLEMENT_DYNAMIC(Inputbox_Line, CDialogEx)

Inputbox_Line::Inputbox_Line(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Inputbox_Line, pParent)
	, sx(_T(""))
	, sy(_T(""))
	, ex(_T(""))
	, ey(_T(""))
	, pParent(pParent)
{

}

Inputbox_Line::~Inputbox_Line()
{
}

void Inputbox_Line::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, sx);
	DDX_Text(pDX, IDC_EDIT4, sy);
	DDX_Text(pDX, IDC_EDIT5, ex);
	DDX_Text(pDX, IDC_EDIT6, ey);
}


BEGIN_MESSAGE_MAP(Inputbox_Line, CDialogEx)
	ON_BN_CLICKED(IDOK_dda, &Inputbox_Line::OnBnClickeddda)
	ON_BN_CLICKED(IDOK_Bresenham, &Inputbox_Line::OnBnClickedBresenham)
END_MESSAGE_MAP()


// Inputbox_Line 消息处理程序


void Inputbox_Line::OnBnClickeddda()
{
	UpdateData(true);
	CSketchpadDlg* parent = (CSketchpadDlg*)pParent;
	parent->m_line.sx = _ttoi(sx);
	parent->m_line.sy = _ttoi(sy);
	parent->m_line.ex = _ttoi(ex);
	parent->m_line.ey = _ttoi(ey);


	parent->m_line.type = 1;
	CDialogEx::OnOK();
}


void Inputbox_Line::OnBnClickedBresenham()
{
	UpdateData(true);
	CSketchpadDlg* parent = (CSketchpadDlg*)pParent;
	parent->m_line.sx = _ttoi(sx);
	parent->m_line.sy = _ttoi(sy);
	parent->m_line.ex = _ttoi(ex);
	parent->m_line.ey = _ttoi(ey);

	parent->m_line.type = 2;
	CDialogEx::OnOK();
}
