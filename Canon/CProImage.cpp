#include "StdAfx.h"
#include "CProImage.h"
/**************************************************
	函数名: ProImage::processImage
	功能描述: 根据widths的图像信息对图像进行批量处理处理，
	                  flag为缩放或抠图标志位
	输入:1.widths：类型：vector<proSave>
	                           描述：图像的存储信息，包括宽度和存储路径
             2.flag：类型：bool型
						  描述：缩放或者抠图的标志位，true时，抠图&缩放
						             false时，只进行缩放
	输出: 无
	返回值: bool型，成功获取返回true;否则返回false.
	其他: 无
	修改历史: 无
*************************************************/
bool ProImage::processImage(const vector<proSave>& widths,bool flag)
{
	Mat theImage = imread(orginalImgPath);
	if (!theImage.data || widths.size() == 0)
	{
		return false;
	}
	//图像的等比例放缩
	Mat tempImage;
	if (flag == false)
	{	
		for (int i=0;i<widths.size();++i)
		{
			int width = widths[i].width;
			int height =(int)(((double)theImage.rows / (double)theImage.cols)*(double)width);
			resize(theImage,tempImage,Size(width,height));
			imwrite(widths[i].resizePath,tempImage);
		}
	}
	//对原图进行抠图处理，并进行缩放
	if (flag == true)
	{
		for (int row=0;row<theImage.rows;++row)
		{
			uchar *data = theImage.ptr<uchar>(row);
			for (int col=0;col<theImage.cols;++col)
			{
				int b = (int)data[3*col];
				int g = (int)data[3*col+1];
				int r = (int)data[3*col+2];
				//抠图阈值
				if ((g)>threhold&&(b)>threhold&&r>threhold&&abs(b-r)<10&&abs(b-g)<10)
				{
					data[3*col] = 255;
					data[3*col+1]=255;
					data[3*col+2]=255;
				}
			}
		}
		//抠图放缩
		for (int i=0;i<widths.size();++i)
		{
			int width = widths[i].width;
			int height =(int)(((double)theImage.rows / (double)theImage.cols)*(double)width);
			resize(theImage,tempImage,Size(width,height));
			imwrite(widths[i].processPath,tempImage);
		}	
	}
	tempImage.release();
	theImage.release();
	return true;
}
/**************************************************
	函数名: ProImage::processImage
	功能描述: 对单张图像进行抠图处理
	输入:1.savePath：类型：string
	                              描述：存储路径
	输出: 无
	返回值: bool型，成功获取返回true;否则返回false.
	其他: 无
	修改历史: 无
*************************************************/
bool ProImage::processImage(string savePath)
{
	Mat theImage = imread(orginalImgPath);	
	if (!theImage.data)
	{
		return false;
	}
	for (int row=0;row<theImage.rows;++row)
	{
		uchar *data = theImage.ptr<uchar>(row);
		for (int col=0;col<theImage.cols;++col)
		{
			int b = (int)data[3*col];
			int g = (int)data[3*col+1];
			int r = (int)data[3*col+2];
			//抠图阈值
			if ((g)>threhold&&(b)>threhold&&r>threhold&&abs(b-r)<10&&abs(b-g)<10)
			{
				data[3*col] = 255;
				data[3*col+1]=255;
				data[3*col+2]=255;
			}
		}
	}
	imwrite(savePath,theImage);
	return true;
}