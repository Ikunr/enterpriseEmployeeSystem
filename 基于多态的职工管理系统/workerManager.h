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

	// չʾ�˵� 
	void show_Menu();
	// �˳�����
	void exitSystem();
	// ���ְ��
	void add_Emp();

	// ��¼ְ������
	int m_EmpNum;
	// ��¼ְ����ֵָ��
	Worker** m_EmpArray;


};


