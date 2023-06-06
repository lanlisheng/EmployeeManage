#include "WorkerManager.h"


WorkerManager::WorkerManager() {
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;//初始化记录人数
		this->m_EmpArray = NULL;//初始化数组指针
		this->m_FileIsEmpty = true;//初始化文件是否为空标志
		ifs.close();
		return;
	}
	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//文件为空
		cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;//初始化记录人数
		this->m_EmpArray = NULL;//初始化数组指针
		this->m_FileIsEmpty = true;//初始化文件是否为空标志
		ifs.close();
		return;
	}

	//文件存在，数据存在
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; ++i) {
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id
			<< "\t职工姓名：" << this->m_EmpArray[i]->m_Name
			<< "\t岗位：" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

//展示菜单
void WorkerManager::ShowMenu()
{
	cout << "*********************************************************" << endl;
	cout << "****************欢迎使用职工管理系统！*******************" << endl;
	cout << "****************** 0.退出管理程序 ***********************" << endl;
	cout << "****************** 1.增加职工信息 ***********************" << endl;
	cout << "****************** 2.显示职工信息 ***********************" << endl;
	cout << "****************** 3.删除离职员工 ***********************" << endl;
	cout << "****************** 4.修改职工信息 ***********************" << endl;
	cout << "****************** 5.查找职工信息 ***********************" << endl;
	cout << "****************** 6.按照编号排序 ***********************" << endl;
	cout << "****************** 7.清空文档信息 ***********************" << endl;
	cout << "*********************************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//直接退出
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;

	int addNum = 0;//保存用户输入的数量
	cin >> addNum;
	if (addNum > 0) {
		//添加职工
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间的人数=原来记录人数+新增人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; ++i) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; ++i)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择
			cout << "请输入第" << i + 1 << "个员工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个员工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				cout << "添加失败" << endl;
				break;
			}
			//将创建的职工指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有的空间
		delete[]this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;

		//保存文件
		this->save();

		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//添加成功
		cout << "成功添加" << addNum << "名职工" << endl;
	}
	else {
		cout << "输入有误！" << endl;
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	//用输出的方式打开文件
	ofs.open(FILENAME, ios::out);

	//将每个人的数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; ++i) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//写入后关闭文件
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {//经理
			worker = new Manager(id, name, dId);
		}
		else {//老板
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; ++i) {
			//利用多态单独调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; ++i) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Del_Emp()
{
	//判断文件是否存在
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		//按照职工编号删除
		cout << "请输入想要删除的职工编号: " << endl;
		int id = 0;
		cin >> id;//输入一个ID编号
		int index = this->IsExist(id);
		if (index != -1) {
			//职工存在，并且要删除的员工位置为index
			for (int i = index; i < this->m_EmpNum - 1; ++i) {
				//数据覆盖
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			//更新到文件中
			this->save();
			cout << "删除员工" << id << "成功！" << endl;
		}
		else {
			cout << "删除失败，文件中未找到对应的职工ID" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		//按照职工编号修改
		cout << "请输入想要修改的职工编号: " << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) {
			//存在对应id职工
			delete this->m_EmpArray[index];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << " 号职工，请输入新职工信息：" << endl;
			cout << "请输入职工新编号: " << endl;
			cin >> newId;
			cout << "请输入职工新姓名: " << endl;
			cin >> newName;
			cout << "请输入职工新岗位: " << endl;
			cout << "1、普通职员 " << endl;
			cout << "2、经理 " << endl;
			cout << "3、老板 " << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更改数据保存到数组中
			this->m_EmpArray[index] = worker;
			cout << "修改职工信息成功！" << "部门编号：" << this->m_EmpArray[index]->m_DeptId << endl;
			//保存到文件中
			this->save();
		}
		else {
			cout << "修改失败，文件中未找到对应的职工ID" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在，或者记录为空" << endl;
	}
	else {
		//输入您要查找的方式:
		cout << "输入您要查找的方式:" << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照职工姓名查找" << endl;

		int Select = 0;
		cin >> Select;
		if (Select == 1) {
			//按照编号查找
			int id;
			cout << "请输入查找职工的编号：" << endl;
			cin >> id;

			int index = IsExist(id);
			if (index != -1) {
				//找到职工
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (Select == 2) {
			//按照姓名查找
			string name;
			cout << "请输入查找职工的姓名:" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < m_EmpNum; ++i) {
				if (this->m_EmpArray[i]->m_Name == name) {
					//查找成功
					flag = true;
					cout << "查找成功，职员编号为：" << this->m_EmpArray[i]->m_Id << "号职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!flag) {
				cout << "查找失败！查无此人" << endl;
			}
		}
		else {
			cout << "输入的查找方式有误！" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择职工信息排序方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; ++i) {
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; ++j) {
				if (select == 1) {
					//升序
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else if (select == 2) {
					//降序
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					cout << "选择排序方式错误！" << endl;
				}
			}
			if (i != minOrMax) {
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序完成，排序后保存结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_Emp()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//打开模式：ios：：trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; ++i) {
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; ++i) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}