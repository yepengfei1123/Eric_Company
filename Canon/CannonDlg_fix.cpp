
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


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    


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



BOOL CCannonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
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
	}
	
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	//设置滑动条范围（0,255）,初始值为160
	InitializeScroll(m_ScrollBar,0,255,160);

	//抠图处理阈值初始化为160
	this.threhold = m_ScrollBar.GetScrollPos();

	//显示滑动条当前阈值
	EditDisplayNum(threhold,IDC_EDIT1);
	UpdateData(TRUE);

	CWnd *wd = (CWnd*)GetDlgItem(IDC_PREPARE);
	wd->EnableWindow(FALSE);
	wd = (CWnd*)GetDlgItem(IDC_BUTTON2);
	wd->EnableWindow(FALSE);
	wd = (CWnd*)GetDlgItem(IDC_STOP);
	wd->EnableWindow(FALSE);
	//获取系统串口端口
	std::vector<string> comStringVec;
	GetSystemCom(comStringVec);
	//把stringvec压入Comlist中
	StringVecToCComboBox(comStringVec,comList);
	//转盘档位命令
	SetTimeVec(timeVector,sizeof(timeVector)/sizeof(unsigned char));
	//默认显示找到的第一个串口
	comList.SetCurSel(0);
	//初始化串口表示位为false
	comFlag = false;
	//转盘状态
	isPlaneStart = true;

/*
	char buf[300];
	char buf1[10];
	int nn;
	char c1,c2,c3;
	string pp="copyrights.txt";
	string pp1="in2.txt";
	numinfile(pp,nn,c1,c2,c3);
	if (nn >= 100)
	{
		AfxMessageBox("超过使用期限");
		CDialogEx::OnCancel();
	}
	else
	{
		savechangetofile(pp,nn+1);
	}
*/
	return TRUE;  //除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCannonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCannonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCannonDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CSliderCtrl* pSliderCtl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int ScrollVal = m_ScrollBar.GetScrollPos();
	//显示滑动条位置
	EditDisplayNum(ScrollVal,IDC_EDIT1);
	switch (nSBCode)
	{    
		// 如果向左滚动一列，则pos减1    
		case SB_LINEUP:
			ScrollVal -= 1;    
			break;    
		// 如果向右滚动一列，则pos加1    
		case SB_LINEDOWN:    
			ScrollVal  += 1;    
			break;    
		// 如果向左滚动一页，则pos减10  
		case SB_PAGEUP:    
			ScrollVal -= 10;    
			break;    
		// 如果向右滚动一页，则pos加10 
		case SB_PAGEDOWN:    
			 ScrollVal  += 10;    
			 break;    
		// 如果滚动到最左端，则pos为1 
		case SB_TOP:    
			 ScrollVal = 0;    
			 break;    
		// 如果滚动到最右端，则pos为100 
		case SB_BOTTOM:    
			 ScrollVal = 255;    
			 break;      
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值 
		case SB_THUMBPOSITION:    
			 ScrollVal = nPos;    
			 break;    
		//下面的m_ScrollBar.SetScrollPos(ScrollVal);执行时会第二次进入此函数，最终确定滚动块位置，并且会直接到default分支，所以在此处设置编辑框中显示数值   
		default:    
			SetDlgItemInt(IDC_EDIT1, ScrollVal);   
			return;    
	} 
	//设置滚动块位置
	m_ScrollBar.SetScrollPos(ScrollVal);   
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



