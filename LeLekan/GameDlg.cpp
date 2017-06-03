// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LeLekan.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 4;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 4;
	

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


// CGameDlg 消息处理程序


void CGameDlg::InitBackgound()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\game_dlg_background.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);

	CClientDC dc(this);

	m_dcMem.CreateCompatibleDC(&dc);

	m_dcMem.SelectObject(bmp);

	// 调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);

	// 标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	// 设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	// 使窗口居中
	CenterWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackgound();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement()
{
	//HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\game_element.bmp"), IMAGE_BITMAP,
	//	0, 0, LR_LOADFROMFILE);

	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\head_element.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);															//***

	CClientDC dc(this);

	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(bmp);

	// 加载掩码图片

	//HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\game_element_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\head_mask.bmp"), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);															//***

	m_dcMask.CreateCompatibleDC(&dc);

	m_dcMask.SelectObject(hMask);
}

void CGameDlg::OnClickedBtnStart()
{
	// 初始化游戏地图
	m_gameControl.StartGame();

	int nLeft = 50;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// 绘制单张图片
			//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, 
			//	nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nElemW,
				nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0,
				m_gameControl.m_anMap[i][j] * nElemH, SRCPAINT);	//将背景与掩码相或，边保留，图像区域为1
			
			m_dcMem.BitBlt(nLeft + j * nElemW,
				nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0,
				m_gameControl.m_anMap[i][j] * nElemH, SRCAND);		//将元素图片相与，边保留，图像区域为元素图片
			
		}
	}

	Invalidate(FALSE);

}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	if (nRow > 3 || nCol > 3)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint)
	{//第一个点
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{//第二个点
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);

		//获得路径
		Vertex avPath[4];
		//判断是否是相同图片,是则绘制连接线
		if (m_gameControl.Link(avPath))
		{
			//画提示线
			DrawTipLine(avPath);

			//清除
			m_gameControl.gameLogic.Clear(m_gameControl.m_anMap, m_gameControl.m_ptSelFirst, m_gameControl.m_ptSelSec);

			UpdateMap();//消去图片
			m_picCount -= 2;
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);

		//判断图片数量是否为0，是则游戏结束
		if (m_picCount == 0)
		{
			AfxMessageBox(_T("恭喜你挑战成功！"), MB_OK);
		}
	}
	m_bFirstPoint = !m_bFirstPoint;

}


void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


void CGameDlg::DrawTipLine(Vertex avPath[2])
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//绘制连接线
	if (m_gameControl.gameLogic.m_nVertexNum == 2)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[0].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[0].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[1].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[1].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.SelectObject(pOldPen);
		m_gameControl.gameLogic.Delete();
		m_gameControl.gameLogic.Delete();
	}
	if (m_gameControl.gameLogic.m_nVertexNum == 3)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[0].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[0].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[1].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[1].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.MoveTo(m_ptGameTop.x + avPath[1].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[1].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[2].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[2].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.SelectObject(pOldPen);
		m_gameControl.gameLogic.Delete();
		m_gameControl.gameLogic.Delete();
		m_gameControl.gameLogic.Delete();
	}
	if (m_gameControl.gameLogic.m_nVertexNum == 4)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[0].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[0].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[1].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[1].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.MoveTo(m_ptGameTop.x + avPath[1].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[1].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[2].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[2].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.MoveTo(m_ptGameTop.x + avPath[2].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[2].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[3].col*m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[3].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.SelectObject(pOldPen);
		m_gameControl.gameLogic.Delete();
		m_gameControl.gameLogic.Delete();
		m_gameControl.gameLogic.Delete();
		m_gameControl.gameLogic.Delete();
	}
}


void CGameDlg::UpdateMap()
{
	int nLeft = m_ptGameTop.y;
	int nTop = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int nInfo = m_gameControl.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);	//将背景与掩码相或，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);	//将元素图片相与，边保留，图像区域为元素图片
		}
	}
}


void CGameDlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetClientRect(rtClient);	//获得客户区大小

	//标题栏和外边框大小				
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();	

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	//设置对话框显示在windows窗口正中央
	CenterWindow();
}