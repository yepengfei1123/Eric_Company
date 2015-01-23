/***************************************************************
    Copyright (C), 2014- , XI'AN RANKE INFORMATION TECHNOLOGY CO., LTD
	�ļ���: CamearControl.h
	����: ������
	�汾: v1.0 
	����: 2014.08
	��������: ���ݼ������SDK������¹��ܣ�
	                  1.�������
					  2.��ȡ�ÿ�����������õ�ISO��AV��TV����
					  3.��ȡ�����Ƭ�ļ����µ���Ƭ
					  4.��HashList.h�е��๲ͬ��������������Ĳ���
	����: ��
	�����б�: ���ļ�Ϊһ������Canon������࣬���嶨�忴�����
	�޸���ʷ: ��
*************************************************************/
#pragma once
/*�������skd��lib��*/
#pragma comment(lib,"EDSDK.lib")
/*�������skd��ͷ�ļ���*/
#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"
/*opencvͷ�ļ�*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv/cv.hpp"
#include "opencv/cxcore.hpp"
#include <string>
/*��ϣ��CHashList��ͷ�ļ�*/
#include "CHashList.h"
using namespace cv;

struct save
{
	int width;
	string resizePath;
	string processPath;
};
struct BatchProcess
{
	int width;
	vector<string> path;
};
/**************************************************
	����: CCamearControl
	����: ������
	�汾: v1.0 
	����: 2014.08
	��������: ���ݼ������SDK������¹��ܣ�
	                  1.�������
					  2.��ȡ�ÿ�����������õ�ISO��AV��TV����
					  3.��ȡ�����Ƭ�ļ����µ���Ƭ
					  4.��HashList.h�е��๲ͬ��������������Ĳ���
	����: ��
	�����б�: 1.
	�޸���ʷ: ��
*************************************************/
class CCamearControl
{
public:
	CCamearControl(void);
	~CCamearControl(void);
public:
	//��ȡ��������
	EdsCameraRef theCamera;
	//�����
	bool OpenCamera();
	//����
	int  TakePhotos();	
	//�ͷ����
	bool ReleaseCamera();
	//���ص������ϵ�·��
	string orginalImgPath;
private:
	//��ȡ���
	bool GetCamera();
	//����¼������Ļص�����ָ��
	typedef EdsError ( EDSCALLBACK *EdsObjectEventHandler)(
		EdsObjectEvent inEvent,       //�¼�����������
		EdsBaseRef inRef,                 //��������ݽṹ
		EdsVoid *inContext);             //����ص������Ĳ���
	//������������ص�����ָ��
	typedef EdsError ( EDSCALLBACK * EdsPropertyEventHandler )(
		EdsPropertyEvent inEvent,      //�¼�����������
		EdsPropertyID inPropertyID,   //Ҫ���õĲ���
		EdsUInt32 inParam,                 //���Ӳ���
		EdsVoid *inContext );               //����ص������Ĳ���
	//������ڴ�������ͼ�񵽵�����
	bool DownloadImage(EdsDirectoryItemRef directoryItem);
	//����ͼ��Ļص������ľ���ʵ��
	static EdsError EDSCALLBACK process(EdsObjectEvent inEvent,
															  EdsBaseRef object,
															  EdsVoid *context);
	//����ISO��AV��TV�ĺ����ľ���ʵ��
	static EdsError EDSCALLBACK propertySet(EdsPropertyEvent inEvent,
																	EdsPropertyID inPropertyID,
																	EdsUInt32 inParam,
																	EdsVoid *inContext );
public:
	//����CHashList�������ù�ϣ�������������
	CHashList list;
	//ISO����
	EdsPropertyDesc isoPropety;
	//AV����
	EdsPropertyDesc avPropety;
	//TV����
	EdsPropertyDesc tvPropety;
	//��ȡ��������õĲ����б�
	bool GetCameraInfo();
	//���õ��������
	bool SetCameraInfo(EdsUInt32 isoValue,EdsUInt32 avValue,EdsUInt32 tvValue);
	//���ر�־λ
	bool prepareFlag ;
	//��ȡ����ļ���
	bool GetImageDirectory(int picNumber,vector<string> pathName);

	//busy counter
	int counter;
	//sleep time
	unsigned int sleepTime;
};

