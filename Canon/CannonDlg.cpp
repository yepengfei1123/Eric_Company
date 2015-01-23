// CannonDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Cannon.h"
#include "CannonDlg.h"
#include "string"

#include <stdlib.h>
#include <fstream>
#include <ostream>
#include <iostream>

using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCannonDlg �Ի���


CCannonDlg::CCannonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCannonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Edit1 = _T("");
	stepCount = 0;
	//CCannonDlg::m_filePath = NULL;
}

void CCannonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ScrollBar);
	DDX_Control(pDX, IDC_COMBO1, isoComBox);
	DDX_Control(pDX, IDC_COMBO2, avCombox);
	DDX_Control(pDX, IDC_COMBO3, tvCombox);
	DDX_Control(pDX, IDC_PICNUMBER, picNumber);
	DDX_Control(pDX, IDC_COMLIST, comList);
	DDX_Control(pDX, IDC_AROUNDTIME, roundTime);
}

BEGIN_MESSAGE_MAP(CCannonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CCannonDlg::OnCustomdrawSlider1)
ON_BN_CLICKED(IDC_BUTTON1, &CCannonDlg::OnClickedButtonOpen)
ON_BN_CLICKED(IDC_BUTTON2, &CCannonDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_PREPARE, &CCannonDlg::OnBnClickedPrepare)
ON_BN_CLICKED(IDC_PROCESSIMAGE, &CCannonDlg::OnBnClickedProcessimage)
ON_BN_CLICKED(IDC_SINGALPROCESS, &CCannonDlg::OnBnClickedSingalprocess)
ON_BN_CLICKED(IDC_STOP, &CCannonDlg::OnBnClickedStop)
ON_BN_CLICKED(IDC_BATACHIMAGE, &CCannonDlg::OnBnClickedBatachimage)
ON_BN_CLICKED(IDC_SINGLEIMAGE, &CCannonDlg::OnBnClickedSingleimage)
ON_BN_CLICKED(IDC_OPENCOM, &CCannonDlg::OnBnClickedOpencom)
ON_BN_CLICKED(IDC_EXIT, &CCannonDlg::OnBnClickedExit)
ON_BN_CLICKED(IDC_BUTTON4, &CCannonDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_TESTSTART, &CCannonDlg::OnBnClickedTeststart)
ON_BN_CLICKED(IDC_TESTSTOP, &CCannonDlg::OnBnClickedTeststop)
END_MESSAGE_MAP()


// CCannonDlg ��Ϣ�������

BOOL CCannonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

		//��������ʼ��
		m_ScrollBar.SetScrollRange(0,255);
		m_ScrollBar.SetScrollPos(160);
		int ScrollVal = m_ScrollBar.GetScrollPos();
		//���ÿ�ͼ��ֵ
		threshold = ScrollVal;
		CString str;
		str.Format(_T("%d"),ScrollVal);
		CEdit* pEditOne;
		pEditOne=(CEdit*)GetDlgItem(IDC_EDIT1);
		//��ʾ������������
		pEditOne->SetWindowText(str);
		UpdateData(TRUE);
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	CWnd *wd = (CWnd*)GetDlgItem(IDC_PREPARE);
	wd->EnableWindow(FALSE);
	wd = (CWnd*)GetDlgItem(IDC_BUTTON2);
	wd->EnableWindow(FALSE);
	wd = (CWnd*)GetDlgItem(IDC_STOP);
	wd->EnableWindow(FALSE);
	GetSystemCom();
	SetTimeVec();
	comList.SetCurSel(0);
	//��ʼ�����ڱ�ʾλΪfalse
	comFlag = false;
	//ת��״̬
	isPlaneStart = true;

	char buf[300];
	char buf1[10];
	int nn;
	char c1,c2,c3;
	string pp="copyrights.txt";
	string pp1="in2.txt";
	numinfile(pp,nn,c1,c2,c3);
	if (nn >= 100)
	{
		AfxMessageBox("����ʹ������");
		CDialogEx::OnCancel();
	}
	else
	{
		savechangetofile(pp,nn+1);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCannonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCannonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCannonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCannonDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CSliderCtrl* pSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int ScrollVal = m_ScrollBar.GetScrollPos();

	CString str;
	str.Format(_T("%d"),ScrollVal);
	CEdit* pEditOne;
	pEditOne=(CEdit*)GetDlgItem(IDC_EDIT1);
	pEditOne->SetWindowText(str);
	switch (nSBCode)    
	    {    
		        // ����������һ�У���pos��1   
			        case SB_LINEUP:    
			            ScrollVal -= 1;    
			            break;    
			        // ������ҹ���һ�У���pos��1   
				        case SB_LINEDOWN:    
			            ScrollVal  += 1;    
			            break;    
			       // ����������һҳ����pos��10   
				        case SB_PAGEUP:    
			            ScrollVal -= 10;    
			            break;    
			        // ������ҹ���һҳ����pos��10   
				        case SB_PAGEDOWN:    
			            ScrollVal  += 10;    
			            break;    
			        // �������������ˣ���posΪ1   
				        case SB_TOP:    
			            ScrollVal = 0;    
			            break;    
			        // ������������Ҷˣ���posΪ100   
				        case SB_BOTTOM:    
			            ScrollVal = 255;    
			            break;      
			        // ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ   
			        case SB_THUMBPOSITION:    
			            ScrollVal = nPos;    
			            break;    
		        // �����m_horiScrollbar.SetScrollPos(pos);ִ��ʱ��ڶ��ν���˺���������ȷ��������λ�ã����һ�ֱ�ӵ�default��֧�������ڴ˴����ñ༭������ʾ��ֵ   
			        default:    
			            SetDlgItemInt(IDC_EDIT1, ScrollVal);   
			            return;    
			    }    
	  
		    // ���ù�����λ��   
		    m_ScrollBar.SetScrollPos(ScrollVal);   

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



/**************************************************
	������: CCannonDlg::OnClickedButtonOpen
	��������: 1.�������Ƿ�򿪣�����������������˵��Ƿ���ֵ
	                  2.����CCamearControl����Ƿ�������������
					  3.�õ�����������õ�ISO��AV��TV����
					  4.�������Ĭ�ϲ���
	����: ��
	���: ��
	����ֵ: ��
	����: ��
	�޸���ʷ: ��
*************************************************/
void CCannonDlg::OnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!isoList.empty())
	{
		AfxMessageBox(_T("����Ѵ�"));
		return;
	}
	CCamearControl cameraCtrl;
	//�����
	bool flag = cameraCtrl.OpenCamera();
	if (flag == false)
	{
		AfxMessageBox(_T("��ȡ���ʧ��"));
	}
	else
	{
		//�õ�����������õĲ�����Ϣ
		flag = cameraCtrl.GetCameraInfo();
		//������ϣ��
		CHashList getHashList;
		getHashList.CreatAllList();
		int isoIndex(0);
		//���ù�ϣ��õ������Ӧ�������
		for (int i=0 ;i<cameraCtrl.isoPropety.numElements;++i)
		{
			CommanderList listTemp;
			listTemp.key = cameraCtrl.isoPropety.propDesc[i];
			if (listTemp.key == 0x00)
			{
				isoIndex = i;
			}
			listTemp.command = getHashList.FindObject(getHashList.isoHashList,listTemp.key);
			isoList.push_back(listTemp) ;
			CString stringTemp;
			stringTemp.Format("%s",listTemp.command.c_str());
			//�������ʾ�������˵���
			isoComBox.InsertString(i,stringTemp);
		}
		int avIndex(0);
		for (int i=0 ;i<cameraCtrl.avPropety.numElements;++i)
		{
			CommanderList listTemp;
			listTemp.key = cameraCtrl.avPropety.propDesc[i];
			if (listTemp.key == 0x28)
			{
				avIndex = i;
			}
			listTemp.command = getHashList.FindObject(getHashList.avHashList,listTemp.key);
			avList.push_back(listTemp);
			CString stringTemp;
			stringTemp.Format("%s",listTemp.command.c_str());
			avCombox.InsertString(i,stringTemp);
		}
		int tvIndex(0);
		for (int i=0 ;i<cameraCtrl.tvPropety.numElements;++i)
		{
			CommanderList listTemp;
			listTemp.key = cameraCtrl.tvPropety.propDesc[i];		
			if (listTemp.key == 0x73)
			{
				tvIndex = i;
			}
			listTemp.command = getHashList.FindObject(getHashList.tvHashList,listTemp.key);
			tvList.push_back(listTemp) ;
			CString stringTemp;
			stringTemp.Format("%s",listTemp.command.c_str());
			tvCombox.InsertString(i,stringTemp);
		}
		AfxMessageBox(_T("������ɹ�"));
		CWnd *wd = (CWnd*)GetDlgItem(IDC_PREPARE);
		wd->EnableWindow(TRUE);
		wd = (CWnd*)GetDlgItem(IDC_BUTTON2);
		wd->EnableWindow(TRUE);
		wd = (CWnd*)GetDlgItem(IDC_STOP);
		wd->EnableWindow(TRUE);
		//����Ĭ�ϲ���
		isoComBox.SetCurSel(isoIndex);
		avCombox.SetCurSel(avIndex);
		tvCombox.SetCurSel(tvIndex);
	}
	flag = cameraCtrl.ReleaseCamera();
}
/**************************************************
	������: CCannonDlg::OnBnClickedButton2
	��������: 1.���߳���������ͼ��
	                  2.����ת��ת��������ת�������
					  3.��ʾ�������
					  4.�����ͣ����
					  5.ֹͣ���ܣ�����ʾ�Ƿ񱣴��ϴ������ͼ��
	����: ��
	���: ��
	����ֵ: ��
	����: ��
	�޸���ʷ: ��
*************************************************/
void CCannonDlg::OnBnClickedButton2()
{
	if (isoList.empty()||avList.empty()||tvList.empty())
	{
		AfxMessageBox(_T("����������ʹ�����M��"));
		return;
	}
	if (isPlaneStart == true)
	{
		AfxMessageBox(_T("���Ȱ�����ֹͣ��ʹ���ֹͣת����"));
		return;
	}
	CWnd *wd = (CWnd*)GetDlgItem(IDC_PREPARE);
	wd->EnableWindow(FALSE);
	wd = (CWnd*)GetDlgItem(IDC_BUTTON2);
	wd->EnableWindow(TRUE);
	wd = (CWnd*)GetDlgItem(IDC_STOP);
	wd->EnableWindow(TRUE);
	CWinThread * pThread;
	pThread = AfxBeginThread(threadFunction,(LPVOID)this);
}

