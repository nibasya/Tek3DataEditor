// CDataSelectDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "TEK3DataEditor.h"
#include "afxdialogex.h"
#include "CDataSelectDlg.h"


// CDataSelectDlg ダイアログ

IMPLEMENT_DYNAMIC(CDataSelectDlg, CDialogEx)

CDataSelectDlg::CDataSelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DATANUM_SELECT, pParent)
{

}

CDataSelectDlg::~CDataSelectDlg()
{
}

void CDataSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATANUM_SELECT, m_CtrlListData);
}


BEGIN_MESSAGE_MAP(CDataSelectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDataSelectDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DATANUM_SELECT, &CDataSelectDlg::OnNMDblclkListDatanumSelect)
END_MESSAGE_MAP()


// CDataSelectDlg メッセージ ハンドラー


BOOL CDataSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	m_CtrlListData.InsertColumn(0, "No.");
	m_CtrlListData.InsertColumn(1, "タイトル");
	m_CtrlListData.InsertColumn(2, "年/月/日 時");
	m_CtrlListData.InsertColumn(3, "自軍");
	m_CtrlListData.InsertColumn(4, "相手");
	m_CtrlListData.SetItemCount(10);
	m_CtrlListData.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	BYTE* p;
	CString buff;
	for (int i = 0; i < 10; i++) {
		p = m_pData + 20 + i*8;
		buff.Format("%d", i + 1);
		m_CtrlListData.InsertItem(i, buff);
		if (*(m_pData + 10 + i) == 0) {
			m_CtrlListData.SetItem(i, 1, LVIF_TEXT, "    -    ", 0, 0, 0, 0);
			m_CtrlListData.SetItem(i, 2, LVIF_TEXT, "      -      ", 0, 0, 0, 0);
			m_CtrlListData.SetItem(i, 3, LVIF_TEXT, "  -  ", 0, 0, 0, 0);
			m_CtrlListData.SetItem(i, 4, LVIF_TEXT, "   -   ", 0, 0, 0, 0);
			continue;
		}

		switch (*(p + 0)) {
			case 0: buff = "日米開戦"; break;
			case 1: buff = "奇襲真珠湾"; break;
			case 2: buff = "ミッドウェイ海戦"; break;
			case 3: buff = "ソロモン攻防戦"; break;
			case 4: buff = "マリアナ沖海戦"; break;
			case 5: buff = "決戦レイテ沖海戦"; break;
			case 6: buff = "大和特攻"; break;
			default: buff = "UNKNOWN"; break;
		}
		m_CtrlListData.SetItem(i, 1, LVIF_TEXT, buff.GetString(), 0, 0, 0, 0);

		buff.Format("%d/%02d/%02d %02d時", *(p + 1) + *(p + 2) * 256 + 1, *(p + 3) + 1, *(p + 4) + 1, *(p + 5) + 1);
		m_CtrlListData.SetItem(i, 2, LVIF_TEXT, buff.GetString(), 0, 0, 0, 0);
		switch (*(p + 6)) {
			case 0: buff = "日本国"; break;
			case 1: buff = "米国"; break;
			default: buff = "unknown"; break;
		}
		m_CtrlListData.SetItem(i, 3, LVIF_TEXT, buff.GetString(), 0, 0, 0, 0);
		switch (*(p + 7)) {
		case 0: buff = "対COM戦"; break;
		case 1: buff = "対人戦"; break;
		default: buff = "unknown"; break;
		}
		m_CtrlListData.SetItem(i, 4, LVIF_TEXT, buff.GetString(), 0, 0, 0, 0);
	}

	for (int i = 0; i < 5; i++) {
		m_CtrlListData.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CDataSelectDlg::OnBnClickedOk()
{
	m_Num = m_CtrlListData.GetSelectionMark();
	if (m_Num != -1) {
		if (*(m_pData + 10 + m_Num) != 0) {	//	check if this is valid data
			CDialogEx::OnOK();
		}
	}
}


void CDataSelectDlg::OnNMDblclkListDatanumSelect(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedOk();
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	*pResult = 0;
}
