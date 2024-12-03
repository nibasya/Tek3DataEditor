
// TEK3DataEditorDlg.h : ヘッダー ファイル
//

#pragma once


// CTEK3DataEditorDlg ダイアログ
class CTEK3DataEditorDlg : public CDialogEx
{
// コンストラクション
public:
	CTEK3DataEditorDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEK3DATAEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	#define ALLDATASIZE (513290)
	BYTE m_pAllData[ALLDATASIZE];	// copy of SAVEDAT.TK3
	BYTE* m_pSaveData;	// pointer to current savedata
	int m_SaveDataNum;		// savedata num; starting from 1
	CString m_SaveDataPath;	// path of SAVEDAT.TEK3
	HANDLE m_hSaveData;	// handle of the opened savedata. this will be kept open until end of the edit.
	bool m_fDirtyData;	// true if change has been done since last save  / load
	bool m_fDataReady;	// true if m_pAllData is valid
	enum EState {INITIAL, SHIPTYPE, SHIP, SHIPQUAD, PLANETYPE, PLANESTOCK, PLANESQUAD, NATION, BASE} m_State;

	CButton m_CtrlButtonLoad;
	CButton m_CtrlButtonSave;
	CButton m_CtrlButtonDataSelect;
	CButton m_CtrlButtonShipTypeEdit;
	CButton m_CtrlButtonShipEdit;
	CButton m_CtrlButtonShipQuadEdit;
	CButton m_CtrlButtonPlaneTypeEdit;
	CButton m_CtrlButtonPlaneStockEdit;
	CButton m_CtrlButtonPlaneSquadEdit;
	CButton m_CtrlButtonNationEdit;
	CButton m_CtrlButtonBaseEdit;
	CButton m_CtrlButtonDateTime;

	CEdit m_CtrlEditFolder;
	CEdit m_CtrlEditTargetData;
	CEdit m_CtrlEditCurrentWork;

	CListCtrl m_CtrlListMain;

	afx_msg void OnBnClickedButtonLoad();
	void ChangeSaveDataNum();
	afx_msg void OnBnClickedButtonDataSelect();

	/// <summary>
	/// Converts value to string
	/// </summary>
	/// <param name="s"></param>
	/// <returns>String of the value</returns>
	CString UShortToString(unsigned short s);

	/// <summary>
	/// Converts Nation value to CString
	/// </summary>
	/// <param name="c"></param>
	/// <returns>String of the nation</returns>
	CString UCharToNation(unsigned char c);

	/// <summary>
	/// Converts ShipType value to CString
	/// </summary>
	/// <param name="c">Ship type</param>
	/// <returns>String of the ship type</returns>
	CString UCharToShipType(unsigned char c);

	/// <summary>
	/// Converts gun size value to CString
	/// </summary>
	/// <param name="c">gun size</param>
	/// <returns>String of the gun size</returns>
	CString UCharToGunSize(char c);

	/// <summary>
	///  Converts number of main guns per turrets value to CString
	/// </summary>
	/// <param name="c"></param>
	/// <returns>String of number of main guns per turrets</returns>
	CString UCharToMainGun(unsigned char c);

	/// <summary>
	///  Converts number of sub guns per turrets value to CString
	/// </summary>
	/// <param name="c"></param>
	/// <returns>String of number of sub guns per turrets</returns>
	CString UCharToSubGun(unsigned char c);

	/// <summary>
	///  Converts number of guns per turrets value to CString
	/// </summary>
	/// <param name="c"></param>
	/// <returns>String of number of guns per turrets</returns>
	CString UCharToMonsuu(unsigned char c);

	/// <summary>
	///  Clear all data and columns in m_CtrlListMain.
	/// </summary>
	void ClearList();
	afx_msg void OnBnClickedButtonShiptypeEdit();
};
