#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "functions.h"

// Based on the selected criteria the list of contacts are displayed using listContacts function
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if (addressBook->contactCount == 0) {
        printf("⚠️  Address book is empty.\n");
        return;
    }

    // Temporary copy of contacts
    Contact temp[100];  // assuming max contacts = 100
    for (int i = 0; i < addressBook->contactCount; i++) {
        temp[i] = addressBook->contacts[i];
    }

    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = i + 1; j < addressBook->contactCount; j++) {
            int cmp = 0;
            if (sortCriteria == 1)  // sort by name
                cmp = strcmp(temp[i].name, temp[j].name);
            else if (sortCriteria == 2)  // sort by phone
                cmp = strcmp(temp[i].phone, temp[j].phone);
            else if (sortCriteria == 3)  // sort by email
                cmp = strcmp(temp[i].email, temp[j].email);

            if (cmp > 0) {
                Contact swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }
    // Display after swapping
    printf("\nContact List (Sorted by %s):\n", (sortCriteria == 1 ? "Name" : (sortCriteria == 2 ? "Phone" : "Email")));
    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-5d %-25s %-20s %-30s\n", 
               i + 1, temp[i].name, temp[i].phone, temp[i].email);
    }
    printf("--------------------------------------------------------------------\n");
}

// function to create new contacts and validate
void createContact(AddressBook *addressBook)
{

    char name_str[50], phone_str[11], email_str[30];
    int valid;

    //------------------------------------- Name --------------------------------------------------
    do
    {
        printf("\nEnter the name: ");
        scanf("%[^\n]", name_str); 
        getchar();
 
        valid = validate_name(name_str);
        if (!valid) {
            printf("❌ Invalid Name. Please try again.\n");
        }
    } while(!valid);

    printf("✅ Valid Name\n");

    // ------------------------------------ Phone number -------------------------------------------
    do 
    {
        printf("\nEnter 10 digit phone number: ");
        scanf("%s", phone_str);
        getchar();

        valid = validate_phone(phone_str);
        if(!valid){
            printf("❌ Invalid Phone Number. Please try again.\n");
        } else if (!phone_unique(addressBook, phone_str)) {
            printf("❌ Phone Number already exists. Try again.\n");
            valid = 0;
        }
    } while (!valid);

    printf("✅ Valid Phone number\n");

    // ---------------------------------------- Email ID -----------------------------------------
    do 
    {
        printf("\nEnter email ID: ");
        scanf("%s", email_str);
        getchar();
        valid = validate_email(email_str);
        if(!valid) {
            printf("❌ Invalid Email ID. Please try again.\n");
        } else if (!email_unique(addressBook, email_str)) {
            printf("❌ Email ID already exists. Try again.\n");
            valid = 0;
        }
    } while (!valid);

    printf("✅ Valid Email ID\n");

    strcpy(addressBook->contacts[addressBook->contactCount].name , name_str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone , phone_str);
    strcpy(addressBook->contacts[addressBook->contactCount].email , email_str);

    addressBook->contactCount++;
    
    printf("✅ The Contact has been created Successfully...\n");
}

// Function to search for conatcts based on name, number and email
void searchContact(AddressBook *addressBook) 
{

    if (addressBook->contactCount == 0) {
        printf("⚠️  Address book is empty.\n");
        return;
    }

    int option;
    char str[100];
    int index = -1;

    while (1) {
        printf("\nSearch Contact By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Go back to main menu\n");
        printf("\nEnter choice: ");
        scanf("%d", &option);
        getchar(); 

        if (option == 1) {
            printf("\nEnter name: ");
            scanf("%[^\n]",str);
            getchar();
            index = isNamePresent(addressBook, str);
        } 
        else if (option == 2) {
            printf("\nEnter phone number: ");
            scanf("%s",str);
            getchar();
            index = isNumberPresent(addressBook, str);
        } 
        else if (option == 3) {
            printf("\nEnter email: ");
            scanf("%s",str);
            getchar();
            index = isEmailPresent(addressBook, str);
        } 
        else if (option == 4) {
            printf("\n🔙 Going back to main menu...\n");
            return;
        }
        else {
            printf("❌ Invalid option. Please choose again.\n");
            continue; // restart loop
        }
        
        break; // break out of loop only if user selected a valid option
    }

    if (index != -1) { // Valid index
        printf("\n-------------------------------------------------------------------\n");
        printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

        printf("%-5d %-25s %-20s %-30s\n", 
            index + 1, addressBook->contacts[index].name,
            addressBook->contacts[index].phone,
            addressBook->contacts[index].email);
        printf("-------------------------------------------------------------------\n");
        
    }
}

