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
	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��λ����
	virtual string getDeptName();

protected:
private:
};