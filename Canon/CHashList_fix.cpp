#include "stdafx.h"

#include "CHashList.h"


void CCameraCtrlCmdHash::InitCameraCtrlHash()
{
	CommanderList commandListTemp;
	vector<CommanderList> isoCommandlist;

	commandListTemp.command = _T("AUTO");
	commandListTemp.key = 0x00;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("50");
	commandListTemp.key = 0X40;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("100");
	commandListTemp.key = 0X48;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("125");
	commandListTemp.key = 0X4b;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("160");
	commandListTemp.key = 0X4d;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("200");
	commandListTemp.key = 0X50;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("250");
	commandListTemp.key = 0X53;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("320");
	commandListTemp.key = 0X55;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("400");
	commandListTemp.key = 0X58;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("500");
	commandListTemp.key = 0X5b;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("640");
	commandListTemp.key = 0X5d;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("800");
	commandListTemp.key = 0X60;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1000");
	commandListTemp.key = 0X63;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1250");
	commandListTemp.key = 0X65;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1600");
	commandListTemp.key = 0X68;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2000");
	commandListTemp.key = 0X6b;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2500");
	commandListTemp.key = 0X6d;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("3200");
	commandListTemp.key = 0X70;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("4000");
	commandListTemp.key = 0X73;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("5000");
	commandListTemp.key = 0X75;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("6400");
	commandListTemp.key = 0X78;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("8000");
	commandListTemp.key = 0X7b;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("10000");
	commandListTemp.key = 0X7d;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("12800");
	commandListTemp.key = 0X80;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("25600");
	commandListTemp.key = 0X88;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("51200");
	commandListTemp.key = 0X90;
	isoCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("102400");
	commandListTemp.key = 0X98;
	isoCommandlist.push_back(commandListTemp);
	isoList.CreatHashList(isoCommandlist);
	isoCommandlist.clear();

	vector<CommanderList> avCommandlist;
	commandListTemp.command = _T("1");
	commandListTemp.key = 0X08;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.1");
	commandListTemp.key = 0X0B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.2");
	commandListTemp.key = 0X0C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.2(1/3)");
	commandListTemp.key = 0X0D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.4");
	commandListTemp.key = 0X10;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.6");
	commandListTemp.key = 0X13;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.8");
	commandListTemp.key = 0X14;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1.8(1/3)");
	commandListTemp.key = 0X15;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2");
	commandListTemp.key = 0X18;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2.2");
	commandListTemp.key = 0X1B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2.5");
	commandListTemp.key = 0X1C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2.5(1/3)");
	commandListTemp.key = 0X1D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2.8");
	commandListTemp.key = 0X20;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("3.2");
	commandListTemp.key = 0X23;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("3.5");
	commandListTemp.key = 0X24;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("3.5(1/3)");
	commandListTemp.key = 0X25;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("4");
	commandListTemp.key = 0X28;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("4.5");
	commandListTemp.key = 0X2B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("4.5");
	commandListTemp.key = 0X2C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("5.0");
	commandListTemp.key = 0X2D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("5.6");
	commandListTemp.key = 0X30;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("6.3");
	commandListTemp.key = 0X33;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("6.7");
	commandListTemp.key = 0X34;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("7.1");
	commandListTemp.key = 0X35;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("8");
	commandListTemp.key = 0X38;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T ("9");
	commandListTemp.key = 0X3B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("9.5");
	commandListTemp.key = 0X3C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("10");
	commandListTemp.key = 0X3D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("11");
	commandListTemp.key = 0X40;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("13(1/3)");
	commandListTemp.key = 0X43;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("13");
	commandListTemp.key = 0X44;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("14");
	commandListTemp.key = 0X45;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("16");
	commandListTemp.key = 0X48;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("18");
	commandListTemp.key = 0X4B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("19");
	commandListTemp.key = 0X4C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("20");
	commandListTemp.key = 0X4D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("22");
	commandListTemp.key = 0X50;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("25");
	commandListTemp.key = 0X53;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("27");
	commandListTemp.key = 0X54;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("29");
	commandListTemp.key = 0X55;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("32");
	commandListTemp.key = 0X58;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("36");
	commandListTemp.key = 0X5B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("38");
	commandListTemp.key = 0X5C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("40");
	commandListTemp.key = 0X5D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("45");
	commandListTemp.key = 0X60;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("51");
	commandListTemp.key = 0X63;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("54");
	commandListTemp.key = 0X64;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("57");
	commandListTemp.key = 0X65;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("64");
	commandListTemp.key = 0X68;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("72");
	commandListTemp.key = 0X6B;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("76");
	commandListTemp.key = 0X6C;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("80");
	commandListTemp.key = 0X6D;
	avCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("91");
	commandListTemp.key = 0X70;
	avCommandlist.push_back(commandListTemp);

	avList.CreatHashList(avCommandlist);
	avCommandlist.clear();


	std::vector<CommanderList> tvCommandlist;
	commandListTemp.command = _T("Bulb");
	commandListTemp.key = 0X0C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("30\"");
	commandListTemp.key = 0X10;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = ("25\"");
	commandListTemp.key = 0X13;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("20\"");
	commandListTemp.key = 0X14;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("20\"(1/3)");
	commandListTemp.key = 0X15;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("15\"");
	commandListTemp.key = 0X18;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("13\"");
	commandListTemp.key = 0X1B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("10\"");
	commandListTemp.key = 0X1C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("10\"(1/3)");
	commandListTemp.key = 0X1D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("8\"");
	commandListTemp.key = 0X20;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("6\"(1/3)");
	commandListTemp.key = 0X23;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("6\"");
	commandListTemp.key = 0X24;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("5\"");
	commandListTemp.key = 0X25;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("4\"");
	commandListTemp.key = 0X28;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("3\"2");
	commandListTemp.key = 0X2B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("3\"");
	commandListTemp.key = 0X2C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("2\"5");
	commandListTemp.key = 0X2D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("2\"");
	commandListTemp.key = 0X30;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("1\"6");
	commandListTemp.key = 0X33;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1\"5");
	commandListTemp.key = 0X34;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("1\"3");
	commandListTemp.key = 0X35;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command =_T("1\"");
	commandListTemp.key = 0X38;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"8");
	commandListTemp.key = 0X3B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"7");
	commandListTemp.key = 0X3C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"6");
	commandListTemp.key = 0X3D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"5");
	commandListTemp.key = 0X40;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"4");
	commandListTemp.key = 0X43;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"3");
	commandListTemp.key = 0X44;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("0\"3(1/3)");
	commandListTemp.key = 0X45;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/4");
	commandListTemp.key = 0X48;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/5");
	commandListTemp.key = 0X4B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/6");
	commandListTemp.key = 0X4C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/6(1/3)");
	commandListTemp.key = 0X4D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/8");
	commandListTemp.key = 0X50;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/10(1/3)");
	commandListTemp.key = 0X53;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/10");
	commandListTemp.key = 0X54;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/13");
	commandListTemp.key = 0X55;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/15");
	commandListTemp.key = 0X58;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/20(1/3)");
	commandListTemp.key = 0X5B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/20");
	commandListTemp.key = 0X5C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/25");
	commandListTemp.key = 0X5D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/30");
	commandListTemp.key = 0X60;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/40");
	commandListTemp.key = 0X63;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/45");
	commandListTemp.key = 0X64;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/50");
	commandListTemp.key = 0X65;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/60");
	commandListTemp.key = 0X68;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/80");
	commandListTemp.key = 0X6B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/90");
	commandListTemp.key = 0X6C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/100");
	commandListTemp.key = 0X6D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/125");
	commandListTemp.key = 0X70;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/160");
	commandListTemp.key = 0X73;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/180");
	commandListTemp.key = 0X74;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/200");
	commandListTemp.key = 0X75;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/250");
	commandListTemp.key = 0X78;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/320");
	commandListTemp.key = 0X7B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/350");
	commandListTemp.key = 0X7C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/400");
	commandListTemp.key = 0X7D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/500");
	commandListTemp.key = 0X80;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/640");
	commandListTemp.key = 0X83;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/750");
	commandListTemp.key = 0X84;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/800");
	commandListTemp.key = 0X85;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/1000");
	commandListTemp.key = 0X88;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/1250");
	commandListTemp.key = 0X8B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/1500");
	commandListTemp.key = 0X8C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/1600");
	commandListTemp.key = 0X8D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/2000");
	commandListTemp.key = 0X90;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/2500");
	commandListTemp.key = 0X93;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/3000");
	commandListTemp.key = 0X94;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/3200");
	commandListTemp.key = 0X95;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/4000");
	commandListTemp.key = 0X98;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/5000");
	commandListTemp.key = 0X9B;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/6000");
	commandListTemp.key = 0X9C;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/6400");
	commandListTemp.key = 0X9D;
	tvCommandlist.push_back(commandListTemp);
	commandListTemp.command = _T("1/8000");
	commandListTemp.key = 0XA0;
	tvCommandlist.push_back(commandListTemp);

	tvList.CreatHashList(tvCommandlist);
	tvCommandlist.clear();
}



