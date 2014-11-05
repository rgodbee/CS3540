/*
 * Richard Godbee
 * CS3540
 * Assg. 2
 * /
#include "bank_account.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>


int main()
{
	//good info
	account* a1 = create_account("Bob", 1, 50.0);
	display_account(a1);
	deposit(a1, 20.0);
	withdraw(a1, 12.0);
	display_account(a1);
	//bad input for deposit and withdraw
	deposit(a1, -500.0);
	withdraw(a1, 500.0);
	display_account(a1);
	delete_account(a1);
	return 0;
}
