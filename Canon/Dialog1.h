#pragma once
#include "afxwin.h"
#include "string"


// Dialog1 �Ի���

class Dialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog1)

public:
	Dialog1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Dlg1Edit1;
	CString m_Dlg1Edit2;
	CString m_Dlg1Edit3;
	CString m_Dlg1Edit4;
	//CString fileName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnEnChangeEditWidth();
	CString m_Height;
	CString m_Width;
	CComboBox comlist;
	///////////////////////////////////////////////

	void OnBnClickedCancel();
	CString m_Width3;
	static int CALLBACK  BrowseCallbackProc1(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData);
};
