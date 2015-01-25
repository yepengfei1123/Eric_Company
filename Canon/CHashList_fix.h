#pragma once

#include <string>
#include <vector>
using namespace std;
//命令结构体
struct CommanderList
{
	string  command;
	int		key;
};
//哈希表结构体
struct HashList
{
	string hashCom;
	int hashkey;
	int times;
};


class CHashList
{
public:
	CHashList();
	//vector<CommanderList> isoCommandlist;	
	//vector<CommanderList> avCommandlist;
	//vector<HashList> avHashList;
	//vector<CommanderList> tvCommandlist;
	//vector<HashList> tvHashList;	
	//vector<HashList> isoHashList;
	//void InitCommandList();
public:
	string FindObject(const vector<HashList>& hashList,const int& objectCode);
	void CreatHashList(vector<CommanderList> list,vector<HashList> &hashList);
	//void process();
	std::vector<CommanderList> GetCommanderList();
	std::vector<CHashList> GetHashList();
	//void CreatAllList();
private:
	std::vector<CommanderList> commanderList;
	std::vector<CHashList> hashList;
};


class CCameraCtrlCmdHash:CHashList
{
public:
	CCameraCtrlCmdHash();
	~CCameraCtrlCmdHash();
private:
	vector<CommanderList> isoCommandlist;	
	vector<CommanderList> avCommandlist;
	vector<HashList> avHashList;
	vector<CommanderList> tvCommandlist;
	vector<HashList> tvHashList;	
	vector<HashList> isoHashList;
	
};