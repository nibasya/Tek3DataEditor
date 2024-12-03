
// TEK3DataEditorDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "TEK3DataEditor.h"
#include "TEK3DataEditorDlg.h"
#include "afxdialogex.h"
#include "CDataSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTEK3DataEditorDlg ダイアログ



CTEK3DataEditorDlg::CTEK3DataEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEK3DATAEDITOR_DIALOG, pParent), m_pSaveData(NULL), m_fDirtyData(false), m_fDataReady(false), m_hSaveData(0), m_State(INITIAL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEK3DataEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_CtrlButtonLoad);
	DDX_Control(pDX, IDC_BUTTON1_SAVE, m_CtrlButtonSave);
	DDX_Control(pDX, IDC_BUTTON_DATA_SELECT, m_CtrlButtonDataSelect);
	DDX_Control(pDX, IDC_BUTTON_SHIPTYPE_EDIT, m_CtrlButtonShipTypeEdit);
	DDX_Control(pDX, IDC_BUTTON_SHIP_EDIT, m_CtrlButtonShipEdit);
	DDX_Control(pDX, IDC_BUTTON_SHIPSQUAD_EDIT, m_CtrlButtonShipQuadEdit);
	DDX_Control(pDX, IDC_BUTTON_PLANETYPE_EDIT, m_CtrlButtonPlaneTypeEdit);
	DDX_Control(pDX, IDC_BUTTON_PLANESTOCK_EDIT, m_CtrlButtonPlaneStockEdit);
	DDX_Control(pDX, IDC_BUTTON_PLANESQUAD_EDIT, m_CtrlButtonPlaneSquadEdit);
	DDX_Control(pDX, IDC_BUTTON_NATION_EDIT, m_CtrlButtonNationEdit);
	DDX_Control(pDX, IDC_BUTTON_BASE_EDIT, m_CtrlButtonBaseEdit);
	DDX_Control(pDX, IDC_EDIT_FOLDER, m_CtrlEditFolder);
	DDX_Control(pDX, IDC_EDIT_TARGETDATA, m_CtrlEditTargetData);
	DDX_Control(pDX, IDC_EDIT_CURRENTWORK, m_CtrlEditCurrentWork);
	DDX_Control(pDX, IDC_LIST_MAIN, m_CtrlListMain);
	DDX_Control(pDX, IDC_BUTTON_TIME_EDIT, m_CtrlButtonDateTime);
}

BEGIN_MESSAGE_MAP(CTEK3DataEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTEK3DataEditorDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_DATA_SELECT, &CTEK3DataEditorDlg::OnBnClickedButtonDataSelect)
	ON_BN_CLICKED(IDC_BUTTON_SHIPTYPE_EDIT, &CTEK3DataEditorDlg::OnBnClickedButtonShiptypeEdit)
END_MESSAGE_MAP()


// CTEK3DataEditorDlg メッセージ ハンドラー

BOOL CTEK3DataEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CTEK3DataEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CTEK3DataEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CTEK3DataEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEK3DataEditorDlg::OnBnClickedButtonLoad()
{
	if (m_fDirtyData) {
		int ret = MessageBox("セーブデータをロードします。現在編集中のセーブデータを破棄してもよろしいですか？", "確認", MB_OKCANCEL);
		if (ret == IDCANCEL) {
			return;
		}
	}
	CFileDialog fd(true, "TK3", "SAVEDAT.TK3", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "TEK3 savedata|SAVEDAT.TK3|AllData|*.*||");
	if (fd.DoModal() != IDOK) {
		MessageBox("ロードをキャンセルしました");
		return;
	}
	CString target = fd.GetPathName();
	if (PathFileExists(target) == FALSE) {
		MessageBox("ファイルが存在しません。ロードをキャンセルします。");
		return;
	}
	HANDLE hTgt = CreateFile(target, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hTgt == INVALID_HANDLE_VALUE) {
		MessageBox("ファイルを開けません。ロードをキャンセルします。");
		return;
	}
	LARGE_INTEGER li;
	if (GetFileSizeEx(hTgt, &li) == 0) {
		MessageBox("ファイルサイズの取得に失敗しました。ロードをキャンセルします。");
		CloseHandle(hTgt);
		return;
	}
	if (li.HighPart != 0 || li.LowPart != ALLDATASIZE) {
		MessageBox("ファイルサイズが想定外です。ロードをキャンセルします。");
		CloseHandle(hTgt);
		return;
	}

	m_fDirtyData = false;
	m_SaveDataPath = target;
	m_fDataReady = false;
	if (m_hSaveData) {
		CloseHandle(m_hSaveData);
	}
	m_hSaveData = hTgt;
	m_CtrlEditFolder.Clear();
	m_CtrlEditTargetData.Clear();
	m_CtrlEditCurrentWork.Clear();

	DWORD readData;
	if (ReadFile(m_hSaveData, m_pAllData, ALLDATASIZE, &readData, NULL) == 0) {
		MessageBox("ファイルの読み込みに失敗しました");
		CloseHandle(m_hSaveData);
		m_hSaveData = 0;
		return;
	}
	if (readData != ALLDATASIZE) {
		MessageBox("読み込んだデータサイズが想定と一致しませんでした。");
		CloseHandle(m_hSaveData);
		m_hSaveData = 0;
		return;
	}
	m_fDataReady = true;
	CString folder = target;
	PathRemoveFileSpecA(folder.GetBuffer());
	m_CtrlEditFolder.SetWindowText(folder);
	m_SaveDataNum = 1;
	ChangeSaveDataNum();
}

