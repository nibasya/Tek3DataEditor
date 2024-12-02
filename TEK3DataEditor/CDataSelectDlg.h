#pragma once
#include "afxdialogex.h"


// CDataSelectDlg ダイアログ

class CDataSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataSelectDlg)

public:
	CDataSelectDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CDataSelectDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATANUM_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CtrlListData;
	BYTE* m_pData;
	int m_Num;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMDblclkListDatanumSelect(NMHDR* pNMHDR, LRESULT* pResult);
};
