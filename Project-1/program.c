/* 
   Gregory Mann 
   Fall 2017
   COSC 341 
   Project 1
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* A few macros for readabillity. */
#define TRUE  1
#define FALSE 0
#define NOP NULL

/* See the implementations for more info. */
double compute_pi(int n);
double compute_sqrt(double x);
int is_prime(int n);
void display_primes(int n);
void process_scores();
double compute_tax(int income, char *status, char state);
int quadratic(
  double a,
  double b,
  double c,
  double *solution1,
  double *solution2);
int factorial(int n);
void file_count(char *file, int *characters, int *lines);
void file_sort(char *infile, char *outfile);
void file_student(char *infile);

/* 
   Prompt is a helper function. I found myself typing it's contents
   often. It prints out the message string then reads in the type
   specified by the input and stores it in ptr.

   message: The message to be printed to the screen.
   input: A format string that dectates what type is read into ptr.
   ptr: A reference to the variable that that will accept the value 
   read by the format string.
*/
void prompt(char *message, char *input, void *ptr)
{
  printf(message);
  fflush(stdout);
  scanf(input, ptr);
}

/* 
   The main function.
*/
int main()
{
  char *menu_text =
    "1-computing pi\n\
2-computing square root\n\
3-displaying primes\n\
4-processing grades\n\
5-computing tax\n\
6-solving quadratic\n\
7-computing factorial\n\
8-counting file\n\
9-sorting file\n\
10-student file\n\
11-quit\n";

  /*
    These are the variouse inputs and outputs that the menu uses to
    call functions.
  */
  int response, income, characters, lines;
  char state, response_str[30] = "", response2_str[30] = "";
  double a, b, c, solution, solution1, solution2;

  /* This is the main menu for the program. Entering 11 will exit. */
  while (TRUE)
  {
    prompt(menu_text, "%d", &response);

    switch (response)
    {
      
//------------------------------------------------------------------------------
      
    case 1:
      prompt("\nEnter N terms of pi: ", "%d", &response);
      printf("Pi is: %f\n\n", compute_pi(response));
      break;
      
//------------------------------------------------------------------------------
      
    case 2:
      prompt("\nEnter a number to square root: ", "%d", &response);
      printf(
	"The square root of %d is %f\n\n",
	response,
	compute_sqrt((double)response));
      break;
      
//------------------------------------------------------------------------------      

    case 3:
      prompt(
	"\nWhat number would you like to find primes up to? ",
	"%d",
	&response);
      display_primes(response);
      printf("\n");
      break;

//------------------------------------------------------------------------------      
      
    case 4:
      printf("\n");
      process_scores();
      printf("\n");
      break;
      
//------------------------------------------------------------------------------
      
    case 5:
      printf("\nComputeing taxis.\n");
      prompt("Enter you status:(married, single)\n", "%s", response_str);

      prompt("\nWhat is your residency status: (i, o)\n", " %c", &state);

      prompt("\nWhat is your income?\n", "%d", &income);

      solution = compute_tax(income, response_str, state);

      if (solution == -1)
	printf("Invalid entry\n\n");
      else
	printf("Your tax amount is: %.2f%%\n\n", solution);
      break;

//------------------------------------------------------------------------------
      
    case 6:
      printf("\nEnter a, b, and c of the quadratic function:\n\
e.g. \n\
> 1 3 -4\n\
> ");

      fflush(stdout);

      scanf("%lf%lf%lf", &a, &b, &c);
      
      if (quadratic(a, b, c, &solution1, &solution2))
	printf("The solutions are %lf, %lf\n\n", solution1, solution2);
      else
	printf("The quadratic %lf, %lf, %lf has no solution.\n\n", a, b, c);
      break;

//------------------------------------------------------------------------------
      
    case 7:
      prompt("\nWhat number would you to factorial? ", "%d", &response);
      printf("The factorial of %d is %d\n\n", response, factorial(response));
      break;

//------------------------------------------------------------------------------      

    case 8:
      printf("\nFile count\n");
      prompt("Please enter a filename: ", "%s", &response_str);
      file_count(response_str, &characters, &lines);
      printf(
	"%s has %d characters and %d lines.\n\n",
	response_str,
	characters,
	lines);
      break;

//------------------------------------------------------------------------------      

    case 9:
      printf("\nFile sort\n");
      prompt("Please enter the input file name: ", "%s", response_str);
      prompt("Please enter the output file name: ", "%s", response2_str);
      file_sort(response_str, response2_str);
      break;

//------------------------------------------------------------------------------      

    case 10:
      printf("\nStudent File\n");
      prompt("Please enter a filename: ", "%s", &response_str);
      file_student(response_str);
      break;

//------------------------------------------------------------------------------      

    case 11:
      /* Exits the program */
      return 0;
      break;

//------------------------------------------------------------------------------      
    }
  }
}