void CTEK3DataEditorDlg::ChangeSaveDataNum()
{
	if (m_SaveDataNum < 1 || m_SaveDataNum>10) {
		MessageBox("m_SaveDataの値が範囲外です。データを破棄します。");
		m_fDataReady = false;
		if (m_hSaveData) {
			CloseHandle(m_hSaveData);
			m_hSaveData = 0;
			m_CtrlEditTargetData.Clear();
		}
		return;
	}
	m_pSaveData = m_pAllData + 100 + 51319 * (m_SaveDataNum - 1);
	CString n;
	n.Format("%d", m_SaveDataNum);
	m_CtrlEditTargetData.SetWindowText(n);
}


void CTEK3DataEditorDlg::OnBnClickedButtonDataSelect()
{
	if (!m_fDataReady) {
		MessageBox("データをロードしてください");
		return;
	}

	CDataSelectDlg dlg;
	dlg.m_pData = m_pAllData;
	if (dlg.DoModal() != IDOK) {
		return;
	}
	m_SaveDataNum = dlg.m_Num + 1;
	ChangeSaveDataNum();
}

CString CTEK3DataEditorDlg::UShortToString(unsigned short s)
{
	CString buff;
	buff.Format("%hu", s);
	return buff;
}

CString CTEK3DataEditorDlg::UCharToNation(unsigned char c)
{
	switch (c) {
	case 1: return "大日本帝國";
	case 2: return "アメリカ合衆国";
	case 3: return "大英帝国";
	case 4: return "オランダ王国";
	case 5: return "オーストラリア";
	case 6: return "ソビエト連邦";
	case 7: return "ドイツ第三帝国";
	default: return "unknown";
	}
}

CString CTEK3DataEditorDlg::UCharToShipType(unsigned char c)
{
	unsigned char type = c & 0xc0;
	CString 防空;
	CString 重雷装;
	switch (type) {
	case 0x00: break;
	case 0x40: 防空 = "(防空)"; break;
	case 0x80: 重雷装 = "(重雷装)"; break;
	case 0xc0: break;	// 航空type
	}

	c = c & 0x0f;

	switch (c) {
	case 0: return CString("正規空母") + 防空 + 重雷装;
	case 1: return CString("軽空母") + 防空 + 重雷装;
	case 2: return CString("水上機母艦") + 防空 + 重雷装;
	case 3: return CString("超弩級戦艦") + 防空 + 重雷装;
	case 4: return CString("戦艦") + 防空 + 重雷装;
	case 5: return CString("航空戦艦") + 防空 + 重雷装;
	case 6: return CString("重巡洋艦") + 防空 + 重雷装;
	case 7: return CString("軽巡洋艦") + 防空 + 重雷装;
	case 8: return CString("航空巡洋艦") + 防空 + 重雷装;
	case 9: return CString("駆逐艦") + 防空 + 重雷装;
	case 10: return CString("潜水艦") + 防空 + 重雷装;
	default: return CString("不明") + 防空 + 重雷装;
	}
}

CString CTEK3DataEditorDlg::UCharToGunSize(char c)
{
	switch (c) {
	case 0x00: return "51.0cm";
	case 0x01: return "46.0cm";
	case 0x02: return "40.6cm";
	case 0x03: return "40.0cm";
	case 0x04: return "38.1cm";
	case 0x05: return "38.0cm";
	case 0x06: return "35.6cm";
	case 0x07: return "30.5cm";
	case 0x08: return "28.0cm";
	case 0x09: return "20.3cm";
	case 0x0a: return "20.0cm";
	case 0x0b: return "19.0cm";
	case 0x0c: return "18.0cm";
	case 0x0d: return "15.5cm";
	case 0x0e: return "15.2cm";
	case 0x0f: return "15.0cm";
	case 0x10: return "14.0cm";
	case 0x11: return "13.3cm";
	case 0x12: return "12.7cm";
	case 0x13: return "12.0cm";
	case 0x14: return "11.9cm";
	case 0x15: return "11.4cm";
	case 0x16: return "10.5cm";
	case 0x17: return "10.2cm";
	case 0x18: return "10.0cm";
	case 0x19: return "8.8cm";
	case 0x1a: return "8.0cm";
	case 0x1b: return "7.6cm";
	default: return "unknown";
	}
}

CString CTEK3DataEditorDlg::UCharToMainGun(unsigned char c)
{
	return UCharToMonsuu((c >> 4) + 1);
}

CString CTEK3DataEditorDlg::UCharToSubGun(unsigned char c)
{
	return UCharToMonsuu((c >> 5) + 1);
}

CString CTEK3DataEditorDlg::UCharToMonsuu(unsigned char c)
{
	switch (c) {
	case 1: return "単装";
	case 2: return "連装";
	case 3: return "3連装";
	case 4: return "4連装";
	case 5: return "5連装";
	default: return "unknown";
	};
}

