#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE  1
#define FALSE 0
#define BOOLEAN int

double compute_pi(int n);
double compute_sqrt(double x);
int is_prime(int n);
void display_primes(int n);
void process_scores();
double compute_tax(int income, char* status, char state);
/* int quadratic(double a, double b, double c, double *solution1, double *solution2); */
int factorial(int n);
/* void file_count(char *file, int *characters, int *lines); */


void prompt(char* message, char* input, void* ptr)
{
  printf(message);
  fflush(stdout);
  scanf(input, ptr);
}

int main()
{
  const char* message =
    "1-Computing pi\n\
2-Computing square root\n\
3-Displaying primes\n\
4-Processing grades\n\
5-Computing tax\n\
6-Solving quadratic\n\
7-Computing factorial\n\
8-Counting file\n\
9-Sorting file\n\
10-Student file\n\
11-quit\n";

  int response, income;
  char *status, response_str[] = "";
  char state;

  while (TRUE)
  {
    printf("%s", message);
    scanf("%d", &response);

    switch (response)
    {
    case 1:
      prompt("Enter N terms of pi: ", "%d", &response);
      printf("Pi is: %f\n", compute_pi(response));
      break;

    case 2:
      prompt("Enter a number to square root: ", "%d", &response);
      printf("The square root of %d is %f\n", response, compute_sqrt((double)response));
      break;

    case 3:
      prompt("Enter the number of primes you want: ", "%d", &response);
      display_primes(response);
      break;

    case 4:
      process_scores();
      break;

    case 5:
      printf("Computeing taxis.\n");

      prompt("Are you married? Y/N\n", "%s", response_str);
      
      if (response_str[0] == 'Y' || response_str[0] == 'y')
	status = "married";
      else
	status = "single";
	  
      prompt("Are you an instate resident? Y/N\n", "%s", response_str);
      
      if (response_str[0] == 'Y' || response_str[0] == 'y')
	state = 'i';
      else
	state = 'o';

      prompt("What is your income?\n", "%d", &income);

      printf("Your tax amount is: %f\n", compute_tax(income, status, state));
      break;

    case 6:
      /* int quadratic(double a, double b, double c, double *solution1, double *solution2); */
      break;

    case 7:
      prompt("What number would you like to find the factorial of?: ", "%d", &response);
      printf("The factorial of %d is %d\n", response, factorial(response));
      break;

    case 8:
      break;

    case 9:
      break;

    case 10:
      break;

    case 11:
      /* Exits the program */
      return 0;
      break;
    }
  }
}

/* Compute pi with 4(1 - 1/3 + 1/5 - 1/7 + 1/9...) */
double compute_pi(int n)
{
  double pi = 1.0;
  double term = 0.0;

  for (int i = 0; i < n; i++)
  {
    term = 1 / (3.0 + i * 2);

    if (i % 2)
      pi += term;
    else
      pi -= term;
  }

  return pi * 4;
}

double compute_sqrt(double x)
{
  double guess = 1;

  for (int i = 0; i < 10; i++)
    guess = 0.5 * (guess + x / guess);

  return guess;
}

int is_prime(int n)
{
  /* If the number is divisable by any number greater than 2 and less
   * than itself then return false */
  for (int i = 2; i < n; i++)
    if (!(n % i))
      return FALSE;

  return TRUE;
}

void display_primes(int n)
{
  printf("Primes are: ");

  for (int i = 1; i <= n; i++)
    if (is_prime(i))
      printf("%d ", i);

  printf("\n");
}

// TODO get the names working and clear the warnings
void process_scores()
{
  char name[] = "", *best_student, *worst_student;
  int
    avg = 0,
    grade = 0,
    best_grade = INT_MIN,
    worst_grade = INT_MAX,
    number_of_students = 0;
  
  printf("Enter student names and scores.\n\
E.g.\n\
> Jane 90\n");

    printf("Enter q to quit.\n");
    
  while (TRUE)
  {
    prompt("> ", "%s", name);
    printf("%s", name);
    
    /* Break out if the user enters q or Q */
    if (! strcmp(name, "q") || ! strcmp(name, "Q"));
      break;

    scanf("%d", &grade);

    if (grade > best_grade)
    {
      /* free((void*)best_student); */
      /* best_student = name; */
      best_grade = grade;
    }

    if (grade < worst_grade)
    {
      /* free((void*)worst_student); */
      /* worst_student = name; */
      worst_grade = grade;
    }

    avg += grade;

    number_of_students++;
  }

  printf("The avarage grade is: %f\n", (float)avg / number_of_students);
  printf("The best student %s has a grade of %d.\n", &best_student, best_grade);
  printf("The worst student %s has a grade of %d.\n", &worst_student, worst_grade);
}

double compute_tax(int income, char* status, char state)
{
  double rate = -1.0;
  int tax_increase = INT_MAX;

  if (! strcmp(status, "MARRIED") || ! strcmp(status, "married"))
  {
    rate = 10.0;
    tax_increase = 50000;
  }
  else if (! strcmp(status, "SINGLE") || ! strcmp(status, "single"))
  {
    rate = 20.0;
    tax_increase = 30000;
  }
  else
    return -1.0;

  if (income > tax_increase)
    rate += 5.0;
  else if (income < 0)
    return -1.0;
  
  if (state == 'O' || state == 'o')
    rate -= 3.0;
  else if (state == 'I' || state == 'i')
    // TODO WHY IS THIS OKAY????
    NULL;
  else
    return -1.0;

  return rate;
}

/* int quadratic(double a, double b, double c, double *solution1, double *solution2) */
/* { */
  
/* } */

int factorial(int n)
{
  if (n == 1)
    return 1;
  
  return n * factorial(n - 1);
}

/* void file_count(char *file, int *characters, int *lines) */
/* { */
  
/* } */
