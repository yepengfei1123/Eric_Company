#include "StdAfx.h"
#include "CamearControl.h"
CCamearControl::CCamearControl(void)
{
	counter=0;
	prepareFlag = false;
}
CCamearControl::~CCamearControl(void)
{
}
/**************************************************
	函数名: CCamearControl::GetCamera()
	功能描述: 根据SDK获取相机
	输入: 无
	输出: CCamearControl::theCamera  : 相机的句柄
	返回值: bool型，成功获取返回true;否则返回false.
	其他: 根据prepareFlag标志，设置是否给相机写入回调函数。
	          当需要拍一张下载一张的时候置标志位为true,反之亦然。
	修改历史: 无
*************************************************/
bool CCamearControl::GetCamera()
{
	EdsError flag = EDS_ERR_OK;
	//相机列表
	EdsCameraListRef cameraList = NULL;
	EdsUInt32 count =0;
	//获取与电脑相连的所有相机列表
	flag = EdsGetCameraList(&cameraList);
	//获取相机个数
	if (flag == EDS_ERR_OK)
	{
		flag = EdsGetChildCount(cameraList, &count);
	}
	//默认获取列表中第一个相机
	if (flag == EDS_ERR_OK)
	{
		flag = EdsGetChildAtIndex(cameraList, 0, &theCamera);
	}
	if (prepareFlag == true)
	{
		if (flag == EDS_ERR_OK)
		{
			//设置下载图像的回调函数
			EdsObjectEventHandler handleObjectEvent;
			handleObjectEvent = process;
			flag = EdsSetObjectEventHandler(theCamera,kEdsObjectEvent_All,handleObjectEvent,this);
		}
	}
	//释放相机列表
	if (cameraList!=NULL)
	{
		EdsRelease(cameraList);
		cameraList = NULL;
	}
	if (flag != EDS_ERR_OK)
	{
		return false;
	}
	return true;
}
/**************************************************
	函数名: CCamearControl::OpenCamera()
	功能描述: 根据SDK打开相机，是相机和电脑建立逻辑联系
	输入: 无
	输出: 无
	返回值: bool型，成功获取返回true;否则返回false.
	其他: 无
	修改历史: 无
*************************************************/
bool CCamearControl::OpenCamera()
{
	EdsError err = EDS_ERR_OK;
	theCamera = NULL;
	//初始化SDK
	err = EdsInitializeSDK();
	//获取相机
	if(err == EDS_ERR_OK)
	{
		GetCamera();
	}
	//建立联系
	if(err == EDS_ERR_OK)
	{
		err = EdsOpenSession(theCamera);
	}
	if (err != EDS_ERR_OK)
	{
		return false;
	}
	return true;
}
/**************************************************
	函数名: CCamearControl::TakePhotos()
	功能描述: 拍照
	输入: 无
	输出: 无
	返回值: int型
				  ==0时：拍摄成功
				  ==1时：对焦失败
				  ==2时：内存卡已满
	其他: 无
	修改历史: 无
*************************************************/
int CCamearControl::TakePhotos()
{
	//锁定UI，不能手动控制相机
	EdsError err = EDS_ERR_OK;
	err = EdsSendStatusCommand(theCamera, kEdsCameraStatusCommand_UILock, 0);
	//拍照
	if (err == EDS_ERR_OK)
	{
		err = EdsSendCommand( theCamera, kEdsCameraCommand_TakePicture, 0);
	}
	//释放UI
	if(err == EDS_ERR_OK )
	{
		err = EdsSendStatusCommand(theCamera, kEdsCameraStatusCommand_UIUnLock, 0);
	}
	if (err != EDS_ERR_OK)
	{
		counter++;
	}
	//如果对内存卡已满返回
	if (err == EDS_ERR_TAKE_PICTURE_CARD_NG)
	{
		return 2;
	}
	//如果对焦失败返回
	if (err == EDS_ERR_TAKE_PICTURE_AF_NG)
	{
		return 1;
	}
	return 0;
}
/**************************************************
	函数名: CCamearControl::ReleaseCamera()
	功能描述: 关闭电脑与相机的逻辑联系，释放相机
	输入: 无
	输出: 无
	返回值: bool型，成功获取返回true;否则返回false.
	其他: 无
	修改历史: 无
*************************************************/
bool CCamearControl::ReleaseCamera()
{	
	EdsError err = EDS_ERR_OK;
	//关闭逻辑联系
	err = EdsCloseSession(theCamera);
	//释放相机
	if(theCamera != NULL)
	{
		EdsRelease(theCamera);
	}
	//终止SDK
	err = EdsTerminateSDK();
	if (err != EDS_ERR_OK)
	{
		return false;
	}
	return true;
}
/**************************************************
	函数名: CCamearControl::DownloadImage
	功能描述: 下载内存中的图像到电脑上
	输入：directoryItem：类型：EdsDirectoryItemRef
	                                     描述：需要下载的文件信息
				orginalImgPath：类型：string
											描述：下载到电脑上的路径
	输出: 无
	返回值: bool型，成功获取返回true;否则返回false.
	其他: 无
	修改历史: 无
*************************************************/
bool CCamearControl::DownloadImage(EdsDirectoryItemRef directoryItem)
{
	EdsError err = EDS_ERR_OK;
	EdsDirectoryItemInfo dirItemInfo;
	//获取下载的文件信息
	err = EdsGetDirectoryItemInfo(directoryItem, &dirItemInfo);
	//图像的数据流
	EdsStreamRef stream;
	// Create file stream for transfer destination
	if(err == EDS_ERR_OK)
	{
		EdsChar *imageName = new EdsChar[orginalImgPath.size()+1];
		strcpy(imageName,orginalImgPath.c_str());
		//在电脑上创建文件
		err = EdsCreateFileStream( imageName,kEdsFileCreateDisposition_CreateAlways,kEdsAccess_ReadWrite, &stream);
		delete imageName;
	}
	//下载图像
	if(err == EDS_ERR_OK)
	{
		err = EdsDownload( directoryItem, dirItemInfo.size, stream);
	}
	//检测时候下载完成
	if(err == EDS_ERR_OK)
	{
		err = EdsDownloadComplete(directoryItem);
	}
	//释放数据流
	if( stream != NULL)
	{
		EdsRelease(stream);
		stream = NULL;
	}
	if (err != EDS_ERR_OK)
	{
		return false;
	}
	return true;
}
/**************************************************
	函数名: CCamearControl::process
	功能描述: 下载图像的回调函数
	输入：event：类型：EdsObjectEvent
	                                     描述：事件类型
				object：类型：EdsBaseRef
										描述：佳能数据类型
				context：类型：EdsVoid *
				                        描述：回调函数传入的数据
	输出: 无
	返回值: EdsError型，返回下载是否成功
	其他: 无
	修改历史: 无
*************************************************/
EdsError EDSCALLBACK CCamearControl::process(EdsObjectEvent event,
	EdsBaseRef object,
	EdsVoid *context)
{
	CCamearControl *pThis = (CCamearControl *)context;
	pThis->DownloadImage(object);
	if (object)
	{
		EdsRelease(object);
	}
	return EDS_ERR_OK;
}
/**************************************************
	函数名: CCamearControl::GetCameraInfo
	功能描述: 得到相机可设置的ISO、AV、TV属性
	输入：无
	输出：isoPropety：EdsPropertyDesc类型，可以设置的属性列表
				avPropety：同上
				tvPropety：同上
	返回值: bool型，返回下载是否成功
	其他: 无
	修改历史: 无
*************************************************/
bool CCamearControl::GetCameraInfo()
{
	EdsError err = EDS_ERR_OK;
	err = EdsGetPropertyDesc(theCamera,kEdsPropID_ISOSpeed,&isoPropety);
	err = EdsGetPropertyDesc(theCamera,kEdsPropID_Av,&avPropety);
	err = EdsGetPropertyDesc(theCamera,kEdsPropID_Tv,&tvPropety);
	if (err != EDS_ERR_OK)
	{
		return false;
	}
	return true;
}
/**************************************************
	函数名: CCamearControl::SetCameraInfo
	功能描述:设置相机的的ISO、AV、TV属性
	输入：isoValue：EdsUInt32型，参数的代码
	            avValue：同上
				tvValue：同上
	输出：无
	返回值: bool型，设置成功返回true
	其他: 无
	修改历史: 无
*************************************************/
bool CCamearControl::SetCameraInfo(EdsUInt32 isoValue,EdsUInt32 avValue,EdsUInt32 tvValue)
{
	EdsError err = EDS_ERR_OK;

	err = EdsSetPropertyData(theCamera,kEdsPropID_ISOSpeed,0,sizeof(isoValue),&isoValue);

	err = EdsSetPropertyData(theCamera,kEdsPropID_Av,0,sizeof(avValue),&avValue);

	err = EdsSetPropertyData(theCamera,kEdsPropID_Tv,0,sizeof(tvValue),&tvValue);

	if (err == EDS_ERR_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**************************************************
	函数名: CCamearControl::GetImageDirectory
	功能描述:得到相机目录下，下载最后拍摄的picNumber张照片到电脑上
	输入：picNumber：int型，需要得到照片的张数
	            pathName：vector<string>型，为picNumber张照片设置的路径名
	输出：无
	返回值: bool型，设置成功返回true
	其他: 无
	修改历史: 无
*************************************************/
bool CCamearControl::GetImageDirectory(int picNumber,vector<string> pathName)
{
	EdsError err = EDS_ERR_OK;
	EdsDirectoryItemInfo folderInfo;	
	EdsUInt32 directoryNum(0);
	EdsVolumeRef vol;
	//得到相机的第一个内存卡
	err = EdsGetChildAtIndex(theCamera,0,&vol);	
	EdsDirectoryItemRef folderTemp;		
	if (err == EDS_ERR_OK)
	{
		//得到内存卡的第一个文件夹
		err = EdsGetChildAtIndex(vol,0,&folderTemp);	
		err = EdsRelease(vol);
	}
	EdsDirectoryItemRef currentFolder;
	if (err == EDS_ERR_OK)
	{
		//得到存储照片的文件夹
		err = EdsGetChildAtIndex(folderTemp,0,&currentFolder);
		err = EdsRelease(folderTemp);
	}
	if (err == EDS_ERR_OK)
	{
		//得到该文件夹的信息以及该文件夹下文件的个数
		err = EdsGetDirectoryItemInfo(currentFolder,&folderInfo);
		err = EdsGetChildCount(currentFolder,&directoryNum);
	}
	//当文件夹的问价个数少于需要得到的文件个数，返回false
	if (picNumber>directoryNum)
	{
		return false;
	}
	EdsStreamRef stream;
	EdsDirectoryItemRef picStream;
	int counter(0);
	for (int i=picNumber;i>=1;--i)
	{
		//得到倒数第i个文件的
		EdsGetChildAtIndex(currentFolder,directoryNum-i,&picStream);
		EdsGetDirectoryItemInfo(picStream,&folderInfo);
		EdsChar *imageName = new EdsChar[pathName[counter].size()+1];;
		strcpy(imageName,pathName[counter].c_str());		
		err = EdsCreateFileStream( imageName,kEdsFileCreateDisposition_CreateAlways,kEdsAccess_ReadWrite, &stream);
		//下载该文件
		err = EdsDownload( picStream, folderInfo.size, stream);
		delete imageName;
		++counter;	
	}
	EdsRelease(picStream);
	EdsRelease(stream);
	EdsRelease(currentFolder);
	return true;
}