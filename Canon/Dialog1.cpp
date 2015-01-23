// Dialog1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cannon.h"
#include "Dialog1.h"
#include "afxdialogex.h"


// Dialog1 �Ի���

IMPLEMENT_DYNAMIC(Dialog1, CDialogEx)

Dialog1::Dialog1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog1::IDD, pParent)
	, m_Width3(_T(""))
{
	CStdioFile file;
	if (file.Open(_T("data.txt"),CFile::typeText|CFile::modeReadWrite))
	{
		file.SeekToBegin();
		CString dataInfo;
		file.ReadString(dataInfo);
		m_Dlg1Edit1 = dataInfo;
		file.ReadString(dataInfo);
		m_Dlg1Edit2 = dataInfo;
		file.ReadString(dataInfo);
		m_Dlg1Edit3 = dataInfo;
		file.ReadString(dataInfo);
		m_Dlg1Edit4 = dataInfo;
		file.ReadString(dataInfo);
		m_Width = dataInfo;
		file.ReadString(dataInfo);
		m_Height = dataInfo;
		file.ReadString(dataInfo);
		m_Width3 = dataInfo;	
	}
	file.Close();
}

Dialog1::~Dialog1()
{
}

void Dialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Dlg1Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Dlg1Edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Dlg1Edit3);
	DDX_Text(pDX, IDC_EDIT4, m_Dlg1Edit4);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_Height);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_Width);
	DDX_Text(pDX, IDC_WIDTH3, m_Width3);
}


BEGIN_MESSAGE_MAP(Dialog1, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog1::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &Dialog1::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// Dialog1 ��Ϣ�������


void Dialog1::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CStdioFile file;
	if (!file.Open(_T("data.txt"),CFile::modeCreate|CFile::typeText|CFile::modeReadWrite))
	{
	}
	CString writeInfo = m_Dlg1Edit1 + _T("\n");
	file.WriteString(writeInfo);      //д������  
	writeInfo = m_Dlg1Edit2 + _T("\n");
	file.WriteString(writeInfo);      //д������
	writeInfo = m_Dlg1Edit3 + _T("\n");
	file.WriteString(writeInfo);      //д������
	writeInfo = m_Dlg1Edit4 + _T("\n");
	file.WriteString(writeInfo);      //д������
	writeInfo = m_Height + _T("\n");
	file.WriteString(writeInfo);      //д������
	writeInfo = m_Width + _T("\n");
	file.WriteString(writeInfo);      //д������
	writeInfo = m_Width3 + _T("\n");
	file.WriteString(writeInfo);      //д������
	file.Close();
	CDialogEx::OnOK();
}


void Dialog1::OnBnClickedButtonSave()
{
	TCHAR    szPath[MAX_PATH];
	CString path = "E:\\" ;
	memcpy(szPath,path.GetBuffer(path.GetLength()),path.GetLength());
	CString sFolderPath;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = this->GetSafeHwnd();
	bi.pidlRoot = NULL;//��ʼ���ƶ���rootĿ¼
	bi.pszDisplayName = szPath;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle =_T("���ļ���");
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//�����ļ�
	bi.ulFlags = BIF_EDITBOX;//�����ļ�
	bi.lpfn = BrowseCallbackProc1;
	bi.lParam = LPARAM(szPath);
	bi.iImage=0;
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if(pIDList)
	{
		//SHSetFolderPath(pIDList,)
		SHGetPathFromIDList(pIDList, szPath);
		//ȡ���ļ���·����Buffer��
		sFolderPath = szPath;//���ļ���·��������һ��CString������
		m_Dlg1Edit4 = sFolderPath;                       
		UpdateData(FALSE);
	}
}


int CALLBACK  Dialog1::BrowseCallbackProc1(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)  
{
	CStringA str = "";
	std::string orginalImgPath=str.GetBuffer(0);
	const char * filePath = orginalImgPath.c_str();
	if (uMsg == BFFM_INITIALIZED)
	{ 
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)filePath);   
	}  
	return 0;     
}





