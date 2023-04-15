#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100

struct BankAccount {
    char name[50];
    char accountNumber[20];
    double balance;
};

struct Bank {
    struct BankAccount customers[MAX_CUSTOMERS];
    int numCustomers;
};

void openAccount(struct Bank *bank) {
    if (bank->numCustomers >= MAX_CUSTOMERS) {
        printf("\n\t\t\tCannot open new account. Maximum limit reached.\n");
        return;
    }
    struct BankAccount customer;
    printf("\n\t\t\tEnter name: ");
    scanf("%s", customer.name);
    printf("\n\t\t\tEnter account number: ");
    scanf("%s", customer.accountNumber);
    printf("\n\t\t\tEnter opening balance: ");
    scanf("%lf", &customer.balance);
    bank->customers[bank->numCustomers] = customer;
    bank->numCustomers++;
    printf("\n\t\t\tAccount opened successfully!\n");
}

void displayAccounts(struct Bank bank) {
	int i;
    printf("\n\t\t\tName\tAccount Number\tBalance\n");
    for (i = 0; i < bank.numCustomers; i++) {
        printf("\n\t\t\t%s\t%s\t\t%.2lf\n", bank.customers[i].name, bank.customers[i].accountNumber, bank.customers[i].balance);
    }
}

void deposit(struct Bank *bank, char *accountNumber, double amount) {
	int i;
    for ( i = 0; i < bank->numCustomers; i++) {
        if (strcmp(bank->customers[i].accountNumber, accountNumber) == 0) {
            bank->customers[i].balance += amount;
            printf("\n\t\t\tDeposit of %.2lf successful!\n", amount);
            return;
        }
    }
    printf("\n\t\t\tAccount not found.\n");
}

void withdraw(struct Bank *bank, char *accountNumber, double amount) {
	int i;
    for (i = 0; i < bank->numCustomers; i++) {
        if (strcmp(bank->customers[i].accountNumber, accountNumber) == 0) {
            if (bank->customers[i].balance >= amount) {
                bank->customers[i].balance -= amount;
                printf("\n\t\t\tWithdrawal of %.2lf successful!\n", amount);
            } else {
                printf("\n\t\t\tInsufficient balance!\n");
            }
            return;
        }
    }
    printf("\n\t\t\tAccount not found.\n");
}

void closeAccount(struct Bank *bank, char *accountNumber) {
	int i,j;
    for ( i = 0; i < bank->numCustomers; i++) {
        if (strcmp(bank->customers[i].accountNumber, accountNumber) == 0) {
            for ( j = i; j < bank->numCustomers - 1; j++) {
                bank->customers[j] = bank->customers[j + 1];
            }
            bank->numCustomers--;
            printf("\n\t\t\tAccount closed successfully!\n");
            return;
        }
    }
    printf("\n\t\t\tAccount not found.\n");
}

int main() {
    struct Bank bank;
    bank.numCustomers = 0;
    int choice;
    char accountNumber[20];
    double amount;
    system("color 2");
    printf("\t\t\t\t\t\t\t\t\tThe game was developed by Oliver Nikolajevic");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    do {
        printf("\n\n\n\t\t\t 1. Open Account\n");
        printf("\n\t\t\t 2. Display Accounts\n");
        printf("\n\t\t\t 3. Deposit\n");
        printf("\n\t\t\t 4. Withdraw\n");
        printf("\n\t\t\t 5. Close Account\n");
        printf("\n\t\t\t 6. Exit\n");
        printf("\n\t\t\t Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                openAccount(&bank);
                break;
            case 2:
                displayAccounts(bank);
                break;
            case 3:
        printf("\n\t\t\tEnter account number: ");
                scanf("%s", accountNumber);
        printf("\n\t\t\tEnter amount to deposit: ");
                scanf("%lf", &amount);
        deposit(&bank, accountNumber, amount);
            break;
            case 4:
        printf("\n\t\t\tEnter account number: ");
                scanf("%s", accountNumber);
        printf("\n\t\t\tEnter amount to withdraw: ");
                scanf("%lf", &amount);
        withdraw(&bank, accountNumber, amount);
            break;
            case 5:
        printf("\n\t\t\tEnter account number: ");
                scanf("%s", accountNumber);
            closeAccount(&bank, accountNumber);
            break;
            case 6:
        printf("\n\t\t\tExiting program...\n");
            break;
            default:
        printf("\n\t\t\tInvalid choice. Please try again.\n");
        }
    } while (choice != 6);
return 0;
}
