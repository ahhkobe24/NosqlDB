/////////////////////////////////////////////////////////////////////
// XmlDocument.cpp - Define a class contains three types of Nosqldb//
// Ver 1.0                                                         //
// Application: CSE687 Pr#1, Spring 2017                           //
// Platform:    Win 10 Pro, Visual Studio 2015                     //
// Author:      Xia Hua                                            //
//              xhua02@syr.edu                                     //  
/////////////////////////////////////////////////////////////////////

#include "../Nosql_elem/Nosql_elem.h"
#include "../Nosql_elem/Widget.h"
#include "NosqlDbAll.h"
#include "../Query/Query.h"

#ifdef TEST_NosqlDbAll
int main()
{
	Widget wi; wi.set("this is 1  Widget");
	NoSqlDb<Widget> dbwi;
	Element<Widget> elem1;
	Init init; init.startInit();
	std::cout << "data extracted from test.xml" << "\n";
	NoSqlDb<int> dbint; NoSqlDb<std::string> dbstr; NoSqlDb<Widget> dbdb;
	init.initsaveint(dbint); init.initsaveint(dbstr); init.initsaveint(dbdb);
	NosqldbAll<int, std::string, Widget> dball(&dbint, &dbstr, &dbdb);
	std::thread t1(&NosqldbAll<int, std::string, Widget>::thread_save, &dball);
	std::cout << "we can give it 1 to start the toxmlfile process,then let the system wait for 30 seconds to see the output" << "\n";
	dball.setthread(1);
	Sleep(5000);
	std::cout << "show value of the key elem1";
	dball.showvalue("elem1", dball.getdb1());
	cout << "the key provided is elem1, we change its desc to 687-OOD" << "\n";
	cout << "Display the value with key elem1 before update" << "\n";
	dball.showvalue("elem1", dball.getdb1());
	dball.editAllDesc("elem1", "687-OOD");
	cout << "Display the value with key elem1 after update" << "\n";
	dball.showvalue("elem1", dball.getdb1());
	cout << "the key provided is elem2, we will add key elem3,elem5 to its child" << "\n";
	cout << "Display the value with key elem2 before adding" << "\n";
	dball.showvalue("elem2", dball.getdb1());
	dball.addAllChild("elem2", "elem3");
	dball.addAllChild("elem2", "elem5");
	cout << "Display the value with key elem2 after adding" << "\n";
	dball.showvalue("elem2", dball.getdb1());
	cout << "the key provided is elem2, we will delete key elem3 from its child" << "\n";
	cout << "Display the value with key elem1 before deleting" << "\n";
	dball.showvalue("elem2", dball.getdb1());
	dball.deleteAllChild("elem2", "elem3");
	cout << "Display the value with key elem1 after deleting" << "\n";
	dball.showvalue("elem2", dball.getdb1());
	dball.setthread(3);
	t1.join();
	return 0;
}
#endif