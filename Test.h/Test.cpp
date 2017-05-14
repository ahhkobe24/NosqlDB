///////////////////////////////////////////////////////////////////////////////////////
// XmlDocument.cpp - Define a class to show the implementation of all requirment    //
// Ver 1.0                                                                          //
// Application: CSE687 Pr#1, Spring 2017                                           //
// Platform:    Win 10 Pro, Visual Studio 2015                                     //
// Author:      Xia Hua                                                           //
//              xhua02@syr.edu                                                    //  
////////////////////////////////////////////////////////////////////////////////////


#include "Test.h"
#include<windows.h>
#include <exception>
using namespace std;




int main()
{
	try {
		std::cout << "*****************Welcome to Nosql DB****************************" << "\n";
		std::cout << " this DB can only support three types of Data(String,int,Widget)" << "\n";
		
			std::cout << "*************************************************" << "\n";
			std::cout << "             Requirement 5              " << "\n";
			std::cout << "*************************************************" << "\n";
			std::cout << "this is to show requirement 5, now display extracting data from NosqlDb.xml." << "\n";
			Init init; init.startInit();
			NoSqlDb<int> dbint; NoSqlDb<std::string> dbstr; NoSqlDb<Widget> dbdb;
			init.initsaveint(dbint);init.initsaveint(dbstr);init.initsaveint(dbdb);
			NosqldbAll<int, std::string, Widget> dball(&dbint,&dbstr,&dbdb);
			Query<int, std::string, Widget> que1(&dball);
			testDemo<int, std::string, Widget> test(&dball,&que1);
			test.req6();
			std::thread t1(&NosqldbAll<int, std::string, Widget>::thread_save, &dball);
			dball.setthread(1);
			Sleep(5000);
			cout << "you have already see the out put of the process!we can give it 0 to stop the process" << "\n";
			cout << "Let's stop the process ,and wait for 5 seconds to check if there is still output" << "\n";
			dball.setthread(0);
			Sleep(5000);
			test.req2(); test.req3(); test.req4(); test.req7(); test.req8(); test.req9();
			test.req5();
			test.bonus();
			dball.setthread(3);
			t1.join();
	}
	catch (const std::exception&) { std::cout << "exception occurs!!!" << "\n"; }
	return 0;
}



//t1.join();
///*dball.replce("elem1", "123123", "int");
//que1.queryAll(dball.getallkeys());*/
////dball.toXmlfile();
////dball.toXmlfile();
////Sleep(2000);
////dball.toXmlfile();

//int a;
//cin >> a;
//dball.setthread(a);








