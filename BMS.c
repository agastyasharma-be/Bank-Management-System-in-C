#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// structure for customers
struct Account
{
    char name[50];
    int age;
    int accno;
    float balance;
    long long phoneno;
    int pin;
};

// space for 100 customers alloted
struct Account customer[100];
int totalacc = 0;
int accountno = 1000;
int pin;

// function for create account

void loadaccounts()
{
    FILE *ptr;
    ptr = fopen("accounts.dat", "rb");
    if (ptr == NULL)
    {
        return;
    }
    fread(&totalacc,sizeof(int),1,ptr);
    fread(&accountno, sizeof(int), 1, ptr);
    fread(customer, sizeof(struct Account), totalacc, ptr);
    fclose(ptr);
    printf("Accounts loaded successfully!\n");
    return;

}

void createacc()
{
    if (totalacc >= 100)
    {
        printf("Cannot create more accounts.\n");
        return;
    }
    // details of customer
    getchar();
    printf("Enter your name: ");
    fgets(customer[totalacc].name, 50, stdin);
    printf("Enter your age: ");
    scanf("%d", &customer[totalacc].age);
    printf("Enter  initial deposit acc: ");
    scanf("%f", &customer[totalacc].balance);
    if(customer[totalacc].balance<=0){
        printf("INVALID AMOUNT\n");
        return;
    }
    printf("Enter your phone no: ");
    scanf("%lld", &customer[totalacc].phoneno);
    customer[totalacc].accno = accountno;
    printf("Enter pin for your account: ");
    scanf("%d", &customer[totalacc].pin);
    if(customer[totalacc].pin<1000 || customer[totalacc].pin>9999){
        printf("INVALID PIN\n");
        return;
    }
    printf("\nAccount created successfully!\n");
    printf("Your Account Number is: %d\n", customer[totalacc].accno);
    totalacc++;
    accountno++;
    printf("\n");
};

void depositamt()
{
    float deposit;
    int account;
    int accpin;
    printf("Enter your account no:");
    scanf("%d", &account);
    // account search
    for (int i = 0; i < totalacc; i++)
    {

        if (customer[i].accno == account)
        {
            printf("Enter pin: ");
            scanf("%d", &accpin);
            // pin verification
            if (customer[i].pin == accpin)
            {
                // deposit
                printf("CORRECT PIN!\n");
                printf("HOW MUCH DO YOU WANT TO DEPOSIT: ");
                scanf("%f", &deposit);
                if (deposit <= 0)
                {
                    printf("INVALID AMOUNT!\n");
                    return;
                }
                customer[i].balance += deposit;
                printf("NEW ACCOUNT BALANCE IS: %.2f\n", customer[i].balance);
                return;
            }
            else
            {
                printf("WRONG PIN\n");
                return;
            }
        }
    }
    printf("ACCOUNT NOT FOUND!\n");
}

void deductamt()
{
    float deduct;
    int account;
    int accpin;
    printf("Enter your account no:");
    scanf("%d", &account);
    // account search
    for (int i = 0; i < totalacc; i++)
    {

        if (customer[i].accno == account)
        {
            printf("Enter pin: ");
            scanf("%d", &accpin);
            // pin verification
            if (customer[i].pin == accpin)
            {
                // deduct
                printf("CORRECT PIN!\n");
                printf("HOW MUCH DO YOU WANT TO DEDUCT: ");
                scanf("%f", &deduct);
                if (deduct > customer[i].balance || deduct <= 0)
                {
                    printf("INVALID AMOUNT!\n");
                    return;
                }
                customer[i].balance -= deduct;
                printf("NEW ACCOUNT BALANCE IS: %.2f\n", customer[i].balance);
                return;
            }
            else
            {
                printf("WRONG PIN\n");
                return;
            }
        }
    }
    printf("ACCOUNT NOT FOUND!\n");
}

void getdetails()
{
    int account;
    int accpin;
    printf("Enter your account no:");
    scanf("%d", &account);
    for (int i = 0; i < totalacc; i++)
    {
        if (customer[i].accno == account)
        {
            printf("Enter pin: ");
            scanf("%d", &accpin);
            // pin verification
            if (customer[i].pin == accpin)
            {
                // details
                printf("\n========== CUSTOMER DETAILS ==========\n");
                printf("NAME      : %s\n", customer[i].name);
                printf("AGE       : %d\n", customer[i].age);
                printf("ACCOUNT   : %d\n", customer[i].accno);
                printf("BALANCE   : %.2f\n", customer[i].balance);
                printf("PHONE NO. : %lld\n", customer[i].phoneno);
                printf("======================================\n");
                return;
            }
            printf("WRONG PIN\n");
            return;
        }
    }
    printf("ACCOUNT NOT FOUND!\n");
}

