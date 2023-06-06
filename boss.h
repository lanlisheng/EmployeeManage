#pragma once
#include <iostream>
#include <string>
#include "worker.h"

using namespace std;



class Boss :public Worker
{
public:
	Boss(int id, string name, int dId);
	~Boss();
	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();

protected:
private:
};