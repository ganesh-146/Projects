#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "contact.h"

int validate_name (char *name_str);
int validate_phone (char *phone_str);
int phone_unique(AddressBook *addressBook, char *phone);
int validate_email (char *email_str);
int email_unique(AddressBook *addressBook, char *email);
int  isNamePresent(AddressBook *addressBook, char *str);
int isNumberPresent(AddressBook *addressBook, char *str);
int isEmailPresent(AddressBook *addressBook, char *str);
void edit_contact (AddressBook *addressBook, int index);

#endif