UINT CCannonDlg::threadFunction(LPVOID pParam)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCannonDlg* pDlg = (CCannonDlg*)pParam;
	pDlg->stepCount = 0;
	pDlg->stopOrNot = false;
	pDlg->isStop = false;	
	//�������360��
	CCamearControl cameraCtrl;
	//�����
	bool err = cameraCtrl.OpenCamera();
	//�����������
	int isoIndex = pDlg->isoComBox.GetCurSel();
	int avIndex = pDlg->avCombox.GetCurSel();
	int tvIndex = pDlg->tvCombox.GetCurSel();	
	//�����������
	cameraCtrl.SetCameraInfo((EdsUInt32)pDlg->isoList[isoIndex].key,   //iso����
		(EdsUInt32)pDlg->avList[avIndex].key,     //av����
		(EdsUInt32)pDlg->tvList[tvIndex].key);     //tv����
	//������ʱʱ��
	CString str;
	pDlg->GetDlgItem(IDC_TAKEINTERNAL)->GetWindowText(str);
	cameraCtrl.sleepTime = _ttoi(str);
	//������С��ʱΪ5ms
	if (cameraCtrl.sleepTime < 5)
	{
		cameraCtrl.sleepTime = 5;
	}
	//�������
	int speedLevel = pDlg->roundTime.GetCurSel() + 1;
	//ÿ�ŵ�����ʱ��
	double start(0);
	//DWORD end(0);
	//pDlg->SendComOrder(pDlg->timeVector);
	//Sleep(10);
	pDlg->isPlaneStart = true;
	pDlg->SendComOrder(pDlg->timeVector + speedLevel*4);
	while((pDlg->stepCount) < 360)
	{
		start = GetTickCount();
		start += cameraCtrl.sleepTime;
		//ֱ��ֹͣ
		if (pDlg->isStop == true)
		{
			pDlg->SendComOrder(pDlg->timeVector);
			pDlg->isPlaneStart = false;
			//Sleep(10);
			CString errorMessamge;
			errorMessamge.Format("%d��δ����ɹ�",cameraCtrl.counter);
			pDlg->MessageBox(errorMessamge);
			pDlg->stepCount -= cameraCtrl.counter;
			cameraCtrl.ReleaseCamera();
			if (pDlg->MessageBox(_T("�Ƿ��ϴ�ͼ�񵽵����ϣ�"),_T("���棿"),MB_OKCANCEL )==IDOK)
			{		
				//�ϴ�ͼ��
				pDlg->Save();
				AfxMessageBox(_T("�ϴ��ɹ�"));
			}
			return 0 ;
		}
		//����
 		int flag =  cameraCtrl.TakePhotos();
		//������״̬
		if (flag == 2)
		{
			AfxMessageBox(_T("�ڴ濨��������ֹͣ���㣬����ͼƬ��"));
		}
		if (flag == 1)
		{
			AfxMessageBox(_T("�Զ��Խ�ʧ�ܣ�"));
		}	
		//�����������
		pDlg->stepCount++;
		pDlg->SetDlgItemInt(IDC_PICNUMBER,pDlg->stepCount);	
		start -= GetTickCount();
		//��ʱ
		if (start >0)
		{
			Sleep(start);
		}
		else
		{
			Sleep(0);
		}
	}
	//ֹͣת��
	pDlg->SendComOrder(pDlg->timeVector);
	pDlg->isPlaneStart = false;
	//Sleep(10);
	//��ʾ��Ϣ
	CString errorMessamge;
	errorMessamge.Format("%d��δ����ɹ�",cameraCtrl.counter);
	pDlg->MessageBox(errorMessamge);
	pDlg->stepCount -= cameraCtrl.counter;
	cameraCtrl.ReleaseCamera();
	//������ɣ��ϴ�ͼ��
	if (pDlg->MessageBox(_T("�Ƿ��ϴ�ͼ�񵽵����ϣ�"),_T("���棿"),MB_OKCANCEL )==IDOK)
	{		
		pDlg->Save();
		AfxMessageBox(_T("�ϴ��ɹ�"));
	}	
	return 0;
}

/**************************************************
	������: CCannonDlg::OnBnClickedButton2
	��������: 1.�ϴ������������stepCount��ͼ�񵽵�����
	                  2.����洢·����
	����: ��
	���: ��
	����ֵ: ��
	����: ��
	�޸���ʷ: ��
*************************************************/
void CCannonDlg::Save()
{
	CCamearControl saveControl;
	saveControl.OpenCamera();
	CString strPath = dlg1.m_Dlg1Edit4;
	CreateDirectory(strPath,NULL);
	//��ȡ��ǰ����
	CTime tm = CTime::GetCurrentTime();
	CString dateStr = tm.Format("%Y-%m-%d");
	strPath =strPath+"\\"+ dateStr;
	//���������ļ���
	CreateDirectory(strPath,NULL);
	//��ȡ��ǰʱ��
	CString timeStr = tm.Format("%H-%M-%S");
	strPath =strPath+"\\"+ timeStr;
	//�������ļ����´���ʱ���ļ���
	CreateDirectory(strPath,NULL);
	strPath += "\\";
	CString originalStrPath =strPath+ _T("original") + _T("\\");
	CreateDirectory(originalStrPath,NULL);
	//CString str;
	//�õ���Ҫ�ϴ�����Ƭ��
	//GetDlgItem(IDC_PICNUMBER)->GetWindowText(str);
	//stepCount = _ttoi(str);
	vector<string> pathVector;
	for (int i=1;i<=stepCount;++i)
	{	
		CString numtem = _T("");
		CString strTem = _T("");
		strTem.Format(_T("%.3d"),i);
		numtem = strTem;									
		strTem = originalStrPath + strTem;                   
		CString saveOriginalPath = _T("");
		saveOriginalPath = strTem + _T(".jpg");
		CStringA stra(saveOriginalPath.GetBuffer(0));
		std::string orginalImgPath=stra.GetBuffer(0);    
		//���յı���·��string����
		pathVector.push_back(orginalImgPath);
	}
	//������Ҫ�ϴ��������Լ�·�������ϴ�ͼ��
	saveControl.GetImageDirectory(stepCount,pathVector);
	saveControl.ReleaseCamera();
}
/**************************************************
	������: CCannonDlg::OnBnClickedPrepare
	��������: 1.���Թ���
	                  2.��һ����Ƭ�����ұ����ڵ�����
					  3.�Ը���Ƭ���п�ͼ����
	����: ��
	���: ��
	����ֵ: ��
	����: ��
	�޸���ʷ: ��
*************************************************/
void CCannonDlg::OnBnClickedPrepare()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strPath = dlg1.m_Dlg1Edit4;
	CCamearControl cameraPrePare;
	cameraPrePare.prepareFlag=true;
	CString numtem = _T("");
	CString strTem = _T("");
	strTem = strPath + strTem;                    
	CString saveOriginalPath = _T("");
	saveOriginalPath = strTem +_T("_test")+ _T(".jpg");
	CStringA stra(saveOriginalPath.GetBuffer(0));
	//ԭͼ·��
	std::string imgPath=stra.GetBuffer(0);           
	//����ͼ��·��
	saveOriginalPath = strTem +_T("_test_process")+ _T(".jpg");
	CStringA stra2(saveOriginalPath.GetBuffer(0));
	std::string  processImgPath=stra2.GetBuffer(0);
	//�����
	bool flag = cameraPrePare.OpenCamera();
	int isoIndex = isoComBox.GetCurSel();
	int avIndex = avCombox.GetCurSel();
	int tvIndex = tvCombox.GetCurSel();	
	//�����������
	cameraPrePare.SetCameraInfo((EdsUInt32)isoList[isoIndex].key,
												   	  (EdsUInt32)avList[avIndex].key,
												 	  (EdsUInt32)tvList[tvIndex].key);
	//����
	flag =  cameraPrePare.TakePhotos();	
	//�������״̬
	if (flag == 2)
	{
		AfxMessageBox(_T("�ڴ濨��������ֹͣ���㣬����ͼƬ��"));
	}
	if (flag == 1)
	{
		AfxMessageBox(_T("�Զ��Խ�ʧ�ܣ�"));
	}
	Sleep(2000);
	flag = cameraPrePare.ReleaseCamera();
	//���ظ�ͼ��
	CCamearControl download;
	download.prepareFlag = true;
	download.orginalImgPath = imgPath;
	flag = download.OpenCamera();
	//��ʾ��ͼ��
	showImage(imread(download.orginalImgPath),IDC_IMAGE);
	flag = download.ReleaseCamera();
}

