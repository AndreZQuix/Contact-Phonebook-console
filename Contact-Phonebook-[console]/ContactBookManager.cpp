#include "ContactStorage.h"

void menu(ContactStorage& Storage)
{
	cout << "Press the button to choose an option:\n";

	while (true)
	{
		cout << "\n1. Add contacts \n2. Show all contacts \n3. Show starred contacts \n4. Show by group"
			<< "\n5. Export contacts \n6. Search contact \n7. Change contact \n8. Delete contact \n9. Sort contacts \n0. Delete group \n[esc] Exit\n"
			<< "\nThere are " << Storage.get_storage_size() << " contacts in the phone book\n";

		switch (_getch())
		{
		case '1':
			system("cls");
			Storage.add_contact();
			break;

		case '2':
			system("cls");
			Storage.print_contacts(cout, SELECTION::ALL_CONTACTS);
			break;

		case '3':
			system("cls");
			Storage.print_contacts(cout, SELECTION::BY_STAR);
			break;

		case '4':
			system("cls");
			Storage.print_contacts(cout, SELECTION::BY_GROUP);
			break;

		case '5':
			system("cls");
			Storage.export_contacts();
			break;

		case '6':
			system("cls");
			Storage.find_contact();
			break;

		case '7':
			system("cls");
			Storage.change_contact();
			break;

		case '8':
			system("cls");
			Storage.delete_contact();
			break;

		case '9':
			system("cls");
			Storage.sort_contacts();
			break;

		case '0':
			system("cls");
			Storage.delete_group();
			break;

		case 27:
			return;
			break;

		default:
			cout << "This option does not exist\n";
			break;
		}
	}
}

int main()
{
	cout << "Welcome to phonebook\n"
		<< "--------------------------------------------\n";

	ContactStorage Storage;
	menu(Storage);

	cout << "\nGoodbye" << endl;
}
