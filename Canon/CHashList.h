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
	vector<CommanderList> isoCommandlist;	
	vector<CommanderList> avCommandlist;
	vector<HashList> avHashList;
	vector<CommanderList> tvCommandlist;
	vector<HashList> tvHashList;	
	void	InitCommandList();
public:
	string CHashList::FindObject(const vector<HashList>& hashList,const int& objectCode);
	void CreatHashList(vector<CommanderList> list,vector<HashList> &hashList);
	void process();
	CHashList();
	vector<HashList> isoHashList;
	void CreatAllList();
};