// Function to search for contact and edit its contents
void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) {
        printf("⚠️  Address book is empty.\n");
        return;
    }

    int choice, valid, index;
    char str[100];

    while (1) {
        printf("\nBased on what you want to search\n");
        printf("1. Name\n");
        printf("2. Phone number\n");
        printf("3. Email ID\n");
        printf("4. Go back to main menu\n");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        getchar();
    
        switch (choice) {
            case 1: // Name
                printf("\nEnter the name: ");
                scanf("%[^\n]",str);
                getchar();

                valid = validate_name(str);
                if (!valid) {
                    printf("❌ Invalid Name. Please try again.\n");
                    continue;
                }

                index = isNamePresent(addressBook, str);
                if (index != -1) {
                    printf("\n-------------------------------------------------------------------\n");
                    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

                    printf("%-5d %-25s %-20s %-30s\n", 
                        index + 1, addressBook->contacts[index].name,
                        addressBook->contacts[index].phone,
                        addressBook->contacts[index].email);
                    printf("-------------------------------------------------------------------\n");

                    edit_contact(addressBook, index); // Calling edit function to edit contact
                }
                break;
            
            case 2: // Phone
                printf("\nEnter 10 digit phone number: ");
                scanf("%s", str);
                getchar();

                // validate Phone number (without len for strcasestr)
                for (int i = 0; str[i]; i++) {
                    if (!(str[i] >= '0' && str[i] <= '9')) {
                        printf("❌ Invalid Phone Number. Please try again.\n");
                        continue;
                    }
                }

                index = isNumberPresent(addressBook, str);
                if (index != -1) {
                    printf("\n-------------------------------------------------------------------\n");
                    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

                    printf("%-5d %-25s %-20s %-30s\n", 
                        index + 1, addressBook->contacts[index].name,
                        addressBook->contacts[index].phone,
                        addressBook->contacts[index].email);
                    printf("-------------------------------------------------------------------\n");

                    edit_contact(addressBook, index); // Calling edit function to edit contact
                }
                break;
            
            case 3: // Email
                printf("\nEnter email ID: ");
                scanf("%s", str);
                getchar();

                index = isEmailPresent(addressBook, str);
                if (index != -1) {
                    printf("\n-------------------------------------------------------------------\n");
                    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

                    printf("%-5d %-25s %-20s %-30s\n", 
                        index + 1, addressBook->contacts[index].name,
                        addressBook->contacts[index].phone,
                        addressBook->contacts[index].email);
                    printf("-------------------------------------------------------------------\n");

                    edit_contact(addressBook, index); // Calling edit function to edit contact
                }
                break;
                
            case 4:
                printf("🔙 Going back to main menu\n");
                return;
            
            default:
                printf("❌ Invalid choice. Please try again\n");
                continue;   
        }
        break;
    }
}

// Function to search for contacts and delete it from the structure
void deleteContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("\n❌ No contacts available to delete.\n");
        return;
    }

    int option;
    char str[100];
    int index = -1;

    while (1) {
        printf("\nSearch Contact By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Go back to main menu\n");
        printf("\nEnter choice: ");
        scanf("%d", &option);
        getchar(); 

        if (option == 1) {
            printf("\nEnter name: ");
            scanf("%[^\n]",str);
            getchar();
            index = isNamePresent(addressBook, str);
        } 
        else if (option == 2) {
            printf("\nEnter phone number: ");
            scanf("%s",str);
            getchar();
            index = isNumberPresent(addressBook, str);
        } 
        else if (option == 3) {
            printf("\nEnter email: ");
            scanf("%s",str);
            getchar();
            index = isEmailPresent(addressBook, str);
        } 
        else if (option == 4) {
            printf("\n🔙 Going back to main menu...\n");
            return;
        }
        else {
            printf("❌ Invalid option. Please choose again.\n");
            continue; // restart loop
        }
        
        break; // break out of loop only if user selected a valid option
    }
    
    // Confirm delete
    printf("\n⚠️  Are you sure you want to delete this contact?\n");
    printf("-------------------------------------------------------------------\n");
        printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

        printf("%-5d %-25s %-20s %-30s\n", 
            index + 1, addressBook->contacts[index].name,
            addressBook->contacts[index].phone,
            addressBook->contacts[index].email);
        printf("-------------------------------------------------------------------\n");
    printf("Type 'y' to confirm: ");

    char confirm;
    scanf("%c", &confirm);
    getchar();

    if (confirm != 'y' && confirm != 'Y') {
        printf("❌ Delete cancelled.\n");
        return;
    }

    // Shift contacts left
    for (int i = index; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("✅ Contact deleted successfully.\n");

    // Display
    printf("\nContact List:\n");
    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-5d %-25s %-20s %-30s\n",
            i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------------------------\n");
}

