#pragma once
#include <afxinet.h>


// CFtpThread

class CFtpThread : public CWinThread
{
	DECLARE_DYNCREATE(CFtpThread)

public:
	CFtpThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CFtpThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	UINT PutFile(LPVOID Status);  //不开的一个进程
	CString IPAddr;
	CString UserName;
	CString Password;
	CString FilePath;            //包括文件及后缀
	CString FilePathRemote;


protected:
	DECLARE_MESSAGE_MAP()
};