CCameraCtrlCmdHash::~CCameraCtrlCmdHash()
{
	isoList.~CHashList();
	avList.~CHashList();
	tvList.~CHashList();
}


CHashList::~CHashList()
{
	commanderList.clear();
	hashList.clear();
}

void CHashList::CreatHashList(vector<CommanderList> list)
{
	int hashSize = list.size() * 1.5;
	for (size_t i=0; i<hashSize;++i)
	{
		HashList tempList;
		tempList.hashCom = _T("");
		tempList.hashkey = 0;
		tempList.times = 0;
		hashList.push_back(tempList);
	}
	for (size_t i=0;i<list.size();++i)
	{
		int reLocate(1);
		int adr = (list[i].key)%(hashSize-1);
		if (hashList[adr].times == 0)
		{
			hashList[adr].hashCom = list[i].command;
			hashList[adr].hashkey = list[i].key;
			hashList[adr].times = 1;
		}
		else
		{
			int timesTemp(1);
			while (hashList[adr].times != 0)
			{
				adr = (adr + (reLocate++))%(hashSize-1);
				timesTemp++;
			}
			hashList[adr].hashCom = list[i].command;
			hashList[adr].hashkey = list[i].key;
			hashList[adr].times = timesTemp;
		}
	}
}


string CHashList::FindObject(const int& objectCode)
{
	int adrTemp = objectCode%(hashList.size()-1);
	if (hashList[adrTemp].hashkey == objectCode)
	{
		return hashList[adrTemp].hashCom;
	}
	else if (hashList[adrTemp].times == 0)
	{
		return _T("");
	}
	else
	{
		int reLocate(1);
		while(1)
		{
			adrTemp = (adrTemp + (reLocate++))%(hashList.size()-1);
			if (hashList[adrTemp].times == 0)
			{
				return _T("");
				break;
			}
			if (hashList[adrTemp].hashkey == objectCode)
			{
				return hashList[adrTemp].hashCom;
				break;
			}
		}
	}
}

/*
void CHashList::CreatAllList()
{
	this->CreatHashList(isoCommandlist,isoHashList);
	this->CreatHashList(avCommandlist,avHashList);
	this->CreatHashList(tvCommandlist,tvHashList);
}
*/


string Find(const int& objectCode,COMMANDER command)
{
	switch(command)
	{
		case ISO:
			return isoList.FindObject(objectCode);
		case AV:
			return avList.FindObject(objectCode);
		case TV:
			return tvList.FindObject(objectCode);
		default:
			return _T("");
	}
}
