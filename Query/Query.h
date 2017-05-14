#pragma once
///////////////////////////////////////////////////////////////////////
// Query.h - Define a class provide all the query based on NosqlDball//
// Ver 1.1                                                           //
// Application: CSE687 Pr#1, Spring 2017                             //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015        //
// Author:      Xia Hua                                              //
//              xhua02@syr.edu                                       //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define Query class, it a instance of NosqlDbAll as its private member,
* to provide functions to query through the three Nosqldbs.
*
Class
---------------------------------
* NosqldbAll

improtant functions
---------------------------------
void queryAll(Keys keys);    -----------query all the Element in the Database
Keys unionquery(std::vector<int> vec); ----------- Implement unionquery, vec is the earlier queries  your want to union
std::vector<std::string> queryByCate(Key key, int i = 1); ----------- query by category
Keys queryByName(Key key, int i = 1);  ----------- query by name(key)
Keys queryByTime(Key pretime, Key aftime = gettime()); ----------- query by time
Keys queryByData(Key key);  ----------- query by data
void showAll(Keys keys);  ----------- display all the element in the Keys
Keys queryChildren(Key key, int i = 1); -----------query child for a specific key
Keys queryNameRegex(Key key);      -----------regular expression query by name ,start with e and ends in numbers [1-9], length more than 2
Keys queryCateRegex(Key key);    -----------regular expression query by category, contains 'oo' , ends in numbers [1-5], length more than 4
* Required Files:
* ---------------
*   - NosqlDbAll.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 3 Feb 2017
* - First release
* ver 1.1 : 5 Feb 2017
* - add regular expression query
*/
#include "../NosqlDbAll/NosqlDbAll.h"
#include <regex>



template<typename Dbt1, typename Dbt2, typename Dbt3>
class Query{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Query(NosqldbAll<typename Dbt1, typename Dbt2, typename Dbt3>* dball)
	{
		dba = dball;
	}
	Query(Query<typename Dbt1, typename Dbt2, typename Dbt3>& que)  //copy constructor
	{
		dba = que.dba;
	}
	
	void queryAll(Keys keys);    //query all the Element in the Database
	Keys unionquery(std::vector<int> vec); // Implement unionquery, vec is the earlier queries  your want to union
	std::vector<std::string> queryByCate(Key key);    // query by category
	Keys queryByName(Key key);                     // query by name(key)
	Keys queryByTime(Key pretime, Key aftime = getlocaltime()); // query by time
	Keys queryByData(Key key);                             // query by data
	void showAll(Keys keys);                            // display all the element in the Keys
	Keys queryChildren(Key key);              // query child for a specific key 
	Keys queryNameRegex(Key key);            //regular expression query  
	Keys queryCateRegex(Key key);            //regular expression query
	static std::string getlocaltime();
private:
	NosqldbAll<Dbt1, Dbt2, Dbt3>* dba;
};

