#include "StdAfx.h"
#include "CProImage.h"
/**************************************************
	������: ProImage::processImage
	��������: ����widths��ͼ����Ϣ��ͼ���������������
	                  flagΪ���Ż��ͼ��־λ
	����:1.widths�����ͣ�vector<proSave>
	                           ������ͼ��Ĵ洢��Ϣ��������Ⱥʹ洢·��
             2.flag�����ͣ�bool��
						  ���������Ż��߿�ͼ�ı�־λ��trueʱ����ͼ&����
						             falseʱ��ֻ��������
	���: ��
	����ֵ: bool�ͣ��ɹ���ȡ����true;���򷵻�false.
	����: ��
	�޸���ʷ: ��
*************************************************/
bool ProImage::processImage(const vector<proSave>& widths,bool flag)
{
	Mat theImage = imread(orginalImgPath);
	if (!theImage.data || widths.size() == 0)
	{
		return false;
	}
	//ͼ��ĵȱ�������
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
	//��ԭͼ���п�ͼ��������������
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
				//��ͼ��ֵ
				if ((g)>threhold&&(b)>threhold&&r>threhold&&abs(b-r)<10&&abs(b-g)<10)
				{
					data[3*col] = 255;
					data[3*col+1]=255;
					data[3*col+2]=255;
				}
			}
		}
		//��ͼ����
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
	������: ProImage::processImage
	��������: �Ե���ͼ����п�ͼ����
	����:1.savePath�����ͣ�string
	                              �������洢·��
	���: ��
	����ֵ: bool�ͣ��ɹ���ȡ����true;���򷵻�false.
	����: ��
	�޸���ʷ: ��
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
			//��ͼ��ֵ
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