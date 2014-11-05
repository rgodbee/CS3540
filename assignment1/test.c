#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define INITIAL_ARRAY_SIZE 10

int* get_grades (int* num_grades);

float calc_ave (int num_grades, int* grades);

void display_ave (int num_grades, float ave);

int main ()
{
  int num_grades;
  int* grades = get_grades (&num_grades);
  float ave = calc_ave (num_grades, grades);
  display_ave (num_grades, ave);
  return 0;
}

int* get_grades (int* num_grades)
{
  assert (num_grades != NULL);
  *num_grades = 0;
  int size = INITIAL_ARRAY_SIZE;
  int grade;
  int* grades = malloc (size * sizeof (int));
  printf ("enter a grade - negative to terminate ");
  scanf ("%d", &grade);
  while (grade >= 0)
  {
    if (*num_grades == size)
    {
      int* temp = malloc (2 * size * sizeof (int));
      for (int i = 0; i < size; i++)
	temp[i] = grades[i];
      free (grades);
      grades = temp;
    }
    grades[*num_grades] = grade;
    (*num_grades)++;
    printf ("enter a grade - negative to terminate ");
    scanf ("%d", &grade);
  }
  assert (grades != NULL);
  assert (*num_grades >= 0);
  return grades;
}

float calc_ave (int num_grades, int* grades)
{
  assert (num_grades >= 0);
  assert (grades != NULL);
  int sum = 0;
  for (int i = 0; i < num_grades; i++)
    sum += grades[i];
  float ave = 0;
  if (num_grades > 0)
    ave = (float)sum / num_grades;
  return ave;
}

void display_ave (int num_grades, float ave)
{
  if (num_grades == 0)
    printf ("no grades entered\n");
  else
    printf ("average is %f\n", ave);
}
