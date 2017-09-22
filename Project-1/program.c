#include <stdio.h>

#define TRUE  1
#define FALSE 0
#define BOOLEAN int

double compute_pi(int n);

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

  while(1)
  {
    printf("%s", message);
    scanf("%d", &response);
      
    int pi_terms;
      
    switch (response)
    {
    case 1:
      printf("Enter N terms of pi: \n");
      scanf("%d", &pi_terms);
      printf("Pi is: %f\n", compute_pi(pi_terms));
      break;

    case 2:
      break;

    case 3:
      break;

    case 4:
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
  BOOLEAN add = FALSE;

  for (int i = 0; i < n; i++)
  {
    term = 1 / (3.0 + i * 2);

    if (add)
    {
      pi += term;
      add = FALSE;
    }
    else
    {
      pi -= term;
      add = TRUE;
    }
  }
  
  return pi * 4;
}