/**************************************************
	函数名: CCannonDlg::OnClickedButtonOpen
	功能描述: 1.检测相机是否打开，利用相机属性下拉菜单是否有值
	          2.利用CCamearControl检测是否可以正常打开相机
			  3.得到相机可以设置的ISO、AV、TV命令
			  4.设置相机默认参数
	输入: 无
	输出: 无
	返回值: 无
	其他: 无
	修改历史: 无
*************************************************/
void CCannonDlg::OnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isoList.empty())
	{
		AfxMessageBox(_T("相机已打开"));
		return;
	}
	CCamearControl cameraCtrl;
	//打开相机
	switch (OpenCamera())
	{
		//如果没有相机，返回错误信息
		case CAMERA_CTRL_NOCAMERA:
			AfxMessageBox(_T("没有相机！"));
			return;
		case CAMERA_CTRL_CONNECTERROR:
			AfxMessageBox(_T("连接错误，请检查连接线！"));
			return;
		case CAMERA_CTRL_OK:
			AfxMessageBox(_T("相机打开成功！"));
			return;
		default: 
			AfxMessageBox(_T("错误")); 
			return;	
	}


	/*
	bool flag = cameraCtrl.OpenCamera();
	if (flag == false)
	{
		AfxMessageBox(_T("获取相机失败"));
	}
	
	else
	{
	*/
		//得到相机可以设置的参数信息
		flag = cameraCtrl.GetCameraInfo();
		//创建哈希表
		CHashList getHashList;
		getHashList.CreatAllList();
		int isoIndex(0);
		//利用哈希表得到命令对应的命令含义
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
			//命令含义显示在下拉菜单中
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
		AfxMessageBox(_T("打开相机成功"));
		CWnd *wd = (CWnd*)GetDlgItem(IDC_PREPARE);
		wd->EnableWindow(TRUE);
		wd = (CWnd*)GetDlgItem(IDC_BUTTON2);
		wd->EnableWindow(TRUE);
		wd = (CWnd*)GetDlgItem(IDC_STOP);
		wd->EnableWindow(TRUE);
		//设置默认参数
		isoComBox.SetCurSel(isoIndex);
		avCombox.SetCurSel(avIndex);
		tvCombox.SetCurSel(tvIndex);
	//}
	flag = cameraCtrl.ReleaseCamera();
}
/**************************************************
	函数名: CCannonDlg::OnBnClickedButton2
	功能描述: 1.开线程批量拍摄图像
	                  2.控制转盘转动（控制转盘软件）
					  3.显示拍摄进程
					  4.添加暂停功能
					  5.停止功能，会提示是否保存上次拍摄的图像
	输入: 无
	输出: 无
	返回值: 无
	其他: 无
	修改历史: 无
*************************************************/
void CCannonDlg::OnBnClickedButton2()
{
	if (isoList.empty()||avList.empty()||tvList.empty())
	{
		AfxMessageBox(_T("请打开相机或者使相机置M档"));
		return;
	}
	if (isPlaneStart == true)
	{
		AfxMessageBox(_T("请先按测试停止，使电机停止转动！"));
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
	// TODO: 在此添加控件通知处理程序代码
	CCannonDlg* pDlg = (CCannonDlg*)pParam;
	pDlg->stepCount = 0;
	pDlg->stopOrNot = false;
	pDlg->isStop = false;	
	//最多拍摄360张
	CCamearControl cameraCtrl;
	//打开相机
	bool err = cameraCtrl.OpenCamera();
	//设置相机参数
	int isoIndex = pDlg->isoComBox.GetCurSel();
	int avIndex = pDlg->avCombox.GetCurSel();
	int tvIndex = pDlg->tvCombox.GetCurSel();	
	//设置相机参数
	cameraCtrl.SetCameraInfo((EdsUInt32)pDlg->isoList[isoIndex].key,   //iso参数
		(EdsUInt32)pDlg->avList[avIndex].key,     //av参数
		(EdsUInt32)pDlg->tvList[tvIndex].key);     //tv参数
	//设置延时时间
	CString str;
	pDlg->GetDlgItem(IDC_TAKEINTERNAL)->GetWindowText(str);
	cameraCtrl.sleepTime = _ttoi(str);
	//设置最小延时为5ms
	if (cameraCtrl.sleepTime < 5)
	{
		cameraCtrl.sleepTime = 5;
	}
	//启动电机
	int speedLevel = pDlg->roundTime.GetCurSel() + 1;
	//每张的拍摄时间
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
		//直接停止
		if (pDlg->isStop == true)
		{
			pDlg->SendComOrder(pDlg->timeVector);
			pDlg->isPlaneStart = false;
			//Sleep(10);
			CString errorMessamge;
			errorMessamge.Format("%d张未拍摄成功",cameraCtrl.counter);
			pDlg->MessageBox(errorMessamge);
			pDlg->stepCount -= cameraCtrl.counter;
			cameraCtrl.ReleaseCamera();
			if (pDlg->MessageBox(_T("是否上传图像到电脑上？"),_T("保存？"),MB_OKCANCEL )==IDOK)
			{		
				//上传图像
				pDlg->Save();
				AfxMessageBox(_T("上传成功"));
			}
			return 0 ;
		}
		//拍照
 		int flag =  cameraCtrl.TakePhotos();
		//检测相机状态
		if (flag == 2)
		{
			AfxMessageBox(_T("内存卡已满！请停止拍摄，保存图片！"));
		}
		if (flag == 1)
		{
			AfxMessageBox(_T("自动对焦失败！"));
		}	
		//设置拍摄进程
		pDlg->stepCount++;
		pDlg->SetDlgItemInt(IDC_PICNUMBER,pDlg->stepCount);	
		start -= GetTickCount();
		//延时
		if (start >0)
		{
			Sleep(start);
		}
		else
		{
			Sleep(0);
		}
	}
	//停止转盘
	pDlg->SendComOrder(pDlg->timeVector);
	pDlg->isPlaneStart = false;
	//Sleep(10);
	//提示信息
	CString errorMessamge;
	errorMessamge.Format("%d张未拍摄成功",cameraCtrl.counter);
	pDlg->MessageBox(errorMessamge);
	pDlg->stepCount -= cameraCtrl.counter;
	cameraCtrl.ReleaseCamera();
	//拍摄完成，上传图像
	if (pDlg->MessageBox(_T("是否上传图像到电脑上？"),_T("保存？"),MB_OKCANCEL )==IDOK)
	{		
		pDlg->Save();
		AfxMessageBox(_T("上传成功"));
	}	
	return 0;
}

