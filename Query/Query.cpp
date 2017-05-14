
////////////////////////////////////////////////////////////////////////////////
// XmlDocument.cpp - Define a class provide all the query based on NosqlDball //
// Ver 1.0                                                                   //
// Application: CSE687 Pr#1, Spring 2017                                     //
// Platform:    Win 10 Pro, Visual Studio 2015                              //
// Author:      Xia Hua                                                    //
//              xhua02@syr.edu                                            //  
////////////////////////////////////////////////////////////////////////////

#include "../NosqlDbAll/NosqlDbAll.h"
#include "Query.h"

#ifdef TEST_Query
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
	Query<int, std::string, Widget> que1(&dball);
	std::cout << "  now display query value for a specific key." << "\n";
	std::cout << "the key provided is elem1" << "\n";
	que1.queryByName("elem1");
	std::cout << "  now display child for a specific key." << "\n";
	std::cout << "the key provided is elem1" << "\n";
	que1.queryChildren("elem1");
	std::cout << "  now display query for all keys contian a specific string in name." << "\n";
	std::cout << "the string provided is em" << "\n";
	que1.queryByName("em");
	std::cout << "  now display query for all keys contian a specific string in category." << "\n";
	std::cout << "the string provided is fo" << "\n";
	que1.queryByCate("fo");
	std::cout << "  now display query for all keys contian a specific string in data instance(only for string)." << "\n";
	std::cout << "the string provided is is" << "\n";
	que1.queryByData("is");
	std::cout << "  now display query by time." << "\n";
	std::cout << "query value between 2016/03/03 and 2017/01/01" << "\n";
	que1.queryByTime("2016/03/03", "2017/01/01");
	std::cout << "Only give the start time 2016/03/03, the end time will set to present" << "\n";
	que1.queryByTime("2016/03/03");
	std::cout << "We query all the names start with character 'e',end with a number from 1-9 and length more than 2" << "\n";
	que1.queryNameRegex("1");
	std::cout << "We query all the category contain with \"oo\",end with a number from 1-4 and length more than 4" << "\n";
	que1.queryCateRegex("1");
	
	return 0;
}
#endif