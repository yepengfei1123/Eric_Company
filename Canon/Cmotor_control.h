
// motor_control.h : ͷ�ļ�
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
	//�򻯵Ĳ���������
	////////////////////////
	//����Ҫ��ȫ�ֱ���
	unsigned long rstep; 
	float realstep;
	unsigned long nowstep;
	unsigned int angle;
	char comflag;			//���ڱ�־	
	void* hCom; 			//���ھ��
	//����
	int init_system();		//��ʼ��
	void release_system();	//�ͷ�
	int step_1();			//ת��1��
	int set_round(unsigned long step);		//����һȦ�Ĳ���
	void hex2ascii(unsigned char *asc,unsigned long hex); //����ת��
	void transfer(unsigned long* x);//��С��ת��
};