/**************************************************
	函数名: CCannonDlg::OnBnClickedButton2
	功能描述: 1.上传相机最后拍摄的stepCount张图像到电脑上
	                  2.构造存储路径名
	输入: 无
	输出: 无
	返回值: 无
	其他: 无
	修改历史: 无
*************************************************/
void CCannonDlg::Save()
{
	CCamearControl saveControl;
	saveControl.OpenCamera();
	CString strPath = dlg1.m_Dlg1Edit4;
	CreateDirectory(strPath,NULL);
	//获取当前日期
	CTime tm = CTime::GetCurrentTime();
	CString dateStr = tm.Format("%Y-%m-%d");
	strPath =strPath+"\\"+ dateStr;
	//创建日期文件夹
	CreateDirectory(strPath,NULL);
	//获取当前时间
	CString timeStr = tm.Format("%H-%M-%S");
	strPath =strPath+"\\"+ timeStr;
	//在日期文件夹下创建时间文件夹
	CreateDirectory(strPath,NULL);
	strPath += "\\";
	CString originalStrPath =strPath+ _T("original") + _T("\\");
	CreateDirectory(originalStrPath,NULL);
	//CString str;
	//得到需要上传的照片数
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
		//最终的保存路径string类型
		pathVector.push_back(orginalImgPath);
	}
	//根据需要上传的张数以及路径名，上传图像
	saveControl.GetImageDirectory(stepCount,pathVector);
	saveControl.ReleaseCamera();
}
/**************************************************
	函数名: CCannonDlg::OnBnClickedPrepare
	功能描述: 1.测试功能
	                  2.拍一张照片，并且保存在电脑上
					  3.对该照片进行抠图处理
	输入: 无
	输出: 无
	返回值: 无
	其他: 无
	修改历史: 无
*************************************************/
void CCannonDlg::OnBnClickedPrepare()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPath = dlg1.m_Dlg1Edit4;
	CCamearControl cameraPrePare;
	cameraPrePare.prepareFlag=true;
	CString numtem = _T("");
	CString strTem = _T("");
	strTem = strPath + strTem;                    
	CString saveOriginalPath = _T("");
	saveOriginalPath = strTem +_T("_test")+ _T(".jpg");
	CStringA stra(saveOriginalPath.GetBuffer(0));
	//原图路径
	std::string imgPath=stra.GetBuffer(0);           
	//处理图的路径
	saveOriginalPath = strTem +_T("_test_process")+ _T(".jpg");
	CStringA stra2(saveOriginalPath.GetBuffer(0));
	std::string  processImgPath=stra2.GetBuffer(0);
	//打开相机
	bool flag = cameraPrePare.OpenCamera();
	int isoIndex = isoComBox.GetCurSel();
	int avIndex = avCombox.GetCurSel();
	int tvIndex = tvCombox.GetCurSel();	
	//设置相机参数
	cameraPrePare.SetCameraInfo((EdsUInt32)isoList[isoIndex].key,
												   	  (EdsUInt32)avList[avIndex].key,
												 	  (EdsUInt32)tvList[tvIndex].key);
	//拍照
	flag =  cameraPrePare.TakePhotos();	
	//检测拍照状态
	if (flag == 2)
	{
		AfxMessageBox(_T("内存卡已满！请停止拍摄，保存图片！"));
	}
	if (flag == 1)
	{
		AfxMessageBox(_T("自动对焦失败！"));
	}
	Sleep(2000);
	flag = cameraPrePare.ReleaseCamera();
	//下载该图像
	CCamearControl download;
	download.prepareFlag = true;
	download.orginalImgPath = imgPath;
	flag = download.OpenCamera();
	//显示该图像
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
	// 复制图片
	cimg.CopyOf(&image ); 
	// 将图片绘制到显示控件的指定区域内
	cimg.DrawToHDC( hDC, &rect ); 
	ReleaseDC( pDC );
}