template<typename Dbt1, typename Dbt2, typename Dbt3>
std::string Query<Dbt1, Dbt2, Dbt3>::getlocaltime()  // getlocal time ,return it as string format
{
	time_t t = time(0);
	char tmp[64];
	tm local;
	localtime_s(&local, &t);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d", &local);
	std::string time_sys = tmp;   //get local system time
	return time_sys;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void Query<Dbt1, Dbt2, Dbt3>::queryAll(Keys keys)
{
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------";
	int i = dba->gettime();
	dba->settime(++i);
		for (size_t iter = 0; iter <keys.size(); iter++)
		{
			if(dba->showvalue(keys[iter], dba->getdb1()))continue;
			if (dba->showvalue(keys[iter], dba->getdb2()))continue;
			if (dba->showvalue(keys[iter], dba->getdb3()))continue;

		}
		std::cout << "-------------Query end !!!------------" << "\n" << "\n";
		dba->setquerykeys(keys);
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void Query<Dbt1, Dbt2, Dbt3>::showAll(Keys keys)
{
	for (size_t iter = 0; iter <keys.size(); iter++)
	{
		if (dba->showvalue(keys[iter], dba->getdb1()))continue;
		if (dba->showvalue(keys[iter], dba->getdb2()))continue;
		if (dba->showvalue(keys[iter], dba->getdb3()))continue;

	}
}


template<typename Dbt1, typename Dbt2, typename Dbt3>
std::vector<std::string> Query<Dbt1, Dbt2, Dbt3>::queryByCate(Key key)
{
	Keys keys = dba->getqueryfromkeys();
	
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------"<<"\n";
	int i = dba->gettime();
	dba->settime(++i);
	Keys tmpkey;
	for (auto iter = keys.cbegin(); iter != keys.cend(); iter++)
	{
	  if (dba->getdb1()->iskey(*iter))
		{
			std::string catestr = dba->getdb1()->value(*iter).category; 
			if (catestr.find(key, 0) < 100 && catestr.find(key, 0) >= 0)   //match input string with category name
			{
				tmpkey.push_back(*iter);
			}
		}
	   if (dba->getdb2()->iskey(*iter))
		{
			std::string cateint = dba->getdb2()->value(*iter).category;
			if (cateint.find(key, 0) < 100 && cateint.find(key, 0) >= 0)
			{
				tmpkey.push_back(*iter);
			}
		}
	   if (dba->getdb3()->iskey(*iter))
	   {
		   std::string cateint = dba->getdb3()->value(*iter).category;
		   if (cateint.find(key, 0) < 100 && cateint.find(key, 0) >= 0)
		   {
			   tmpkey.push_back(*iter);
		   }
	   }
	}
	if(tmpkey.empty())std::cout << "-------no element has found--------" << "\n" << "\n";
	else {
		showAll(tmpkey);
		std::cout << "-------------Query end !!!------------" << "\n" << "\n";
	}
	dba->setquerykeys(tmpkey);  //store query result
	return dba->getqueryfromkeys();
}
//
template<typename Dbt1, typename Dbt2, typename Dbt3>
typename Query< Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::queryByName(Key key)
{
	Keys keys = dba->getqueryfromkeys();
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------";
	int i = dba->gettime();
	dba->settime(++i);
	Keys tmpkey;
	for (auto iter = keys.cbegin(); iter != keys.cend(); iter++)
	{
		if (dba->getdb1()->iskey(*iter))
		{
			std::string tmp = dba->getdb1()->value(*iter).name;
			if (tmp.find(key, 0) < 100 && tmp.find(key, 0) >= 0) //match input string with category name
			{
				tmpkey.push_back(*iter);
			}
		}
		if (dba->getdb2()->iskey(*iter))
		{
			std::string tmp = dba->getdb2()->value(*iter).name;
			if (tmp.find(key, 0) < 100 && tmp.find(key, 0) >= 0)
			{
				tmpkey.push_back(*iter);
			}
		}
		if (dba->getdb3()->iskey(*iter))
		{
			std::string tmp = dba->getdb3()->value(*iter).name;
			if (tmp.find(key, 0) < 100 && tmp.find(key, 0) >= 0)
			{
				tmpkey.push_back(*iter);
			}
		}
	}
	if (tmpkey.empty())std::cout << "-------no element has found--------" << "\n" << "\n";
	else {
		showAll(tmpkey);
		std::cout << "-------------Query end !!!------------" << "\n" << "\n";
	}
	dba->setquerykeys(tmpkey);  //store query result
	return dba->getqueryfromkeys();
}



template<typename Dbt1, typename Dbt2, typename Dbt3>  // second parameter dafault as present time
typename Query<Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::queryByTime(Key pretime, Key aftime = getlocaltime())  
{
	Keys keys = dba->getqueryfromkeys();
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------";
	int i = dba->gettime();
	dba->settime(++i);
	Keys tmpkey;
	for (auto iter = keys.cbegin(); iter != keys.cend(); iter++)
	{
		if (dba->getdb1()->iskey(*iter))
		{
			std::string tmp = dba->getdb1()->value(*iter).timeDate;
			if ( tmp <= aftime && tmp >= pretime)
			{
				//std::cout << dba->dbt1->value(*iter)->show();//problem!!!!!
				tmpkey.push_back(*iter);
			}
		}
		if (dba->getdb2()->iskey(*iter))
		{
			std::string tmp = dba->getdb2()->value(*iter).timeDate;
			if (tmp <= aftime && tmp >= pretime)
			{
				//std::cout << dba->dbt2->value(*iter)->show();//problem!!!!!
				tmpkey.push_back(*iter);
			}
		}
		if (dba->getdb3()->iskey(*iter))
		{
			std::string tmp = dba->getdb3()->value(*iter).timeDate;
			if (tmp <= aftime && tmp >= pretime)
			{
				//std::cout << dba->dbt3->value(*iter)->show();//problem!!!!!
				tmpkey.push_back(*iter);
			}
		}

	}
	if (tmpkey.empty())std::cout << "-------no element has found--------" << "\n" << "\n";
	else {
		showAll(tmpkey);
		std::cout << "-------------Query end !!!------------" << "\n" << "\n";
	}
	dba->setquerykeys(tmpkey);  //store query result
	return dba->getqueryfromkeys();
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename Query<Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::queryByData(Key key)
{
	Keys keys = dba->getqueryfromkeys();
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------";
	int i = dba->gettime();
	dba->settime(++i);
	Keys tmpkey;
	for (auto iter = keys.cbegin(); iter != keys.cend(); iter++)
	{
		std::string tmp = dba->getdb2()->value(*iter).data;
		if (tmp.find(key, 0) < 100 && tmp.find(key, 0) >= 0)
		{
			//std::cout << dba->dbt2->value(*iter)->show();//problem!!!!!
			tmpkey.push_back(*iter);
		}
	}
	if (tmpkey.empty())std::cout << "-------no element has found--------" << "\n" << "\n";
	else {
		
		showAll(tmpkey);
		std::cout << "-------------Query end !!!------------" << "\n" << "\n";
	}
	dba->setquerykeys(tmpkey);  //store query result
	return dba->getqueryfromkeys();
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename Query<Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::unionquery(std::vector<int> vec)
{
	if (vec.size() <= 0)std::cout << "no input !!" << "\n";
	Keys tmpkey = dba->getprequerykeys(vec[0]);
	for (size_t i = 1; i < vec.size(); i++) {
		if (vec[i] > dba->gettime()|| vec[i] < 0)
		{
			std::cout << "type error, no step" << "\n";
			return dba->getqueryfromkeys();
		}
		Keys keyintemp = dba->getprequerykeys(vec[i]);
		tmpkey.insert(tmpkey.end(), keyintemp.begin(), keyintemp.end());
	}
		std::vector<std::string>::iterator vector_iterator;
		sort(tmpkey.begin(), tmpkey.end());

		tmpkey.erase(unique(tmpkey.begin(), tmpkey.end()), tmpkey.end());
		dba->setquerykeys(tmpkey);
		std::cout << "-----------this is the step " << dba->gettime() << " query-----------";
		int i = dba->gettime();
		dba->settime(++i);
		std::cout << tmpkey.size()<<"\n";
		showAll(tmpkey);
	return tmpkey;
}


template<typename Dbt1, typename Dbt2, typename Dbt3>
typename Query<Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::queryChildren(Key key)
{
	Keys keys = dba->getqueryfromkeys();
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------"<<"\n";
	int i = dba->gettime();
	dba->settime(++i);
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (key == keys[i])break;
		if (i == keys.size() - 1)
		{
			std::cout << "----------No element has found!!-------"<<"\n";
			return dba->getqueryfromkeys();
		}
	}
	std::vector<std::string> tmp;size_t t;
	if (dba->getdb1()->iskey(key))
	{
		t = dba->getdb1()->value(key).child.size();
		if (t != 0)
		{
			tmp = dba->getdb1()->value(key).child;
			std::cout << "The children of key " << key << " is :";
		}
	}
	if (dba->getdb2()->iskey(key))
	{
		t = dba->getdb2()->value(key).child.size();
		if (t != 0)
		{
			tmp = dba->getdb2()->value(key).child;
			std::cout << "The children of key " << key << " is :";
		}
	}
	if (dba->getdb3()->iskey(key))
	{
		t = dba->getdb3()->value(key).child.size();
		if (t != 0)
		{
			tmp = dba->getdb3()->value(key).child;
			std::cout << "The children of key " << key << " is :";
		}

	}
	for (size_t i = 0; i <t ; i++)std::cout << tmp[i] << ",";
	std:: cout << "\n"; std::cout << "\n"; dba->setquerykeys(tmp);return tmp;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename Query<Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::queryNameRegex(Key key)
{
	std::cout << "-----------this is the step " << dba->gettime()<< " query-----------" << "\n";
	int i = dba->gettime();
	dba->settime(++i);
	std::regex match("e.*[0-9]");             // match name start with e and ends in numbers [1-9], length more than 2
	Keys keys = dba->getallkeys();
	Keys tmp;
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (std::regex_match(keys[i], match)) {
			tmp.push_back(keys[i]);
		}
	}
	showAll(tmp);
	dba->setquerykeys(tmp);
	return tmp;

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
typename Query<Dbt1, Dbt2, Dbt3>::Keys Query<Dbt1, Dbt2, Dbt3>::queryCateRegex(Key key)
{
	std::cout << "-----------this is the step " << dba->gettime() << " query-----------" << "\n";
	int i = dba->gettime();
	dba->settime(++i);
	std::regex match(".*[o][o].*[1-5]");   // // match category name contains 'oo' , ends in numbers [1-5], length more than 4
	Keys keys = dba->getallkeys();
	Keys tmp;
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (std::regex_match(dba->getdb1()->value(keys[i]).category.getValue(),match)) {
			tmp.push_back(keys[i]);
		}
		if (std::regex_match(dba->getdb2()->value(keys[i]).category.getValue(), match)) {
			tmp.push_back(keys[i]);
		}
		if (std::regex_match(dba->getdb3()->value(keys[i]).category.getValue(), match)) {
			tmp.push_back(keys[i]);
		}
	}
	showAll(tmp);
	dba->setquerykeys(tmp);
	return tmp;

}

