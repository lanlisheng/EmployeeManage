#include "employee.h"


Employee::Employee(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

Employee::~Employee()
{

}

//��ʾ������Ϣ
void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id << "\tְ��������" << this->m_Name << "\t��λ��" << this->getDeptName() << "\t��λְ����ɾ�����������" << endl;
}

//��ȡ��λ��Ϣ
std::string Employee::getDeptName()
{
	return string("Ա��");
}