UINT CCannonDlg::ProcessImage(LPVOID pParam)
{
	// TODO: 在此添加控件通知处理程序代码
	//申请一个线程
	CWinThread*   pThreadProcess;
	//ThreadVideoPlay是线程函数
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
	//初始化入口参数bi开始
	bi.hwndOwner = this->GetSafeHwnd();
	bi.pidlRoot = NULL;//初始化制定的root目录
	bi.pszDisplayName = szPath;//此参数如为NULL则不能显示对话框
	bi.lpszTitle =_T("打开文件夹");
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	bi.ulFlags = BIF_EDITBOX;//包括文件
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = LPARAM(szPath);
	bi.iImage=0;
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		//SHSetFolderPath(pIDList,)
		SHGetPathFromIDList(pIDList, szPath);
		//取得文件夹路径到Buffer里
		sFolderPath = szPath ;//将文件夹路径保存在一个CString对象里
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
	//	//判断是否是目录或者是隐藏文件，又或者是".."和"."，如果是，进入下一轮循环
	//	if (finderDict.IsDirectory())
	//	{
	//		CString str;
	//		//得到文件名
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
	//判断是否是目录或者是隐藏文件，又或者是".."和"."，如果是，进入下一轮循环
	if (finder.IsDirectory())
	{
		CString str;
		//得到文件名
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
			else//如果是文件
			{
				CString str;
				//得到文件名
				str = finder1.GetFileName();
				//得到文件后缀名
				int nLen = str.GetLength() - finder1.GetFileTitle().GetLength();
				str = str.Right(nLen);
				//判断文件格式，如果是图像文件，将其完整的路径保存在列表中
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
				saveResizePath = resizePath[folderIter][j] + numtem + _T(".jpg");      //最终的保存路径CString类型
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
	
	AfxMessageBox(_T("批量处理完成"));
	return;
}

void CCannonDlg::OnBnClickedSingalprocess()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()!=IDOK)
		return;
	CStringA stra1(dlg.GetPathName().GetBuffer(0));
	std::string mgPath=stra1.GetBuffer(0);

	CString str;
	//得到文件后缀名
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
		saveResizePath = resizePathVec[j] ;     //最终的保存路径CString类型
		CStringA stra1(saveResizePath.GetBuffer(0));
		std::string resizeImgPath=stra1.GetBuffer(0);

		proSave saveTemp;
		saveTemp.width = _ttoi(pathVector[j]);
		saveTemp.resizePath = resizeImgPath;

		savePathVec.push_back(saveTemp);		
	}
	batchImage.processImage(savePathVec,false);
	AfxMessageBox(_T("处理完成"));
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
	// TODO: 在此添加控件通知处理程序代码
	isStop = !isStop;
}


