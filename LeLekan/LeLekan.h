
// LeLekan.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLeLekanApp: 
// �йش����ʵ�֣������ LeLekan.cpp
//

class CLeLekanApp : public CWinApp
{
public:
	CLeLekanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLeLekanApp theApp;
