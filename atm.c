#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct date {
    int m;
    int d;
    int y;
};

struct Account {
    struct date dates;
    int accountNumber;
    int PIN;
    float balance;
};

struct Account account;

void createAccount();
void readAccount(int choice, int loggedInAccountNumber);
void depositOrWithdraw(int accountNumber, bool isDeposit);
void deleteAccount(int choice);
void updateBalance(int accountNumber, float newBalance, int m, int d, int y);

int main() {
    int userChoice;
    char accountNumberStr[10];
    int accountNumber, PIN;
    bool loggedIn = false;

    while (!loggedIn) {
        printf("Please log in\n");
        printf("Account Number: ");
        scanf("%d", &accountNumber);

        printf("PIN: ");
        scanf("%d", &PIN);

        FILE* file = fopen("account.dat", "r");
        int storedAccountNumber, storedPIN;
        bool accountFound = false;

        while (fscanf(file, "Date: %d/%d/%d | Account Number: %d | PIN: %d | Balance: %f\n", &account.dates.m, &account.dates.d, &account.dates.y, &storedAccountNumber, &storedPIN, &account.balance) == 6) {
            if (storedAccountNumber == accountNumber && storedPIN == PIN) {
                accountFound = true;
                break;
            }
        }

        fclose(file);

        if (accountFound) {
            printf("Login successful!\n");
            loggedIn = true;
        } else {
            printf("No record found. Please try again.\n");
        }
    }

    while (1) {
        printf("\nWelcome to PUP-On-Line Banking Systems\n");
        printf("1. Create Account\n2. Read Account\n3. Update Account\n4. Delete Account\n5. Exit\nEnter the number of your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("\n1. Account Number Only\n2. PIN Only\n3. Balance Only\n4. Date Only\n5. All - Account Number, PIN & Balance\n6. All Accounts in account.dat\nEnter your choice: ");
                scanf("%d", &userChoice);
                readAccount(userChoice, accountNumber);
                break;
            case 3:
                printf("\n1. Withdraw\n2. Deposit\nEnter your choice: ");
                scanf("%d", &userChoice);
                depositOrWithdraw(accountNumber, userChoice == 2);
                break;
            case 4:
                printf("\n1. Delete one record\n2. Delete all records in account.dat\nEnter your choice: ");
                scanf("%d", &userChoice);
                deleteAccount(userChoice);
                break;
            case 5:
                printf("\nThank you for using PUP-On-Line Banking Systems.\n");
                return 0;
        }
    }

    return 0;
}

void createAccount() {
    FILE* file = fopen("account.dat", "a"); 
    int accountNumber, PIN;
    float balance;
    char accountNumberStr[10], PINStr[10];

    printf("\nEnter new account number: ");
    scanf("%s", accountNumberStr);

    accountNumber = atoi(accountNumberStr);

    while (fscanf(file, "Date: %d/%d/%d | Account Number: %d | PIN: %d | Balance: %f\n", &account.dates.m, &account.dates.d, &account.dates.y, &account.accountNumber, &account.PIN, &account.balance) == 6) {
        if (account.accountNumber == accountNumber) {
            printf("\nInvalid account number. An account with the same account number already exists.\n");
            fclose(file);
            return;
        }
    }

    printf("Enter new PIN: ");
    scanf("%s", PINStr);

    PIN = atoi(PINStr);

    printf("Enter initial balance: ");
    scanf("%f", &balance);

    printf("Enter date (MM/DD/YYY): ");
    scanf("%d/%d/%d", &account.dates.m, &account.dates.d, &account.dates.y);

    fclose(file);

    file = fopen("account.dat", "a");

    fprintf(file, "Date: %02d/%02d/%d | Account Number: %05d | PIN: %04d | Balance: %.2f\n", account.dates.m, account.dates.d, account.dates.y, accountNumber, PIN, balance);
    printf("\nAccount added successfully.\n");

    fclose(file);
}

void readAccount(int choice, int loggedInAccountNumber) {
    struct Account currentAccount;
    FILE *file = fopen("account.dat", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "Date: %d/%d/%d | Account Number: %d | PIN: %d | Balance: %f\n", &currentAccount.dates.m, &currentAccount.dates.d, &currentAccount.dates.y, &currentAccount.accountNumber, &currentAccount.PIN, &currentAccount.balance) == 6) {
        if (choice == 6) {
            printf("Account Number: %d | PIN: %d | Balance: %.2f | Date: %02d/%02d/%d\n",
                   currentAccount.accountNumber, currentAccount.PIN, currentAccount.balance, currentAccount.dates.m, currentAccount.dates.d, currentAccount.dates.y);
        } else if (currentAccount.accountNumber == loggedInAccountNumber) {
            switch (choice) {
                case 1:
                    printf("Account Number: %d\n", currentAccount.accountNumber);
                    break;
                case 2:
                    printf("PIN: %d\n", currentAccount.PIN);
                    break;
                case 3:
                    printf("Balance: %.2f\n", currentAccount.balance);
                    break;
                case 4:
                    printf("Date: %02d/%02d/%d\n", currentAccount.dates.m, currentAccount.dates.d, currentAccount.dates.y);
                    break;
                case 5:
                    printf("Account Number: %d\n", currentAccount.accountNumber);
                    printf("PIN: %d\n", currentAccount.PIN);
                    printf("Balance: %.2f\n", currentAccount.balance);
                    printf("Date: %02d/%02d/%d\n", currentAccount.dates.m, currentAccount.dates.d, currentAccount.dates.y);
                    break;
            }
            fclose(file);
            return;
        }
    }

    fclose(file); 
}

