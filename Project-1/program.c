#include <stdio.h>

#define TRUE  1
#define FALSE 0
#define BOOLEAN int

double compute_pi(int n);
double compute_sqrt(double x);
int is_prime(int n);
void display_primes(int n);
void process_scores();
double compute_tax(int income, char* status, char state);

int main()
{

  char* message =
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

  int response;

  while (TRUE)
  {
    printf("%s", message);
    scanf("%d", &response);

    switch (response)
    {
    case 1:
      printf("Enter N terms of pi: \n");
      scanf("%d", &response);
      printf("Pi is: %f\n", compute_pi(response));
      break;

    case 2:
      printf("Enter a number to square root: \n");
      scanf("%d", &response);
      printf("The square root of %d is %f\n", response, compute_sqrt((double)response));
      break;

    case 3:
      printf("Enter a number to compute primes up to: \n");
      scanf("%d", &response);
      display_primes(response);
      break;

    case 4:
      process_scores();
      break;

    case 5:
      
      break;

    case 6:
      break;

    case 7:
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
  /* If the number is divisable by any number > 2 or < n return false */
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

// TODO implement me
void process_scores()
{

}

double compute_tax(int income, char* status, char state)
{

}
