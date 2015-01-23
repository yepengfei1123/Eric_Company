//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#include "stdafx.h"
#include "Cmotor_control.h"

Cmotor_control::Cmotor_control()						//构造函数
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
	//取得串口
	ret0 = (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), 0, KEY_READ,&rhandle));
	if(ret0!=ERROR_SUCCESS) 
		return -1;  
	if(::RegEnumValue(rhandle, nCount, ValueName, &nValueSize, NULL, &nType,(LPBYTE)ValueData, &nDataSize) ==ERROR_NO_MORE_ITEMS)
		return -1;
	//打开串口
	strtemp = ValueData;
	strtemp.Insert(0,_T("\\\\.\\"));
	hCom=CreateFile(strtemp,				//多功能函数，可以创建以下对象，并返回访问句柄：控制台，通信资源，目录（只读打开），磁盘驱动器，文件，邮槽，管道
		GENERIC_READ|GENERIC_WRITE, 
		0, 
		NULL,
		OPEN_EXISTING, 
		0, 
		NULL);
	if(hCom==(HANDLE)-1)
	{
		AfxMessageBox(TEXT("打开COM失败!"));
		//DWORD x = GetLastError();
		//x = x;
		return -1;
	}
	SetupComm(hCom,1024,1024);		//初始化一个指定的通信设备的通信参数

	COMMTIMEOUTS TimeOuts;			//在用ReadFile和WriteFile读写串行口时，需要考虑超时问题

	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=1;
	TimeOuts.ReadTotalTimeoutConstant=5;


	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts);				//设定通讯设备读写时的超时参数
	DCB dcb;										//串口通讯的DCB结构
	DWORD errret;
	GetCommState(hCom,&dcb);
	//设置通讯参数
	dcb.BaudRate=9600; 
	dcb.ByteSize=8;							//指定端口当前使用的数据位
	dcb.Parity=NOPARITY;					//指定端口当前使用的奇偶校验方法
	dcb.StopBits=ONESTOPBIT;				//指定端口当前使用的停止位数
	if(!SetCommState(hCom,&dcb))
		errret = GetLastError();

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);		//清空缓冲区
	comflag = 1;
	//载入配置
	FILE *fl;
	fl = fopen("dataset.ini","rb");
	if(fl == NULL)
	{
		return 0;
	}
	fread(&rstep,sizeof(rstep),1,fl);
	fclose(fl);
	//配置下载到设备
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
void Cmotor_control::release_system()		//释放
{
	CloseHandle(hCom);	
	comflag = 0;
}
int Cmotor_control::step_1()			//转动1度
{
	unsigned char sendbuffer[5];
	unsigned char revbuffer[5];
	unsigned long ltemp;
	unsigned long i;
	//UpdateData(TRUE);                 //mfc函数 更新数据
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
int Cmotor_control::set_round(unsigned long step)		//设置一圈的步数
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