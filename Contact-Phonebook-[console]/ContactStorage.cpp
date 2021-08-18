#include "ContactStorage.h"
#include <regex>
#include <algorithm>

void menu(ContactStorage& Storage);

/* check if cin gets digit */

size_t check_inner_stream()
{
	int num;
	cin >> num;

	if (!cin)
	{
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "Not a number\n";
		return 0;
	} 
	
	return num;
}

/* get contact number from user and check if it is correct */

int ContactStorage::get_existing_contact_number()
{
	print_contacts(cout, SELECTION::ALL_CONTACTS);

	while (true)
	{
		size_t num = check_inner_stream();
		if (num != 0)
		{
			if (num > storage.size())
				cout << "This contact does not exist\n";
			else return --num;
		}
	}
}

/* get group number from user and check if it is correct */

int ContactStorage::get_existing_group_number()
{
	if (groups.size() == 0)
	{
		cout << "There are no any groups\n";
		return -1;
	}

	for (size_t num = 0; num < groups.size(); num++)
		cout << num + 1 << " " << groups[num].get_name() << '\n';

	cout << "Type the group number and press [enter]\n";
	while (true)
	{
		size_t number = check_inner_stream();
		if (number != 0)
		{
			--number;
			if (number < groups.size()) return number;
			else cout << "\nIncorrect group number\n";
		}
	}
}

/* define_something() - get value, check if it is correct and return to constructor */

/*-----------------------------------------------------------------------------------*/

string ContactStorage::define_name()
{
	string name;
	cout << "\nType a contact name and press [enter]\n";
	while (true)
	{
		getline(cin, name);
		if (name.size() >= 1)
			return name;
		else cout << "Name must be at least 1 character\n";
	}
}

string ContactStorage::define_phone_number()
{
	string phone_number;
	regex r("\\+?\\d{1,4}?(\\s?|.?)\\d{3}(\\s?|.?)\\d{3}(\\s?|.?)\\d{2}(\\s?|.?)\\d{2}");
	smatch c;

	cout << "\nType a contact phone number and press [enter]\n";

	while (true)
	{
		getline(cin, phone_number);
		if (regex_match(phone_number, c, r)) return phone_number;
		else cout << "Wrong number\n";
	}
}

bool ContactStorage::define_is_starred()
{
	cout << "\nStar this contact? Press [enter] for Yes | Any key for No\n";
	if (_getch() == 13)
		return true;
	else return false;
}

/*-----------------------------------------------------------------------------------*/

/* add contact in a group if there is a need */

void ContactStorage::define_group(Contact& contact)
{
	cout << "\nPress 0 to Create new group | Press 1 to Choose the existing one | Press 2 to Not create any group\n";
	while (true)
	{
		switch (_getch())
		{
		case '0':
		{
			cout << "\nType the group name and press [enter]\n";
			string group_name;
			cin.ignore();
			getline(cin, group_name);
			vector<ContactGroup>::iterator it;

			if (groups.size() >= 1)
			{
				for (it = groups.begin(); it != groups.end(); ++it)
				{
					if ((*it).get_name() == group_name) 
						(*it).add_to_group(contact);
				}
			}

			groups.push_back(ContactGroup(group_name, contact));
			return;
			break;
		}

		case '1':
		{
			int i = get_existing_group_number();
			if (i == -1) return;
			groups[i].add_to_group(contact);
			return;
			break;
		}

		case '2':
			return;
			break;

		default:
			cout << "This function does not exist\n";
			break;
		}
	}
}

/* add new contact to the storage */

void ContactStorage::add_contact()
{
	cout << "Type how many contacts do you want to add and press [enter]\n";
	size_t contacts_count = check_inner_stream();
	if (contacts_count == 0) return;

	for (size_t i = 0; i < contacts_count; i++)
	{
		storage.push_back(Contact(define_is_starred(), define_phone_number(), define_name()));
		define_group(storage[i]);
	}
}

/* print the contacts in certain stream */

void ContactStorage::print_contacts(ostream& out, const SELECTION& MODE)
{
	int num = 0;
	if (MODE == SELECTION::ALL_CONTACTS)
	{
		out << "Number\tStarred\t\t\tName\t\t\tPhone number\t\t\tGroup\n";
		for (auto& elem : storage)
		{
			out << ++num << "\t" << elem;
			out << this->get_contact_group(elem) << endl;
		}
	}
	else if (MODE == SELECTION::BY_GROUP)
	{
		int num = get_existing_group_number();

		if (num >= 0)
		{
			out << "Number\tStarred\t\t\tName\t\t\tPhone number\t\t\tGroup\n";
			for (auto& elem : storage)
				for (int i = 0; i < groups[num].get_group_size(); i++)
					if (elem == groups[num].get_contact(i))
					{
						out << num + 1 << "\t" << elem;
						out << groups[num].get_name() << endl;
					}
		}
	}
	else if (MODE == SELECTION::BY_STAR)
	{
		out << "Number\tStarred\t\t\tName\t\t\tPhone number\t\t\tGroup\n";
		for (auto& elem : storage)
			if (elem.is_starred())
			{
				out << ++num << "\t" << elem;
				out << this->get_contact_group(elem) << endl;
			}
	}
}

