// Inputbox_Ellipse.cpp: 实现文件
//

#include "pch.h"
#include "Sketchpad.h"
#include "Inputbox_Ellipse.h"
#include "afxdialogex.h"
#include "SketchpadDlg.h"


// Inputbox_Ellipse 对话框

IMPLEMENT_DYNAMIC(Inputbox_Ellipse, CDialogEx)

Inputbox_Ellipse::Inputbox_Ellipse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Inputbox_Ellipse, pParent)
	, x(_T(""))
	, y(_T(""))
	, a(_T(""))
	, b(_T(""))
	, pParent(pParent)
{

}

Inputbox_Ellipse::~Inputbox_Ellipse()
{
}

void Inputbox_Ellipse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, x);
	DDX_Text(pDX, IDC_EDIT4, y);
	DDX_Text(pDX, IDC_EDIT5, a);
	DDX_Text(pDX, IDC_EDIT6, b);
}


BEGIN_MESSAGE_MAP(Inputbox_Ellipse, CDialogEx)
	ON_BN_CLICKED(IDOK_Ellipse, &Inputbox_Ellipse::OnBnClickedEllipse)
END_MESSAGE_MAP()


// Inputbox_Ellipse 消息处理程序


void Inputbox_Ellipse::OnBnClickedEllipse()
{
	UpdateData(true);
	CSketchpadDlg* parent = (CSketchpadDlg*)pParent;
	parent->m_ellipse.x = _ttoi(x);
	parent->m_ellipse.y = _ttoi(y);
	parent->m_ellipse.a = _ttoi(a);
	parent->m_ellipse.b = _ttoi(b);

	parent->m_ellipse.type = 1;
	CDialogEx::OnOK();
}
