#include <stdio.h>

int main ()
{
	int num_grades = 0;
	int sum = 0;
	int grades;

	printf ("enter a grade - negative to terminate\n");
	scanf ("%d", &grade);
	while(grade >= 0)
	{
		num_grades++;
		sum += grade;
		printf ("enter a grade - negative to terminate\n");
		scanf ("%d", &grade);
	}

	if (num_grades == 0)
		printf ("no grades\n");
	else
	{
		double ave = (double) sum / num_grades;
		printf ("average: %f", ave);
	}

	

	return 0;
}
