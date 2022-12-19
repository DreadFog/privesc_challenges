#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
typedef struct {
    int account;
    char firstName[30];
    char lastName[30];
    float balance;
} account;

int main(int argc, char const *argv[])
{
    account db[5];
    for (int i = 0; i < 5; i++)
    {
        db[i].account = i;
        db[i].balance = 100.0;
    }
    strcpy(db[0].firstName, "John");
    strcpy(db[0].lastName, "Doe");
    strcpy(db[1].firstName, "Jane");
    strcpy(db[1].lastName, "Doe");
    strcpy(db[2].firstName, "John");
    strcpy(db[2].lastName, "Smith");
    strcpy(db[3].firstName, "Jane");
    strcpy(db[3].lastName, "Smith");
    strcpy(db[4].firstName, "Peter");
    strcpy(db[4].lastName, "Parker");
    if (argc != 2) {
        printf("Usage: %s password\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "str0ngp455w0rd!") != 0) {
        printf("Invalid password. Only the accountant can manage accounts\n");
        return 1;
    }
    // ask for an operation: withdraw, deposit, balance, transfer
    char operation[10];
    printf("Enter operation: \n");
    scanf("%s", operation);
    if (strcmp(operation, "withdraw") == 0) {
        // ask for account number
        int account;
        printf("Enter account number: \n");
        scanf("%d", &account);
        // ask for amount
        float amount;
        printf("Enter amount: \n");
        scanf("%f", &amount);
        // withdraw amount from account
        db[account].balance -= amount;
        printf("New balance: %f\n", db[account].balance);
    } else if (strcmp(operation, "deposit") == 0) {
        // ask for account number
        int account;
        printf("Enter account number: \n");
        scanf("%d", &account);
        // ask for amount
        float amount;
        printf("Enter amount: \n");
        scanf("%f", &amount);
        // deposit amount to account
        db[account].balance += amount;
        printf("New balance: %f\n", db[account].balance);
    } else if (strcmp(operation, "balance") == 0) {
        // ask for account number
        int account;
        printf("Enter account number: \n");
        scanf("%d", &account);
        // print balance of account
        printf("Balance: %f, %s, %s\n", db[account].balance, db[account].firstName, db[account].lastName);
    } else if (strcmp(operation, "transfer") == 0) {
        // ask for account number
        int account1;
        printf("Enter account number: \n");
        scanf("%d", &account1);
        // ask for amount
        float amount;
        printf("Enter amount: \n");
        scanf("%f", &amount);
        // ask for account number
        int account2;
        printf("Enter account number: \n");
        scanf("%d", &account2);
        // transfer amount from account1 to account2
        db[account1].balance -= amount;
        db[account2].balance += amount;
        printf("New balance: %f\n", db[account1].balance);
    } else if (strcmp(operation, "debug") == 0) {
        printf("Account\tFirst Name\tLast Name\tBalance\n");
        for (int i = 0; i < 5; i++)
        {
            printf("%d\t%s\t\t%s\t\t%f\n", db[i].account, db[i].firstName, db[i].lastName, db[i].balance);
        }
        // set root permissions
        setuid(0);
        printf("In debug mode, you can read the log files of the bank\n");
        printf("Their name follows the pattern 'transactions_day_<number>.log\n");
        printf("Enter the log file name to read: \n");
        char filename[100];
        scanf("%s", filename);
        // add /var/log/bank/ to the beginning of the filename
        char to_read[15] = "/var/log/bank/";
        strcat(to_read, filename);
        printf("Reading file %s\n", to_read);       
        // read the log file
        FILE *fp;
        char line[100];
        fp = fopen(to_read, "r");
        if (fp == NULL) {
            printf("Error opening file");
            return 1;
        }
        while (fgets(line, 100, fp) != NULL) {
            printf("%s", line);
        }
        fclose(fp);
    } else {
        printf("Invalid operation");
        printf("Valid operations: withdraw, deposit, balance, transfer");
        return 1;
    }
    return 0;
}