void transfer()
{
    int account1;
    int account2;
    int accpin;
    int transferamt;
    printf("Enter your account no:");
    scanf("%d", &account1);
    for (int i = 0; i < totalacc; i++)
    {
        if (customer[i].accno == account1)
        {
            printf("Enter pin: ");
            scanf("%d", &accpin);
            // pin verification
            if (customer[i].pin == accpin)
            {
                printf("Enter the reciever's bank account no: ");
                scanf("%d", &account2);
                if (account1 == account2)
                {
                    printf("YOU CANNOT TRANSFER TO THE SAME ACCOUNT!\n");
                    return;
                }
                for (int j = 0; j < totalacc; j++)
                {
                    if (customer[j].accno == account2)
                    {
                        printf("Enter the amount you want to transfer");
                        scanf("%d", &transferamt);
                        if (transferamt <= 0)
                        {
                            printf("INVALID AMOUNT!\n");
                            return;
                        }
                        if (transferamt > customer[i].balance)
                        {
                            printf("INSUFFICIENT BALANCE!\n");
                            return;
                        }
                        customer[i].balance -= transferamt;
                        customer[j].balance += transferamt;
                        printf("TRANSACTION DONE SUCCESSFULLY\n");
                        return;
                    }
                }
                printf("RECEIVER ACCOUNT NOT FOUND!\n");
                return;
            }
            printf("WRONG PIN\n");
            return;
        }
    }
    printf("ACCOUNT NOT FOUND!\n");
    return;
}

void deleteacc()
{
    int account;
    int accpin;
    printf("Enter the account you want to delete: ");
    scanf("%d", &account);
    for (int i = 0; i < totalacc; i++)
    {
        if (customer[i].accno == account)
        {
            printf("Enter pin: ");
            scanf("%d", &accpin);
            // pin verification
            if (customer[i].pin == accpin)
            {
                for (int j = i; j < totalacc - 1; j++)
                {
                    customer[j] = customer[j + 1];
                }
                totalacc--;
                printf("Account deleted successfully\n");
                return;
            }
            printf("WRONG PIN!\n");
            return;
        }
    }
    printf("ACCOUNT NOT FOUND!\n");
}

void changepin()
{
    int account;
    int oldpin;
    int newpin;
    printf("Enter your account number: ");
    scanf("%d", &account);
    for (int i = 0; i < totalacc; i++)
    {
        if (customer[i].accno == account)
        {
            printf("Enter old pin: ");
            scanf("%d", &oldpin);
            // pin verification
            if (customer[i].pin == oldpin)
            {
                printf("Enter new pin: ");
                scanf("%d", &newpin);
                if (newpin < 1000 || newpin > 9999)
                {
                    printf("Pin must be 4 digits!\n");
                    return;
                }
                else if (newpin == oldpin)
                {
                    printf("New pin can't be same as old pin");
                    return;
                }
                customer[i].pin = newpin;
                printf("Pin changed successfully!\n");
                return;
            }
            printf("Wrong pin!\n");
            return;
        }
    }
    printf("Account not found\n");
}

void saveaccounts()
{
    FILE *ptr;
    ptr = fopen("accounts.dat", "wb");
    if (ptr == NULL)
    {
        printf("Error opening the file: \n");
        return;
    }
    fwrite(&totalacc, sizeof(int), 1, ptr);
    fwrite(&accountno, sizeof(int), 1, ptr);
    fwrite(customer, sizeof(struct Account), totalacc, ptr);
    fclose(ptr);
}

int main()
{
    loadaccounts();
    while (1)
    {
        int choice;
        printf("========== BANK MANAGEMENT SYSTEM ==========\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. View Details\n");
        printf("6. Delete Account\n");
        printf("7. Change PIN\n");
        printf("8. Exit\n");
        printf("===========================================\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createacc();
            break;
        case 2:
            depositamt();
            break;
        case 3:
            deductamt();
            break;
        case 4:
            transfer();
            break;
        case 5:
            getdetails();
            break;
        case 6:
            deleteacc();
            break;
        case 7:
            changepin();
            break;
        case 8:
            printf("Thank you for using our Bank Management System!\n");
            saveaccounts();
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
