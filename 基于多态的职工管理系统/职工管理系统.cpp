// 基于多态的职工管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#include "workerManager.h"


//void test01()
//{
//	Worker* worker = new Employee(1, "zhangsan", 5);
//	worker->showInfo();
//
//	delete worker;
//	worker = nullptr;
//
//	worker = new Manager(2, "zhangsi", 7);
//	worker->showInfo();
//
//	delete worker;
//	worker = nullptr;
//
//	worker = new Boss(3, "zhangwu", 8);
//	worker->showInfo();
//}

int main()
{
	//test01();
	
	// 实例化管理者对象 
	WorkerManager wm;


	// 用户选择 
	int choice = 0;

	while (true)
	{
		// 展示菜单 
		wm.show_Menu();

		
		cout << "请输入你的选择 ：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:  // 退出代码
			wm.exitSystem();
			break;
		case 1:  // 增加职工
			wm.add_Emp();
			break;
		case 2:  // 显示职工
			wm.show_Emp();
			break;
		case 3:  // 删除职工
			wm.delte_Emp();
			break;
		case 4:  // 修改职工
			wm.mod_Emp();
			break;
		case 5:  // 查找职工
			wm.find_Emp();
			break;
		case 6:  // 排序职工
			wm.sort_Emp();
			break;
		case 7:  // 清空文档 
			wm.clean_File();
			break;
		default:
			system("cls"); // 清屏操作 
			break;
		}


	}


	



	system("pause");
	return 0;
}


