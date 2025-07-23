#pragma once
// 普通员工文件 
#include <iostream>
#include "worker.h"

using namespace std;

// 员工类
class Employee : public Worker
{
public:

	// 构造函数 
	Employee(int id, string name, int dId);

	void showInfo();
	string getDeptName();

};

