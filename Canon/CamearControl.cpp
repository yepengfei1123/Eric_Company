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
	������: CCamearControl::GetCamera()
	��������: ����SDK��ȡ���
	����: ��
	���: CCamearControl::theCamera  : ����ľ��
	����ֵ: bool�ͣ��ɹ���ȡ����true;���򷵻�false.
	����: ����prepareFlag��־�������Ƿ�����д��ص�������
	          ����Ҫ��һ������һ�ŵ�ʱ���ñ�־λΪtrue,��֮��Ȼ��
	�޸���ʷ: ��
*************************************************/
bool CCamearControl::GetCamera()
{
	EdsError flag = EDS_ERR_OK;
	//����б�
	EdsCameraListRef cameraList = NULL;
	EdsUInt32 count =0;
	//��ȡ�������������������б�
	flag = EdsGetCameraList(&cameraList);
	//��ȡ�������
	if (flag == EDS_ERR_OK)
	{
		flag = EdsGetChildCount(cameraList, &count);
	}
	//Ĭ�ϻ�ȡ�б��е�һ�����
	if (flag == EDS_ERR_OK)
	{
		flag = EdsGetChildAtIndex(cameraList, 0, &theCamera);
	}
	if (prepareFlag == true)
	{
		if (flag == EDS_ERR_OK)
		{
			//��������ͼ��Ļص�����
			EdsObjectEventHandler handleObjectEvent;
			handleObjectEvent = process;
			flag = EdsSetObjectEventHandler(theCamera,kEdsObjectEvent_All,handleObjectEvent,this);
		}
	}
	//�ͷ�����б�
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
	������: CCamearControl::OpenCamera()
	��������: ����SDK�������������͵��Խ����߼���ϵ
	����: ��
	���: ��
	����ֵ: bool�ͣ��ɹ���ȡ����true;���򷵻�false.
	����: ��
	�޸���ʷ: ��
*************************************************/
bool CCamearControl::OpenCamera()
{
	EdsError err = EDS_ERR_OK;
	theCamera = NULL;
	//��ʼ��SDK
	err = EdsInitializeSDK();
	//��ȡ���
	if(err == EDS_ERR_OK)
	{
		GetCamera();
	}
	//������ϵ
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
	������: CCamearControl::TakePhotos()
	��������: ����
	����: ��
	���: ��
	����ֵ: int��
				  ==0ʱ������ɹ�
				  ==1ʱ���Խ�ʧ��
				  ==2ʱ���ڴ濨����
	����: ��
	�޸���ʷ: ��
*************************************************/
int CCamearControl::TakePhotos()
{
	//����UI�������ֶ��������
	EdsError err = EDS_ERR_OK;
	err = EdsSendStatusCommand(theCamera, kEdsCameraStatusCommand_UILock, 0);
	//����
	if (err == EDS_ERR_OK)
	{
		err = EdsSendCommand( theCamera, kEdsCameraCommand_TakePicture, 0);
	}
	//�ͷ�UI
	if(err == EDS_ERR_OK )
	{
		err = EdsSendStatusCommand(theCamera, kEdsCameraStatusCommand_UIUnLock, 0);
	}
	if (err != EDS_ERR_OK)
	{
		counter++;
	}
	//������ڴ濨��������
	if (err == EDS_ERR_TAKE_PICTURE_CARD_NG)
	{
		return 2;
	}
	//����Խ�ʧ�ܷ���
	if (err == EDS_ERR_TAKE_PICTURE_AF_NG)
	{
		return 1;
	}
	return 0;
}
/**************************************************
	������: CCamearControl::ReleaseCamera()
	��������: �رյ�����������߼���ϵ���ͷ����
	����: ��
	���: ��
	����ֵ: bool�ͣ��ɹ���ȡ����true;���򷵻�false.
	����: ��
	�޸���ʷ: ��
*************************************************/
bool CCamearControl::ReleaseCamera()
{	
	EdsError err = EDS_ERR_OK;
	//�ر��߼���ϵ
	err = EdsCloseSession(theCamera);
	//�ͷ����
	if(theCamera != NULL)
	{
		EdsRelease(theCamera);
	}
	//��ֹSDK
	err = EdsTerminateSDK();
	if (err != EDS_ERR_OK)
	{
		return false;
	}
	return true;
}
/**************************************************
	������: CCamearControl::DownloadImage
	��������: �����ڴ��е�ͼ�񵽵�����
	���룺directoryItem�����ͣ�EdsDirectoryItemRef
	                                     ��������Ҫ���ص��ļ���Ϣ
				orginalImgPath�����ͣ�string
											���������ص������ϵ�·��
	���: ��
	����ֵ: bool�ͣ��ɹ���ȡ����true;���򷵻�false.
	����: ��
	�޸���ʷ: ��
*************************************************/
bool CCamearControl::DownloadImage(EdsDirectoryItemRef directoryItem)
{
	EdsError err = EDS_ERR_OK;
	EdsDirectoryItemInfo dirItemInfo;
	//��ȡ���ص��ļ���Ϣ
	err = EdsGetDirectoryItemInfo(directoryItem, &dirItemInfo);
	//ͼ���������
	EdsStreamRef stream;
	// Create file stream for transfer destination
	if(err == EDS_ERR_OK)
	{
		EdsChar *imageName = new EdsChar[orginalImgPath.size()+1];
		strcpy(imageName,orginalImgPath.c_str());
		//�ڵ����ϴ����ļ�
		err = EdsCreateFileStream( imageName,kEdsFileCreateDisposition_CreateAlways,kEdsAccess_ReadWrite, &stream);
		delete imageName;
	}
	//����ͼ��
	if(err == EDS_ERR_OK)
	{
		err = EdsDownload( directoryItem, dirItemInfo.size, stream);
	}
	//���ʱ���������
	if(err == EDS_ERR_OK)
	{
		err = EdsDownloadComplete(directoryItem);
	}
	//�ͷ�������
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
	������: CCamearControl::process
	��������: ����ͼ��Ļص�����
	���룺event�����ͣ�EdsObjectEvent
	                                     �������¼�����
				object�����ͣ�EdsBaseRef
										������������������
				context�����ͣ�EdsVoid *
				                        �������ص��������������
	���: ��
	����ֵ: EdsError�ͣ����������Ƿ�ɹ�
	����: ��
	�޸���ʷ: ��
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
	������: CCamearControl::GetCameraInfo
	��������: �õ���������õ�ISO��AV��TV����
	���룺��
	�����isoPropety��EdsPropertyDesc���ͣ��������õ������б�
				avPropety��ͬ��
				tvPropety��ͬ��
	����ֵ: bool�ͣ����������Ƿ�ɹ�
	����: ��
	�޸���ʷ: ��
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
	������: CCamearControl::SetCameraInfo
	��������:��������ĵ�ISO��AV��TV����
	���룺isoValue��EdsUInt32�ͣ������Ĵ���
	            avValue��ͬ��
				tvValue��ͬ��
	�������
	����ֵ: bool�ͣ����óɹ�����true
	����: ��
	�޸���ʷ: ��
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
	������: CCamearControl::GetImageDirectory
	��������:�õ����Ŀ¼�£�������������picNumber����Ƭ��������
	���룺picNumber��int�ͣ���Ҫ�õ���Ƭ������
	            pathName��vector<string>�ͣ�ΪpicNumber����Ƭ���õ�·����
	�������
	����ֵ: bool�ͣ����óɹ�����true
	����: ��
	�޸���ʷ: ��
*************************************************/
bool CCamearControl::GetImageDirectory(int picNumber,vector<string> pathName)
{
	EdsError err = EDS_ERR_OK;
	EdsDirectoryItemInfo folderInfo;	
	EdsUInt32 directoryNum(0);
	EdsVolumeRef vol;
	//�õ�����ĵ�һ���ڴ濨
	err = EdsGetChildAtIndex(theCamera,0,&vol);	
	EdsDirectoryItemRef folderTemp;		
	if (err == EDS_ERR_OK)
	{
		//�õ��ڴ濨�ĵ�һ���ļ���
		err = EdsGetChildAtIndex(vol,0,&folderTemp);	
		err = EdsRelease(vol);
	}
	EdsDirectoryItemRef currentFolder;
	if (err == EDS_ERR_OK)
	{
		//�õ��洢��Ƭ���ļ���
		err = EdsGetChildAtIndex(folderTemp,0,&currentFolder);
		err = EdsRelease(folderTemp);
	}
	if (err == EDS_ERR_OK)
	{
		//�õ����ļ��е���Ϣ�Լ����ļ������ļ��ĸ���
		err = EdsGetDirectoryItemInfo(currentFolder,&folderInfo);
		err = EdsGetChildCount(currentFolder,&directoryNum);
	}
	//���ļ��е��ʼ۸���������Ҫ�õ����ļ�����������false
	if (picNumber>directoryNum)
	{
		return false;
	}
	EdsStreamRef stream;
	EdsDirectoryItemRef picStream;
	int counter(0);
	for (int i=picNumber;i>=1;--i)
	{
		//�õ�������i���ļ���
		EdsGetChildAtIndex(currentFolder,directoryNum-i,&picStream);
		EdsGetDirectoryItemInfo(picStream,&folderInfo);
		EdsChar *imageName = new EdsChar[pathName[counter].size()+1];;
		strcpy(imageName,pathName[counter].c_str());		
		err = EdsCreateFileStream( imageName,kEdsFileCreateDisposition_CreateAlways,kEdsAccess_ReadWrite, &stream);
		//���ظ��ļ�
		err = EdsDownload( picStream, folderInfo.size, stream);
		delete imageName;
		++counter;	
	}
	EdsRelease(picStream);
	EdsRelease(stream);
	EdsRelease(currentFolder);
	return true;
}