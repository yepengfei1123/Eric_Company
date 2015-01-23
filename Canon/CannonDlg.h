
// CannonDlg.h : 头文件
//

#pragma once
#include "CamearControl.h"
#include "Dialog1.h"
#include "CHashList.h"
#include "afxwin.h"
#include "CvvImage.h"
#include "CProImage.h"


// CCannonDlg 对话框
class CCannonDlg : public CDialogEx
{
// 构造
public:
	CCannonDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CANNON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider1;
	CString m_Edit1;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CScrollBar m_ScrollBar;
	afx_msg void OnClickedButtonOpen();
	afx_msg void OnBnClickedButton2();
	Dialog1 dlg1;
	int threshold;
	int m_nFileStatus;
	afx_msg void OnBnClickedPrepare();
	static UINT CCannonDlg::threadFunction(LPVOID pParam);
	afx_msg void OnBnClickedPause();
	bool stopOrNot;
	vector<CommanderList> isoList;
	vector<CommanderList> avList;
	vector<CommanderList> tvList;
	CComboBox isoComBox;
	CComboBox avCombox;
	CComboBox tvCombox;
	void showImage(Mat img,UINT ID);
	afx_msg void OnBnClickedProcessimage();
	static UINT ProcessImage(LPVOID pParam);
	afx_msg void OnBnClickedSingalprocess();
	//度数计数比变量
	int stepCount;	
	//拍照张数
	CEdit picNumber;
	//保存函数
	void Save();
	static int CALLBACK  BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData);
	bool isStop;
	//停止
	afx_msg void OnBnClickedStop();
	int isSucceed;
	afx_msg void OnBnClickedBatachimage();
	afx_msg void OnBnClickedSingleimage();
	//串口
	void GetSystemCom();
	CComboBox comList;
	afx_msg void OnBnClickedOpencom();
	HANDLE hCom;
	bool comFlag;
	bool SendComOrder(unsigned char* lpOutBuffer);
	CComboBox roundTime;
	//vector<unsigned char *> timeVector;
	unsigned char timeVector[4*7];
	void SetTimeVec();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedTeststart();
	afx_msg void OnBnClickedTeststop();
	bool isPlaneStart;


	void numinfile(string path,int &num,char& ch1,char& ch2,char& ch3);
	void savechangetofile(string path,int num);
};