void depositOrWithdraw(int accountNumber, bool isDeposit) {
    struct Account account;
    FILE* file = fopen("account.dat", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE* tempFile = fopen("tempFile.dat", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int found = 0;
    while (fscanf(file, "Date: %d/%d/%d | Account Number: %d | PIN: %d | Balance: %f\n", &account.dates.m, &account.dates.d, &account.dates.y, &account.accountNumber, &account.PIN, &account.balance) == 6) {
        if (account.accountNumber == accountNumber) {
            found = 1;
            float balance = account.balance;
            float amount;

            if (isDeposit) {
                printf("\nEnter amount to deposit: ");
                scanf("%f", &amount);
                balance += amount;
            } else {
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);

                if (amount > balance) {
                    printf("Insufficient balance. Transaction canceled.\n");
                    fclose(file);
                    fclose(tempFile);
                    remove("tempFile.dat");
                    return;
                }

                balance -= amount;
            }

            account.balance = balance;

            printf("Enter new date (MM/DD/YY): ");
            scanf("%d/%d/%d", &account.dates.m, &account.dates.d, &account.dates.y);
        }
        fprintf(tempFile, "Date: %02d/%02d/%d | Account Number: %05d | PIN: %04d | Balance: %.2f\n", account.dates.m, account.dates.d, account.dates.y, account.accountNumber, account.PIN, account.balance);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("\nAccount not found. No changes made.\n");
        remove("tempFile.dat");
        return;
    }

    remove("account.dat");
    rename("tempFile.dat", "account.dat");

    printf("\nBalance updated successfully.\n");
}

void deleteAccount(int choice) {
    if (choice == 2) {
        char userChoice;

        printf("Are you sure you want to delete all accounts in account.dat? Enter [Y] to DELETE and [C] to CANCEL: ");
        while (scanf(" %c", &userChoice) != 1 || (userChoice != 'Y' && userChoice != 'C')) {
            printf("\nInvalid input. Please enter only [Y] and [C]\n");
            printf("Are you sure you want to delete all accounts in account.dat? Enter [Y] to DELETE and [C] to CANCEL: ");
            while (getchar() != '\n');
        }

        if (userChoice == 'Y') {
            FILE *file = fopen("account.dat", "w");
            if (file == NULL) {
                printf("Error opening file!\n");
                return;
            }
            fclose(file);
            printf("\nAll accounts in account.dat have been deleted.\n");
        } else {
            printf("\nAccount deletion canceled.\n");
        }
    } 
    else {
        int accountNumber;
        char accountNumberStr[10];
        char userChoice;

        printf("Enter account number: ");
		scanf("%s", accountNumberStr);

        accountNumber = atoi(accountNumberStr); 

        FILE *file = fopen("account.dat", "r");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }

        FILE *tempFile = fopen("tempFile.dat", "w");
        if (tempFile == NULL) {
            printf("Error creating temporary file!\n");
            fclose(file);
            return;
        }

        int found = 0;
        struct Account account;
        while (fscanf(file, "Date: %d/%d/%d | Account Number: %d | PIN: %d | Balance: %f\n", &account.dates.m, &account.dates.d, &account.dates.y, &account.accountNumber, &account.PIN, &account.balance) == 6) {
            if (account.accountNumber == accountNumber) {
                found = 1;
            } else {
                fprintf(tempFile, "Date: %02d/%02d/%d | Account Number: %05d | PIN: %04d | Balance: %.2f\n", account.dates.m, account.dates.d, account.dates.y, account.accountNumber, account.PIN, account.balance);
            }
        }

        fclose(file);
        fclose(tempFile);

        if (!found) {
            printf("\nAccount number not found. No changes made.\n");
            remove("tempFile.dat");
            return;
        }

        printf("\nAccount Number %d has been found. Enter [Y] to DELETE and [C] to CANCEL: ", accountNumber);
        scanf(" %c", &userChoice);

        if (userChoice == 'Y') {
            remove("account.dat");
            rename("tempFile.dat", "account.dat");
            printf("\nAccount deleted successfully.\n");
        } else {
            remove("tempFile.dat");
            printf("\nAccount deletion canceled.\n");
        }
    }
}

void updateBalance(int accountNumber, float newBalance, int m, int d, int y) {
    FILE* file = fopen("account.dat", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE* tempFile = fopen("tempFile.dat", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int found = 0;
    struct Account account;
    while (fscanf(file, "Date: %d/%d/%d | Account Number: %d | PIN: %d | Balance: %f\n", &account.dates.m, &account.dates.d, &account.dates.y, &account.accountNumber, &account.PIN, &account.balance) == 6) {
        if (account.accountNumber == accountNumber) {
            found = 1;
            account.balance = newBalance;
            account.dates.m = m;
            account.dates.d = d;
            account.dates.y = y;
        }
        fprintf(tempFile, "Date: %02d/%02d/%d | Account Number: %05d | PIN: %04d | Balance: %.2f\n", account.dates.m, account.dates.d, account.dates.y, account.accountNumber, account.PIN, account.balance);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("\nAccount not found. No changes made.\n");
        remove("tempFile.dat");
        return;
    }

    remove("account.dat");
    rename("tempFile.dat", "account.dat");

    printf("Enter new date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &account.dates.m, &account.dates.d, &account.dates.y);

    account.dates.m = m;
    account.dates.d = d;
    account.dates.y = y;

    printf("\nBalance updated successfully.");
}
