// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LeLekan.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
END_MESSAGE_MAP()


// CGameDlg ��Ϣ�������


void CGameDlg::InitBackgound()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\game_dlg_background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CClientDC dc(this);

	m_dcMem.CreateCompatibleDC(&dc);

	m_dcMem.SelectObject(bmp);

	// �������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);

	// ����������߿��С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	// ���ô��ڴ�С
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	// ʹ���ھ���
	CenterWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackgound();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\game_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CClientDC dc(this);

	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(bmp);
}

void CGameDlg::OnClickedBtnStart()
{
	// ��ͼ��ʼ��Ϊ�̶�ֵ
	int anMap[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}
	int nLeft = 50;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// ���Ƶ���ͼƬ
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
		}
	}

}
