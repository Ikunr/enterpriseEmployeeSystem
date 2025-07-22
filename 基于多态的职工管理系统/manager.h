#pragma once

#include <iostream>
#include "worker.h"

using namespace std;

class Manager : public Worker
{
public:

	// ¹¹Ôìº¯Êý 
	Manager(int id, string name, int dId);

	void showInfo();
	string getDeptName();

};

