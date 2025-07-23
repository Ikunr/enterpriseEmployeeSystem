
#include "workerManager.h"


WorkerManager::WorkerManager()
{
	// ��ʼ����Ա����
	this->m_EmpNum = 0;
	this->m_EmpArray = nullptr;

}

WorkerManager::~WorkerManager()
{

}

void WorkerManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");

	exit(0);
}

void WorkerManager::add_Emp()
{
	cout << "���������ְ������ ��" << endl;

	int addNum = 0;  //�����û���������
	cin >> addNum;
	if (addNum > 0)
	{
		// ��������¿ռ��С 
		int newSize = this->m_EmpNum + addNum;  // �¿ռ�����

		// �����¿ռ� 
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray)
		{
			for (int idx = 0; idx < this->m_EmpNum; idx++)
			{
				newSpace[idx] = this->m_EmpArray[idx];
			}
		}

		// ��������� 
		for (int idx = 0; idx < addNum; idx++)
		{
			int id;		 // ְ�����
			string name; // ְ������
			int dSelect; // ����ѡ��


			cout << "������� " << idx + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "������� " << idx + 1 << "����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��"<< endl;
			cout << "1����ְͨ�� " << endl;
			cout << "2������ " << endl;
			cout << "3���ܲ� " << endl;
			cin >> dSelect;

			Worker* worker = nullptr;

			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			// ������ְ�����浽��������
			newSpace[this->m_EmpNum + idx] = worker;
		}

		// �ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		// �����µ�ְ������
		this->m_EmpNum = newSize;
		cout << "�ɹ����" << addNum << "����ְ��" << endl;;
	}
	else
	{
		cout << "������������" << endl;
	}
}