/* 
   Computes pi with the formula 4(1 - 1/3 + 1/5 - 1/7 + 1/9...) up to
   the nth term.

   n: Number of terms to compute up to when calculating pi.
   return: Aproximation of pi.
*/
double compute_pi(int n)
{
  double pi = 0.0;
  double term = 0.0;

  for (int i = 0; i < n; i++)
  {
    /* Compute value of the term. */
    term = 1 / (1.0 + i * 2);

    /* Alternate between adding and subtracting the term by using i % 2 */
    if (i % 2)
      pi -= term;
    else
      pi += term;
  }

  return 4 * pi;
}

/* 
   Computes the square root of the input x.
   
   x: The number that will be square rooted.
   return: The square root of x.
*/
double compute_sqrt(double x)
{
  double guess = 1;

  for (int i = 0; i < 10; i++)
    guess = 0.5 * (guess + x / guess);

  return guess;
}

/* 
   Determines if the input n is prime or not.
   Returns 1 if the input is prime and 0 if it's not.

   n: The input that's being checked to see if it's a prime number.
   reutrn: The return value is 1 if the n is prime and 0 if it's not.
*/
int is_prime(int n)
{
  /* 
     If n is divisible by any number greater than 2 and less than
     itself then return false. 

     Yes I know this is really really slow.
  */
  for (int i = 2; i < n; i++)
    if (!(n % i))
      return FALSE;

  return TRUE;
}

/* 
   Displays all the prime numbers up to and including n.

   n: The max prime number that you would like to display.
*/
void display_primes(int n)
{
  printf("Primes are: ");

  /*
    For every number between 2 and n check to see if it's prime. If
    it is print it out.
  */
  for (int i = 2; i <= n; i++)
    if (is_prime(i))
      printf("%d ", i);

  printf("\n");
}

/* 
   This function asks the user to input a list of student score pairs.
   It then displays the avarage score, best score, best scoring
   student, worst score, and the worst scoring student.
*/
void process_scores()
{
  char line[50], *name, *str_score, best_student[30], worst_student[30];
  int
    avg = 0,
    score = 0,
    best_score = INT_MIN,
    worst_score = INT_MAX,
    number_of_students = 0;

  printf("Enter student names and scores.\n\
E.g.\n\
> Jane 90\n\
Enter q to quit.\n");

  /* 
     Clear the input buffer.

     NOTE: fflush does not clear stdin.
  */
  fgets(line, 50, stdin);
  
  while (TRUE)
  {
    printf("> ");

    /* Read in the line. */
    fgets(line, 50, stdin);

    /* Find the space seperating the name and score. */
    str_score = strchr(line, ' ');

    /* 
       If the line contains no space and the input is "q" or "Q" then
       break the loop.

       This will segfault if the only thing on the line is a name that
       does not start with q. However I think that you want us to
       "split" the string to demonstrate string mutability instead of
       using two consecutive scanf calls.
    */
    if (str_score == NULL)
      if (strncmp(line, "Q", 1) == 0 || strncmp(line, "q", 1) == 0)
	break;

    /* The name should be the first thing on the line. */
    name = line;

    /* 
       Replace the space with NULL because it will be end of the name
       and the start of the score.
    */
    *str_score = '\0';
    
    /* 
       Now increment the pointer so it's past NULL terminator so it's
       now pointing to the score.
    */
    str_score++;

    /* Parse the string for the score. */
    sscanf(str_score, "%d", &score);
    
    /* 
       If the current score is the best one set the best name and the
       best score.
    */
    if (score > best_score)
    {
      strcpy(best_student, name);
      best_score = score;
    }

    /* 
       If the current score is the worst one set the worst name and
       the worst score.
    */
    if (score < worst_score)
    {
      strcpy(worst_student, name);
      worst_score = score;
    }

    avg += score;

    number_of_students++;
  }

  printf("\nThe avarage score is: %f\n", (float)avg / number_of_students);
  printf("%s has the best score, %d.\n", best_student, best_score);
  printf("%s has the worst score, %d.\n", worst_student, worst_score);
}

