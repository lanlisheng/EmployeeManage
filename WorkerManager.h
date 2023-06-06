#pragma once//防止头文件重复包含
#include <iostream>//包含输入输出流头文件
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
using namespace std;


#define  FILENAME "empFile.txt"

class WorkerManager
{
public:
	//构造函数
	WorkerManager();
	//展示菜单
	void ShowMenu();

	//实现退出系统功能
	void exitSystem();

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//标志文件是否为空
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化职员
	void init_Emp();

	//显示职工
	void Show_Emp();

	//判断职工是否存在
	int IsExist(int id);

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空职工文档
	void Clean_Emp();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//析构函数
	~WorkerManager();
protected:
private:
};