void CCannonDlg::showImage(Mat img,UINT ID)
{
	
	CDC *pDC = GetDlgItem(ID)->GetDC(); 
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;  
	GetDlgItem(ID)->GetClientRect(&rect); 
	resize(img,img,Size(1200,800));
	IplImage image=img;
	CvvImage cimg;
	// ����ͼƬ
	cimg.CopyOf(&image ); 
	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	cimg.DrawToHDC( hDC, &rect ); 
	ReleaseDC( pDC );
}




UINT CCannonDlg::ProcessImage(LPVOID pParam)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����һ���߳�
	CWinThread*   pThreadProcess;
	//ThreadVideoPlay���̺߳���
	//pThreadProcess   =   AfxBeginThread(ProcessImage,(LPVOID) this);
	return 1;
}


//UINT CCannonDlg::ProcessImage(LPVOID pParam)
void CCannonDlg::OnBnClickedProcessimage()
{
	TCHAR    szPath[MAX_PATH];
	CString path = dlg1.m_Dlg1Edit4 + "\\";
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
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = LPARAM(szPath);
	bi.iImage=0;
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if(pIDList)
	{
		//SHSetFolderPath(pIDList,)
		SHGetPathFromIDList(pIDList, szPath);
		//ȡ���ļ���·����Buffer��
		sFolderPath = szPath ;//���ļ���·��������һ��CString������
		//sFolderPath += "\\";
	}


	//CFileFind finderDict;
	vector<CString> folderVec;
	BOOL bResult;
	//bResult = finderDict.FindFile(sFolderPath);
	CString strPath ;//= finder.GetFileName();
	//while (bResult)
	//{
	//	bResult = finderDict.FindNextFile();
	//	//�ж��Ƿ���Ŀ¼�����������ļ����ֻ�����".."��"."������ǣ�������һ��ѭ��
	//	if (finderDict.IsDirectory())
	//	{
	//		CString str;
	//		//�õ��ļ���
	//		strPath = finderDict.GetRoot();
	//		sFolderPath += "\\*.*";
	//		//fileName = finder.GetFileTitle();
	//	}
	//}
	//finderDict.Close();



	CFileFind finder;
	//CString fileName;
	
	//unsigned long filenum=0;
	bResult=finder.FindFile(sFolderPath);
	//= finder.GetFileName();
	//while (bResult)
	//{
	vector<CString> rootVec;
	bResult = finder.FindNextFile();
	//�ж��Ƿ���Ŀ¼�����������ļ����ֻ�����".."��"."������ǣ�������һ��ѭ��
	if (finder.IsDirectory())
	{
		CString str;
		//�õ��ļ���
		sFolderPath += "\\*";
		bResult = finder.FindFile(sFolderPath);
		while(bResult)
		{
			//str = finder.GetFilePath();
			bResult = finder.FindNextFile();
			if( finder.IsDots() || finder.IsHidden())
				continue;
			//str = finder.GetFilePath();
			if (finder.IsDirectory())
			{
				//str = finder.GetFilePath();
				rootVec.push_back(finder.GetFilePath() + "\\");
				folderVec.push_back(finder.GetFilePath() + "\\original\\*.*");
			}
		}	
	}
	finder.Close();

	vector<vector<CString>> filePathVec;
	for (size_t i = 0; i<folderVec.size(); ++i)
	{
		CFileFind finder1;
		vector<CString> filePath;
		BOOL result1 = finder1.FindFile(folderVec[i]);
		while (result1)
		{
			result1 = finder1.FindNextFile();
			if(finder1.IsDirectory()|| finder1.IsDots() || finder1.IsHidden())
				continue;
			else//������ļ�
			{
				CString str;
				//�õ��ļ���
				str = finder1.GetFileName();
				//�õ��ļ���׺��
				int nLen = str.GetLength() - finder1.GetFileTitle().GetLength();
				str = str.Right(nLen);
				//�ж��ļ���ʽ�������ͼ���ļ�������������·���������б���
				if(str == ".jpg" || str == ".png" || str == ".bmp" || str == ".gif")
				{
					filePath.push_back(finder1.GetFilePath());
				}
			}		
		}
		filePathVec.push_back(filePath);
		finder1.Close();
	}
	


	vector<CString> pathVector;
	//if (pDlg->dlg1.m_Width != ""&& _ttoi(pDlg->dlg1.m_Width) )
	if (dlg1.m_Width != ""&& _ttoi(dlg1.m_Width) )
	{
		pathVector.push_back(dlg1.m_Width);
	}
	//if (pDlg->dlg1.m_Height != ""&& _ttoi(pDlg->dlg1.m_Height))
	if (dlg1.m_Height != ""&& _ttoi(dlg1.m_Height))
	{
		pathVector.push_back(dlg1.m_Height);
	}
	//if (pDlg->dlg1.m_Width3 != ""&& _ttoi(pDlg->dlg1.m_Width3))
	if (dlg1.m_Width3 != ""&& _ttoi(dlg1.m_Width3))
	{
		pathVector.push_back(dlg1.m_Width3);
	}

	vector<vector<CString>> resizePath;
	
	for (int fileIter = 0; fileIter < rootVec.size(); ++fileIter)
	{
		vector<CString> resizePathVec;
		CFileFind isExist;
		for (int i=0;i<pathVector.size();++i)
		{
			CString strPathTemp = rootVec[fileIter];
			strPathTemp += _T("Size_") + pathVector[i] +_T("\\");
			bool flag = isExist.FindFile(strPathTemp);
			if (flag == false)
			{ 
				CreateDirectory(strPathTemp,NULL);
			}
			//else
			//{
			strPathTemp += _T("\\");
			//}
			CString resizeStrPath = strPathTemp+ _T("resize") + _T("\\");
			resizePathVec.push_back(resizeStrPath);
			CreateDirectory(resizeStrPath,NULL);
		}
		resizePath.push_back(resizePathVec);
		isExist.Close();
	}
	
	
	for (int folderIter = 0; folderIter < filePathVec.size() ; ++folderIter)
	{
		vector<CString> filePath = filePathVec[folderIter];
		ProImage batchImage;
		for (int i=0;i<filePath.size();++i)
		{				
			CStringA stra(filePath[i].GetBuffer(0));
			std::string orginalImgPath=stra.GetBuffer(0); 
			batchImage.orginalImgPath = orginalImgPath;
			Mat temp = imread(orginalImgPath);
			showImage(temp,IDC_IMAGE);
			vector<proSave> savePathVec;
			CString numtem = _T("");
			CString strTem = _T("");
			strTem.Format(_T("%.3d"),i+1);
			numtem = strTem;

			for (int j=0;j<pathVector.size();++j)
			{
				CString saveResizePath = _T("");
				saveResizePath = resizePath[folderIter][j] + numtem + _T(".jpg");      //���յı���·��CString����
				CStringA stra1(saveResizePath.GetBuffer(0));
				std::string resizeImgPath=stra1.GetBuffer(0);

				proSave saveTemp;
				saveTemp.width = _ttoi(pathVector[j]);
				saveTemp.resizePath = resizeImgPath;

				savePathVec.push_back(saveTemp);		
			}
			//batchImage.threhold =  (uchar) pDlg-> m_ScrollBar.GetScrollPos();
			batchImage.threhold =  (uchar)  m_ScrollBar.GetScrollPos();
			batchImage.processImage(savePathVec,false);
		}
	}
	
	AfxMessageBox(_T("�����������"));
	return;
}

