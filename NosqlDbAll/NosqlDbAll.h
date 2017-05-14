#pragma once
///////////////////////////////////////////////////////////////////
// NosqlDbAll.h - Define a class contains three types of Nosqldb //
// Ver 1.0                                                       //
// Application: CSE687 Pr#1, Spring 2017                         //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015   //
// Author:      Xia Hua                                         //
//              xhua02@syr.edu                                  //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define NosqldbAll class, it has three types of Nosqldbs as its private member,
* to provide functions to operate through the three Nosqldbs . It just looks like a big database contians 
* three types of data from user view
*
Class
---------------------------------
* NosqldbAll

improtant functions
---------------------------------
//--------keys or key operation
Keys getallkeys();             --------------return all the keys
Keys getprequerykeys(int i);  --------------get keys from earlier query results
Keys getqueryfromkeys();     --------------get keys from the new query will based on
bool setquerykeys(Keys keys); --------------store query result
Keys setqueryfromkeys(Keys key); --------------set keys from the new query will based on
int getquerykeyssize(); -------------- get how many query results have been stored
void setallkeys();   --------------reset allkeys

//-------update delete add operations
bool editAllDesc(Key key, std::string new_text);  --------------edit metadata desc for a specific key in three database
bool addAllChild(Key key, Key childkey);   --------------add child relationship for a specific key in three database
bool deleteAllChild(Key key, Key childkey); --------------delete child relationship for a specific key in three database
bool deleteAllE(Key key); --------------delete element for a specific key in three database and its child relationship
bool replce(Key key, std::string value, std::string type); --------------replace instance of data for a specific key in three database

//---xml------------------------------------------
void toXmlfile();  -------------- store all the elements in three database in xml file

//void thread_save();   create a thread to do toXmlfile()
//-------------db----------------------------
NoSqlDb<Dbt1>* getdb1();  --------------getter db
NoSqlDb<Dbt2>* getdb2();  --------------getter db
NoSqlDb<Dbt3>* getdb3();  --------------getter db
bool insertdb(Element<Dbt1> p);
bool insertdb(Element<Dbt2> p);
bool insertdb(Element<Dbt3> p);  --------------insert element ,overload

* Required Files:
* ---------------
*   - Nosql_elem.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 3 Feb 2017
* - First release
*
*/
#include "../Nosql_elem/Nosql_elem.h"
#include <thread>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <exception>

template<typename Dbt1, typename Dbt2, typename Dbt3>
class NosqldbAll {
public:
	using Key = std::string;
	using Keys = std::vector<Key>;
	NosqldbAll() {}
	NosqldbAll(NoSqlDb<Dbt1>* dbi, NoSqlDb<Dbt2>* dbs, NoSqlDb<Dbt3>* dbd)
	{
			Keys keyintemp = dbi->keys();
			allkeys.insert(allkeys.begin(), keyintemp.begin(), keyintemp.end());
			Keys keystrtemp = dbs->keys();
			allkeys.insert(allkeys.end(), keystrtemp.begin(), keystrtemp.end());
			Keys keychartemp = dbd->keys();
			allkeys.insert(allkeys.end(), keychartemp.begin(), keychartemp.end());
		querykey.push_back(allkeys);
		quefromkeys.insert(quefromkeys.begin(), allkeys.begin(), allkeys.end());
		dbt1 = dbi;
		dbt2 = dbs;
		dbt3 = dbd;
	}
	
	//--------keys or key operation    time  
	Keys getallkeys();                                   //return all the keys
	Keys getprequerykeys(int i);                        //get keys from earlier query results
	Keys getqueryfromkeys();                           //get keys from the new query will based on 
	bool setquerykeys(Keys keys);                         //store query result 
	Keys setqueryfromkeys(Keys key);                     //set keys from the new query will based on
	int getquerykeyssize();                            // get how many query results have been stored
	void setallkeys();                                 //reset allkeys 
	void settime(int a);
	int gettime();
	//-------update delete add operations
	bool editAllDesc(Key key, std::string new_text);              //edit metadata desc for a specific key in three database
	bool addAllChild(Key key, Key childkey);                  //add child relationship for a specific key in three database
	bool deleteAllChild(Key key, Key childkey);                 //delete child relationship for a specific key in three database
	bool deleteAllE(Key key);                                       //delete element for a specific key in three database and its child relationship
	bool replce(Key key, std::string value, std::string type);              //replace instance of data for a specific key in three database
	bool erasechild(std::vector<std::string>::iterator iter,Key key, NoSqlDb<int>* dbt1);
	bool erasechild(std::vector<std::string>::iterator iter,Key key, NoSqlDb<std::string>* dbt2);
	bool erasechild(std::vector<std::string>::iterator iter,Key key, NoSqlDb<Widget>* dbt3);
	//---xml
	void toXmlfile();  // store all the elements in three database in xml file
	
