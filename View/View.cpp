///////////////////////////////////////////////////////////////////////////////////////
// XmlDocument.cpp - Define a class to create a UI for user to operate this database//
// Ver 1.0                                                                          //
// Application: CSE687 Pr#1, Spring 2017                                           //
// Platform:    Win 10 Pro, Visual Studio 2015                                     //
// Author:      Xia Hua                                                           //
//              xhua02@syr.edu                                                    //  
////////////////////////////////////////////////////////////////////////////////////
#include "../Nosql_elem/Nosql_elem.h" 
#include "../Query/Query.h"
#include "../NosqlDbAll/NosqlDbAll.h"
#include "../NosqlDbAll/Wbthread.h"
#include "../View/View.h"
#include "../Test.h/Test.h"
#include<iostream>
#include<thread>
#include<windows.h>
#include <exception>
using namespace std;



#ifdef TEST_View
int main()
{
	
		Init init;init.startInit();
		NoSqlDb<int> dbint;NoSqlDb<std::string> dbstr;NoSqlDb<Widget> dbdb;

			init.initsaveint(dbint);init.initsaveint(dbstr);init.initsaveint(dbdb);
			NosqldbAll<int, std::string, Widget> dball(&dbint, &dbstr, &dbdb);
			Query<int, std::string, Widget> que1(&dball);
			testDemo<int, std::string, Widget> test(&dball, &que1);
			view<int, std::string, Widget> drawview(&dball, &que1);
			drawview.mainview();
		
}
#endif











