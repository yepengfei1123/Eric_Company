#pragma once
#include <afxinet.h>


// CFtpThread

class CFtpThread : public CWinThread
{
	DECLARE_DYNCREATE(CFtpThread)

public:
	CFtpThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFtpThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	UINT PutFile(LPVOID Status);  //������һ������
	CString IPAddr;
	CString UserName;
	CString Password;
	CString FilePath;            //�����ļ�����׺
	CString FilePathRemote;


protected:
	DECLARE_MESSAGE_MAP()
};


