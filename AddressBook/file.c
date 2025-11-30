// This file contains function that is used to load the contacts at the start of program from contatcs.csv file to structure
// Also save all the contact details into a file before terminating

#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "w");
    if (fptr == NULL) {
        printf("❌ Error: Could not open file for saving.\n");
        return;
    }

    // Writing the data into contacts.csv
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("✅ %d contacts saved successfully.\n", addressBook->contactCount);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv", "r");
    if (fptr == NULL) {
        printf("⚠️ No contacts found. Starting fresh.\n");
        addressBook->contactCount = 0;
        return;
    }

    int i = 0;
    // Reading the data into the structure
    while (i < MAX_CONTACTS &&
           fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) == 3) {
        i++;
    }
    addressBook->contactCount = i;

    fclose(fptr);
    printf("\n✅ %d contacts loaded from file.\n", i);
}

