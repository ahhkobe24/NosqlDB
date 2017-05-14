///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - Nsql_elem.h - Define elements and 
//                their contianer and initialization             //
// Ver 1.0                                                       //
// Application: CSE687 Pr#1, Spring 2017                         //
// Platform:    Win 10 Pro, Visual Studio 2015                   //
// Author:      Xia Hua                                          //
//              xhua02@syr.edu                                   //  
///////////////////////////////////////////////////////////////////

#include "Nosql_elem.h"
#include "Widget.h"
#include "../NosqlDbAll/NosqlDbAll.h"
#include "../Query/Query.h"
using namespace XmlProcessing;
using Sptr = std::shared_ptr<AbstractXmlElement>;

#ifdef TEST_Nosql_elem
int main()
{
	Widget wi; wi.set("this is 1  Widget");
    NoSqlDb<Widget> dbwi;
	Element<Widget> elem1;
	elem1.name = "elem1";
	elem1.category = "food";
	elem1.desc = "CSE-687";
	elem1.data = wi;
	Element<Widget> elem2;
	elem2.name = "elem2";
	elem2.category = "food";
	elem2.desc = "CSE-687";
	wi.set("this is 2 Widget");
	elem2.data = wi;
	dbwi.insert(elem2.name, elem2);
	dbwi.insert(elem1.name, elem1);
	std::cout << dbwi.value(elem1.name).show();
	std::cout << "edit Desc" << "\n";
	dbwi.editDesc(elem1.name, "CES-681");
	std::cout<<dbwi.value(elem1.name).show();
	std::cout << "add elem2 to elem1's child" << "\n";
	dbwi.addChild(elem1.name, elem2.name);
	std::cout << dbwi.value(elem1.name).show();
	Init init; init.startInit();
	std::cout << "data extracted from test.xml" << "\n";
	NoSqlDb<int> dbint; NoSqlDb<std::string> dbstr; NoSqlDb<Widget> dbdb;
	init.initsaveint(dbint); init.initsaveint(dbstr); init.initsaveint(dbdb);
	NosqldbAll<int, std::string, Widget> dball(&dbint, &dbstr, &dbdb);
	Query<int, std::string, Widget> que1(&dball);
	que1.queryAll(dball.getallkeys());
}
#endif