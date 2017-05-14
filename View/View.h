#pragma once
/////////////////////////////////////////////////////////////////////////////
// View.h - Define a class to create a UI for user to operate this database//
// Ver 1.0                                                                //
// Application: CSE687 Pr#1, Spring 2017                                  //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015             //
// Author:      Xia Hua                                                   //
//              xhua02@syr.edu                                            //
////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define view class, it creates a simple UI for user to operate the databse; 
* Not display this time
Class
---------------------------------
* view

improtant functions
---------------------------------
void startView();  --------draw the main view
void queryView();   -------- implement each selection of queries
bool checktime(char* ch);    --------check if the input match the time format
void querySelectView();  --------draw the query view
void updateSelectView(); --------draw the update view
void editView();  -------- implement each selection of edit
void mainview(); --------implement each step of selection
std::string cinin(); -----------get input of user and chech its format
void deleteView(); -------- implement each selection of delete
void deleteSelectView()--------draw the delete view
Element<int> conElem(int i);  -------- get input of user and form a Element for insert  overload
Element<std::string> conElem(std::string str);
Element<Widget> conElem(Widget i);   //

* Required Files:
* ---------------
*   -NosqlDbAll.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 5 Feb 2017
* - First release
*
*/
#include "../NosqlDbAll/NosqlDbAll.h"
#include<iostream>
#include <sstream>
#include<string>
template<typename Dbt1, typename Dbt2, typename Dbt3>
class view
{public:
	view(NosqldbAll<typename Dbt1, typename Dbt2, typename Dbt3>* dba, Query<typename Dbt1, typename Dbt2, typename Dbt3>* que)
	{
		dbaview = dba;
		que1 = que;;
	}
	void startView();  // draw the main view
	void queryView();   // implement each selection of queries
	bool checktime(char* ch);    //check if the input match the time format
	void queryRegex();
	void querySelectView();  //draw the query view
	void updateSelectView(); //draw the update view 
	void editView();  // implement each selection of edit
	void mainview(); //implement each step of selection
	std::string cinin(); // get input of user and chech its format
	void deleteView(); // implement each selection of delete
	void deleteSelectView();//draw the delete view
	Element<int> conElem(int i);  // get input of user and form a Element for insert  overload
	Element<std::string> conElem(std::string& str);
	Element<Widget> conElem(Widget& i);
	//std::string fromXml();
private:
	char mvcommand;
	char querycommand;
	char editcommand;
	char deletecommand;
	Query<Dbt1, Dbt2, Dbt3>* que1;
	NosqldbAll<Dbt1, Dbt2, Dbt3>* dbaview;

};

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::startView()
{
	std::string str;
	std::system("CLS");
	std::cout << "*****************Welcome to Nosql DB****************************" << "\n";
	std::cout << " this DB can only support three types of Data(String,int,Widget)" << "\n";
	std::cout << "*****************Main View****************************" << "\n";
	std::cout << " 1. Query" << "\n";
	std::cout << " 2. Delete" << "\n";
	std::cout << " 3. Update" << "\n";
	std::cout << " 4. Insert" << "\n";
	std::cout << " 5. control toxmlfile process" << "\n";
	std::cout << " 6. Exit" << "\n";
	std::cout << "Please enter your command in [1,6]:";
	str = cinin();
	mvcommand = str[0];
	if (str.size() > 1)mvcommand = '\0';
	std::system("CLS");

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::mainview()
{
	while(mvcommand != '6')
	{
		std::string type;
		char tmp[40]; string str = tmp; 
		mvcommand = '\0';
		querycommand = '\0';
		editcommand = '\0';
		deletecommand = '\0';
		startView();
		switch (mvcommand)
		{
		case '1':
			queryView();
			break;
		case '2':
			deleteView();
			break;
		case '3':
			editView();
			break;
		case '4':
			std::cout << "please enter Data type(string,int,Widget): "; std::cin >> type;
			if (type == "int")
			{
				dbaview->insertdb(conElem(1));
			}
			if (type == "string")	
			{
				std::string str;
				dbaview->insertdb(conElem(str));
			}
			if (type == "Widget")
			{
				dbaview->insertdb(conElem(Widget()));
			}break;
		case '5':
			std::cout << "please enter 0/1(0 to end, 1 to start ): ";std::cin.getline(tmp, 40);
			char input = Convert<char>::fromString(tmp);
			if(input =='1'|| input =='0')dbaview->setthread(input);break;
		}
	}
	dbaview->toXmlfile();
	dbaview->setthread(3);


}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::querySelectView()
{
	std::string str;
	std::cout << "*****************Welcome to Nosql DB****************************" << "\n";
	std::cout << " this DB can only support three types of Data(String,int,Widget)" << "\n";
	std::cout << "*****************Query View****************************" << "\n";
	std::cout << " 1. QueryALL" << "\n";
	std::cout << " 2. QueryByName(key)" << "\n";
	std::cout << " 3. QueryByCategoryName" << "\n";
	std::cout << " 4. QueryByTime" << "\n";
	std::cout << " 5. QueryByData(Only for string)"<<"\n";
	std::cout << " 6. Union Query  " << "\n";
	std::cout << " 7. Intersection  Query  " << "\n";
	std::cout << " 8. Query Children " << "\n";
	std::cout << " 9. Regular expression query " << "\n";
	std::cout << " 10. Back to Main View  " << "\n";
	std::cout << "Please enter your command in [1,10]:" ;

	str = cinin();
	if(str.size() > 1)querycommand = '\0';
	if (str.size() == 2)querycommand = '0';
	else querycommand = str[0];
	
	
	//querycommand = '2';
	
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::deleteSelectView()
{
	std::string str;
	std::cout << "*****************Welcome to Nosql DB****************************" << "\n";
	std::cout << " this DB can only support three types of Data(String,int,Widget)" << "\n";
	std::cout << "*****************Delete View****************************" << "\n";
	std::cout << " 1. Delete Element" << "\n";
	std::cout << " 2. Delete child relationship" << "\n";
	std::cout << " 3. Back to Main View  " << "\n";
	std::cout << "Please enter your command in [1,3]:";
	str = cinin();
	deletecommand = str[0];
	if (str.size() > 1)deletecommand = '\0';

	//querycommand = '2';

}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::updateSelectView()
{
	//std::system("CLS");
	std::string str;
	std::cout << "*****************Welcome to Nosql DB****************************" << "\n";
	std::cout << " this DB can only support three types of Data(String,int,Widget)" << "\n";
	std::cout << "*****************Edit View****************************" << "\n";
	std::cout << " 1. Edit Description" << "\n";
	std::cout << " 2. Add child relationship" << "\n";
	std::cout << " 3. Replace data  " << "\n";
	std::cout << " 4. Back to Main View  " << "\n";
	std::cout << "Please enter your command in [1,4]:";
	str = cinin();
	editcommand = str[0];
	
	if (str.size() > 2)editcommand = '\0';
	//std::system("CLS");

}


template<typename Dbt1, typename Dbt2, typename Dbt3>
bool view<Dbt1, Dbt2, Dbt3>::checktime(char* ch)
{
	
	    bool istrue[10];
		memset(istrue, false, sizeof(istrue));
		if (ch[0]=='2')istrue[0] = true;
		if(ch[1]=='0')istrue[1] = true;
		if (ch[2] == '0' || ch[2] == '1')istrue[2] = true;
		if (ch[3] >= '0' && ch[3] <= '9')istrue[3] = true;
		if (ch[4] == '/')istrue[4] = true;
		if (ch[5] =='1'|| ch[5] =='0')istrue[5] = true;
		if (ch[5] == '1') {
			if (ch[6] <= '2'&&ch[6] >= '0')istrue[6] = true;
		}
		if (ch[5] == '0') {
			if (ch[6] <= '9'&&ch[6] >= '1')istrue[6] = true;
		}
		if (ch[7] == '/')istrue[7] = true;
		if (ch[8] >= '0'&& ch[8] <= '3')istrue[8] = true;
		if (ch[8] == '0') {
			if (ch[9] <= '9'&&ch[9] >= '1')istrue[9] = true;
		}
		if (ch[8] == '2') {
			if (ch[9] <= '9'&&ch[9] >= '1')istrue[9] = true;
		}
		if (ch[8] == '1') {
			if (ch[9] <= '9'&&ch[9] >= '1')istrue[9] = true;
		}
		if (ch[8] == '3') {
			if (ch[9] == '0'||ch[9] == '1')istrue[6] = true;
		}
		for (int i = 0; i < 10;i++)
		{
			if (istrue[i] == false) return false;
		}
		return true;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::queryView()
{
	std::string queryBystr;std::string quecatename;std::string strpre;std::string straf;char quepretime[11];char queaftime[11];bool flag = false;
	while (querycommand != '0')
	{
		string tmptimes; string tmp; std::vector<int> vec;int i = 1;if (flag){i--;flag = false;}
		std::stringstream stream; std::string quename; std::string queculomn;  querySelectView(); string times;
		switch (querycommand) {
		case '1':
			que1->queryAll(dbaview->getqueryfromkeys());break;
		case '2':
			std::cout << "Please enter the name you wanna query by: ";std::cin >> quename;que1->queryByName(quename);break;
		case '3':
			std::cout << "Please enter the category name you wanna query by: ";std::cin >> quecatename;
			que1->queryByCate(quecatename);break;
		case '4':
			std::cout << "Please enter the time you wanna query from: ";std::cin >> quepretime;
			while (!(checktime(quepretime)))
			{std::cout << "Format error " << "\n";
	          std::cout << "Please enter the time you wanna query from: ";std::cin >> quepretime;}
			std::cout << "Please enter the time you wanna query to: ";std::cin >> queaftime;
			while (!(checktime(queaftime)))
			{std::cout << "Format error " << "\n";
				std::cout << "Please enter the time you wanna query from: ";std::cin >> queaftime;}
			strpre = quepretime;straf = queaftime;que1->queryByTime(strpre, straf);
			break;
		case '5':
			std::cout << "Please enter the data string you wanna query by: ";std::cin >> queryBystr;
			que1->queryByData(queryBystr);break;
		case '6':
			std::cout << "How many unions you wanna join(no larger than query step): ";tmp = cinin(); 
			for (int i = 0; i < Convert<int>::fromString(tmp); i++) {
				std::cout << "Please enter which steps of query you wanna union(number " << i + 1 << " ): ";tmptimes = cinin();
				vec.push_back(Convert<int>::fromString(tmptimes));
			}
			que1->unionquery(vec);break;
		case '7':
			std::cout << "Please enter which step of query you wanna Intersect with: "; std::cin >> times;
			dbaview->setqueryfromkeys(dbaview->getprequerykeys(Convert<int>::fromString(times)));flag = true;break;
		case '8':
			std::cout << "Please enter the key you wanna query by: ";std::cin >> queryBystr;
			que1->queryChildren(queryBystr);break;
		case '9':
			queryRegex(); break;
		default:
			break;
		}if (i == 0)dbaview->setqueryfromkeys(dbaview->getallkeys());
	}dbaview->setqueryfromkeys(dbaview->getallkeys());
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::editView()
{
	std::string keyedtdesc;
	std::string keyfath;
	std::string keychild;
	std::string new_desc;
	while (editcommand != '4')
	{
		updateSelectView();
		switch (editcommand) {
		case '1':
			std::cout << "Please enter the key you wanna edt desc: ";
			std::cin >> keyedtdesc;
			std::cout << "Please enter the new desc: ";
			std::cin >> new_desc;
			dbaview->editAllDesc(keyedtdesc, new_desc);
			break;
		case '2':
			std::cout << "Please enter the key of father: ";
			std::cin >> keyfath;
			std::cout << "Please enter the key of child: ";
			std::cin >> keychild;
			dbaview->addAllChild(keyfath, keychild);
			break;
		case '3':
			std::cout << "Please enter the key : ";std::cin >> keyfath;
			std::cout << "Please enter new Data value: "; std::cin >> keychild;
			std::cout << "Please enter type(string,int,Widget): "; std::cin >> new_desc;
			dbaview->replce(keyfath, keychild, new_desc);
			break;
		}
	}
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::deleteView()
{
	std::string keydelete;
	std::string keyfath;
	std::string keychild;
	std::string new_desc;
	while (deletecommand != '3')
	{
		deleteSelectView();
		switch (deletecommand) {
		case '1':
			std::cout << "Please enter the key you wanna delete: ";
			std::cin >> keydelete;
			dbaview->deleteAllE(keydelete);
			break;
		case '2':
			std::cout << "Please enter the key of father: ";
			std::cin >> keyfath;
			std::cout << "Please enter the key of child: ";
			std::cin >> keychild;
			dbaview->deleteAllChild(keyfath,keychild);
			break;
		}
	}
}


template<typename Dbt1, typename Dbt2, typename Dbt3>
std::string view<Dbt1, Dbt2, Dbt3>::cinin()
{
	char order[50];
	std::cin.getline(order, 50);
	if (!strcmp(order, "\0"))
		std::cin.getline(order, 50);
	std::string res(order);
	return res;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
Element<int> view<Dbt1, Dbt2, Dbt3>::conElem(int i)
{
	Element<int> elem;
	std::string name; std::string categoryname; std::string desc; string data;
	std::cout << "Please enter the name : "; std::cin >> name; elem.name = name;
	std::cout << "Please enter the categoryname : "; std::cin >> categoryname; elem.category = categoryname;
	std::cout << "Please enter the description : "; desc = cinin(); elem.desc = desc;
	std::cout << "Please enter the data : "; std::cin >> data; elem.data = Convert<int>::fromString(data);
	std::cout << "Element created!!" << "\n";
	return elem;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
Element<std::string> view<Dbt1, Dbt2, Dbt3>::conElem(std::string& str)
{
	Element<std::string> elem;
	std::string name; std::string categoryname; std::string desc; std::string data;
	std::cout << "Please enter the name : "; std::cin >> name; elem.name = name;
	std::cout << "Please enter the categoryname : "; std::cin >> categoryname; elem.category = categoryname;
	std::cout << "Please enter the description : "; desc = cinin(); elem.desc = desc;
	std::cout << "Please enter the data : "; std::cin >> data; elem.data = data;
	std::cout << "Element created!!" << "\n";
	return elem;
}

template<typename Dbt1, typename Dbt2, typename Dbt3>
Element<Widget> view<Dbt1, Dbt2, Dbt3>::conElem(Widget& i)
{
	Element<Widget> elem;
	std::string name; std::string categoryname; std::string desc;string data;
	std::cout << "Please enter the name : "; std::cin >> name; elem.name = name;
	std::cout << "Please enter the categoryname : "; std::cin >> categoryname; elem.category = categoryname;
	std::cout << "Please enter the description : "; desc = cinin(); elem.desc = desc;
	std::cout << "Please enter the data : "; std::cin >> data;
	Widget wi; wi.set(data);
	elem.data =wi;
	std::cout << "Element created!!" << "\n";
	return elem;
}



template<typename Dbt1, typename Dbt2, typename Dbt3>
void view<Dbt1, Dbt2, Dbt3>::queryRegex()
{
	std::cout << "now display query name with regular expression." << "\n";
	std::cout << "We query all the names start with character 'e',end with a number from 1-9 and length more than 2" << "\n";
	que1->queryNameRegex("1");
	std::cout << "now display query category with regular expression." << "\n";
	std::cout << "We query all the category contain with \"oo\",end with a number from 1-4 and length more than 4" << "\n";
	que1->queryCateRegex("1");
}

