#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// ===================This part contains functions to encrypt and decrypt files by calling external python scripts================

void encrypt(char filename[]){
    char enc[50];
    sprintf(enc,"python encryptor.py %s", filename);
    system(enc);
}
void decrypt(char filename[]){
    char dec[50];
    sprintf(dec,"python decryptor.py %s", filename);
    system(dec);
}

// ===================This part contains structure definition that will store any person's account info when they try to access their account================

struct Aaccount{
    unsigned long int AccountNo;
    char firstName[15], lastName[15];
    char address[50];
    char dob[11];
    char password[5];
    unsigned long int balance;
    unsigned long int transactionNum;
    long int transactionHistory[1000];
};

// ===================This part contains function to generate a random 6 digit account number================

long generateAccNum(){
    long accNum=0;
    int i;
    for(i=0;i<6;i++){
        accNum=accNum*10+(rand()%9);
    }
    if(accNum>=0){
        return accNum;
    }
    else{
        return (-accNum);
    }
}

// ================================================================================================================================================

int main(){
FILE *SecurityFile, *AccountFile, *AccountNumberList;
char securityCode[20], enteredCode[20];
char enteredPassCode[20];
char securityFile[30]={'s','e','c','u','r','i','t','y','.','t','x','t'}, c[2], accNum[7], AccountNumbers[15][1000];
int retVal=1, option, option1,  i;
long int amount, AccNum, NumberOfCustomers;
    


    typedef struct Aaccount Account;
    Account account;
    SecurityFile=fopen(securityFile,"r");
    retVal=fscanf(SecurityFile,"%c", &c);
    // ===================This part contains code to set-up the system for normal usage and set an administrator password================
    if(retVal==EOF){
        retVal=fscanf(SecurityFile,"%s", securityCode);
        printf("===========================================SETUP GUIDE=================================================\n\n\n");
        printf("............Please set up a password for your system (URGENT)..........\n\nPlease enter a strong security password:\n");
        scanf("%s", securityCode);
        fclose(SecurityFile);
        SecurityFile=fopen(securityFile,"w");
        fprintf(SecurityFile,"%s",securityCode);
        fclose(SecurityFile);
        printf("\nPlease restart the program to avail the banking services\n");
        AccountNumberList=fopen("AccountNumbers.txt", "w");
        fprintf(AccountNumberList,"0\n");
        fclose(AccountNumberList);
        encrypt("AccountNumbers.txt");
        encrypt(securityFile);
        system("pause");
        return 0;
    }
    // ===================This part is executed if the setup part has been already completed======================
    else{
        printf("Please enter the security code to access the system.....\n");
        scanf("%s",enteredCode);
        decrypt(securityFile);
        SecurityFile=fopen(securityFile,"r");
        fscanf(SecurityFile,"%s",securityCode);
        fclose(SecurityFile);
        encrypt(securityFile);
        if(strcmp(securityCode,enteredCode)==0){
            system("cls");
        }
        else{
            printf("Invalid entry....");
            system("pause");
            system("cls");
            return 1;
        }
        while(1){
            while(1){
                printf("Please select one of the following options : \n");
                printf("\n1. Log into your account.\n2. Create an account.\n3. Administrator services.\n\n");
                scanf("%d", &option);
                system("cls");
                if(option==1){
                    printf("Please enter your account number :\n");
                    scanf("%ld", &AccNum);
                    sprintf(accNum,"%ld.txt", AccNum);
                    AccountFile=fopen(accNum,"r");
                    if(AccountFile==NULL){
                        printf("Account doesn't exist.....\nPlease check the details and try again later....\n");
                        fclose(AccountFile);
                        system("pause");
                        system("cls");
                        break;
                    }
                    else{
                        fclose(AccountFile);
                        decrypt(accNum);
                        AccountFile=fopen(accNum,"r");
                        fscanf(AccountFile,"%ld\n%s %s\n%s\n%s\n%s\n%ld\n%ld\n",&account.AccountNo, account.firstName, account.lastName,account.address,account.dob,account.password,&account.balance,&account.transactionNum);
                        encrypt(accNum);
                        printf("\nHello %s \nPlease enter your secret password to continue: \n", account.firstName);
                        scanf("%s", enteredPassCode);
                        if(strcmp(enteredPassCode,account.password)!=0){
                            printf("Entered password doesn't match\nPlease try again\n");
                            fclose(AccountFile);
                            encrypt(accNum);
                            system("pause");
                            system("cls");
                            break;
                        }
                        else{
                            system("cls");
                        }
                        decrypt(accNum);
                        for(i=0;i<account.transactionNum;i++){
                             fscanf(AccountFile,"%ld\n",&account.transactionHistory[i]);
                        }
                        encrypt(accNum);
                        printf("Please select a service option:  \n1. Withdraw Money.\n2. Deposit Money\n3. Show account balance\n4. Show last 10 transactions.\n");
                        scanf("%d", &option1);
                        if(option1==1){
                            printf("Enter withdrawal amount :\n");
                            scanf("%ld", &amount);
                            if(amount<30000 && amount<account.balance){
                                account.balance=account.balance-amount;
                                account.transactionHistory[account.transactionNum]=-amount;
                                account.transactionNum++;
                                fclose(AccountFile);
                                AccountFile=fopen(accNum,"w");
                                fprintf(AccountFile,"%ld\n%s %s\n%s\n%s\n%s\n%ld\n%ld\n",account.AccountNo, account.firstName,account.lastName,account.address,account.dob,account.password,account.balance,account.transactionNum);
                                for(i=0;i<account.transactionNum;i++){
                                    fprintf(AccountFile,"%ld\n",account.transactionHistory[i]);
                                }
                                fclose(AccountFile);
                                encrypt(accNum);
                                printf("Please collect your cash\n\nHave a nice day");
                                printf("Would you like to display your account balance on the screen ?\ny/n\n");
                                scanf("%s", c);
                                if(c[0]=='y'){
                                    printf("Your account balance is = %ld\nThank you for using RBI services.\nHave a nice day\n", account.balance);
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                                else{
                                    printf("Thank you for using RBI services.\nHave a nice day\n");
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                                break;
                            }
                            else{
                                printf("Withdrawal amount cannot be dispatched\nPlease reduce the amount and try again\n");
                                fclose(AccountFile);
                                encrypt(accNum);
                                system("pause");
                                system("cls");
                                break;
                            }
                        }
                        if(option1==2){
                            printf("Enter deposit amount :\n");
                            scanf("%ld", &amount);
                            account.balance+=amount;
                            account.transactionHistory[account.transactionNum]=amount;
                            account.transactionNum++;
                            fclose(AccountFile);
                            AccountFile=fopen(accNum,"w");
                            fprintf(AccountFile,"%ld\n%s %s\n%s\n%s\n%s\n%ld\n%ld\n",account.AccountNo, account.firstName,account.lastName,account.address,account.dob,account.password,account.balance,account.transactionNum);
                            for(i=0;i<account.transactionNum;i++){
                                fprintf(AccountFile,"%ld\n",account.transactionHistory[i]);
                            }
                            fclose(AccountFile);
                            encrypt(accNum);
                            printf("Your amount has been deposited.\nWould you like to display your account balance on the screen ?\ny/n\n");
                            scanf("%s", c);
                            
                            if(c[0]=='y'){
                                printf("Your account balance is = %ld\nThank you for using RBI services.\nHave a nice day\n", account.balance);
                                system("pause");
                                system("cls");
                            }
                            else{
                                printf("Thank you for using RBI services.\nHave a nice day\n");
                                system("pause");
                                system("cls");
                            }
                            break;
                        }
                        if(option1==3){
                            printf("Your account balance is = %ld\nThank you for using RBI services.\nHave a nice day\n", account.balance);
                            fclose(AccountFile);
                            system("pause");
                            system("cls");
                            break;
                        }
                        if(option1==4){
                            printf("Your current account balance is %ld\n", account.balance);
                            printf("SHOWING THE LAST 10 TRANSACTIONS :\n");
                            if(account.transactionNum<=10){
                                for(i=(account.transactionNum-1);i>=0;i--){
                                    if(i==0){
                                        printf("Opening balance                 %ld\n",account.transactionHistory[i]);
                                    }
                                    else if(account.transactionHistory[i]<0){
                                        printf("Withdrawal                      %ld\n",-account.transactionHistory[i]);
                                    }
                                    else if(account.transactionHistory[i]>0){
                                        printf("Deposit                         %ld\n",account.transactionHistory[i]);
                                    }
                                }
                                fclose(AccountFile);
                                system("pause");
                                system("cls");
                                break;
                            }
                            if(account.transactionNum>10){
                                for(i=(account.transactionNum-1);i>=(account.transactionNum-10);i--){
                                    if(i==0){
                                        printf("Opening balance                 %ld\n",account.transactionHistory[i]);
                                    }
                                    else if(account.transactionHistory[i]<0){
                                        printf("Withdrawal                      %ld\n",-account.transactionHistory[i]);
                                    }
                                    else if(account.transactionHistory[i]>0){
                                        printf("Deposit                         %ld\n",account.transactionHistory[i]);
                                    }
                                }
                                fclose(AccountFile);
                                system("pause");
                                system("cls");
                                break;
                            }
                        }
                    }
                }
                else if(option==2){
                    printf("Generating an account number for you.......\n");
                    while(1){
                        AccNum=generateAccNum();
                        sprintf(accNum,"%ld.txt", AccNum);
                        AccountFile=fopen(accNum,"r");
                        retVal=fscanf(AccountFile,"%c", &c);
                        if(retVal==EOF){
                            printf("Your auto generated account number is : %ld\n\n", AccNum);
                            system("pause");
                            break;
                        }
                        else{
                            continue;
                        }
                    }
                    fclose(AccountFile);
                    AccountFile=fopen(accNum,"w");
                    printf("Please enter your name :\n");
                    scanf("%s %s", account.firstName, account.lastName);
                    printf("Please enter your address :\n");
                    scanf("%s", account.address);
                    printf("Please enter your date of birth (D.O.B.) : \n");
                    scanf("%s", account.dob);
                    printf("Please enter the amount that you want to deposit into your account (minimum amount is Rs. 1000) :\n");
                    scanf("%ld", &amount);
                    printf("Please enter your password :\n");
                    scanf("%s", account.password);
                    if(amount<1000){
                        printf("Please deposit an amount greater than 1000 Rs.\n\n");
                        fclose(AccountFile);
                        remove(accNum);
                        system("pause");
                        system("cls");
                        break;
                    }
                    else{
                        account.balance=amount;
                        account.transactionNum=1;
                        account.transactionHistory[0]=account.balance;
                        account.AccountNo=AccNum;
                        fprintf(AccountFile,"%ld\n%s %s\n%s\n%s\n%s\n%ld\n%ld\n%ld\n",account.AccountNo,account.firstName,account.lastName,account.address,account.dob,account.password,account.balance,account.transactionNum,account.transactionHistory[0]);
                        printf("Dear RBI customer, your account has been created.\nThank you for choosing our banking services.\n\n");
                        printf("Your current account balance now is : %ld\n\n\n", account.balance);
                        decrypt("AccountNumbers.txt");
                        AccountNumberList=fopen("AccountNumbers.txt", "r");
                        fscanf(AccountNumberList, "%ld\n", &NumberOfCustomers);
                        for(i=0;i<NumberOfCustomers;i++){
                            fscanf(AccountNumberList, "%s\n", AccountNumbers[i]);
                        }
                        fclose(AccountNumberList);
                        AccountNumberList=fopen("AccountNumbers.txt", "w");
                        fprintf(AccountNumberList,"%ld\n", NumberOfCustomers+1);
                        for(i=0;i<NumberOfCustomers;i++){
                            fprintf(AccountNumberList, "%s\n", AccountNumbers[i]);
                        }
                        fprintf(AccountNumberList, "%s\n", accNum);
                        fclose(AccountNumberList);
                        encrypt("AccountNumbers.txt");
                        fclose(AccountFile);
                        encrypt(accNum);
                        system("pause");
                        system("cls");
                    }
                }
                else if(option==3){
                    printf("Please enter the security code to continue further :\n");
                    scanf("%s", enteredCode);
                    decrypt(securityFile);
                    SecurityFile=fopen(securityFile,"r");
                    fscanf(SecurityFile,"%s",securityCode);
                    if(strcmp(securityCode,enteredCode)==0){
                        fclose(SecurityFile);
                        encrypt(securityFile);
                        system("cls");
                    }
                    else{
                        encrypt(securityFile);
                        printf("Invalid entry....\n");
                        system("pause");
                        system("cls");
                        break;
                    }
                    printf("Select an option from the following :\n1. Change the security password.\n2. Get all account balances.\n3. System Shutdown.\n");
                    scanf("%d",&option1);
                    system("cls");
                    if(option1==1){
                        printf("Please enter the new security code :\n");
                        scanf("%s",securityCode);
                        printf("Please confirm the new security code :\n");
                        scanf("%s",enteredCode);
                        if(strcmp(securityCode,enteredCode)==0){
                            SecurityFile=fopen(securityFile,"w");
                            fprintf(SecurityFile,"%s", enteredCode);
                            fclose(SecurityFile);
                            encrypt(securityFile);
                            system("cls");
                            break;
                        }
                        else{
                            printf("Entered passwords do not match.\n");
                            fclose(SecurityFile);
                            system("pause");
                            system("cls");
                            break;
                        }
                    }
                    else if(option1==2){
                        decrypt("AccountNumbers.txt");
                        AccountNumberList=fopen("AccountNumbers.txt","r");
                        fscanf(AccountNumberList,"%ld\n", &NumberOfCustomers);
                        for(i=0;i<NumberOfCustomers;i++){
                            fscanf(AccountNumberList,"%s\n", AccountNumbers[i]);
                        }
                        fclose(AccountNumberList);
                        printf("Displaying all the accounts with their current balances : \n\n");
                        printf("Account Number          Customer Name             Address          Date of Birth             Balance\n");
                        for(i=0;i<NumberOfCustomers;i++){
                            decrypt(AccountNumbers[i]);
                            AccountFile=fopen(AccountNumbers[i],"r");
                            fscanf(AccountFile,"%ld\n%s %s\n%s\n%s\n%s\n%ld\n%ld\n",&account.AccountNo, account.firstName, account.lastName,account.address,account.dob,account.password,&account.balance,&account.transactionNum);
                            printf("%ld                %15s%20s          %13s                %ld\n", account.AccountNo, account.firstName,account.address,account.dob,account.balance);
                            fclose(AccountFile);
                            encrypt(AccountNumbers[i]);
                        }
                        printf("\n\n");
                        encrypt("AccountNumbers.txt");
                        system("pause");
                        system("cls");
                    }
                    else if(option1==3){
                        system("cls");
                        system("pause");
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}
