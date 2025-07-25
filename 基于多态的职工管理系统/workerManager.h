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

	//保存文件
	void save();

	// 统计文件中的人数
	int get_EmpNum();

	// 初始化职工
	void init_Emp();

	// 显示职工
	void show_Emp();

	//判断职工是否存在
	int isExist(int id);

	// 删除职工
	void delte_Emp();
	
	//修改职工
	void mod_Emp();

	// 查找职工
	void find_Emp();

	//按照职工编号排序
	void sort_Emp();

	// 清空文件
	void clean_File();

	// 判断文件是否空位 
	bool m_FileIsEmpty;
	// 记录职工人数
	int m_EmpNum;
	// 记录职工数值指针
	Worker** m_EmpArray;


};


