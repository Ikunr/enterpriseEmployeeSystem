#pragma once
#include <iostream>


#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;


class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();

	// 展示菜单 
	void show_Menu();
	// 退出功能
	void exitSystem();
	// 添加职工
	void add_Emp();

	// 记录职工人数
	int m_EmpNum;
	// 记录职工数值指针
	Worker** m_EmpArray;


};


