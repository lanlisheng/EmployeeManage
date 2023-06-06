#include "WorkerManager.h"


WorkerManager::WorkerManager() {
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;//��ʼ����¼����
		this->m_EmpArray = NULL;//��ʼ������ָ��
		this->m_FileIsEmpty = true;//��ʼ���ļ��Ƿ�Ϊ�ձ�־
		ifs.close();
		return;
	}
	//�ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;//��ʼ����¼����
		this->m_EmpArray = NULL;//��ʼ������ָ��
		this->m_FileIsEmpty = true;//��ʼ���ļ��Ƿ�Ϊ�ձ�־
		ifs.close();
		return;
	}

	//�ļ����ڣ����ݴ���
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->init_Emp();

	//���Դ���
	/*for (int i = 0; i < this->m_EmpNum; ++i) {
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
			<< "\tְ��������" << this->m_EmpArray[i]->m_Name
			<< "\t��λ��" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

//չʾ�˵�
void WorkerManager::ShowMenu()
{
	cout << "*********************************************************" << endl;
	cout << "****************��ӭʹ��ְ������ϵͳ��*******************" << endl;
	cout << "****************** 0.�˳��������� ***********************" << endl;
	cout << "****************** 1.����ְ����Ϣ ***********************" << endl;
	cout << "****************** 2.��ʾְ����Ϣ ***********************" << endl;
	cout << "****************** 3.ɾ����ְԱ�� ***********************" << endl;
	cout << "****************** 4.�޸�ְ����Ϣ ***********************" << endl;
	cout << "****************** 5.����ְ����Ϣ ***********************" << endl;
	cout << "****************** 6.���ձ������ ***********************" << endl;
	cout << "****************** 7.����ĵ���Ϣ ***********************" << endl;
	cout << "*********************************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//ֱ���˳�
}

void WorkerManager::Add_Emp()
{
	cout << "����������ְ����������" << endl;

	int addNum = 0;//�����û����������
	cin >> addNum;
	if (addNum > 0) {
		//����ְ��
		//���������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ������=ԭ����¼����+��������
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; ++i) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//��������������
		for (int i = 0; i < addNum; ++i)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��
			cout << "�������" << i + 1 << "��Ա����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��Ա��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
				cout << "����ʧ��" << endl;
				break;
			}
			//��������ְ��ָ�뱣�浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�еĿռ�
		delete[]this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//�����ļ�
		this->save();

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		//���ӳɹ�
		cout << "�ɹ�����" << addNum << "��ְ��" << endl;
	}
	else {
		cout << "��������" << endl;
	}
	//�����������
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	//������ķ�ʽ���ļ�
	ofs.open(FILENAME, ios::out);

	//��ÿ���˵�����д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; ++i) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//д���ر��ļ�
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
		//ͳ����������
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
		if (dId == 1)//��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {//����
			worker = new Manager(id, name, dId);
		}
		else {//�ϰ�
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; ++i) {
			//���ö�̬�������ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�����������
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
	//�ж��ļ��Ƿ����
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		//����ְ�����ɾ��
		cout << "��������Ҫɾ����ְ�����: " << endl;
		int id = 0;
		cin >> id;//����һ��ID���
		int index = this->IsExist(id);
		if (index != -1) {
			//ְ�����ڣ�����Ҫɾ����Ա��λ��Ϊindex
			for (int i = index; i < this->m_EmpNum - 1; ++i) {
				//���ݸ���
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼��Ա����
			//���µ��ļ���
			this->save();
			cout << "ɾ��Ա��" << id << "�ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ��ļ���δ�ҵ���Ӧ��ְ��ID" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		//����ְ������޸�
		cout << "��������Ҫ�޸ĵ�ְ�����: " << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) {
			//���ڶ�Ӧidְ��
			delete this->m_EmpArray[index];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << " ��ְ������������ְ����Ϣ��" << endl;
			cout << "������ְ���±��: " << endl;
			cin >> newId;
			cout << "������ְ��������: " << endl;
			cin >> newName;
			cout << "������ְ���¸�λ: " << endl;
			cout << "1����ְͨԱ " << endl;
			cout << "2������ " << endl;
			cout << "3���ϰ� " << endl;
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
			//�������ݱ��浽������
			this->m_EmpArray[index] = worker;
			cout << "�޸�ְ����Ϣ�ɹ���" << "���ű�ţ�" << this->m_EmpArray[index]->m_DeptId << endl;
			//���浽�ļ���
			this->save();
		}
		else {
			cout << "�޸�ʧ�ܣ��ļ���δ�ҵ���Ӧ��ְ��ID" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڣ����߼�¼Ϊ��" << endl;
	}
	else {
		//������Ҫ���ҵķ�ʽ:
		cout << "������Ҫ���ҵķ�ʽ:" << endl;
		cout << "1������ְ����Ų���" << endl;
		cout << "2������ְ����������" << endl;

		int Select = 0;
		cin >> Select;
		if (Select == 1) {
			//���ձ�Ų���
			int id;
			cout << "���������ְ���ı�ţ�" << endl;
			cin >> id;

			int index = IsExist(id);
			if (index != -1) {
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (Select == 2) {
			//������������
			string name;
			cout << "���������ְ��������:" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < m_EmpNum; ++i) {
				if (this->m_EmpArray[i]->m_Name == name) {
					//���ҳɹ�
					flag = true;
					cout << "���ҳɹ���ְԱ���Ϊ��" << this->m_EmpArray[i]->m_Id << "��ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!flag) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "����Ĳ��ҷ�ʽ����" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ��ְ����Ϣ����ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; ++i) {
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; ++j) {
				if (select == 1) {
					//����
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else if (select == 2) {
					//����
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					cout << "ѡ������ʽ����" << endl;
				}
			}
			if (i != minOrMax) {
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "������ɣ�����󱣴���Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_Emp()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//��ģʽ��ios����trunc �������ɾ���ļ������´���
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
		cout << "��ճɹ���" << endl;
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