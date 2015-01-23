
// CannonDlg.h : ͷ�ļ�
//

#pragma once
#include "CamearControl.h"
#include "Dialog1.h"
#include "CHashList.h"
#include "afxwin.h"
#include "CvvImage.h"
#include "CProImage.h"


// CCannonDlg �Ի���
class CCannonDlg : public CDialogEx
{
// ����
public:
	CCannonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CANNON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	//���������ȱ���
	int stepCount;	
	//��������
	CEdit picNumber;
	//���溯��
	void Save();
	static int CALLBACK  BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData);
	bool isStop;
	//ֹͣ
	afx_msg void OnBnClickedStop();
	int isSucceed;
	afx_msg void OnBnClickedBatachimage();
	afx_msg void OnBnClickedSingleimage();
	//����
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
