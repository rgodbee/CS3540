/*
 * Richard Godbee
 * CS3540
 * Assg. 2
 * /
#ifndef _ACCOUNT_H
#define _ACCOUNT_H

typedef struct 
{
	char* owner;
	int account_number;
	float balance;
}account;

/***************************************
input: owner, initial balance, account number
output: pointer to a bank account
return NULL is any input is not valid
***************************************/
account* create_account(char* owner, int account_number, float balance);

/***************************************
precondition: a is not NULL - checked with assertion
return displays all attributes of the account - format not specified
***************************************/
void display_account(const account* a);

/***************************************
precondition: a is not NULL - checked with assertion
precondition: amount must be positive
postcondition: amount has been added to balance
returns false if amount of deposit is not positive - true otherwise
***************************************/
int deposit(account* a, float amount);

/***************************************
precondition: a is not NULL - checked with assertion
precondition: amount must be positive & cannot be larger than the balance
postcondition: amount has been subtracted from balance
returns false if amount of withdrawal is not valid - true otherwise
***************************************/
int withdraw(account* a, float amount);

/***************************************
postcondition: all memory allocated to the bank account has been deallocated
does nothing if input pointer is NULL
***************************************/
void delete_account(account* a);

#endif