void CCannonDlg::OnBnClickedSingalprocess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()!=IDOK)
		return;
	CStringA stra1(dlg.GetPathName().GetBuffer(0));
	std::string mgPath=stra1.GetBuffer(0);

	CString str;
	//�õ��ļ���׺��
	int nLen = dlg.GetPathName().GetLength() - dlg.GetFileName().GetLength();
	str = dlg.GetPathName().Left(nLen-1);
	CFileFind getRootPath;
	bool flg = getRootPath.FindFile(str);
	flg = getRootPath.FindNextFile();
	CString rootPath = getRootPath.GetRoot();

	getRootPath.Close();

	vector<CString> pathVector;
	//if (pDlg->dlg1.m_Width != ""&& _ttoi(pDlg->dlg1.m_Width) )
	if (dlg1.m_Width != ""&& _ttoi(dlg1.m_Width) )
	{
		pathVector.push_back(dlg1.m_Width);
	}
	//if (pDlg->dlg1.m_Height != ""&& _ttoi(pDlg->dlg1.m_Height))
	if (dlg1.m_Height != ""&& _ttoi(dlg1.m_Height))
	{
		pathVector.push_back(dlg1.m_Height);
	}
	//if (pDlg->dlg1.m_Width3 != ""&& _ttoi(pDlg->dlg1.m_Width3))
	if (dlg1.m_Width3 != ""&& _ttoi(dlg1.m_Width3))
	{
		pathVector.push_back(dlg1.m_Width3);
	}

	vector<CString> resizePathVec;

	for (int i=0;i<pathVector.size();++i)
	{

		CString strPathTemp = rootPath;
		strPathTemp += _T("Size_") + pathVector[i] + _T(".jpg");  ;
		resizePathVec.push_back(strPathTemp);

	}

	ProImage batchImage;

	batchImage.orginalImgPath = mgPath;
	Mat tempImage = imread(mgPath);
	showImage(tempImage,IDC_IMAGE);

	vector<proSave> savePathVec;

	for (int j=0;j<pathVector.size();++j)
	{
		CString saveResizePath = _T("");
		saveResizePath = resizePathVec[j] ;     //���յı���·��CString����
		CStringA stra1(saveResizePath.GetBuffer(0));
		std::string resizeImgPath=stra1.GetBuffer(0);

		proSave saveTemp;
		saveTemp.width = _ttoi(pathVector[j]);
		saveTemp.resizePath = resizeImgPath;

		savePathVec.push_back(saveTemp);		
	}
	batchImage.processImage(savePathVec,false);
	AfxMessageBox(_T("�������"));
}


int CALLBACK  CCannonDlg::BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)  
{
	CStdioFile file;

	CString dataInfo;

	if (file.Open(_T("data.txt"),CFile::typeText|CFile::modeReadWrite))
	{
		file.SeekToBegin();	

		file.ReadString(dataInfo);

		file.ReadString(dataInfo);

		file.ReadString(dataInfo);

		file.ReadString(dataInfo);

	}
	CStringA str(dataInfo.GetBuffer(0));
	std::string orginalImgPath=str.GetBuffer(0);
	const char * filePath = orginalImgPath.c_str();
	file.Close();
	if (uMsg == BFFM_INITIALIZED)
	{ 

		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)filePath);   

	}  

	return 0;     
}

void CCannonDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isStop = !isStop;
}