/* delete a certain contact */

void ContactStorage::delete_contact()
{
	cout << "Choose a contact to delete\n\n";
	storage.erase(storage.begin() + get_existing_contact_number());
	cout << "Deleted successfully\n\n";
}

/* change a certain contact */

void ContactStorage::change_contact()
{
	cout << "Choose a contact you want to change\n\n";
	int num = get_existing_contact_number();

	cout << "Change: \t\t| [esc] to go back to menu \n1. Name \n2. Phone number \n3. Group \n4. Star/Unstar\n";
	switch (_getch())
	{
	case '1':
		storage[num].set_name(define_name());
		break;

	case '2':
		storage[num].set_phone_number(define_phone_number());
		break;

	case '3':
		define_group(storage[num]);
		break;

	case '4':
		storage[num].set_star();
		break;

	case 27:
		return;
		break;

	default:
		cout << "This function does not exist\n";
		break;
	}
}

/* ask user for export type: all contacts, by group, by star */

void ContactStorage::choose_export_type(ostream& os)
{
	cout << "Export: \n1. All contacts \n2. By group \3. By star\n";
	switch (_getch())
	{
	case '1':
		print_contacts(os, SELECTION::ALL_CONTACTS);
		break;

	case '2':
		print_contacts(os, SELECTION::BY_GROUP);
		break;

	case '3':
		print_contacts(os, SELECTION::BY_STAR);
		break;

	default:
		cout << "This function does not exist. Contacts were not exported\n";
		return;
		break;
	}
	cout << "Exported successfully\n\n";
}

/* get a file path and print the contacts with print_contacts(...) method */

void ContactStorage::export_contacts() //to do: exporting
{
	cout << "This contact storage will be exported to the executable file path\n"
		<< "Press [enter] to continue | Press 0 to change the path \t\t| [esc] to main menu\n"
		<< "\nWarning: Previous exported contacts would be removed from the file\n";
	switch (_getch())
	{
	case '0':
	{
		cout << "Type the file path in the following form: C:/Users/User/Documents\n";
		string path;
		cin.ignore();
		getline(cin, path);
		path += "/Exported_contacts.txt";
		ofstream os{ path };
		if (!os.is_open())
			cout << "Error: Failed to find the path";
		else
		{
			choose_export_type(os);
			os.close();
		}
		break;
	}
	case 13:
	{
		ofstream os{ "Exported_contacts.txt"};
		if (!os.is_open())
		{
			cout << "Error: Failed to find the path";
		}
		else
		{
			choose_export_type(os);
			os.close();
		}
		break;
	}
	case 27:
		return;
		break;

	default:
		cout << "This function does not exist\n";
		break;
	}
}

/* find a contact by name, phone number */

void ContactStorage::find_contact()
{
	cout << "Find by: \t\t| [esc] to go back to main menu\n1. Name \n2. Phone number \n";
	cin.ignore();
	switch (_getch())
	{
	case '1':
	{
		cout << "Type the name to find\n";
		string r;
		getline(cin, r);
		for (const auto& elem : storage)
			if (r == elem.get_name())
				cout << elem << this->get_contact_group(elem) << endl;
		break;
	}

	case '2':
	{
		cout << "Type the phone number to find\n";
		string r;
		getline(cin, r);
		for (const auto& elem : storage)
			if (r == elem.get_phone_number())
				cout << elem << this->get_contact_group(elem) << endl;
		break;
	}

	case 27:
		return;
		break;

	default:
		cout << "This function does not exist\n";
		break;
	}
}

/* sort contacts by name, phone_number or group */

void ContactStorage::sort_contacts()
{
	cout << "Sort by: \t\t |[esc] to go back to main menu\n1. Name \n2. Phone number \n3. Group \n";
	switch (_getch())
	{
	case '1':
		sort(storage.begin(), storage.end(), [](const Contact& contact1, const Contact& contact2) { return contact1.get_name() < contact2.get_name(); });
		break;

	case '2':
		sort(storage.begin(), storage.end(), [](const Contact& contact1, const Contact& contact2) { return contact1.get_phone_number() < contact2.get_phone_number(); });
		break;

	case '3':
		sort(storage.begin(), storage.end(), [&](const Contact& contact1, const Contact& contact2) { return get_contact_group(contact1) < get_contact_group(contact2); });
		break;

	case 27:
		return;
		break;

	default:
		cout << "This function doesn not exist\n";
		break;
	}
}

/* get contact's group name; if contact is not in group return " " */

string ContactStorage::get_contact_group(const Contact& contact)
{
	for (int num = 0; num < groups.size(); num++)
	{
		for (int i = 0; i < groups[num].get_group_size(); i++)
			if (contact == groups[num].get_contact(i))
				return groups[num].get_name();
	}
	return " ";
}

/* delete certain group without deleting any contacts */

void ContactStorage::delete_group()
{
	cout << "Choose group you want to delete. Contacts will not be deleted\n";
	groups.erase(groups.begin() + get_existing_group_number());
	cout << "Deleted successfully\n";
}
