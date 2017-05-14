#pragma once

///////////////////////////////////////////////////////////////////
// Nsql_elem.h - Define elements and their contianer and initialization //
// Ver 1.0                                                              //
// Application: CSE687 Pr#1, Spring 2017                               //
// Platform:    Win 10 Pro, Visual Studio 2015                        //
// Author:      Xia Hua                                              //
//              xhua02@syr.edu                                      //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define Elements class, and define NoSqlDb class as a contianer to
* hold Elements, and provide functions to operate the contianer. And the Init is to initialize 
* when the application starts
*
Class
---------------------------------
* Elements
* Init
* NoSqlDb

improtant functions
---------------------------------
* Elements: show() -------print out the element
*
* NoSqlDb: Keys keys()  -------return all the keys in map(db)
* NoSqlDb: Element<Data> value(Key key)  ------- return value for a specific key
* NoSqlDb: bool insert(Key key, Element<Data> elem) -----------insert element into map(db)
* NoSqlDb: bool editDesc(Key key, std::string text) ---------edit metadata desc
* NoSqlDb: bool addChild(Key key, Key childkey) ------------add child relationship
* NoSqlDb: bool replaceData(Key key, Property<Data> p) -------------replace instance of data
* NoSqlDb: bool deleteE(Key key);  --------------delete element from map through key
* NoSqlDb:bool deleteChild(Key key, Key childkey) ------------delete child relationship
* NoSqlDb:void makeElem(Key key,std::shared_ptr < AbstractXmlElement > pRoot)  ---------make doc element to store xml
*
* Init:void startInit();   ------open xml file ,extrat data
* Init:void initsaveint(NoSqlDb<Widget>& db);  overlord-----------initialize  database , insert elements
* Init:void startInitsave(Keys keys,Element<Widget> elem);  overlord---------initialize Elements

* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp,
*     XmlElement.h, XmlElement.cpp
*     Property.h
* 
* Maintenance History:
* --------------------
* ver 1.0 : 4 Feb 2017
* - First release 
* 
*/

#include "../Property/Property.h"
#include "../XmlDocument/StrHelper.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement.h"
#include "../Convert/Convert.h"
#include<iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include<typeinfo>
#include <fstream>
#include "Widget.h"

using namespace XmlProcessing;
using Sptr = std::shared_ptr<AbstractXmlElement>;
template <typename Data>
class Element
{
 public:
	using Name = std::string;
	using CategoryName = std::string;
	using Desc = std::string;
	using Child = std::vector<std::string>;
	using TimeDate = std::string;

	Property<Name> name;            // metadata
	Property<CategoryName> category; // metadata
	Property<Desc> desc; // metadata
	Child child; // vector 
	Property<TimeDate> timeDate;//metadata  
	Property<Name> type;// metadata
	Property<Data> data;  // data
	std::string show();

};



template <typename Data>
std::string Element<Data>::show()
{
	// show children when you've implemented them

	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name(key)" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "Desc" << " : " << desc;
	out << "\n    " << std::setw(8) << "Child" << " : ";
	for (int iter = 0; iter != child.size(); iter++)//output child which is vector
	{
		out << child[iter]<<"  ";
	};
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n    " << std::setw(8) << "type" << " : " << type;
	out << "\n    " << std::setw(8) << "data" << " : " << data;
	out << "\n";
	return out.str();
}

template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;
	bool isempty();                          // check if the map is empty
	//---------keys-------------
	bool iskey(Key key);                  //check if the key belongs to this map
	Keys keys();                          //return all the keys in map(db)
	Element<Data> value(Key key);               //find element through key

	//-------------insert--------

	bool insert(Key key, Element<Data> elem);            //insert element into map(db)

	//--------------update------------

	bool editDesc(Key key, std::string text);             //edit metadata desc 
	bool addChild(Key key, Key childkey);                 //add child relationship
	bool replaceData(Key key, Property<Data> p);          //replace instance of data

	//------------------delete---------------
	bool deleteE(Key key);                         //delete element from map through key
	size_t count();
	bool deleteChild(Key key, Key childkey);     //delete child relationship
	//-------------xml-------------------
	void makeElem(Key key,std::shared_ptr < AbstractXmlElement > pRoot);
	
private:
	using Item = std::pair<Key, Element<Data>>;

	std::unordered_map<Key, Element<Data>> store;
	
};


//-------------return all the keys in map(db)---------
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