/* 
   This function computes some imaginary tax rules and returns the
   percentage that your going to be taxed.

   income: The amount that you make in a year.
   *status: Marital status "married" or "single".
   state: State residency 'i' for in state or 'o' for out of state.
*/
double compute_tax(int income, char *status, char state)
{
  double rate = -1.0;
  int tax_increase = INT_MAX;

  /* 
     Set the initial tax amount and set the value for the next tax
     bracket based on marital status.
  */
  if (strcmp(status, "MARRIED") == 0 || strcmp(status, "married") == 0)
  {
    rate = 10.0;
    tax_increase = 50000;
  }
  else if (strcmp(status, "SINGLE") == 0 || strcmp(status, "single") == 0)
  {
    rate = 20.0;
    tax_increase = 30000;
  }
  else
    return -1.0;

  /* 
     Increase the tax amount if your income is enough to put you in
     the next tax bracket.
  */
  if (income > tax_increase)
    rate += 5.0;
  else if (income < 0)
    return -1.0;
  
  /* 
     Reduce the tax amount if your out of state.
  */
  if (state == 'O' || state == 'o')
    rate -= 3.0;
  else if (state == 'I' || state == 'i')
    NOP; /* NO OPERATION */
  else
    return -1.0;

  return rate;
}

/* 
   Solves a quadratic problem using the quadratic formula. It returns
   0 if their are no solutions, and 1 if their are solutions. If their
   are solutions they are stored in the pointers solution1 and
   solution2. 
   
   a, b, c: The coefficients of your quadratic equation.
   solution1, solution2: If the quadratic has real solutions these 
   will contain them if their is no solution they will both
   contain 0.0.
   result: It's 1 if their are real solutions and 0 otherwise.
*/
int quadratic(
  double a,
  double b,
  double c,
  double *solution1,
  double *solution2)
{
  double discriminant = (b * b) - (4 * a * c);

  *solution1 = 0.0;
  *solution2 = 0.0;

  /* If the discriminant is < 0 then there are no solutions. */
  if (discriminant < 0)
    return FALSE;

  /* Turn b into -b. */
  b -= b * 2;

  *solution1 = (b + compute_sqrt(discriminant)) / (2.0 * a);
  *solution2 = (b - compute_sqrt(discriminant)) / (2.0 * a);

  return TRUE;
}

/* 
   Returns the factorial of the number n.

   n: The number to be (!) e.g. n!
   return: The result of the factorial n!
*/
int factorial(int n)
{
  if (n == 1)
    return 1;
  
  return n * factorial(n - 1);
}

/* 
   Counts the number of character and lines in a file.

   file: The input file to be counted.
   characters: A pointer to the variable that will contain the number of 
   characters in the file.
   lines: A pointer to the variable that will contain the number of lines
   in the file.
*/
void file_count(char *file, int *characters, int *lines)
{
  FILE *fp;
  char temp;
  
  *characters = 0;
  *lines = 0;

  fp = fopen(file, "r");

  /*
    Get the first character of the file to make sure that the initial
    value of temp is not EOF.
  */
  temp = getc(fp);

  while (temp != EOF)
  {
    (*characters)++;

    /* Just count the number of newlines to get the line count. */
    if (temp == '\n')
      (*lines)++;

    temp = getc(fp);
  }

  fclose(fp);  
}

