#pragma once

#include <iostream>
#include "worker.h"

using namespace std;

// 经理类 
class Manager : public Worker
{
public:

	// 构造函数 
	Manager(int id, string name, int dId);

	void showInfo();
	string getDeptName();

};

