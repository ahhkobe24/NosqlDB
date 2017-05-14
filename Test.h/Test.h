#pragma once
////////////////////////////////////////////////////////////////////////////////
// Test.h - Define a class to show the implementation of all requirment      //
// Ver 1.0                                                                   //
// Application: CSE687 Pr#1, Spring 2017                                     //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015               //
// Author:      Xia Hua                                                     //
//              xhua02@syr.edu                                              //
//////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define NosqldbAll class, it has three types of Nosqldbs as its private member,
* to provide functions to operate through the three Nosqldbs . It just looks like a big database contians
* three types of data from user view
*
Class
---------------------------------
* testDemo

improtant functions
---------------------------------
void req(int i );
void req2();          //funciton to show requirement 2
void req3();
void req4();
void req5();
void req6();
void req7();
void req8();
void req9();
void bonus();

* Required Files:
* ---------------
*   - Nosql_elem.h Query.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 Feb 2017
* - First release
*
*/


#include<iostream>
#include "../NosqlDbAll/NosqlDbAll.h"
#include "../Query/Query.h"
using namespace std;
template<typename Dbt1, typename Dbt2, typename Dbt3>
class testDemo
{
public:
	testDemo(NosqldbAll<int,std::string, Widget>* dball,Query<int, std::string, Widget>* que1) {
		quetest = que1;
		dbatest = dball;
	}
	void req(int i );
	void req2();          //funciton to show requirement 2
	void req3();
	void req4();
	void req5();
	void req6();
	void req7();
	void req8();
	void req9();
	void bonus();

private:
	Query<Dbt1, Dbt2, Dbt3>* quetest;
	NosqldbAll<Dbt1, Dbt2, Dbt3>* dbatest;
};

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req(int i )
{
	cout << "*************************************************" << "\n";
	cout << "             Requirement " << i << "             " << "\n";
	cout << "*************************************************" << "\n";

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req2()
{
	req(2);
	cout << "this is to show requirement 2, this will display all the element in database." << "\n";
	quetest->queryAll(dbatest->getallkeys());
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req3()
{
	req(3); 
	cout << "this is to show requirement 3, this will display adding a key/value pair into database." << "\n";
	Element<Widget> elem;
	Widget wi; wi.set("this is Widget");
	elem.name = "addtest";
	elem.category = "Test group";
	elem.desc = "just test";
	elem.data = wi;
	cout << "the element of type Widget will be added is as follow, type and time data will be saved automatically "<<"\n";
	cout << elem.show();
	dbatest->insertdb(elem);
	cout << "display all the element in database." << "\n";
	quetest->queryAll(dbatest->getallkeys());
	cout << "this is to show requirement 3, this will display deleting a key/value pair into database." << "\n";
	cout << "we need to offer the key(name) is: elem3 "<<"\n";
	dbatest->deleteAllE("elem3");
	cout << "display all the element in database." << "\n";
	quetest->queryAll(dbatest->getallkeys());
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req4()
{
	req(4); 
	cout << "this is to show requirement 4, now display changing desc in specific key." << "\n";
	cout << "the key provided is elem1, we change its desc to 687-OOD" << "\n";
	cout << "Display the value with key elem1 before update" << "\n";
	dbatest->showvalue("elem1", dbatest->getdb1());
	dbatest->editAllDesc("elem1", "687-OOD");
	cout << "Display the value with key elem1 after update" << "\n";
	dbatest->showvalue("elem1", dbatest->getdb1());                     //show update desc

	cout << "this is to show requirement 4, now display adding child to specific key." << "\n";
	cout << "the key provided is elem2, we will add key 2elem4,elem5 to its child" << "\n";
	cout << "Display the value with key elem2 before adding" << "\n";
	dbatest->showvalue("elem2", dbatest->getdb1());
	dbatest->addAllChild("elem2", "2elem4");
	dbatest->addAllChild("elem2", "elem5");
	cout << "Display the value with key elem2 after adding" << "\n";
	dbatest->showvalue("elem2", dbatest->getdb1());                   

	cout << "this is to show requirement 4, now display deleting child to specific key." << "\n";
	cout << "the key provided is elem2, we will delete key 2elem4 from its child" << "\n";
	cout << "Display the value with key elem2 before deleting" << "\n";
	dbatest->showvalue("elem2", dbatest->getdb1());
	dbatest->deleteAllChild("elem2", "2elem4");
	cout << "Display the value with key elem2 after deleting" << "\n";
	dbatest->showvalue("elem2", dbatest->getdb1());                    

	cout << "this is to show requirement 4, now display replacing instance for a specific key." << "\n";
	cout << "the key provided is elem1, we will replace instance" << "\n";
	cout << "Display the value with key elem5 before replacing" << "\n";
	dbatest->showvalue("elem5", dbatest->getdb1());
	dbatest->replce("elem5", "687687", "widget");
	cout << "Display the value with key elem5 after replacing" << "\n";
	dbatest->showvalue("elem5", dbatest->getdb3());                    
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req5()
{
	req(5);
	std::cout << "this is to show requirement 5, now display save data to text.xml." << "\n";
	//dbatest->toXmlfile();
	std::cout << "now all your updates have been written to NosqlDb.xml" << "\n";

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req6()
{
	req(6);
	std::cout << "this is to show requirement 6, now display starting a thread to store data to NosqlDb.xml." << "\n";
	std::cout << "we can give it 1 to start the process,then let the system wait for 5 seconds to see the output" << "\n";
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req7()
{
	req(7);
	std::cout << "this is to show requirement 7, now display query value for a specific key." << "\n";
	std::cout << "the key provided is elem1" << "\n";
	quetest->queryByName("elem1");
	std::cout << "this is to show requirement 7, now display child for a specific key." << "\n";
	std::cout << "the key provided is elem1" << "\n";
	quetest->queryChildren("elem1");
	std::cout << "this is to show requirement 7, now display query for all keys contian a specific string in name." << "\n";
	std::cout << "the string provided is em" << "\n";
	quetest->queryByName("em");
	std::cout << "this is to show requirement 7, now display query for all keys contian a specific string in category." << "\n";
	std::cout << "the string provided is fo" << "\n";
	quetest->queryByCate("fo");
	std::cout << "this is to show requirement 7, now display query for all keys contian a specific string in data instance(only for string)." << "\n";
	std::cout << "the string provided is is" << "\n";
	quetest->queryByData("is");
	std::cout << "this is to show requirement 7, now display query by time." << "\n";
	std::cout << "query value between 2016/03/03 and 2017/01/01" << "\n";
	quetest->queryByTime("2016/03/03","2017/01/01");
	std::cout << "Only give the start time 2016/03/03, the end time will set to present" << "\n";
	quetest->queryByTime("2016/03/03");  //end time default set to present
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req8()
{
	req(8);
	std::cout << "this is to show requirement 8, now display start a new query based on an earlier query." << "\n";
	std::cout << "We display a new name query which name contains 2 based on the 4 step of  query in requirment 7"<< "\n";
	dbatest->setqueryfromkeys(dbatest->getprequerykeys(4));
	quetest->queryByName("2");
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::req9()
{
	req(9);
	std::cout << "this is to show requirement 9, now display union two or more earlier queries" << "\n";
	std::cout << "We display union the 1,5  step of  queries in requirement7 and 8 in requirement8 " << "\n";
	std::vector<int> vec= { 1,5,8};
	quetest->unionquery(vec);
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void testDemo<Dbt1, Dbt2, Dbt3>::bonus()
{
	cout << "*************************************************" << "\n";
	cout << "             Bonus- Regular expression             " << "\n";
	cout << "*************************************************" << "\n";
	std::cout << "this is to show Bonus part, now display query name." << "\n";
	std::cout << "We query all the names start with character 'e',end with a number from 1-9 and length more than 2" << "\n";
	quetest->queryNameRegex("1");
	std::cout << "We query all the category contain with \"oo\",end with a number from 1-4 and length more than 4" << "\n";
	quetest->queryCateRegex("1");


}