template<typename Data>
bool NoSqlDb<Data>::insert(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
	{
		std::cout << "no repeated key allowed" << "n/";
		return false;
	}
	time_t t = time(0);
	char tmp[64];
	tm local;
	localtime_s(&local, &t);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d", &local);
	std::string time_sys = tmp;                         //get local system time
	if(elem.timeDate.getValue().size()==0)elem.timeDate = time_sys;
	std::string  tmp4 = typeid(Data).name(); // find the type of data
	if (tmp4 == typeid(std::string).name())tmp4 = "string";
	if (tmp4 == typeid(Widget).name())tmp4 = "widget";
	elem.type = tmp4;  
	store[key] = elem;
	std::cout << "Element " << elem.name << " has been inserted!!" << "\n";
	return true;
}



template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}

template<typename Data>
bool NoSqlDb<Data>::isempty()
{
	return store.empty();
}

template<typename Data>
bool NoSqlDb<Data>::iskey(Key key)
{
	if (store.find(key) == store.end())return false;
	else
	return true;
}


template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.count();
}


template<typename Data>
bool NoSqlDb<Data>::editDesc(Key key,   std::string new_text)
{
	if (store.find(key)==store.end())
	{
		return false;
	}
	store[key].desc = new_text;  //update desc
	return true;
	
}

template<typename Data>
bool NoSqlDb<Data>::deleteE(Key key)
{
	if (store.find(key) == store.end()) {
		return false;
	}
		store.erase(key);
		return true;
}

template<typename Data>
bool NoSqlDb<Data>::addChild(Key key, Key childkey)
{
	if (store.find(key) == store.end()) {
		return false;
	}
	

	for(int iter = 0; iter != store[key].child.size(); ++iter)
	{
		if (store[key].child[iter] == childkey) // check if the child key has exsit
		{
			std::cout << childkey << " is already a child of " << key << "\n";
			return false;
		}
	}
	store[key].child.push_back(childkey);                        //add child key
	std::cout << "now, " << childkey << " is a child of " << key << "\n";
	return true;
}

template<typename Data>
bool NoSqlDb<Data>::deleteChild(Key key, Key childkey)
{
	if (store.find(key) == store.end()) {
		//std::cout << "no father element has found" << "\n";
		return false;
	}

	for (std::vector<std::string>::iterator iter = store[key].child.begin(); iter != store[key].child.end(); ++iter)
	{
		if (*iter == childkey)
		{
			store[key].child.erase(iter);
			std::cout << childkey << " is no longer a child of " << key << "\n";
			return true;
		}
	}
	return false;
}

template <typename Data>
void NoSqlDb<Data>::makeElem(Key key,std::shared_ptr < AbstractXmlElement > pRoot) // make element of xml file
{
	Convert<Data> C;
	Sptr pIdElem = makeTaggedElement("Element");
	Sptr pNameElem = makeTaggedElement("name");
	Sptr pCateElem = makeTaggedElement("category");
	Sptr pDescElem = makeTaggedElement("Desc");
	Sptr pChildElem = makeTaggedElement("Child");
	Sptr pTypeElem = makeTaggedElement("Type");
	Sptr pDataElem = makeTaggedElement("Data");
	Sptr pTimeElem = makeTaggedElement("Time");   // create tags
	pRoot->addChild(pIdElem);
	pIdElem->addChild(pNameElem);
	Sptr pTextName = makeTextElement(this->value(key).name);  //create text
	pNameElem->addChild(pTextName);
	pIdElem->addChild(pCateElem);
	Sptr pTextCate = makeTextElement(this->value(key).category);
	pCateElem->addChild(pTextCate);
	pIdElem->addChild(pDescElem);
	Sptr pTextDesc = makeTextElement(this->value(key).desc);
	pDescElem->addChild(pTextDesc);
	pIdElem->addChild(pChildElem);
	for (size_t i = 0; i < this->value(key).child.size(); i++)
	{
		Sptr pKeyElem = makeTaggedElement("Key");
		Sptr pTextChild = makeTextElement(this->value(key).child[i]);
			pChildElem->addChild(pKeyElem);
			pKeyElem->addChild(pTextChild);
	}
	pIdElem->addChild(pTypeElem);
	Sptr pTextTyep = makeTextElement(this->value(key).type);
	pTypeElem->addChild(pTextTyep);
	pIdElem->addChild(pDataElem);
	Sptr pTextData = makeTextElement(C.toString(this->value(key).data));
	pDataElem->addChild(pTextData);
	pIdElem->addChild(pTimeElem);
	Sptr pTextTime = makeTextElement(this->value(key).timeDate);
	pTimeElem->addChild(pTextTime);                              //create text and add it to tag
	
}

template<typename Data>
bool NoSqlDb<Data>::replaceData(Key key, Property<Data> p)   //replace data
{
	if (store.find(key) == store.end())
	{
		//std::cout << "no element has found" << "\n";
		return false;
	}
	store[key].data = p;
	return true;

}

/////

class Init                                      // Nosql Db initialize class 
{
public:
	void startInit();                 // open xml file ,extrat data

	using Key = std::string;
	using Keys = std::vector<Key>;
	//using ElmVec = std::vector<Element<Data>>;

	

