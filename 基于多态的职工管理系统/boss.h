#pragma once
// ��ͨԱ���ļ� 
#include <iostream>
#include "worker.h"

using namespace std;

class Boss : public Worker
{
public:

	// ���캯�� 
	Boss(int id, string name, int dId);

	void showInfo();
	string getDeptName();

};

