
// motor_control.h : 头文件
//

#pragma once
#include "afxwin.h"

class Cmotor_control
{
public:
	Cmotor_control();
	~Cmotor_control();
public:
	CComboBox comlist;
	///////////////////////////////////////////////
	//简化的操作函数库
	////////////////////////
	//所需要的全局变量
	unsigned long rstep; 
	float realstep;
	unsigned long nowstep;
	unsigned int angle;
	char comflag;			//串口标志	
	void* hCom; 			//串口句柄
	//函数
	int init_system();		//初始化
	void release_system();	//释放
	int step_1();			//转动1度
	int set_round(unsigned long step);		//设置一圈的步数
	void hex2ascii(unsigned char *asc,unsigned long hex); //数据转换
	void transfer(unsigned long* x);//大小端转换
};