void CCannonDlg::OnBnClickedBatachimage()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//初始化入口参数bi开始
	bi.hwndOwner = this->GetSafeHwnd();
	//bi.pszDisplayName = 0;
	bi.pidlRoot = NULL;//初始化制定的root目录
	bi.pszDisplayName = szPath;//此参数如为NULL则不能显示对话框
	bi.lpszTitle =_T("打开文件夹");
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	bi.ulFlags = BIF_EDITBOX;//包括文件
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = LPARAM(szPath);
	bi.iImage=0;
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		//SHSetFolderPath(pIDList,)
		SHGetPathFromIDList(pIDList, szPath);
		//取得文件夹路径到Buffer里
		sFolderPath = szPath;//将文件夹路径保存在一个CString对象里
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
		//判断是否是目录或者是隐藏文件，又或者是".."和"."，如果是，进入下一轮循环
		if (finder.IsDirectory())
		{
			CString str;
			//得到文件名
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
		else//如果是文件
		{
			CString str;
			//得到文件名
			str = finder1.GetFileName();
			//得到文件后缀名
			int nLen = str.GetLength() - finder1.GetFileTitle().GetLength();
			str = str.Right(nLen);
			//判断文件格式，如果是图像文件，将其完整的路径保存在列表中
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
			saveResizeProcessPath = processPathVec[j] + numtem  + _T(".jpg");      //最终的保存路径CString类型
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
	AfxMessageBox(_T("批量处理完成"));
	return;
}




 
void CCannonDlg::OnBnClickedSingleimage()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()!=IDOK)
		return;
	CStringA stra1(dlg.GetPathName().GetBuffer(0));
	std::string mgPath=stra1.GetBuffer(0);

	CString str;
	//得到文件后缀名
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
		saveResizePath = resizePathVec[j] ;     //最终的保存路径CString类型
		CStringA stra1(saveResizePath.GetBuffer(0));
		std::string processImgPath=stra1.GetBuffer(0);

		proSave saveTemp;
		saveTemp.width = _ttoi(pathVector[j]);
		saveTemp.processPath = processImgPath;

		savePathVec.push_back(saveTemp);		
	}
	batchImage.processImage(savePathVec,true);
	AfxMessageBox(_T("处理完成"));
}
//获取系统端口名称，
void CCannonDlg::GetSystemCom(vector<string> &stringVec)
{
	CRegKey RegKey;  
	int nCount = 0;       //串口个数
	CString tempCStr;  
	if(RegKey.Open(HKEY_LOCAL_MACHINE,"Hardware\\DeviceMap\\SerialComm") == ERROR_SUCCESS)    
	{    
		while(true)    
		{    
			char ValueName[_MAX_PATH];    
			unsigned char ValueData[_MAX_PATH];    
			DWORD nValueSize = _MAX_PATH;    
			DWORD nDataSize = _MAX_PATH;    
			DWORD nType;
			//RegEnumValue函数的作用是,从被指定打开的注册表项中列举所有的值
			//这函数每调用一次就会拷贝一个索引值的名称和数据块 
			if(::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)    
			{    
				break;    
			}
			//把串口名称按顺序压入string的vector中
			if(strlen((char*)ValueData))
			{
			//tempCStr.Format("%s",ValueData);
				//comList.AddString(tempCStr);
				stringVec.push_back(ValueData);
			}
			nCount++;
		}    
	}
}