 	void startInitsave(Keys keys,Element<std::string> elem);
	void startInitsave(Keys keys,Element<int> elem);
	void startInitsave(Keys keys,Element<Widget> elem);  //initialize Elements

	void initsaveint(NoSqlDb<int>& db);
	void initsaveint(NoSqlDb<std::string>& db);
	void initsaveint(NoSqlDb<Widget>& db);         //initialize  database , insert elements

		std::string& trim(std::string &s);     // format string
private:
	std::vector<Element<int>> tmpint;
	std::vector<Element<std::string>> tmpstring;
	std::vector<Element<Widget>> tmpdb;         // vector of three types of element to store element extracted from xml file

};


void Init::startInit()
{
		std::string xml;
		XmlDocument doc("../NosqlDb.xml", XmlDocument::file);        //     
		std::string testTag = "Element";                             // find all the tags named element 
		std::vector<Sptr> found = doc.descendents(testTag).select();
		if (found.size() > 0)
		{
			for (auto pElem : found)
			{
				Keys keys;std::string tmp;
				for (int i = 0; i <7; i++)
				{
					if (i == 3) {
						for (size_t j = 0; j < pElem->children().at(i)->children().size(); j++)
						{
							keys.push_back(trim(pElem->children().at(i)->children().at(j)->children().at(0)->value()));
						}
						continue;
					}
					if(pElem->children().at(i)->children().size()!=0)keys.push_back(trim(pElem->children().at(i)->children().at(0)->value()));
					else keys.push_back("");
					if (i == 4)
					{
						tmp = trim(pElem->children().at(i)->children().at(0)->value());
					}
				}
				if (tmp=="int")
				{
					Element<int> tmpele;startInitsave(keys,tmpele);
					continue;
				}
				if (tmp=="string")
				{
					Element<std::string> tmpele;startInitsave(keys,tmpele);
					continue;
				}
				if (tmp=="widget")
				{
					Element<Widget> tmpele;startInitsave(keys,tmpele);
					continue;
				}
			}
			std::cout << "-------------data has been extracted from Nosql.xml------------" << "\n";
		}
}

void Init::startInitsave(Keys keys,Element<std::string> elem)
{
	size_t len = 3;
	elem.name = keys[0];
	elem.category = keys[1];
	elem.desc = keys[2];
	for (len = 3; len < keys.size() - 3; len++)
		elem.child.push_back(keys[len]);
	elem.type = keys[len];
	elem.data = keys[len + 1];
	elem.timeDate = keys[len + 2];
	tmpstring.push_back(elem);
	
}
void Init::startInitsave(Keys keys,Element<int> elem)
{
	size_t len = 3;
	elem.name = keys[0];
	elem.category = keys[1];
	elem.desc = keys[2];
	for (len = 3; len < keys.size() - 3; len++)
		elem.child.push_back(keys[len]);
	elem.type = keys[len ];
	std::stringstream ss;
	std::string str = keys[len + 1];
	int val;
	ss << str;
	ss >> val;
	elem.data = val;
	elem.timeDate = keys[len + 2];
	tmpint.push_back(elem);
}

void Init::startInitsave(Keys keys,Element<Widget> elem)
{
	size_t len = 3;
	elem.name = keys[0];
	elem.category = keys[1];
	elem.desc = keys[2];
	for (len = 3; len < keys.size() - 3; len++)
		elem.child.push_back(keys[len]);
	elem.type = keys[len];
	std::stringstream ss;
	std::string str = keys[len + 1];
	Widget wi; wi.set(str);
	elem.data = wi;
	elem.timeDate = keys[len + 2];
	tmpdb.push_back(elem);
}

std::string& Init::trim(std::string &s)
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	s.erase(0, s.find_first_not_of("\r"));
	s.erase(s.find_last_not_of("\r") + 1);
	s.erase(0, s.find_first_not_of("\n"));
	s.erase(s.find_last_not_of("\n") + 1);
	return s;
}

void Init::initsaveint(NoSqlDb<int>& db)
{
	for (size_t i = 0; i < tmpint.size(); i++)
	{
		db.insert(tmpint[i].name, tmpint[i]);
	}
}

void Init::initsaveint(NoSqlDb<std::string>& db)
{
	for (size_t i = 0; i < tmpstring.size(); i++)
	{
		db.insert(tmpstring[i].name, tmpstring[i]);
	}
}

void Init::initsaveint(NoSqlDb<Widget>& db)
{
	for (size_t i = 0; i < tmpdb.size(); i++)
	{
		db.insert(tmpdb[i].name, tmpdb[i]);
	}
}




/////////////////////////////////////////////////////////////////////
// Persistance class
// - you will need to implement that using the XmlDocument class
//   from Handouts/Repository