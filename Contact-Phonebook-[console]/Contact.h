#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <memory>
#include <vector>
#include <Windows.h>
#include <fstream>

using namespace std;

class Contact
{
	string name;
	string phone_number;
	bool starred;						

public:
	Contact(bool starred, string phone_number, string name)
		: starred(starred), phone_number(phone_number), name(name) {};

	string get_name() const { return name; }
	string get_phone_number() const { return phone_number; }
	bool is_starred() const { return starred; }

	void set_name(string name) { this->name = name; }
	void set_phone_number(string phone_number) { this->phone_number = phone_number; }
	void set_star() { starred = !starred; }

	friend ostream& operator<< (ostream& out, const Contact& contact);
	friend bool operator==(const Contact& contact1, const Contact& contact2);
};