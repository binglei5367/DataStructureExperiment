#pragma once
#include"global.h"
#include "GameLogic.h"
#include"GameControl.h"


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

	// 对话框数据
	enum { IDD = IDD_GAME_DIALOG };


protected:
	CDC m_dcMem;	//内存DC
	CDC m_dcElement;//元素内存DC
	CDC m_dcMask;	//掩码内存DC
	CDC m_dcBG;		//背景DC

	CPoint m_ptGameTop;	//游戏区域起始点
	CSize m_sizeElem;	//元素图片大小
	CRect m_rtGameRect;	//游戏区域大小

	bool m_bFirstPoint;	//是否第一个点

	CGameControl m_gameControl;
	int m_picCount;		//记录剩余图片数量

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
