
#include <fstream>

#include "workerManager.h"

#define FILENAME "empFile.txt"



WorkerManager::WorkerManager()
{

	ifstream ifs;
	ifs.open(FILENAME, ios::in); // 读文件

	// 1、文件不存在 
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		// 初始化成员属性
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		
		ifs.close();
		return;
	}

	// 2、文件存在 数据为空 
	char ch;
	ifs >> ch;

	// eof 代表文件末尾
	if (ifs.eof())
	{
		// 文件为空
		cout << "文件为空 " << endl;
		// 初始化成员属性
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	// 3、文件存在 数据不为空
	int num = get_EmpNum();

	this->m_EmpNum = num;
	//cout << "文件个数 ：" << this->m_EmpNum << endl;

	// 开辟空间
	this->m_EmpArray = new Worker * [m_EmpNum];
	// 将文件中的数据存在数组里面
	init_Emp();

	// 测试代码
	/*for (int idx = 0; idx < num; idx++)
	{
		cout << "职工编号：" << m_EmpArray[idx]->m_ID 
			 << " 姓名：" << m_EmpArray[idx]->m_Name 
			 << " 部门编号：" << m_EmpArray[idx]->m_DeptId << endl;

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
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");

	exit(0);
}

void WorkerManager::add_Emp()
{
	cout << "请输入添加职工数量 ：" << endl;

	int addNum = 0;  //保存用户输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		// 计算添加新空间大小 
		int newSize = this->m_EmpNum + addNum;  // 新空间人数

		// 开辟新空间 
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray)
		{
			for (int idx = 0; idx < this->m_EmpNum; idx++)
			{
				newSpace[idx] = this->m_EmpArray[idx];
			}
		}

		// 添加新数据 
		for (int idx = 0; idx < addNum; idx++)
		{
			int id;		 // 职工编号
			string name; // 职工姓名
			int dSelect; // 部门选择


			cout << "请输入第 " << idx + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第 " << idx + 1 << "个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工岗位："<< endl;
			cout << "1、普通职工 " << endl;
			cout << "2、经理 " << endl;
			cout << "3、总裁 " << endl;
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

			// 将创建职工保存到数组里面
			newSpace[this->m_EmpNum + idx] = worker;
		}

		// 释放原有的空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		// 更新新的职工人数
		this->m_EmpNum = newSize;

		// 更新职工文件不为空 
		this->m_FileIsEmpty = false;
		cout << "成功添加" << addNum << "名新职工" << endl;
		//保存文件 
		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
}


void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); // 用输出文件打开方式 --写文件 

	for (int idx = 0; idx < m_EmpNum; idx++)
	{
		ofs << m_EmpArray[idx]->m_ID     << " "
			<< m_EmpArray[idx]->m_Name   << " "
			<< m_EmpArray[idx]->m_DeptId << endl;
	}

	ofs.close();

}

//统计文件人数 
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

		// 根据不同部门ID 创建不同对象 
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
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int idx = 0; idx < this->m_EmpNum; idx++)
		{
			m_EmpArray[idx]->showInfo();
		}
	}

	// 按任意建清平
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
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		// 判断员工是否存在
		int id;
		cout << "请输入要删除员工的id号" << endl;
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

			cout << "删除成功！" << endl;

		}
		else
		{
			cout << "职工不存在" << endl;
		}
	}

	system("pause");
	system("cls");
	






}

void WorkerManager::mod_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请选择需要修改的职工编号： " << endl;
		int id;
		cin >> id;

		int ret = isExist(id);

		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int newDselect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新名字：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			cout << "修改成功！";
			this->save();
			
		}
		else
		{
			cout << "修改失败 职工不存在！" << endl;
		}



	}

	system("pause");
	system("cls");


}

void WorkerManager::find_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;

		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "请输入要查找的职工编号：" << endl;

			cin >> id;

			int ret = isExist(id);

			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if(select == 2)
		{
			cout << "请输入要查找的职工姓名：" << endl;

			string name;

			cin >> name;

			bool flag = false;
			for (int idx = 0; idx < m_EmpNum; idx++)
			{
				if (m_EmpArray[idx]->m_Name == name)
				{
					cout << "查找成功, 职工编号为："
						<< m_EmpArray[idx]->m_ID
						<< " 号的信息如下：" << endl;

					flag = true;
					m_EmpArray[idx]->showInfo();


				}
			}
			if (flag == false)
			{
				cout << "查无此人" << endl;
			}

		}
		else
		{
			cout << "请输入正确选项" << endl;
		}



	}
}

void WorkerManager::sort_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照职工编号升序" << endl;
		cout << "2、按照职工编号降序" << endl;

		int select = 0;
		cin >> select;

		for (int idx = 0; idx < m_EmpNum; idx++)
		{
			int minOrMax = idx; // 最小值或者最大值
			for (int jdx = idx + 1; jdx < this->m_EmpNum; jdx++)
			{
				if (select == 1)
				{
					if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[jdx]->m_ID)
					{
						minOrMax = jdx;
					}
				}
				else // 降序 
				{
					if (m_EmpArray[minOrMax]->m_ID < m_EmpArray[jdx]->m_ID)
					{
						minOrMax = jdx;
					}
				}
			}
			// 判断一开始认定 最小值或者最大值 是不是计算的最小值或者最大值 如果不是交换数据
			if (idx != minOrMax)
			{
				Worker* temp = this->m_EmpArray[idx];
				m_EmpArray[idx] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;

			}
			
		}


	}

	cout << "排序成功！ 排序后的结果为 :" << endl;

	this->save();
	//展示所有职工 
	this->show_Emp();

}

void WorkerManager::clean_File()
{
	cout << "确认清空文件？" << endl;
	cout << "1、确认 " << endl;
	cout << "2、返回 " << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		// 打开模式 ios::trunc 如果存在删除文件并重新创建
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

		cout << "清空成功！" << endl;
		
	}
	else
	{
		return;
	}

	system("pause");
	system("cls");

}

