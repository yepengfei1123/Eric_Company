/***************************************************************
    Copyright (C), 2014- , XI'AN RANKE INFORMATION TECHNOLOGY CO., LTD
	文件名: CProImage.h
	作者: 卫永波
	版本: v1.0 
	日期: 2014.08
	功能描述: 对图像进行缩放以及抠图处理，用于佳能&转盘项目
	其他: 无
	函数列表: 具体定义看类介绍
	修改历史: 无
*************************************************************/
#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <string>

using namespace cv;
using namespace std;

//图像的存储信息结构体
struct proSave
{
	//图像宽度
	int width;    
	//缩放图像的存储路径
	string resizePath;
	//处理图像的存储路径
	string processPath;
};
/**************************************************
	类名: ProImage
	作者: 卫永波
	版本: v1.0 
	日期: 2014.08
	功能描述: 1.对图像进行等比例放缩
					  2.每张宽度的存储信息保存在proSave的结构体里面
					  3.利用threshold对图像进行抠图处理
	其他: 无
	函数列表: 1.bool processImage(const vector<proSave>& widths,bool falg);
	                   描述：根据widths的图像信息对图像进行处理，
					               flag为缩放或抠图标志位
	                  2.bool processImage(string savePath);
					   描述：对图像只进行单张图像的抠图处理
	修改历史: 无
*************************************************/
class ProImage
{
public:
	//原图的路径地址
	string orginalImgPath;
	uchar threhold;
	bool processImage(const vector<proSave>& widths,bool falg);
	bool processImage(string savePath);
};