/*
  Reads in a file with the following format: 
  An entry count at the top.
  Lines that each have an ID GRADE GPA.
  e.g.
  2
  54321 A 4.0
  12345 C 3.0

  The function then sorts the file by ID and stores it in the output
  file in a similar format (without the entry count at the top).

  infile: The input file (format described above).
  outfile: The file the output goes to (format described above).
*/
void file_sort(char *infile, char *outfile)
{
  FILE *fp;
  int
    current_id,
    *ids,
    inc = 0,
    number_of_students,
    number_of_records = 0;
  char current_grade, *grades;
  double current_gpa, *gpas;

  fp = fopen(infile, "r");

  /* Read in the number of students. */
  fscanf(fp, "%d", &number_of_students);

  /* Allocate memory for the arrays. */
  ids = (int *)malloc(number_of_students * sizeof (int));
  grades = (char *)malloc(number_of_students * sizeof (char));
  gpas = (double *)malloc(number_of_students * sizeof (double));

  /* Read in the students inserting them in accending order. */
  for (int i = 0; i < number_of_students; i++)
  {
    fscanf(fp, "%d %c%lf", &current_id, &current_grade, &current_gpa);
    inc = number_of_records;
    
    /* 
       Move all the "records" with an ID greater than the current ID
       downwards. When this loop ends the value of inc is the position
       where the current "record" will be inserted.
    */
    while (inc > 0 && ids[inc - 1] > current_id)
    {
      ids[inc] = ids[inc - 1];
      grades[inc] = grades[inc - 1];
      gpas[inc] = gpas[inc - 1];
      inc--;
    }

    /* Insert the current record. */
    ids[inc] = current_id;
    grades[inc] = current_grade;
    gpas[inc] = current_gpa;
    
    number_of_records++;
  }

  fclose(fp);

  fp = fopen(outfile, "w");

  /* 
     Write all the data to the outfile with the following format in
     acending order by ID: 	
     ID GRADE GPA
     ID GRADE GPA
     ID GRADE GPA
     ...
  */
  for (int i = 0; i < number_of_students; i++)
    fprintf(fp, "%d %c %lf\n", ids[i], grades[i], gpas[i]);

  fclose(fp);

  free(ids);
  free(grades);
  free(gpas);
}

/*
  A structure representing a student.
*/
struct student
{
  char name[30];
  int age;
  double gpa;
};

/*
  Reads in a file with the following format: 
  An entry count at the top.
  Lines that each have an NAME AGE GPA.
  e.g.
  2
  Jane 18 4.0
  John 20 3.8

  This function prints out the avarage gpa, the students who have a
  GPA >= 2.0, then all the student information.

  infile: The input file (format described above).
*/
void file_student(char *infile)
{
  FILE *fp;
  int number_of_students, inc = 0, number_of_records = 0;
  double avg = 0;
  struct student *students, student;

  fp = fopen(infile, "r");

  /* Read in the number of students. */  
  fscanf(fp, "%d", &number_of_students);

  students =
    (struct student *)malloc(number_of_students * sizeof (struct student));

  /* Read in the students inserting them in accending order. */
  for (int i = 0; i < number_of_students; i++)
  {
    fscanf(fp, "%s%d%lf", student.name, &student.age, &student.gpa);

    inc = number_of_records;

    /* 
       Move all the records with an ID greater than the current ID
       downwards. When this loop ends the value of inc is the position
       where the current record will be inserted.
    */
    while (inc > 0 && strcmp(students[inc - 1].name, student.name) > 0)
    {
      students[inc] = students[inc - 1];
      inc--;
    }

    students[inc] = student;

    number_of_records++;
  }
  
  fclose(fp);
  
  /* Print the average of the students GPAs. */
  for (int i = 0; i < number_of_students; i++)
    avg += students[i].gpa;

  printf("The avarage gpa is %lf\n", avg / number_of_students);

  /* Print the name of all the students who have a GPA >= 2.0. */
  printf("The following students have a gpa >= 2.0:\n");
  
  for (int i = 0; i < number_of_students; i++)
    if (students[i].gpa >= 2.0)
      printf("%s\n", students[i].name);

  /* Print all the student information in acending order by names */
  printf("The following is a list of all the student information:\n");
  
  for (int i = 0; i < number_of_students; i++)
    printf(
      "%s %d %lf\n",
      students[i].name,
      students[i].age,
      students[i].gpa);

  free(students);
}
