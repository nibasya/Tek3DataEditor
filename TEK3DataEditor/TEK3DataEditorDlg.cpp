
// TEK3DataEditorDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "TEK3DataEditor.h"
#include "TEK3DataEditorDlg.h"
#include "afxdialogex.h"

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
	: CDialogEx(IDD_TEK3DATAEDITOR_DIALOG, pParent), m_pSaveData(NULL), m_fDirtyData(false), m_fDataReady(false), m_hSaveData(0)
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
	DDX_Control(pDX, IDC_STATIC_FRAME, m_CtrlFrame);
}

BEGIN_MESSAGE_MAP(CTEK3DataEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTEK3DataEditorDlg::OnBnClickedButtonLoad)
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
	m_hSaveData = 0;

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
	m_hSaveData = hTgt;
	m_SaveData = 1;
	ChangeSaveData();
}

void CTEK3DataEditorDlg::ChangeSaveData()
{
	if (m_SaveData < 1 || m_SaveData>10) {
		MessageBox("m_SaveDataの値が範囲外です。データを破棄します。");
		m_fDataReady = false;
		if (m_hSaveData) {
			CloseHandle(m_hSaveData);
			m_hSaveData = 0;
		}
		return;
	}
	m_pSaveData = m_pAllData + 100 + 51319 * (m_SaveData - 1);
}
