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

	//�����ļ�
	void save();

	// ͳ���ļ��е�����
	int get_EmpNum();

	// ��ʼ��ְ��
	void init_Emp();

	// ��ʾְ��
	void show_Emp();

	//�ж�ְ���Ƿ����
	int isExist(int id);

	// ɾ��ְ��
	void delte_Emp();
	
	//�޸�ְ��
	void mod_Emp();

	// ����ְ��
	void find_Emp();

	//����ְ���������
	void sort_Emp();

	// ����ļ�
	void clean_File();

	// �ж��ļ��Ƿ��λ 
	bool m_FileIsEmpty;
	// ��¼ְ������
	int m_EmpNum;
	// ��¼ְ����ֵָ��
	Worker** m_EmpArray;


};


