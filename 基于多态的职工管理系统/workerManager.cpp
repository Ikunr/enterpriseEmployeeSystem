
#include <fstream>

#include "workerManager.h"

#define FILENAME "empFile.txt"



WorkerManager::WorkerManager()
{

	ifstream ifs;
	ifs.open(FILENAME, ios::in); // ���ļ�

	// 1���ļ������� 
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		// ��ʼ����Ա����
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		
		ifs.close();
		return;
	}

	// 2���ļ����� ����Ϊ�� 
	char ch;
	ifs >> ch;

	// eof �����ļ�ĩβ
	if (ifs.eof())
	{
		// �ļ�Ϊ��
		cout << "�ļ�Ϊ�� " << endl;
		// ��ʼ����Ա����
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	// 3���ļ����� ���ݲ�Ϊ��
	int num = get_EmpNum();

	this->m_EmpNum = num;
	//cout << "�ļ����� ��" << this->m_EmpNum << endl;

	// ���ٿռ�
	this->m_EmpArray = new Worker * [m_EmpNum];
	// ���ļ��е����ݴ�����������
	init_Emp();

	// ���Դ���
	/*for (int idx = 0; idx < num; idx++)
	{
		cout << "ְ����ţ�" << m_EmpArray[idx]->m_ID 
			 << " ������" << m_EmpArray[idx]->m_Name 
			 << " ���ű�ţ�" << m_EmpArray[idx]->m_DeptId << endl;

	}*/
	
	

}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray)
	{
		for (int idx = 0; idx < m_EmpNum; idx++)
		{
			delete m_EmpArray[idx];
		}

		delete[] m_EmpArray;
		m_EmpArray = nullptr;
	}
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

		// ����ְ���ļ���Ϊ�� 
		this->m_FileIsEmpty = false;
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		//�����ļ� 
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
}


void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); // ������ļ��򿪷�ʽ --д�ļ� 

	for (int idx = 0; idx < m_EmpNum; idx++)
	{
		ofs << m_EmpArray[idx]->m_ID     << " "
			<< m_EmpArray[idx]->m_Name   << " "
			<< m_EmpArray[idx]->m_DeptId << endl;
	}

	ofs.close();

}

//ͳ���ļ����� 
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
		Worker* worker = nullptr;

		// ���ݲ�ͬ����ID ������ͬ���� 
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;

		index++;
	}
	ifs.close();
}

void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int idx = 0; idx < this->m_EmpNum; idx++)
		{
			m_EmpArray[idx]->showInfo();
		}
	}

	// �����⽨��ƽ
	/*system("pause");
	system("cls");*/

}

int WorkerManager::isExist(int id)
{
	int index = -1;

	for (int idx = 0; idx < m_EmpNum; idx++)
	{
		if (id == m_EmpArray[idx]->m_ID)
		{
			index = idx;
			break;
		}
	}

	return index;
}

void WorkerManager::delte_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		// �ж�Ա���Ƿ����
		int id;
		cout << "������Ҫɾ��Ա����id��" << endl;
		cin >> id;

		int index = isExist(id);

		if (index != -1)
		{
			for (int idx = index; idx < this->m_EmpNum - 1; idx++)
			{
				m_EmpArray[idx] = m_EmpArray[idx + 1];
			}
			this->m_EmpNum--;
			this->save();

			cout << "ɾ���ɹ���" << endl;

		}
		else
		{
			cout << "ְ��������" << endl;
		}
	}

	system("pause");
	system("cls");
	






}

void WorkerManager::mod_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ѡ����Ҫ�޸ĵ�ְ����ţ� " << endl;
		int id;
		cin >> id;

		int ret = isExist(id);

		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int newDselect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "�����������֣�" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> newDselect;

			Worker* worker = nullptr;

			switch (newDselect)
			{
			case 1:
				worker = new Employee(newId, newName, newDselect);
				break;
			case 2:
				worker = new Manager(newId, newName, newDselect);
				break;
			case 3:
				worker = new Boss(newId, newName, newDselect);
				break;
			default:
				break;
			}

			this->m_EmpArray[ret] = worker;

			cout << "newid" << m_EmpArray[ret]->m_ID
				<< "newName" << m_EmpArray[ret]->m_Name;

			cout << "�޸ĳɹ���";
			this->save();
			
		}
		else
		{
			cout << "�޸�ʧ�� ְ�������ڣ�" << endl;
		}



	}

	system("pause");
	system("cls");


}

void WorkerManager::find_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;

		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "������Ҫ���ҵ�ְ����ţ�" << endl;

			cin >> id;

			int ret = isExist(id);

			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if(select == 2)
		{
			cout << "������Ҫ���ҵ�ְ��������" << endl;

			string name;

			cin >> name;

			bool flag = false;
			for (int idx = 0; idx < m_EmpNum; idx++)
			{
				if (m_EmpArray[idx]->m_Name == name)
				{
					cout << "���ҳɹ�, ְ�����Ϊ��"
						<< m_EmpArray[idx]->m_ID
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;
					m_EmpArray[idx]->showInfo();


				}
			}
			if (flag == false)
			{
				cout << "���޴���" << endl;
			}

		}
		else
		{
			cout << "��������ȷѡ��" << endl;
		}



	}
}

void WorkerManager::sort_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1������ְ���������" << endl;
		cout << "2������ְ����Ž���" << endl;

		int select = 0;
		cin >> select;

		for (int idx = 0; idx < m_EmpNum; idx++)
		{
			int minOrMax = idx; // ��Сֵ�������ֵ
			for (int jdx = idx + 1; jdx < this->m_EmpNum; jdx++)
			{
				if (select == 1)
				{
					if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[jdx]->m_ID)
					{
						minOrMax = jdx;
					}
				}
				else // ���� 
				{
					if (m_EmpArray[minOrMax]->m_ID < m_EmpArray[jdx]->m_ID)
					{
						minOrMax = jdx;
					}
				}
			}
			// �ж�һ��ʼ�϶� ��Сֵ�������ֵ �ǲ��Ǽ������Сֵ�������ֵ ������ǽ�������
			if (idx != minOrMax)
			{
				Worker* temp = this->m_EmpArray[idx];
				m_EmpArray[idx] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;

			}
			
		}


	}

	cout << "����ɹ��� �����Ľ��Ϊ :" << endl;

	this->save();
	//չʾ����ְ�� 
	this->show_Emp();

}

void WorkerManager::clean_File()
{
	cout << "ȷ������ļ���" << endl;
	cout << "1��ȷ�� " << endl;
	cout << "2������ " << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		// ��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);

		ofs.close();

		if (m_EmpArray)
		{
			for (int idx = 0; idx < m_EmpNum; idx++)
			{

				delete m_EmpArray[idx];
				m_EmpArray[idx] = nullptr;
			}

			m_EmpNum = 0;
			delete[]m_EmpArray;
			m_EmpArray = nullptr;
			m_FileIsEmpty = true;
		}

		cout << "��ճɹ���" << endl;
		
	}
	else
	{
		return;
	}

	system("pause");
	system("cls");

}

