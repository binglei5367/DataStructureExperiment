#pragma once
#include"global.h"
#include "GameLogic.h"
#include"GameControl.h"


// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

	// �Ի�������
	enum { IDD = IDD_GAME_DIALOG };


protected:
	CDC m_dcMem;	//�ڴ�DC
	CDC m_dcElement;//Ԫ���ڴ�DC
	CDC m_dcMask;	//�����ڴ�DC
	CDC m_dcBG;		//����DC

	CPoint m_ptGameTop;	//��Ϸ������ʼ��
	CSize m_sizeElem;	//Ԫ��ͼƬ��С
	CRect m_rtGameRect;	//��Ϸ�����С

	bool m_bFirstPoint;	//�Ƿ��һ����

	CGameControl m_gameControl;
	int m_picCount;		//��¼ʣ��ͼƬ����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

protected:
	void InitBackgound();
	void InitElement();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[2]);
	void UpdateMap();
	void UpdateWindow();
};