	void thread_save();  // create a thread to do toXmlfile()
	//void threadtoXmlfile();
	//-------------db
	NoSqlDb<Dbt1>* getdb1();  //getter db
	NoSqlDb<Dbt2>* getdb2();  //getter db
	NoSqlDb<Dbt3>* getdb3();  //getter db
	bool insertdb(Element<Dbt1> p);
	bool insertdb(Element<Dbt2> p);
	bool insertdb(Element<Dbt3> p);  //insert element ,overload
	//------------show------------
	bool showvalue(Key key, NoSqlDb<Dbt1>* dbt1);
	bool showvalue(Key key, NoSqlDb<Dbt2>* dbt2);
	bool showvalue(Key key, NoSqlDb<Dbt3>* dbt3);//print out value of a specific key ,overload
	void setthread(int a);  // turn on or off the toxmlfile thread
	int getthread();
private:
	int time = 1;
	NoSqlDb<Dbt1>* dbt1;
	NoSqlDb<Dbt2>* dbt2;
	NoSqlDb<Dbt3>* dbt3;
	Keys allkeys;
	Keys quefromkeys;   // query based on this Keys
 	std::vector<Keys> querykey; // to store query results
	int auto_save = 0;   // the control of toxmlfile thread 
};

template<typename Dbt1, typename Dbt2, typename Dbt3>
void NosqldbAll<Dbt1, Dbt2, Dbt3>::settime(int a)
{
	time = a;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
int NosqldbAll<Dbt1, Dbt2, Dbt3>::gettime()
{
	return time;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void NosqldbAll<Dbt1, Dbt2, Dbt3>::setthread(int a )
{
	auto_save = a;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
int NosqldbAll<Dbt1, Dbt2, Dbt3>::getthread()
{
	return auto_save;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
NoSqlDb<Dbt1>* NosqldbAll<Dbt1, Dbt2, Dbt3>::getdb1()
{
	return dbt1;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
NoSqlDb<Dbt2>* NosqldbAll<Dbt1, Dbt2, Dbt3>::getdb2()
{
	return dbt2;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
NoSqlDb<Dbt3>* NosqldbAll<Dbt1, Dbt2, Dbt3>::getdb3()
{
	return dbt3;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::showvalue(Key key, NoSqlDb<Dbt3>* dbt3)
{
	if (dbt3->iskey(key))
	{
		std::cout << dbt3->value(key).show();
		return true;
	}
	return false;
}


template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::showvalue(Key key, NoSqlDb<Dbt1>* dbt1)  // display value of a specific key  overload
{
	if (dbt1->iskey(key))
	{
		std::cout << dbt1->value(key).show();
		return true;
	}
	return false;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::showvalue(Key key, NoSqlDb<Dbt2>* dbt2)
{
	if (dbt2->iskey(key))
	{
		std::cout << dbt2->value(key).show();
		return true;
	}
	return false;
}




template<typename Dbt1, typename Dbt2, typename Dbt3>
typename NosqldbAll<Dbt1, Dbt2, Dbt3>::Keys NosqldbAll<typename Dbt1, typename Dbt2, typename Dbt3>::getallkeys()
{

	return allkeys;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename NosqldbAll<Dbt1, Dbt2, Dbt3>::Keys NosqldbAll<typename Dbt1, typename Dbt2, typename Dbt3>::getqueryfromkeys()
{

	return quefromkeys;
}


template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::setquerykeys(Keys keys) {
	querykey.push_back(keys);
	return true;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename NosqldbAll<Dbt1, Dbt2, Dbt3>::Keys NosqldbAll<Dbt1, Dbt2, Dbt3>::setqueryfromkeys(Keys keys) {
	quefromkeys.swap(keys);
	return quefromkeys;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename NosqldbAll<Dbt1, Dbt2, Dbt3>::Keys NosqldbAll<Dbt1,Dbt2, Dbt3>::getprequerykeys(int i)
{
	if (i > getquerykeyssize() || i < 0)
	{
		std::cout << "type error" << "\n";
		return querykey[querykey.size() - 1];
	}
	return querykey[i];
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
int NosqldbAll<Dbt1, Dbt2, Dbt3>::getquerykeyssize()
{
	return querykey.size();
}

template<typename Dbt1, typename Dbt2, typename Dbt3>        // write database to file 
void NosqldbAll<Dbt1, Dbt2, Dbt3>::toXmlfile() {
	
		std::string xml;
		XmlDocument doc;
		Sptr pRoot = makeTaggedElement("NosqlDb");
		doc.docElement() = pRoot;

	for (size_t i = 0; i < allkeys.size(); i++) {
		if (dbt1->iskey(allkeys[i]))
		{
			dbt1->makeElem(allkeys[i],pRoot);      //  create tags
			continue;
		}
		if (dbt2->iskey(allkeys[i]))
		{
			dbt2->makeElem(allkeys[i],pRoot);
			continue;
		}
		if (dbt3->iskey(allkeys[i]))
		{
			dbt3->makeElem(allkeys[i],pRoot);
			continue;
		}
	}
	xml = doc.toString();
	std::ofstream file;
	file.open("../NosqlDb.xml", 0x10);
	file << xml;
	file.close();
	std::cout <<"\n"<< "------------xml file has been updated----------------" <<"\n"<<"\n" ;

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::editAllDesc(Key key, std::string new_text)  // edit desc column
{
	/*querykey.clear();
	querykey.push_back(allkeys);*/  // every time we do the edit operation , the query will be reset to new 
	time = 1;
	std::vector<std::string>::iterator it;
	it = find(allkeys.begin(), allkeys.end(), key);
		
	if (it== allkeys.end())
	{
		std::cout << "no element has found" << "\n";
		return false;
	}
	time = 1;
	if (dbt1->editDesc(key, new_text))
	{
		std::cout << "edit succesfully!!!" << "\n";
		return true;
	}
	if (dbt2->editDesc(key, new_text))
	{
		std::cout << "edit succesfully!!!" << "\n";
		return true;
	}
	if (dbt3->editDesc(key, new_text))
	{
		std::cout << "edit succesfully!!!" << "\n";
		return true;
	}
	
	return false;

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::addAllChild(Key key,Key childkey)
{
	querykey.clear();
	querykey.push_back(allkeys);  // every time we do the edit operation , the query will be reset to new
	time = 1;
	std::vector<std::string>::iterator it,childit;
	it = find(allkeys.begin(), allkeys.end(), key);
	childit = find(allkeys.begin(), allkeys.end(), childkey);
	if (it == allkeys.end())
	{
		std::cout << "no father element has found" << "\n";
		return false;
	}
	if (childit == allkeys.end())
	{
		std::cout << "no child element has found" << "\n";
		return false;
	}
	if (dbt1->addChild(key, childkey))return true;
	if (dbt2->addChild(key, childkey))return true;
	if (dbt3->addChild(key, childkey))return true;
	return false;
}


template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::deleteAllChild(Key key, Key childkey)
{
	querykey.clear();
	querykey.push_back(allkeys);
	time = 1;
	std::vector<std::string>::iterator it, childit;
	it = find(allkeys.begin(), allkeys.end(), key);
	childit = find(allkeys.begin(), allkeys.end(), childkey);
	if (it == allkeys.end())
	{
		std::cout << "no father element has found" << "\n";
		return false;
	}
	if (childit == allkeys.end())
	{
		std::cout << "no child element has found" << "\n";
		return false;
	}
	if (dbt1->deleteChild(key, childkey))return true;
	if (dbt2->deleteChild(key, childkey))return true;
	if (dbt3->deleteChild(key, childkey))return true;
	return false;
}
template<typename Dbt1, typename Dbt2, typename Dbt3>
void NosqldbAll<Dbt1, Dbt2, Dbt3>::setallkeys()
{
	allkeys.clear();
	Keys keyintemp = dbt1->keys();
	allkeys.insert(allkeys.end(), keyintemp.begin(), keyintemp.end());
	Keys keystrtemp = dbt2->keys();
	allkeys.insert(allkeys.end(), keystrtemp.begin(), keystrtemp.end());
	Keys keychartemp = dbt3->keys();
	allkeys.insert(allkeys.end(), keychartemp.begin(), keychartemp.end());
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::deleteAllE(Key key)   //delete element of a specific key 
{bool found = false;
if (dbt1->deleteE(key))     // delete element 
{
	std::cout << key << " has been deleted and its child relationship have been deleted" << "\n"; found = true;
}
else if (dbt2->deleteE(key))
{
	std::cout << key << " has been deleted and its child relationship have been deleted" << "\n"; found = true;
}
else if (dbt3->deleteE(key))
{
	std::cout << key << " has been deleted and its child relationship have been deleted" << "\n"; found = true;
}
if (!found) {
	std::cout << "no element has found" << "\n";
	return false;
}
	time = 1; setallkeys(); querykey.clear(); querykey.push_back(allkeys);
	for (std::vector<std::string>::iterator iter = allkeys.begin(); iter != allkeys.end(); iter++)
	{
		if (dbt1->value(*iter).child.size()>0)         // delete the key from all the child which contains it
		{
			erasechild(iter,key, dbt1);
		}
		if (dbt2->value(*iter).child.size()>0)
		{
			erasechild(iter,key, dbt2);
		}
		if (dbt3->value(*iter).child.size()>0)
		{
			erasechild(iter,key, dbt3);
		}
	}
return true;
}
	
template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1,Dbt2,Dbt3>::erasechild(std::vector<std::string>::iterator iter,Key key, NoSqlDb<int>* dbt1)
{
	std::vector<std::string> tmp = dbt1->value(*iter).child;
	for (std::vector<std::string>::iterator iter1 = tmp.begin(); iter1 != tmp.end(); iter1++)
	{
		if (*iter1 == key) {
			dbt1->deleteChild(*iter, key); break;
		}
	}
	return true;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::erasechild(std::vector<std::string>::iterator iter,Key key, NoSqlDb<std::string>* dbt2)
{
	std::vector<std::string> tmp = dbt2->value(*iter).child;
	for (std::vector<std::string>::iterator iter1 = tmp.begin(); iter1 != tmp.end(); iter1++)
	{
		if (*iter1 == key) {
			dbt2->deleteChild(*iter, key); break;
		}
	}
	return true;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::erasechild(std::vector<std::string>::iterator iter,Key key, NoSqlDb<Widget>* dbt3)
{
	std::vector<std::string> tmp = dbt3->value(*iter).child;
	for (std::vector<std::string>::iterator iter1 = tmp.begin(); iter1 != tmp.end(); iter1++)
	{
		if (*iter1 == key) {
			dbt3->deleteChild(*iter, key); break;
		}
	}
	return true;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::replce(Key key, std::string value ,std::string type)
{
	querykey.clear();querykey.push_back(allkeys);time = 1;
	std::vector<std::string>::iterator it; bool founddb = false;
	it = find(allkeys.begin(), allkeys.end(), key);
	if (it == allkeys.end())
	{
		std::cout << "no element has found" << "\n";return false;
	}
	std::string  tmp1 = typeid(Dbt1).name();
	if (tmp1 == typeid(std::string).name())tmp1 = "string";
	if (tmp1 == typeid(Widget).name())tmp1 = "widget";
	std::string  tmp2 = typeid(Dbt2).name();
	if (tmp2 == typeid(std::string).name())tmp2 = "string";
	if (tmp2 == typeid(Widget).name())tmp2 = "widget";
	std::string  tmp3 = typeid(Dbt3).name();
	if (tmp3 == typeid(std::string).name())tmp3 = "string";
	if (tmp3 == typeid(Widget).name())tmp3 = "widget";
	if (tmp1 == type)
	{
		std::stringstream ss; int val;ss << value; ss >> val;
		Property<Dbt1> p(val);
		if (dbt1->iskey(*it))
		{
			founddb = true;
		}
		dbt1->replaceData(key,p);
	}
	if (tmp2 == type)
	{
		Property<Dbt2> p(value);
		if (dbt2->iskey(*it))
		{
			founddb = true;
		}
		dbt2->replaceData(key, p);
	}
	if (tmp3 == type)
	{
		std::stringstream ss; Widget val;
		val.set(value);
		Property<Dbt3> p(val);
		if (dbt3->iskey(*it))
		{
			founddb = true;
		}
		dbt3->replaceData(key, p);
	}
	if (!founddb)std::cout << "--------data type not match!!!------" << "\n";
	else cout << "--------data has updated------" << "\n"; return false;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::insertdb(Element<Dbt1> p)
{
	if (dbt1->insert(p.name, p)) {
		std::cout << "Element " << p.name << " has been inserted" << "\n";
		setallkeys();
		setqueryfromkeys(allkeys);
		return true;
	}
	return false;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::insertdb(Element<Dbt2> p)
{
	if (dbt2->insert(p.name, p))
	{
		std::cout << "Element " << p.name << " has been inserted" << "\n";
		setallkeys();
		setqueryfromkeys(allkeys);
		return true;
	}
	return false;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool NosqldbAll<Dbt1, Dbt2, Dbt3>::insertdb(Element<Dbt3> p)
{
	if (dbt3->insert(p.name, p)) {
		std::cout << "Element " << p.name << " has been inserted" << "\n";
		setallkeys();
		setqueryfromkeys(allkeys);
		return true;
	}
	return false;
}




template<typename Dbt1, typename Dbt2, typename Dbt3>  // thread will call this function to save data to xmlfile
void NosqldbAll<Dbt1, Dbt2, Dbt3>::thread_save()
{
	try {
		if (this->getthread() == 1)
		{
			toXmlfile();
			Sleep(1000);
		}
		Sleep(1000);
		if (this->getthread() == 3) return;
		else thread_save();
	}
	catch (const std::exception&) {
		std::cout << "exception occurs!!!" << "\n";
	}

}