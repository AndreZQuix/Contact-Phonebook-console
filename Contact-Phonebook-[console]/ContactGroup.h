#pragma once

#include "ContactStorage.h"

class ContactGroup
{
	string name;
	vector<unique_ptr<Contact>> contact_ref;					/* vector of unique pointers to contacts owned by the group */

public:
	ContactGroup(string name, Contact contact) : name(name) 
	{
		contact_ref.push_back(move(make_unique<Contact>(contact)));
	}

	//~ContactGroup() { cout << "Group was deleted\n"; }

	string get_name() const { return name; }
	const Contact &get_contact(int num) const { return *(contact_ref[num]); }								/* get contact data from the group */
	size_t get_group_size() { return contact_ref.size(); }

	void add_to_group(Contact& contact) { contact_ref.push_back(move(make_unique<Contact>(contact))); }		/* add contact in group */
};

