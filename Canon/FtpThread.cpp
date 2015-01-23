// FtpThread.cpp : 实现文件
//

#include "stdafx.h"
//#include "Ftp2.h"
#include "FtpThread.h"


// CFtpThread

IMPLEMENT_DYNCREATE(CFtpThread, CWinThread)

CFtpThread::CFtpThread()
{
	IPAddr = "";
	UserName = "";
	Password = "";
	FilePath =  "";
	FilePathRemote = "";
}

CFtpThread::~CFtpThread()
{
}

BOOL CFtpThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CFtpThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CFtpThread, CWinThread)
END_MESSAGE_MAP()

char BallOut;
// CFtpThread 消息处理程序
UINT CFtpThread::PutFile(LPVOID Status)
{
	int *pnFileStatus;
	CInternetSession *pInetSession;
	CFtpConnection *pFtpConnection=NULL;
	pnFileStatus=(int *)Status;
	*pnFileStatus=0;
	pInetSession=new
		CInternetSession(AfxGetAppName(),1,
		PRE_CONFIG_INTERNET_ACCESS);
	try
	{
		pFtpConnection=pInetSession->GetFtpConnection(IPAddr,UserName,Password);
		//::SetCurrentDirectoryA("C:\\Users\\Administrator\\Desktop\\peppers.bmp");
		//pFtpConnection->SetCurrentDirectory("C:\\Users\\Administrator\\Desktop\\libcurl\\");
	}
	catch(CInternetException *pEx)
	{
		TCHAR szError[1024] = {0};
		if(pEx->GetErrorMessage(szError,1024))
			AfxMessageBox(szError);
		else
			AfxMessageBox(_T("There was an exception"));

		pEx->Delete();
		pFtpConnection=NULL;
		*pnFileStatus=-1;
		goto BallOut;
	}
	*pnFileStatus =1;
	//pFtpConnection->Remove(_T("test.txt"));
	if(!pFtpConnection->PutFile(FilePath,FilePathRemote))
	{
		AfxMessageBox(_T("Transfer data failed!"));
		*pnFileStatus=-2;
	}
	else
	{
		//AfxMessageBox(_T("Transfer data OK!"));
		*pnFileStatus=2;
	}
BallOut:
	if(pFtpConnection!=NULL)
	{
		pFtpConnection->Close();
		delete pFtpConnection;
	}
	delete pInetSession;
//	AfxEndThread(0);
	return false;
}
