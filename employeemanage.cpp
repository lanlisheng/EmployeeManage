#include <iostream>
#include "WorkerManager.h"
#include "employee.h"
#include "Worker.h"
#include "boss.h"
#include "manager.h"

using namespace std;

int main() {

	/*Worker* worker = NULL;
	worker = new Employee(1, "����", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "����", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "����", 3);
	worker->showInfo();
	delete worker;*/
	//ʵ���������߶���
	WorkerManager wm;

	int choice = 0;
	while (true)
	{
		//����չʾ�˵���Ա����
		wm.ShowMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1://���ְ��
			wm.Add_Emp();
			break;
		case 2://��ʾְ��
			wm.Show_Emp();
			break;
		case 3://ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4://�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5://����ְ��
			wm.Find_Emp();
			break;
		case 6://����ְ��
			wm.Sort_Emp();
			break;
		case 7://���ְ��
			wm.Clean_Emp();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}