void CCannonDlg::OnBnClickedBatachimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR    szPath[MAX_PATH];
	//ZeroMemory(szPath,   MAX_PATH); 
	//CString strDef(_T("C:\\WINDOWS\\"));
	//memcpy(szPath,strDef.GetBuffer(strDef.GetLength()),strDef.GetLength());
	CString path = dlg1.m_Dlg1Edit4 + "\\";
	memcpy(szPath,path.GetBuffer(path.GetLength()),path.GetLength());

	//CCannonDlg* pDlg=(CCannonDlg*)pParam;
	CString sFolderPath;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(bi));
	//TCHAR tchPath[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = this->GetSafeHwnd();
	//bi.pszDisplayName = 0;
	bi.pidlRoot = NULL;//��ʼ���ƶ���rootĿ¼
	bi.pszDisplayName = szPath;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle =_T("���ļ���");
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//�����ļ�
	bi.ulFlags = BIF_EDITBOX;//�����ļ�
	bi.lpfn = BrowseCallbackProc;
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
	}


	CFileFind finder;
	CString fileName;
	vector<CString> filePath;
	unsigned long filenum=0;
	BOOL bResult=finder.FindFile(sFolderPath);
	CString strPath ;//= finder.GetFileName();
	while (bResult)
	{
		bResult = finder.FindNextFile();
		//�ж��Ƿ���Ŀ¼�����������ļ����ֻ�����".."��"."������ǣ�������һ��ѭ��
		if (finder.IsDirectory())
		{
			CString str;
			//�õ��ļ���
			strPath = finder.GetRoot();
			sFolderPath += "\\*.*";
			fileName = finder.GetFileTitle();
		}
	}
	finder.Close();
	CFileFind finder1;
	BOOL result1 = finder1.FindFile(sFolderPath);
	while (result1)
	{
		result1 = finder1.FindNextFile();
		if(finder1.IsDirectory()|| finder1.IsDots() || finder1.IsHidden())
			continue;
		else//������ļ�
		{
			CString str;
			//�õ��ļ���
			str = finder1.GetFileName();
			//�õ��ļ���׺��
			int nLen = str.GetLength() - finder1.GetFileTitle().GetLength();
			str = str.Right(nLen);
			//�ж��ļ���ʽ�������ͼ���ļ�������������·���������б���
			if(str == ".jpg" || str == ".png" || str == ".bmp" || str == ".gif")
			{
				filePath.push_back(finder1.GetFilePath());
			}
		}		
	}
	finder1.Close();


	vector<CString> pathVector;
	//if (pDlg->dlg1.m_Width != ""&& _ttoi(pDlg->dlg1.m_Width) )
	if (dlg1.m_Width != ""&& _ttoi(dlg1.m_Width) )
	{
		pathVector.push_back(dlg1.m_Width);
	}
	//if (pDlg->dlg1.m_Height != ""&& _ttoi(pDlg->dlg1.m_Height))
	if (dlg1.m_Height != ""&& _ttoi(dlg1.m_Height))
	{
		pathVector.push_back(dlg1.m_Height);
	}
	//if (pDlg->dlg1.m_Width3 != ""&& _ttoi(pDlg->dlg1.m_Width3))
	if (dlg1.m_Width3 != ""&& _ttoi(dlg1.m_Width3))
	{
		pathVector.push_back(dlg1.m_Width3);
	}


	vector<CString> processPathVec;
	CFileFind isExist;
	for (int i=0;i<pathVector.size();++i)
	{
		CString strPathTemp = strPath;
		strPathTemp += _T("Size_") + pathVector[i];// +_T("\\");
		bool flag = isExist.FindFile(strPathTemp);
		if (flag == false)
		{
			//strPathTemp += _T("\\");
			CreateDirectory(strPathTemp,NULL);
		}
		//else
		//{
			strPathTemp += _T("\\");
	//	}
		CString processStrPath =strPathTemp+ _T("process") + _T("\\");
		processPathVec.push_back(processStrPath);
		CreateDirectory(processStrPath,NULL);
	}
	isExist.Close();
	//isExist.~CFileFind();
	ProImage batchImage;
	for (int i=0;i<filePath.size();++i)
	{		

		CStringA stra(filePath[i].GetBuffer(0));
		std::string orginalImgPath=stra.GetBuffer(0); 
		batchImage.orginalImgPath = orginalImgPath;
		Mat temp = imread(orginalImgPath);
		showImage(temp,IDC_IMAGE);
		vector<proSave> savePathVec;
		CString numtem = _T("");
		CString strTem = _T("");
		strTem.Format(_T("%.3d"),i+1);
		numtem = strTem;

		for (int j=0;j<pathVector.size();++j)
		{

			proSave saveTemp;
			saveTemp.width = _ttoi(pathVector[j]);

			CString saveResizeProcessPath = _T("");
			saveResizeProcessPath = processPathVec[j] + numtem  + _T(".jpg");      //���յı���·��CString����
			CStringA stra2(saveResizeProcessPath.GetBuffer(0));
			std::string processImgPath=stra2.GetBuffer(0);
			saveTemp.processPath = processImgPath;
			saveTemp.resizePath = _T("");
			savePathVec.push_back(saveTemp);		
		}
		//batchImage.threhold =  (uchar) pDlg-> m_ScrollBar.GetScrollPos();
		batchImage.threhold =  (uchar)  m_ScrollBar.GetScrollPos();
		batchImage.processImage(savePathVec,true);
	}
	AfxMessageBox(_T("�����������"));
	return;
}




 
void CCannonDlg::OnBnClickedSingleimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()!=IDOK)
		return;
	CStringA stra1(dlg.GetPathName().GetBuffer(0));
	std::string mgPath=stra1.GetBuffer(0);

	CString str;
	//�õ��ļ���׺��
	int nLen = dlg.GetPathName().GetLength() - dlg.GetFileName().GetLength();
	str = dlg.GetPathName().Left(nLen-1);
	CFileFind getRootPath;
	bool flg = getRootPath.FindFile(str);
	flg = getRootPath.FindNextFile();
	CString rootPath = getRootPath.GetRoot();

	getRootPath.Close();

	vector<CString> pathVector;
	//if (pDlg->dlg1.m_Width != ""&& _ttoi(pDlg->dlg1.m_Width) )
	if (dlg1.m_Width != ""&& _ttoi(dlg1.m_Width) )
	{
		pathVector.push_back(dlg1.m_Width);
	}
	//if (pDlg->dlg1.m_Height != ""&& _ttoi(pDlg->dlg1.m_Height))
	if (dlg1.m_Height != ""&& _ttoi(dlg1.m_Height))
	{
		pathVector.push_back(dlg1.m_Height);
	}
	//if (pDlg->dlg1.m_Width3 != ""&& _ttoi(pDlg->dlg1.m_Width3))
	if (dlg1.m_Width3 != ""&& _ttoi(dlg1.m_Width3))
	{
		pathVector.push_back(dlg1.m_Width3);
	}

	vector<CString> resizePathVec;

	for (int i=0;i<pathVector.size();++i)
	{

		CString strPathTemp = rootPath;
		strPathTemp += _T("Size_") + pathVector[i] +_T("_Process")+ _T(".jpg");  ;
		resizePathVec.push_back(strPathTemp);

	}

	ProImage batchImage;

	batchImage.orginalImgPath = mgPath;
	Mat tempImage = imread(mgPath);
	showImage(tempImage,IDC_IMAGE);

	vector<proSave> savePathVec;

	for (int j=0;j<pathVector.size();++j)
	{
		CString saveResizePath = _T("");
		saveResizePath = resizePathVec[j] ;     //���յı���·��CString����
		CStringA stra1(saveResizePath.GetBuffer(0));
		std::string processImgPath=stra1.GetBuffer(0);

		proSave saveTemp;
		saveTemp.width = _ttoi(pathVector[j]);
		saveTemp.processPath = processImgPath;

		savePathVec.push_back(saveTemp);		
	}
	batchImage.processImage(savePathVec,true);
	AfxMessageBox(_T("�������"));
}
//�õ�ϵͳcomlist
void CCannonDlg::GetSystemCom()
{
	CRegKey RegKey;  
	int nCount = 0;       //���ڵĸ���
	CString tempCStr;  //"Hardware//DeviceMap//SerialComm"
	//  long flag = RegKey.Open(HKEY_LOCAL_MACHINE,"Hardware\\DeviceMap\\SerialComm");
	if(RegKey.Open(HKEY_LOCAL_MACHINE,"Hardware\\DeviceMap\\SerialComm") == ERROR_SUCCESS)    
	{    
		while(true)    
		{    
			char ValueName[_MAX_PATH];    
			unsigned char ValueData[_MAX_PATH];    
			DWORD nValueSize = _MAX_PATH;    
			DWORD nDataSize = _MAX_PATH;    
			DWORD nType;    
			//RegEnumValue������������,�ӱ�ָ���򿪵�ע��������о����е�ֵ
			//�⺯��ÿ����һ�ξͻ´��һ������ֵ�����ƺ����ݿ� 
			if(::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)    
			{    
				break;    
			}
			if(strlen((char*)ValueData))
			{
				tempCStr.Format("%s",ValueData);
				comList.AddString(tempCStr);
			}
			nCount++;
		}    
	}
}