void CCannonDlg::StringVecToCComboBox(vector<string> stringVec,CComboBox& comList)
{
	for (std::vector<string>::iterator i = stringVec.begin(); i != stringVec.end(); ++i)
	{
		//string转cstring压入comlist中
		comList.AddString((*i).c_str());
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
		hCom=CreateFile(strtemp,//COM1口
			GENERIC_READ|GENERIC_WRITE, //允许读和写
			0, //独占方式
			NULL,
			OPEN_EXISTING, //打开而不是创建
			0, //同步方式
			NULL);
		if(hCom==(HANDLE)-1)
		{
			AfxMessageBox("打开COM失败!");
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
		//设置通讯参数
		dcb.BaudRate=9600; 
		dcb.ByteSize=8; 
		dcb.Parity=NOPARITY; 
		dcb.StopBits=ONESTOPBIT; 
		if(!SetCommState(hCom,&dcb))
			errret = GetLastError();
		if (errret == 0)
		{
			MessageBox(_T("配置错误"));
		}
		//PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
		CWnd *wd = (CWnd*)GetDlgItem(IDC_OPENCOM);
		wd->SetWindowText(TEXT("关闭串口"));
		comList.EnableWindow(FALSE);

		roundTime.AddString(_T("1分钟"));
		roundTime.AddString(_T("2分钟"));
		roundTime.AddString(_T("3分钟"));
		roundTime.AddString(_T("4分钟"));
		roundTime.AddString(_T("5分钟"));
		roundTime.AddString(_T("6分钟"));
		roundTime.SetCurSel(5);
		comFlag = true;
	}
	else
	{
		if (MessageBox(_T("是否关闭转盘？"),_T("关闭"),MB_OKCANCEL )==IDOK)
		{		
			//关闭转盘
			SendComOrder(timeVector);
			CloseHandle(hCom);	
			comFlag = false;
			CWnd *wd = (CWnd*)GetDlgItem(IDC_OPENCOM);
			wd->SetWindowText(_T("打开串口"));
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
		AfxMessageBox("写串口失败!");
		return false;
	}
	return true;
}


void CCannonDlg::SetTimeVec(unsigned char [],int length)
{
	//unsigned char lpOutBuffer[4*7];
	memset(timeVector,0,length);//初始化为0
	//停止
	timeVector[0]=0xaa; //帧头
	timeVector[1]=0xca; //命令
	timeVector[2]=0x04; //校验码（帧头+命令）&0xf
	timeVector[3]=0x55; //帧尾
	//timeVector.push_back(lpOutBuffer);
	//1min速度
	timeVector[1*4+0]=0xaa; 
	timeVector[1*4+1]=0xda; 
	timeVector[1*4+2]=0x04; 
	timeVector[1*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//2min速度
	timeVector[2*4+0]=0xaa; 
	timeVector[2*4+1]=0xdb; 
	timeVector[2*4+2]=0x05; 
	timeVector[2*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//3min速度
	timeVector[3*4+0]=0xaa;
	timeVector[3*4+1]=0xdc; 
	timeVector[3*4+2]=0x06; 
	timeVector[3*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//4min速度
	timeVector[4*4+0]=0xaa; 
	timeVector[4*4+1]=0xdd; 
	timeVector[4*4+2]=0x07; 
	timeVector[4*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//5min速度
	timeVector[5*4+0]=0xaa; 
	timeVector[5*4+1]=0xde; 
	timeVector[5*4+2]=0x08; 
	timeVector[5*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
	//6min速度
	timeVector[6*4+0]=0xaa; 
	timeVector[6*4+1]=0xdf; 
	timeVector[6*4+2]=0x09; 
	timeVector[6*4+3]=0x55; 
	//timeVector.push_back(lpOutBuffer);
}

void CCannonDlg::OnBnClickedExit()
{
	if (MessageBox(_T("是否退出？"),_T("退出"),MB_OKCANCEL )==IDOK)
	{	
		if (comFlag == true)
		{
			SendComOrder(timeVector);
			CloseHandle(hCom);	
			comFlag = false;
			CWnd *wd = (CWnd*)GetDlgItem(IDC_OPENCOM);
			wd->SetWindowText(_T("打开串口"));
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
	//启动电机
	if (isPlaneStart == true)
	{
		AfxMessageBox(_T("请先按测试停止，使电机停止转动！"));
		return;
	}
	isPlaneStart = true;
	int speedLevel = roundTime.GetCurSel() + 1;
	SendComOrder(timeVector + speedLevel*4);
}


void CCannonDlg::OnBnClickedTeststop()
{
	//停止
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
	system("del in2.txt");//删除中间文件
}





void CCannonDlg::InitializeScroll(CScrollBar m_ScrollBar,int start,int end,int initialization)
{
	//初始化滑动条范围为(start,end)
	m_ScrollBar.SetScrollRange(start,end);
	//初始化滑动条初始值为initialization
	m_ScrollBar.SetScrollPos(initialization);
}



//把数字显示在Edit空间中
void CCannonDlg::EditDisplayNum(double number, UINT ID)
{
	//把number转化为cstring
	CString str;
	str.Format(_T("%d"),number);
	CEdit* pEditOne;
	pEditOne=(CEdit*)GetDlgItem(ID);
	//显示该数字
	pEditOne->SetWindowText(str);
}



void CCannonDlg::CreatCameraHashList()
{
	//创建哈希表
	CHashList getHashList;
	getHashList.CreatAllList();
	int isoIndex(0);
	//利用哈希表得到命令对应的命令含义
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
		//命令含义显示在下拉菜单中
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
}