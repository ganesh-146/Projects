/****************************************** PROJECT 1 **************************************
Name: Ganesh P
Project Name: Address Book
Date: 15-08-25

Description: 
The Address Book Management System is a C-based console application designed to efficiently store, manage, and retrieve contact information. 
It provides an easy-to-use interface for performing all essential operations typically found in a mobile phone contact list.

Features: 
1. Create contacts
2. Search contacts
3. Edit contacts
4. Delete contacts

*********************************************************************************************/


#include <stdio.h>
#include "contact.h" // Contains structure definition
#include "file.h" // Contains functions to load and save contacts

int main() 
{
    int choice, sortChoice;
    AddressBook addressBook; // Declaring AddressBook structure
    addressBook.contactCount = 0; // Initialling setting contact count to 0

    loadContactsFromFile(&addressBook); // Loading the contacts saved from file to structure

    // Asking user to select features of Address book and perform task based on the given choice
    printf("\n------------------------- Address Book --------------------------------\n");
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts and Exit\n");		
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                int sortChoice; // Based on which sorting should the contact display
                while (1) {
                    printf("\nSelect the sort criteria:\n");
                    printf("1. Name\n");
                    printf("2. Phone number\n");
                    printf("3. Email ID\n");
                    printf("\nEnter your choice: ");
                    scanf ("%d",&sortChoice);
                    getchar();

                    if (sortChoice==1 || sortChoice==2 || sortChoice==3)
                    {
                        listContacts(&addressBook, sortChoice);
                        break;
                    } else {
                        printf("❌ Invalid choice, Please try again\n");
                        continue;
                    }
                    
                }
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook); // Saving the contacts present in structure to a csv file
                break;
            default:
                printf("❌ Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
