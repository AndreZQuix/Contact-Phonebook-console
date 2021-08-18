#pragma once

#include "Contact.h"
#include "ContactGroup.h"

enum class SELECTION
{
	// print contacts by:
	ALL_CONTACTS, BY_GROUP, BY_STAR
};

class ContactStorage
{
	vector<Contact> storage;
	vector<ContactGroup> groups;					/* unique vector of groups for a storage */

	int get_existing_contact_number();				/* get contact number from user and check if it is correct */
	int get_existing_group_number();				/* get group number from user and check if it is correct */	
	string define_name();							/* define_something() - get value, check if it is correct and return to constructor */
	string define_phone_number();
	bool define_is_starred();
	void define_group(Contact& contact);			/* add contact in a group if there is a need */
	void choose_export_type(ostream& os);			/* ask user for export type: all contacts, by group, by star */

public:

	size_t get_storage_size() const { return storage.size(); }
	void add_contact();												/* add new contact to the storage */
	void print_contacts(ostream& out, const SELECTION& MODE);		/* print the contacts in certain stream */
	void delete_contact();											/* delete a certain contact */
	void change_contact();											/* change a certain contact */
	void export_contacts();											/* get a file path and print the contacts with print_contacts(...) method */
	void find_contact();											/* find a contact by name, phone number */
	void sort_contacts();											/* sort contacts by name, phone_number or group */
	void delete_group();											/* delete certain group without deleting any contacts */
	string get_contact_group(const Contact& contact);				/* get contact's group name; if contact is not in group return " " */
};

