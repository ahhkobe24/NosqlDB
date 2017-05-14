#pragma once
#include<string>
#include<iostream>
using namespace std;
// user-made class
class Widget
{
public:
	Widget():data(string()) {}
	Widget(const Widget& wi) :data(wi.get()) {}
	Widget(Widget&& wi) :data(wi.get()) {}
    string get() const { return data; }
	string get() { return data; }
	void set(string str) { data = str; }
	Widget&  operator=(Widget& wi) { this->data = wi.get(); return *this; }
	operator const string() { return data; }

private:
	string data;
};

ostream& operator<<(ostream& out, const Widget& wi)
{
	out << wi.get();
	return out;
}
