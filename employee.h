#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;

class Employee :public Worker
{
public:
	//构造函数
	Employee(int id, string name, int dId);

	//析构函数
	~Employee();
	//显示个人信息
	virtual void showInfo();
	//获取职工岗位名称
	virtual string getDeptName();
protected:
private:
};
