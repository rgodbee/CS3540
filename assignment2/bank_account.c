/*
 * Richard Godbee
 * CS3540
 * Assg. 2
 */
#include "bank_account.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
// used student.c for check method
int is_valid_name (char* n)
{
  return n != NULL && strlen (n) > 0;
}

account* create_account(char* owner, int account_number, float balance)
{
	account* a = NULL;
	if (is_valid_name(owner) && account_number > 0 && balance >= 0.0)
	{
		a = malloc (sizeof(account));
		a -> owner = malloc ((strlen (owner) + 1)* sizeof(char));
		strcpy(a -> owner, owner);
		a -> account_number = account_number;
		a -> balance = balance;
	}
	return a;
}

void display_account(const account* a)
{
	assert(a != NULL);
	printf("%s\n%d\n%f\n", a -> owner, a -> account_number, a -> balance);
}

int deposit(account* a, float amount)
{
	assert(a != NULL);
	if(amount >= 0.0)
	{
		a -> balance += amount;
		return 1;
	}else
		return 0;
}

int withdraw(account* a, float amount)
{
	assert(a != NULL);
	if(amount <= a -> balance)
	{
		a -> balance -= amount;
		return 1;
	}else
		return 0;
}

void delete_account(account* a)
{
	assert(a != NULL);
	free(a -> owner);
	free(a);
}
