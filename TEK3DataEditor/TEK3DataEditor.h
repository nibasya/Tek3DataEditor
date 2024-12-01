
// TEK3DataEditor.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CTEK3DataEditorApp:
// このクラスの実装については、TEK3DataEditor.cpp を参照してください
//

class CTEK3DataEditorApp : public CWinApp
{
public:
	CTEK3DataEditorApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CTEK3DataEditorApp theApp;