void CCannonDlg::OnBnClickedOpencom()
{
	// 
	if (comFlag == false)
	{
		CString strtemp;
		CHAR ValueData[_MAX_PATH];   
		DWORD nValueSize = _MAX_PATH;   
		comList.GetWindowText(ValueData,nValueSize);
		strtemp = ValueData;
		hCom=CreateFile(strtemp,//COM1��
			GENERIC_READ|GENERIC_WRITE, //�������д
			0, //��ռ��ʽ
			NULL,
			OPEN_EXISTING, //�򿪶����Ǵ���
			0, //ͬ����ʽ
			NULL);
		if(hCom==(HANDLE)-1)
		{
			AfxMessageBox("��COMʧ��!");
			return ;
		}

		SetupComm(hCom,100,100); 

		COMMTIMEOUTS TimeOuts;

		TimeOuts.ReadIntervalTimeout=MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier=1;
		TimeOuts.ReadTotalTimeoutConstant=5;


		TimeOuts.WriteTotalTimeoutMultiplier=100;
		TimeOuts.WriteTotalTimeoutConstant=500;
		SetCommTimeouts(hCom,&TimeOuts); 
		DCB dcb;
		DWORD errret;
		GetCommState(hCom,&dcb);
		//����ͨѶ����
		dcb.BaudRate=9600; 
		dcb.ByteSize=8; 
		dcb.Parity=NOPARITY; 
		dcb.StopBits=ONESTOPBIT; 
		if(!SetCommState(hCom,&dcb))
			errret = GetLastError();
		if (errret == 0)
		{
			MessageBox(_T("���ô���"));
		}
		//PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
		CWnd *wd = (CWnd*)GetDlgItem(IDC_OPENCOM);
		wd->SetWindowText(TEXT("�رմ���"));
		comList.EnableWindow(FALSE);

		roundTime.AddString(_T("1����"));
		roundTime.AddString(_T("2����"));
		roundTime.AddString(_T("3����"));
		roundTime.AddString(_T("4����"));
		roundTime.AddString(_T("5����"));
		roundTime.AddString(_T("6����"));
		roundTime.SetCurSel(5);
		comFlag = true;
	}
	else
	{
		if (MessageBox(_T("�Ƿ�ر�ת�̣�"),_T("�ر�"),MB_OKCANCEL )==IDOK)
		{		
			//�ر�ת��
			SendComOrder(timeVector);
			CloseHandle(hCom);	
			comFlag = false;
			CWnd *wd = (CWnd*)GetDlgItem(IDC_OPENCOM);
			wd->SetWindowText(_T("�򿪴���"));
			comList.EnableWindow(TRUE);
			roundTime.ResetContent();
		}	
	}
}

bool CCannonDlg::SendComOrder(unsigned char *lpBuffer )
{
	unsigned char setBuffer[4];
	setBuffer[0] = lpBuffer[0];
	setBuffer[1] = lpBuffer[1];
	setBuffer[2] = lpBuffer[2];
	setBuffer[3] = lpBuffer[3];
	DWORD dwBytesWrite=4;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,setBuffer,dwBytesWrite,& dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		AfxMessageBox("д����ʧ��!");
		return false;
	}
	return true;
}


