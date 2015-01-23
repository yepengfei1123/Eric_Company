/***************************************************************
    Copyright (C), 2014- , XI'AN RANKE INFORMATION TECHNOLOGY CO., LTD
	文件名: CamearControl.h
	作者: 卫永波
	版本: v1.0 
	日期: 2014.08
	功能描述: 根据佳能相机SDK完成以下功能：
	                  1.相机拍照
					  2.获取该款相机可以设置的ISO、AV、TV参数
					  3.获取相机照片文件夹下的照片
					  4.与HashList.h中的类共同工作，设置相机的参数
	其他: 无
	函数列表: 本文件为一个控制Canon相机的类，具体定义看类介绍
	修改历史: 无
*************************************************************/
#pragma once
/*佳能相机skd的lib库*/
#pragma comment(lib,"EDSDK.lib")
/*佳能相机skd的头文件库*/
#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"
/*opencv头文件*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv/cv.hpp"
#include "opencv/cxcore.hpp"
#include <string>
/*哈希表CHashList的头文件*/
#include "CHashList.h"
using namespace cv;


/**************************************************
	类名: CCamearControl
	作者: 卫永波
	版本: v1.0 
	日期: 2014.08
	功能描述: 根据佳能相机SDK完成以下功能：
	                  1.相机拍照
					  2.获取该款相机可以设置的ISO、AV、TV参数
					  3.获取相机照片文件夹下的照片
					  4.与HashList.h中的类共同工作，设置相机的参数
	其他: 无
	函数列表: 1.
	修改历史: 无
*************************************************/
class CCamearControl
{
public:
	CCamearControl(void);
	~CCamearControl(void);
	//标志位
	enum CAMERA_CTRL_FLAG
	{
		CAMERA_CTRL_OK,//正确
		CAMERA_CTRL_ERROR,//出现错误
		CAMERA_CTRL_NOCAMERA,//没有相机
		CAMERA_CTRL_CONNECTERROR,//建立联系异常
		CAMERA_CTRL_CARD_NG,//内存卡已满
		CAMERA_CTRL_AF_NG,//对焦失败
		CAMERA_CTRL_TAKEPHOTO_ERR,//拍照出现问题
		CAMERA_CTRL_CONNECT,//相机已连接标志位
		CAMERA_CTRL_NOTCONNECT//相机未连接标志位
		CAMERA_CTRL_DIRECTIRYCHANGE//目录改变
	};
public:
	//获取相机句柄
	EdsCameraRef GetCameraRef();
	//打开相机
	CAMERA_CTRL_FLAG OpenCamera();
	//拍照
	CAMERA_CTRL_FLAG  TakePhotos();	
	//释放相机
	CAMERA_CTRL_FLAG ReleaseCamera();
	//返回相机是否连接
	CAMERA_CTRL_FLAG isConnect();
	//下载到电脑上的路径
	string orginalImgPath;
private:
	//获取的相机句柄
	EdsCameraRef theCamera;
	//获取相机
	CAMERA_CTRL_FLAG GetCamera(EdsUInt32 count =0);
	//相机连接参数
	CAMERA_CTRL_FLAG connectFlag;  
	//ISO参数
	EdsPropertyDesc isoPropety;
	//AV参数
	EdsPropertyDesc avPropety;
	//TV参数
	EdsPropertyDesc tvPropety;
	//相机事件产生的回调函数指针
	typedef EdsError ( EDSCALLBACK *EdsObjectEventHandler)(
		EdsObjectEvent inEvent,       //事件发生的类型
		EdsBaseRef inRef,                 //相机的数据结构
		EdsVoid *inContext);             //传入回调函数的参数
	//设置相机参数回调函数指针
	typedef EdsError ( EDSCALLBACK * EdsPropertyEventHandler )(
		EdsPropertyEvent inEvent,      //事件发生的类型
		EdsPropertyID inPropertyID,   //要设置的参数
		EdsUInt32 inParam,                 //附加参数
		EdsVoid *inContext );               //传入回调函数的参数
	//从相机内存中下载图像到电脑上
	bool DownloadImage(EdsDirectoryItemRef directoryItem);
	//下载图像的回调函数的具体实现
	static EdsError EDSCALLBACK process(EdsObjectEvent inEvent,
										EdsBaseRef object,
										EdsVoid *context);
	//设置ISO、AV、TV的函数的具体实现
	static EdsError EDSCALLBACK propertySet(EdsPropertyEvent inEvent,
											EdsPropertyID inPropertyID,
											EdsUInt32 inParam,
											EdsVoid *inContext );
public:
	//创建CHashList对象，利用哈希表设置相机参数
	CHashList list;
	//得到相机参数；
	EdsPropertyDesc GetEdsPropertyDesc();
	//获取相机可设置的参数列表
	CAMERA_CTRL_FLAG GetCameraInfo();
	//设置的相机参数
	CAMERA_CTRL_FLAG SetCameraInfo(EdsUInt32 isoValue,EdsUInt32 avValue,EdsUInt32 tvValue);
	//下载标志位
	CAMERA_CTRL_FLAG prepareFlag;
	//获取相机文件夹
	CAMERA_CTRL_FLAG GetImageDirectory(int picNumber,vector<string> pathName);
	//busy counter
	int counter;
	//sleep time
	unsigned int sleepTime;
};

