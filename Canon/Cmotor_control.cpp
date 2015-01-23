//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#include "stdafx.h"
#include "Cmotor_control.h"

Cmotor_control::Cmotor_control()						//���캯��
{
	rstep = 0;
	realstep = 0;
	nowstep = 0;
	angle = 0;

	comflag = 0;
	hCom = NULL;
}
void Cmotor_control::hex2ascii(unsigned char *asc,unsigned long hex)
{
	unsigned long ltemp,ltemp1;
	if(hex > 999999)
		return;
	ltemp = hex;
	ltemp1 = ltemp /100000; 
	asc[0] = (unsigned char)(ltemp1 << 4);
	ltemp = ltemp - ltemp1 * 100000;
	ltemp1 = ltemp / 10000;
	asc[0] = asc[0] + (unsigned char)ltemp1; 
	ltemp = ltemp - ltemp1 * 10000;

	ltemp1 = ltemp /1000; 
	asc[1] = (unsigned char)(ltemp1 << 4);
	ltemp = ltemp - ltemp1 * 1000;
	ltemp1 = ltemp / 100;
	asc[1] = asc[1] + (unsigned char)ltemp1; 
	ltemp = ltemp - ltemp1 * 100;

	ltemp1 = ltemp /10; 
	asc[2] = (unsigned char)(ltemp1 << 4);
	ltemp = ltemp - ltemp1 * 10;
	ltemp1 = ltemp ;
	asc[2] = asc[2] + (unsigned char)ltemp1; 
}
void Cmotor_control::transfer(unsigned long* x)
{
	char buffer[4];
	char temp;
	memcpy(buffer,x,4);
	temp = buffer[0];
	buffer[0] = buffer[3];
	buffer[3] = temp;
	temp = buffer[1];
	buffer[1] = buffer[2];
	buffer[2] = temp;
	memcpy(x,buffer,4);	
}
int Cmotor_control::init_system()
{
	comflag = 0;				
	hCom = NULL;	

	long ret0;
	HKEY rhandle;
	int nCount = 0;
	TCHAR ValueName[_MAX_PATH];     //
	TCHAR ValueData[_MAX_PATH];   
	DWORD nValueSize = _MAX_PATH;   
	DWORD nDataSize = _MAX_PATH;  
	CString strtemp;				//
	DWORD nType; 
	unsigned char sendbuffer[5];
	unsigned char revbuffer[5];
	unsigned long ltemp;
	unsigned long i;
	//ȡ�ô���
	ret0 = (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), 0, KEY_READ,&rhandle));
	if(ret0!=ERROR_SUCCESS) 
		return -1;  
	if(::RegEnumValue(rhandle, nCount, ValueName, &nValueSize, NULL, &nType,(LPBYTE)ValueData, &nDataSize) ==ERROR_NO_MORE_ITEMS)
		return -1;
	//�򿪴���
	strtemp = ValueData;
	strtemp.Insert(0,_T("\\\\.\\"));
	hCom=CreateFile(strtemp,				//�๦�ܺ��������Դ������¶��󣬲����ط��ʾ��������̨��ͨ����Դ��Ŀ¼��ֻ���򿪣����������������ļ����ʲۣ��ܵ�
		GENERIC_READ|GENERIC_WRITE, 
		0, 
		NULL,
		OPEN_EXISTING, 
		0, 
		NULL);
	if(hCom==(HANDLE)-1)
	{
		AfxMessageBox(TEXT("��COMʧ��!"));
		//DWORD x = GetLastError();
		//x = x;
		return -1;
	}
	SetupComm(hCom,1024,1024);		//��ʼ��һ��ָ����ͨ���豸��ͨ�Ų���

	COMMTIMEOUTS TimeOuts;			//����ReadFile��WriteFile��д���п�ʱ����Ҫ���ǳ�ʱ����

	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=1;
	TimeOuts.ReadTotalTimeoutConstant=5;


	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts);				//�趨ͨѶ�豸��дʱ�ĳ�ʱ����
	DCB dcb;										//����ͨѶ��DCB�ṹ
	DWORD errret;
	GetCommState(hCom,&dcb);
	//����ͨѶ����
	dcb.BaudRate=9600; 
	dcb.ByteSize=8;							//ָ���˿ڵ�ǰʹ�õ�����λ
	dcb.Parity=NOPARITY;					//ָ���˿ڵ�ǰʹ�õ���żУ�鷽��
	dcb.StopBits=ONESTOPBIT;				//ָ���˿ڵ�ǰʹ�õ�ֹͣλ��
	if(!SetCommState(hCom,&dcb))
		errret = GetLastError();

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);		//��ջ�����
	comflag = 1;
	//��������
	FILE *fl;
	fl = fopen("dataset.ini","rb");
	if(fl == NULL)
	{
		return 0;
	}
	fread(&rstep,sizeof(rstep),1,fl);
	fclose(fl);
	//�������ص��豸
	ltemp = rstep;
	if(ltemp > 9999)
	{
		return 0;
	}
	sendbuffer[0] = 0x05;
	sendbuffer[1] = 0x00;
	hex2ascii(&(sendbuffer[2]),rstep);
	if(FALSE == WriteFile(hCom,sendbuffer,5,&i,NULL)|| (i == 0))
	{
		return 0;
	}
	Sleep(100); 
	if(FALSE == ReadFile(hCom,revbuffer,5,&i,NULL)|| (i == 0))
	{
		return 0;
	}
	if(revbuffer[0] != 0x01)
	{
		return 0;
	}
	return 1;
}
Cmotor_control::~Cmotor_control()
{

}
void Cmotor_control::release_system()		//�ͷ�
{
	CloseHandle(hCom);	
	comflag = 0;
}
int Cmotor_control::step_1()			//ת��1��
{
	unsigned char sendbuffer[5];
	unsigned char revbuffer[5];
	unsigned long ltemp;
	unsigned long i;
	//UpdateData(TRUE);                 //mfc���� ��������
	ltemp = rstep;
	if(ltemp > 999999)
	{
		return -1;
	}
	angle = angle + 1;
	realstep = realstep + ((float)ltemp / 360);
	ltemp = (unsigned long)(realstep - nowstep + 0.5);
	nowstep = nowstep + ltemp;
	if(angle >= 360)
	{
		nowstep = nowstep - rstep;
		angle = angle - 360;
		realstep = realstep - rstep;
	}

	sendbuffer[0] = 0x02;
	sendbuffer[1] = 0x00;
	hex2ascii(&(sendbuffer[2]),ltemp);//rstep
	if(FALSE == WriteFile(hCom,sendbuffer,5,&i,NULL)|| (i == 0))
	{
		return -1;
	}
	Sleep(100); 
	if(FALSE == ReadFile(hCom,revbuffer,5,&i,NULL)|| (i == 0))
	{
		return -1;
	}
	if(revbuffer[0] != 0x01)
	{
		return -1;
	}
	sendbuffer[0] = 0x01;
	sendbuffer[1] = 0x00;
	sendbuffer[2] = 0x00;
	sendbuffer[3] = 0x00;
	sendbuffer[4] = 2;
	if(FALSE == WriteFile(hCom,sendbuffer,5,&i,NULL)|| (i == 0))
	{
		return -1;
	}
	Sleep(100); 
	if(FALSE == ReadFile(hCom,revbuffer,5,&i,NULL)|| (i == 0))
	{
		return -1;
	}
	if(revbuffer[0] != 0x01)
	{
		return -1;
	}
	return 1;
}
int Cmotor_control::set_round(unsigned long step)		//����һȦ�Ĳ���
{
	unsigned char sendbuffer[5];
	unsigned char revbuffer[5];
	unsigned long ltemp;
	unsigned long i;
	ltemp = step;
	if(ltemp > 9999)
	{
		return -1;
	}
	sendbuffer[0] = 0x05;
	sendbuffer[1] = 0x00;
	hex2ascii(&(sendbuffer[2]),step);
	if(FALSE == WriteFile(hCom,sendbuffer,5,&i,NULL)|| (i == 0))
	{
		return -1;
	}
	Sleep(100); 
	if(FALSE == ReadFile(hCom,revbuffer,5,&i,NULL)|| (i == 0))
	{
		return -1;
	}
	if(revbuffer[0] != 0x01)
	{
		return -1;
	}
	FILE *fl;
	fl = fopen("dataset.ini","wb");
	if(fl == NULL)
	{
		return -1;
	}
	fwrite(&rstep,sizeof(step),1,fl);
	fclose(fl);
	rstep = step;
	return 1;
}