// Inputbox_Circle.cpp: 实现文件
//

#include "pch.h"
#include "Sketchpad.h"
#include "Inputbox_Circle.h"
#include "afxdialogex.h"
#include "SketchpadDlg.h"


// Inputbox_Circle 对话框

IMPLEMENT_DYNAMIC(Inputbox_Circle, CDialogEx)

Inputbox_Circle::Inputbox_Circle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Inputbox_Circle, pParent)
	, x(_T(""))
	, y(_T(""))
	, r(_T(""))
	, pParent(pParent)
{

}

Inputbox_Circle::~Inputbox_Circle()
{
}

void Inputbox_Circle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, x);
	DDX_Text(pDX, IDC_EDIT4, y);
	DDX_Text(pDX, IDC_EDIT6, r);
}


BEGIN_MESSAGE_MAP(Inputbox_Circle, CDialogEx)
	ON_BN_CLICKED(IDOK_Circle, &Inputbox_Circle::OnBnClickedCircle)
END_MESSAGE_MAP()


// Inputbox_Circle 消息处理程序


void Inputbox_Circle::OnBnClickedCircle()
{
	UpdateData(true);
	CSketchpadDlg* parent = (CSketchpadDlg*)pParent;
	parent->m_circle.x = _ttoi(x);
	parent->m_circle.y = _ttoi(y);
	parent->m_circle.r = _ttoi(r);

	parent->m_circle.type = 1;
	CDialogEx::OnOK();
}
