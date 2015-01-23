/***************************************************************
    Copyright (C), 2014- , XI'AN RANKE INFORMATION TECHNOLOGY CO., LTD
	�ļ���: CProImage.h
	����: ������
	�汾: v1.0 
	����: 2014.08
	��������: ��ͼ����������Լ���ͼ�������ڼ���&ת����Ŀ
	����: ��
	�����б�: ���嶨�忴�����
	�޸���ʷ: ��
*************************************************************/
#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <string>

using namespace cv;
using namespace std;

//ͼ��Ĵ洢��Ϣ�ṹ��
struct proSave
{
	//ͼ����
	int width;    
	//����ͼ��Ĵ洢·��
	string resizePath;
	//����ͼ��Ĵ洢·��
	string processPath;
};
/**************************************************
	����: ProImage
	����: ������
	�汾: v1.0 
	����: 2014.08
	��������: 1.��ͼ����еȱ�������
					  2.ÿ�ſ�ȵĴ洢��Ϣ������proSave�Ľṹ������
					  3.����threshold��ͼ����п�ͼ����
	����: ��
	�����б�: 1.bool processImage(const vector<proSave>& widths,bool falg);
	                   ����������widths��ͼ����Ϣ��ͼ����д���
					               flagΪ���Ż��ͼ��־λ
	                  2.bool processImage(string savePath);
					   ��������ͼ��ֻ���е���ͼ��Ŀ�ͼ����
	�޸���ʷ: ��
*************************************************/
class ProImage
{
public:
	//ԭͼ��·����ַ
	string orginalImgPath;
	uchar threhold;
	bool processImage(const vector<proSave>& widths,bool falg);
	bool processImage(string savePath);
};