 // This File contains all the functions required like validate name, number, email, if the data is present in structure ect.
 // these functions are called in contact.c file

#include<stdio.h>
#include<string.h>
#include "contact.h"

// Function to validate user entered name
int validate_name (char *name_str){
    for (int i = 0; name_str[i]; i++) {
        if (!((name_str[i] >= 'a' && name_str[i] <= 'z') || (name_str[i] >= 'A' && name_str[i] <= 'Z') || name_str[i] == ' ' || name_str[i] == '.')) 
        {
            return 0;
        }
    }
    return 1;       
}

// Function to validate user entered phone number
int validate_phone (char *phone_str){
    int len = 0;
    for (int i = 0; phone_str[i]; i++) {
        if (!(phone_str[i] >= '0' && phone_str[i] <= '9')) {
            return 0;
        }
        len++;
    }
    // Length 
    if (len != 10) {
        return 0;
    }
    return 1;

}

// Function to check if the entered phone number is unique
int phone_unique(AddressBook *addressBook, char *phone) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to validate user entered email id
int validate_email (char *email_str){
    int len = strlen(email_str);
    char *position_of_AT = strchr(email_str, '@');

    if (position_of_AT == NULL || strcmp(email_str + len - 4, ".com") != 0 ||
        len < 7 || email_str[0] == '@' || email_str[0] == '.'||
        (email_str + len - 4) - (position_of_AT) < 2) {
        return 0;
    }

    for(int i = 0; email_str[i]; i++){
        if(!((email_str[i]>='a' && email_str[i]<='z') || (email_str[i]>='0' && email_str[i]<='9') || email_str[i]=='@' || email_str[i]=='.' || email_str[i]=='_')){
            return 0;
        }
    }
    return 1;
}

// Function to check if the entered email id is unique
int email_unique(AddressBook *addressBook, char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            return 0;
        }
    }
    return 1;
}

// Search by Name
// Function used to check whether the entered name is present and handle multiple names 
int  isNamePresent(AddressBook *addressBook, char *str) {
    int index[50], count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].name, str) != NULL) { // strcasestr to find the substring of half entered name
            index[count++] = i;
        }
    }

    if (count == 0) {
        printf("❌ No contact found with name '%s'\n", str);
        return -1;
    }

    if (count == 1) {
        return index[0]; // only one match
    }

    // multiple matches → ask user to choose
    int choice;
    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-25s %-20s %-30s\n",
            i + 1,
            addressBook->contacts[index[i]].name,
            addressBook->contacts[index[i]].phone,
            addressBook->contacts[index[i]].email);
    }
    printf("-------------------------------------------------------------------\n");
    printf("Enter serial number: ");
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= count) {
        return index[choice - 1]; // return actual index
    } else {
        printf("❌ Invalid choice\n");
        return -1;
    }
    
}

// Search by Phone number
// Function used to check whether the entered number is present
int isNumberPresent(AddressBook *addressBook, char *str) {
    int index[50], count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].phone, str) != NULL) {  
            index[count++] = i;
        }
    }

    if (count == 0) {
        printf("❌ No contact found with phone starting with '%s'\n", str);
        return -1;
    }

    if (count == 1) {
        return index[0]; // only one match
    }

    int choice;
    printf("⚠️  Multiple contacts found\n");

    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-25s %-20s %-30s\n",
            i + 1,
            addressBook->contacts[index[i]].name,
            addressBook->contacts[index[i]].phone,
            addressBook->contacts[index[i]].email);
    }
    printf("-------------------------------------------------------------------\n");
    printf("Enter serial number: ");
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= count) {
        return index[choice - 1]; // return actual index
    } else {
        printf("❌ Invalid choice\n");
        return -1;
    }
}


// Search by email (prefix, case-insensitive)
// Function used to check whether the entered number is present
int isEmailPresent(AddressBook *addressBook, char *str) {
    int index[50], count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].email, str) != NULL) {  
            index[count++] = i;
        }
    }

    if (count == 0) {
        printf("❌ No contact found with email starting with '%s'\n", str);
        return -1;
    }

    if (count == 1) {
        return index[0]; // only one match
    }

    int choice;
    printf("⚠️  Multiple contacts found\n");

    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-25s %-20s %-30s\n",
            i + 1,
            addressBook->contacts[index[i]].name,
            addressBook->contacts[index[i]].phone,
            addressBook->contacts[index[i]].email);
    }
    printf("-------------------------------------------------------------------\n");
    printf("Enter serial number: ");
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= count) {
        return index[choice - 1]; // return actual index
    } else {
        printf("❌ Invalid choice\n");
        return -1;
    }
}

// Function to ask user what to edit and edit that contents
void edit_contact (AddressBook *addressBook, int index) {
    Contact *c = &addressBook->contacts[index];
    int choice;
    while (1) 
    {
        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Go back to main menu\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        char newValue[50];
        int valid = 0;
        switch (choice) {
            case 1: {  // Edit name
                do {
                    printf("\nEnter new name: ");
                    scanf("%[^\n]", newValue);
                    getchar();
                    // validate
                    valid = validate_name(newValue);
                    if (!valid) {
                        printf("❌ Invalid name. Try again.\n");
                    }
                } while (!valid);
                strcpy(c->name, newValue);
                break;
            }
            case 2: { // Edit phone
                do {
                    printf("\nEnter new phone: ");
                    scanf("%s", newValue);
                    getchar();
                    valid = validate_phone(newValue);
                    if (valid == 0) {
                        printf("❌ Invalid phone. Try again.\n");
                    } else if (!phone_unique(addressBook, newValue)) {
                        printf("❌ Phone Number already exists. Try again.\n");
                        valid = 0;
                    }
                } while (valid != 1);
                strcpy(c->phone, newValue);
                break;
            }
            case 3: { // Edit email
                do {
                    printf("\nEnter new email: ");
                    scanf("%s", newValue);
                    getchar();
                    valid = validate_email(newValue);
                    if (valid == 0) {
                        printf("❌ Invalid email. Try again.\n");
                    } else if (!email_unique(addressBook, newValue)) {
                        printf("❌ Email ID already exists. Try again.\n");
                        valid = 0;
                    }
                } while (valid != 1);
                strcpy(c->email, newValue);
                break;
            }
            case 4: 
                printf("\n🔙 Going back to main menu...\n");
                return;

            default:
                printf("❌ Invalid choice. Please try again\n");
                continue;
        }
    }

    printf("\n✅ Contact updated successfully!\n");
    // Display updated

    printf("\n-------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-30s\n", "S.No", "Name", "Phone", "Email");

    printf("%-5d %-25s %-20s %-30s\n", 
        index + 1, addressBook->contacts[index].name,
        addressBook->contacts[index].phone,
        addressBook->contacts[index].email);
    printf("-------------------------------------------------------------------\n");

}