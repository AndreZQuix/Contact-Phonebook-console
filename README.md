# Contact-Phonebook-console
A console application to keep and manage phonebook information: view, group and export contacts according to your requirements.

This application keeps records of phonebook contacts: their names, phone numbers. There is an opportunity to group contacts, delete, sort and change it's information. Set star function is also included. With ContactStorage class it is easy to make more different contact storages without mixing information.

Program functions:

1. Add contacts.
2. Show all contacts.
3. Show starred contacts: print favourite contacts.
4. Show contacts by group: print contacts from certain group.
5. Export contacts: print contacts in certain .txt file.
6. Search contact: find certain contact by it's name or phone number.
7. Change contact: change contact information.
8. Delete contact: delete contact and it's information from the storage.
9. Sort contacts: sort contact list by name, phone number or group.
10. Delete group: delete group without deleting contacts (implemented with unique pointers vector).

All entered user data are checked for correctness. Phone number correctness is checked with regular expressions.

Checked for memory leaks with Deleaker and Visual Leak Detector. Version with GUI is comming soon.


