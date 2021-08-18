#pragma once

#include "Contact.h"
#include "ContactStorage.h"

ostream& operator<<(ostream& out, const Contact& contact)
{
	contact.starred == true ? out << "*\t\t\t" : out << " \t\t\t";
	out << contact.name << "\t\t\t" << contact.phone_number << "\t\t\t";
	return out;
}

bool operator==(const Contact& contact1, const Contact& contact2)
{
	return (contact1.name == contact2.name && contact1.phone_number == contact2.phone_number && contact1.starred == contact2.starred);
}
