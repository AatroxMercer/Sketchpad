#pragma once


// Inputbox_Ellipse 对话框

class Inputbox_Ellipse : public CDialogEx
{
	DECLARE_DYNAMIC(Inputbox_Ellipse)

public:
	Inputbox_Ellipse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Inputbox_Ellipse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Inputbox_Ellipse };
#endif

private:
	CWnd* pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString x;
	CString y;
	CString a;
	CString b;
	afx_msg void OnBnClickedEllipse();
};