void CCannonDlg::SetTimeVec()
{
	//unsigned char lpOutBuffer[4*7];
	memset(timeVector,0,4*7); //ǰ4*7���ֽ�������
	//ֹͣ
	timeVector[0]=0xaa; //֡ͷ
	timeVector[1]=0xca; //����
	timeVector[2]=0x04; //У���루֡ͷ+���&0xf
	timeVector[3]=0x55; //֡β
	//timeVector.push_back(lpOutBuffer);
	//1min�ٶ�
	timeVector[1*4+0]=0xaa; 
	timeVector[1*4+1]=0xda; 
	timeVector[1*4+2]=0x04; 
	timeVector[1*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//2min�ٶ�
	timeVector[2*4+0]=0xaa; 
	timeVector[2*4+1]=0xdb; 
	timeVector[2*4+2]=0x05; 
	timeVector[2*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//3min�ٶ�
	timeVector[3*4+0]=0xaa;
	timeVector[3*4+1]=0xdc; 
	timeVector[3*4+2]=0x06; 
	timeVector[3*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//4min�ٶ�
	timeVector[4*4+0]=0xaa; 
	timeVector[4*4+1]=0xdd; 
	timeVector[4*4+2]=0x07; 
	timeVector[4*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//5min�ٶ�
	timeVector[5*4+0]=0xaa; 
	timeVector[5*4+1]=0xde; 
	timeVector[5*4+2]=0x08; 
	timeVector[5*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//6min�ٶ�
	timeVector[6*4+0]=0xaa; 
	timeVector[6*4+1]=0xdf; 
	timeVector[6*4+2]=0x09; 
	timeVector[6*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
}

void CCannonDlg::OnBnClickedExit()
{
	if (MessageBox(_T("�Ƿ��˳���"),_T("�˳�"),MB_OKCANCEL )==IDOK)
	{	
		if (comFlag == true)
		{
			SendComOrder(timeVector);
			CloseHandle(hCom);	
			comFlag = false;
			CWnd *wd = (CWnd*)GetDlgItem(IDC_OPENCOM);
			wd->SetWindowText(_T("�򿪴���"));
			comList.EnableWindow(TRUE);
			roundTime.ResetContent();
		}	
		CDialogEx::OnCancel();
	}	
}


void CCannonDlg::OnBnClickedButton4()
{
	// 
	if(IDOK == dlg1.DoModal())
	{
		UpdateData(TRUE);
	}
}


void CCannonDlg::OnBnClickedTeststart()
{
	//
	//�������
	if (isPlaneStart == true)
	{
		AfxMessageBox(_T("���Ȱ�����ֹͣ��ʹ���ֹͣת����"));
		return;
	}
	isPlaneStart = true;
	int speedLevel = roundTime.GetCurSel() + 1;
	SendComOrder(timeVector + speedLevel*4);
}


void CCannonDlg::OnBnClickedTeststop()
{
	//ֹͣ
	SendComOrder(timeVector);
	isPlaneStart = false;
}

void CCannonDlg::numinfile(string path,int &num,char& ch1,char& ch2,char& ch3)
{
	char buf[300];
	char buf1[20];
	fstream in(path);
	int acc=0;
	char zf1,zf2,zf3;

	for(acc=0;acc<13;acc++)
	{
		in.getline(buf,300);	
		if (acc==0)
		{
			zf1 = buf[0];
		}
		if (acc==1)
		{
			zf2 = buf[0];
		}
		if (acc==2)
		{
			zf3 = buf[0];
		}
		//cout<<buf<<endl;
	}
	int sizenum1,sizenum2=0;
	sizenum1 = strlen(buf);
	memset(buf1,0,20);
	for (int i=0;i<sizenum1;i++)
	{
		char tem;
		tem = buf[i];
		if (tem != ' ')
		{
			buf1[i]=buf[i];
			sizenum2++;
		}
		else
		{
			break;
		}
	}
	int numtotal = 0;
	switch (sizenum2)
	{
	case 1:
		numtotal = (buf[0]-65);
		break;
	case 2:
		numtotal = (buf[0]-65)*10+(buf[1]-65);
		break;
	case 3:
		numtotal = (buf[0]-65)*100+(buf[1]-65)*10+(buf[2]-65);
		break;
	}
	num=numtotal;
	ch1=zf1;
	ch2=zf2;
	ch3=zf3;
}
void CCannonDlg::savechangetofile(string path,int num)
{
	char buf[300];
	char buf1[20];
	fstream in(path);
	ofstream outfile("in2.txt",ios::out|ios::trunc);

	int acc;
	for(acc=0;acc<13;acc++)
	{
		in.getline(buf,300);	
		if (acc!=12)
		{
			outfile<<buf<<endl;
		}
	}

	int numtotal = num;
	char savechar[10];
	if(numtotal>=0&&numtotal<=9)
	{
		savechar[0]=numtotal+65;
		savechar[1]='\0';
	}
	else if(numtotal>=10&&numtotal<=99)
	{
		int shi,ge;
		shi=numtotal/10;
		ge=numtotal%10;
		shi+=65;
		ge+=65;
		savechar[0]=shi;
		savechar[1]=ge;
		savechar[2]='\0';
	}
	else if (numtotal>=100&&numtotal<=999)
	{
		int bai,shi,ge;
		int tem;
		bai = numtotal/100;
		tem = numtotal%100;
		shi = tem/10;
		ge = tem%10;
		bai+=65;
		shi+=65;
		ge+=65;
		savechar[0]=bai;
		savechar[1]=shi;
		savechar[2]=ge;
		savechar[3]='\0';
	}
	string str=savechar;
	str += " is writen by xarkit.";
	outfile<<str<<endl;
	in.close();
	outfile.close();

	string line;
	ofstream outfile1(path,ios::out|ios::trunc);
	fstream file1("in2.txt");    
	while(!file1.eof())
	{          
		getline(file1,line);
		outfile1<<line<<endl;
	} 
	outfile1.close();
	file1.close();
	system("del in2.txt");//ɾ���м��ļ�
}

