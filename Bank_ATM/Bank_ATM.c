/*
 * Name: Ganesh P
 * Date: 07-07-25
 * Description: BANK ATM PROJECT
 * */
#include <stdio.h>

int main()
{
	int pin = 1234, entered_pin, choice;
	float  balance = 10000;
	
	//Read your pin validate
	printf("🏦 Welcome to SBI ATM💲\n");
	printf("Please enter your PIN (4-digit): ");
	scanf("%d", &entered_pin);

	if (entered_pin == pin)
	{
		//If pin is valid display the menu and select menu
		do
		{
			printf("\n===== ATM Menu =====\n");
			printf("1. Check Balance\n");
			printf("2. Deposit Money\n");
			printf("3. Withdraw Money\n");
			printf("4. Change PIN\n");
			printf("5. Exit\n");
			printf("Choose an option: ");
			scanf("%d", &choice);
			printf("\n");

			//Based on user choice perform the operation
			switch (choice)
			{
				case 1:
					//Logic for check the balance
					printf("🪙  Your current balance: ₹%0.2f\n", balance);
					continue;

				case 2:
					//Logic for Deposit the money
					float deposit;
					printf("💰 Enter amount to deposit: ₹");
					scanf("%f", &deposit);

					if (deposit > 0) {
						balance = balance + deposit;
						printf("✅ ₹%0.2f deposited successfully!\n", deposit);
					} else {
						printf("❗ Invalid input!\n");
						continue;
					}
					printf("\n");
					char answer1;
					printf("Do you want to check the balance? (Y/N):\n");
					scanf(" %c", &answer1);

					if (answer1 == 'Y' || answer1 == 'y'){
						printf("🪙  Your current balance: ₹%0.2f\n", balance);
					} else if (answer1 == 'N' || answer1 == 'n'){
						printf("Transaction completed. Thank You!🤝\n");
					} else {
						printf("❗ Invalid input!. Transaction completed!. Returning back to ATM Menu.\n");
					}
					continue;

				case 3:
					//Logic for withdraw the money
					float withdraw;
					printf("💸 Enter amount to withdraw: ₹");
					scanf("%f", &withdraw);

					if(withdraw > 0){
						if (withdraw <= balance){
							balance = balance - withdraw;
							printf("✅ ₹%0.2f withdrawn successfully!\n", withdraw);
						} else {
							printf("❌ Insufficient balance!\n");
							continue;
						}
					} else {
						printf("❗ Invalid input!\n");
						continue;
					}
					printf("\n");
					char answer2;
					printf("Do you want to check the balance? (Y/N):\n");
					scanf(" %c", &answer2);

					if( answer2 == 'Y' || answer2 == 'y'){
						printf("🪙  Your current balance: ₹%0.2f\n", balance);
					} else if (answer2 == 'N' || answer2 == 'n'){
						printf("Transaction completed!. Thank You!🤝\n");
					} else {
						printf("❗ Invalid input!. Transaction completed!. Returning to ATM Menu.\n");
					}
					continue; 

				case 4:
					//Logic for Change the PIN.
					int old_pin, new_pin;
					printf("🔑 Enter your Old PIN (4-digit): ");
					scanf("%d", &old_pin);
					printf("🔒 Enter New PIN (4-digit): ");
					scanf("%d", &new_pin);

					if (old_pin == pin)
					{
						int digit_count = 0, temp;
						temp = new_pin;

						while(temp != 0){
							temp = temp / 10;
							digit_count++;
						}
						if(digit_count == 4){
							pin = new_pin;
							printf("✅ INFO: PIN Updated Successfully....\n");
						}else{
							printf("❌ Error: PIN must be of exactly 4-digits\n");
							continue;
						}
					} else {
						printf("❌ INFO: Entered PIN is Invalid\n");
					}
					continue;
				case 5:
					//Exit from application
					printf("👋 Thank you for using SBI ATM. Have a nice day!!❤️ \n");
					break;
				default:
					//Apart from menu if user enters print error.
					printf("❗ Invalid choice. Please try again.\n");
			}
		} while (choice != 5);
	}
	else
	{
		printf("❌ Invalid PIN. Access Denied.\n");
	}
	return 0;
}