void CTEK3DataEditorDlg::ClearList()
{
	m_CtrlListMain.DeleteAllItems();
	int nColumnCount = m_CtrlListMain.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) {
		m_CtrlListMain.DeleteColumn(0);
	}
}


void CTEK3DataEditorDlg::OnBnClickedButtonShiptypeEdit()
{
	if (m_State == SHIPTYPE) {
		return;	// as the software is already in ship type edit mode, do nothing
	}

	if (!m_fDataReady) {
		MessageBox("データをロードしてください");
		return;
	}
	m_CtrlListMain.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	ClearList();
	char c = 1;
	m_CtrlListMain.InsertColumn(c++, "ID", LVCFMT_LEFT);
	m_CtrlListMain.InsertColumn(c++, "国籍", LVCFMT_LEFT);
	m_CtrlListMain.InsertColumn(c++, "艦型", LVCFMT_LEFT);
	m_CtrlListMain.InsertColumn(c++, "艦種", LVCFMT_LEFT);
	m_CtrlListMain.InsertColumn(c++, "耐久", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "甲板", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "主口", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "主門", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "主基", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "副口", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "副門", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "副基", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "魚門", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "魚基", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "高角", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "機銃", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "爆雷", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "速度", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "艦載", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "石油", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "生産", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "費用", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "鉄鋼", LVCFMT_RIGHT);
	m_CtrlListMain.InsertColumn(c++, "生産日数", LVCFMT_RIGHT);

	const int typeNum = 235;
	m_CtrlListMain.SetItemCount(typeNum);
	BYTE* p = m_pSaveData + 0x2bf3;

	const int buffSize = 12;
	char buff[buffSize + 2];
	char numOfTurrets;
	memset(buff, 0, buffSize + 2);
	for (unsigned short i = 0; i < typeNum; i++, p += 38) {
		char c = 1;
		m_CtrlListMain.InsertItem(i, UShortToString(i));	// ID
		memcpy(buff, p, buffSize);
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToNation(*(p + 0x0d)), 0, 0, 0, 0);	// 国籍
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, buff, 0, 0, 0, 0);	// 艦型
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToShipType(*(p + 0x22)), 0, 0, 0, 0);	// 艦種
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x16)), 0, 0, 0, 0);	// 耐久
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x17)), 0, 0, 0, 0);	// 甲板
		numOfTurrets = *(p + 0x0f);
		if (numOfTurrets == 0) {
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "　-　", 0, 0, 0, 0);	// 主砲口径
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "-", 0, 0, 0, 0);	// 主砲門数
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "-", 0, 0, 0, 0);	// 主砲基数
		}
		else {
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToGunSize(*(p + 0x10)), 0, 0, 0, 0);	// 主砲口径
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToMainGun(*(p + 0x0f)), 0, 0, 0, 0);	// 主砲門数
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x0f) & 0x0f), 0, 0, 0, 0);	// 主砲基数
		}
		numOfTurrets = *(p + 0x11);
		if (numOfTurrets == 0) {
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "　-　", 0, 0, 0, 0);	// 副砲口径
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "-", 0, 0, 0, 0);	// 副砲門数
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "-", 0, 0, 0, 0);	// 副砲基数
		}
		else {
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToGunSize(*(p + 0x12)), 0, 0, 0, 0);	// 副砲口径
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToSubGun(*(p + 0x11)), 0, 0, 0, 0);	// 副砲門数
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x11) & 0x1f), 0, 0, 0, 0);	// 副砲基数
		}
		numOfTurrets = *(p + 0x13);
		if (numOfTurrets == 0) {
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "-", 0, 0, 0, 0);	// 魚雷門数
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, "-", 0, 0, 0, 0);	// 魚雷基数
		}
		else {
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UCharToMainGun(*(p + 0x13)), 0, 0, 0, 0);	// 魚雷門数
			m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x13) & 0x0f), 0, 0, 0, 0);	// 魚雷基数
		}
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x14)), 0, 0, 0, 0);	// 高角砲
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x15)), 0, 0, 0, 0);	// 機銃
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, (*(p + 0x22) & 0x10) ? "O" : "-", 0, 0, 0, 0);	// 爆雷
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x18)), 0, 0, 0, 0);	// 速度
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x19)), 0, 0, 0, 0);	// 艦載機数
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x1a)), 0, 0, 0, 0);	// 石油
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, (*(p + 0x22) & 0x20) ? "O" : "-", 0, 0, 0, 0);	// 生産
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(unsigned short*)(p + 0x1b)), 0, 0, 0, 0);	// 費用
		m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(unsigned short*)(p + 0x1d)), 0, 0, 0, 0);	// 鉄鋼
		// m_CtrlListMain.SetItem(i, c++, LVIF_TEXT, UShortToString(*(p + 0x16)), 0, 0, 0, 0);	// 生産日数

	}

	for (int i = 0; i < m_CtrlListMain.GetHeaderCtrl()->GetItemCount(); i++) {
		m_CtrlListMain.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}
