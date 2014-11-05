#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define INITIAL_ARRAY_SIZE 10

int* get_grades (int* num_grades);

float calc_ave (int num_grades, int* grades);

void display_ave (int num_grades, float ave);

float calc_median (int num_grades, int* grades);

void display_median(int num_grades, float median);

float calc_std_dev(int num_grades, int* grades);

void display_std_dev(int num_grades, float std_dev);

int main ()
{
  int num_grades;
  int* grades = get_grades (&num_grades);
  float ave = calc_ave (num_grades, grades);
  display_ave (num_grades, ave);
  float median = calc_median(num_grades, grades);
  display_median(num_grades, median);
  float std_dev = calc_std_dev(num_grades, grades);
  display_std_dev(num_grades, std_dev);
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
      int i = 0;
      for (i = 0; i < size; i++)
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
  int i = 0;
  for (i = 0; i < num_grades; i++)
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

float calc_median (int num_grades, int* grades)
{
  assert (num_grades >= 0);
  assert (grades != NULL);
  float median;
  if ( num_grades % 2 == 0)   
   median = (grades[(int)(num_grades/2)] + grades[(int)(num_grades/2+1)])/2.0 ;                   
  else                                                    
   median = grades[(int)(num_grades/2)];  
  return median;
}

void display_median(int num_grades, float median)
{
  if (num_grades == 0)
    printf ("no grades entered\n");
  else
    printf ("median is %f\n", median);
}

float calc_std_dev(int num_grades, int* grades)
{
  assert (num_grades >= 0);
  assert (grades != NULL);
  float mean=0;
  float sum_deviation=0;
  int i;
    for(i=0; i<num_grades;++i)
    {
        mean+= grades[i];
    }
    mean=mean/num_grades;
    for(i=0; i<num_grades;++i)
    sum_deviation+=(grades[i]-mean)*(grades[i]-mean);
    return sqrt(sum_deviation/num_grades); 
}

void display_std_dev(int num_grades, float std_dev)
{
  if (num_grades == 0)
    printf ("no grades entered\n");
  else
    printf ("standard deviation is %f\n", std_dev);
}
