/* TODO:
   add comments to all of the methods
   look into spacing and readability
*/

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

void prompt(char *message, char *input, void *ptr)
{
  printf(message);
  fflush(stdout);
  scanf(input, ptr);
}

int main()
{
  const char *menu_text =
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

  int response, income, characters, lines;
  char state, *status, response_str[30] = "", response2_str[30] = "";
  double a, b, c, solution1, solution2;

  while (TRUE)
  {
    printf(menu_text);
    scanf("%d", &response);

    // TODO clean this up
    switch (response)
    {
    case 1:
      prompt("Enter N terms of pi: ", "%d", &response);
      printf("Pi is: %f\n", compute_pi(response));
      break;

    case 2:
      prompt("Enter a number to square root: ", "%d", &response);
      printf(
	"The square root of %d is %f\n",
	response,
	compute_sqrt((double)response));
      break;

    case 3:
      prompt("How many primes would you like? ", "%d", &response);
      display_primes(response);
      break;

    case 4:
      process_scores();
      break;

    case 5:
      // TODO take input from strings here
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
      // TODO handle the case where they dont enter the right information
      printf(
	"Your tax amount is: %f\n",
	compute_tax(income, status, state));
      break;

    case 6:
      // TODO enter all the parameters on one line
      prompt("Enter in a value for a: ", "%lf", &a);
      prompt("Enter in a value for b: ", "%lf", &b);
      prompt("Enter in a value for c: ", "%lf", &c);

      if (quadratic(a, b, c, &solution1, &solution2))
	printf("The solutions are %lf, %lf\n", solution1, solution2);
      else
	printf("The quadratic %lf, %lf, %lf has no solution.\n", a, b, c);
      break;

    case 7:
      prompt("What number would you to factorial? ", "%d", &response);
      printf("The factorial of %d is %d\n", response, factorial(response));
      break;

    case 8:
      prompt("Please enter a filename: ", "%s", &response_str);
      file_count(response_str, &characters, &lines);
      printf(
	"%s has %d characters and %d lines.\n",
	response_str,
	characters,
	lines);
      break;

    case 9:
      prompt("Please enter the name of the file to be sorted: ", "%s", response_str);
      prompt("Please enter the name of the output file: ", "%s", response2_str);

      file_sort(response_str, response2_str);
      break;

    case 10:
      prompt("Please enter a filename: ", "%s", &response_str);
      file_student(response_str);
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
  double pi = 0.0;
  double term = 0.0;

  for (int i = 0; i < n; i++)
  {
    term = 1 / (1.0 + i * 2);

    if (i % 2)
      pi -= term;
    else
      pi += term;
  }

  return 4 * pi;
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
  /* If n is divisable by any number greater than 2 and less
   * than itself then return false */
  for (int i = 2; i < n; i++)
    if (!(n % i))
      return FALSE;

  return TRUE;
}

void display_primes(int n)
{
  printf("Primes are: ");

  for (int i = 2; i <= n; i++)
    if (is_prime(i))
      printf("%d ", i);

  printf("\n");
}

void process_scores()
{
  char name[30], best_student[30], worst_student[30];
  int
    avg = 0,
    grade = 0,
    best_grade = INT_MIN,
    worst_grade = INT_MAX,
    number_of_students = 0;

  printf("Enter student names and scores.\n\
E.g.\n\
> Jane 90\n\
Enter q to quit.\n");

  // TODO: I think that I need to split a single string in two
  while (TRUE)
  {
    prompt("> ", "%s", name);

    /* break out if the user enters q or Q */
    if (strcmp(name, "q") == 0 || strcmp(name, "Q") == 0)
      break;

    scanf("%d", &grade);

    if (grade > best_grade)
    {
      sprintf(best_student, "%s", name);
      best_grade = grade;
    }

    if (grade < worst_grade)
    {
      sprintf(worst_student, "%s", name);
      worst_grade = grade;
    }

    avg += grade;

    number_of_students++;
  }

  printf("The avarage grade is: %f\n", (float)avg / number_of_students);
  printf("The best student %s has a grade of %d.\n", best_student, best_grade);
  printf("The worst student %s has a grade of %d.\n", worst_student, worst_grade);
}

double compute_tax(int income, char *status, char state)
{
  double rate = -1.0;
  int tax_increase = INT_MAX;

  // TODO see if entering the wring strings still produces an error
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

int quadratic(
  double a,
  double b,
  double c,
  double *solution1,
  double *solution2)
{
  double discriminant = (b * b) - (4 * a * c);

  *solution1 = 0;
  *solution2 = 0;

  if (discriminant < 0)
    return FALSE;

  // TODO: see why sin is not working here
  b -= b * 2;

  *solution1 = b + compute_sqrt(discriminant) / (2 * a);
  *solution2 = b - compute_sqrt(discriminant) / (2 * a);

  return TRUE;
}

int factorial(int n)
{
  if (n == 1)
    return 1;
  
  return n * factorial(n - 1);
}

void file_count(char *file, int *characters, int *lines)
{
  FILE *fp;
  char temp;
  int character_count = 0, line_count = 0;

  fp = fopen(file, "r");

  temp = getc(fp);

  while (temp != EOF)
  {
    character_count++;
    
    if (temp == '\n')
      line_count++;

    temp = getc(fp);
  }

  fclose(fp);

  *characters = character_count;
  *lines = line_count;
}

void file_sort(char *infile, char *outfile)
{
  FILE *fp;
  
  // current length is the number of item in the array
  int id, *ids, number_of_students, inc = 0, current_length = 0;
  char grade, *grades;
  double gpa, *gpas;

  fp = fopen(infile, "r");

  fscanf(fp, "%d", &number_of_students);

  // TODO swap the size of and number of students
  ids = (int *)malloc(sizeof (int) * number_of_students);
  grades = (char *)malloc(sizeof (char) * number_of_students);
  gpas = (double *)malloc(sizeof (double) * number_of_students);

  // TODO comment this up
  // Read in the students and insert them in accending order
  for (int i = 0; i < number_of_students; i++)
  {
    fscanf(fp, "%d %c%lf", &id, &grade, &gpa);

    inc = current_length;
    
    // Move all the records with an ID greater than the current ID downwards
    while (inc > 0 && ids[inc - 1] > id)
    {
      ids[inc] = ids[inc - 1];
      grades[inc] = grades[inc - 1];
      gpas[inc] = gpas[inc - 1];
      inc--;
    }
    
    ids[inc] = id;
    grades[inc] = grade;
    gpas[inc] = gpa;
    
    current_length++;
  }

  // Close the reading file
  fclose(fp);

  // Open the outfile for writing
  fp = fopen(outfile, "w");

  // Write the data to the file
  for (int i = 0; i < number_of_students; i++)
    fprintf(fp, "%d %c %lf\n", ids[i], grades[i], gpas[i]);

  fclose(fp);

  free(ids);
  free(grades);
  free(gpas);
}

struct student {
  char name[30];
  int age;
  double gpa;
};

void file_student(char *infile)
{
  FILE *fp;
  int number_of_students;
  int inc = 0, current_length = 0;
  double avg_gpa = 0;
  struct student *students, student;

  fp = fopen(infile, "r");

  fscanf(fp, "%d", &number_of_students);

  students = (struct student *)malloc(number_of_students * sizeof (struct student));

  // TODO also document this up
  for (int i = 0; i < number_of_students; i++)
  {
    fscanf(fp, "%s%d%lf", student.name, &student.age, &student.gpa);

    inc = current_length;

    while (inc > 0 && strcmp(students[inc - 1].name, student.name) > 0)
    {
      students[inc] = students[inc - 1];
      inc--;
    }

    students[inc] = student;

    current_length++;
  }
  
  // TODO print the avarage gpa of all students
  for (int i = 0; i < number_of_students; i++)
    avg_gpa += students[i].gpa;

  printf("The avarage gpa is %lf\n", avg_gpa / number_of_students);

  // TODO print the names of all the students whoes GPAs are >= 2.0
  printf("The following students have a gpa > 2.0:\n");
  for (int i = 0; i < number_of_students; i++)
    if (students[i].gpa >= 2.0)
      printf("%s\n", students[i].name);

  // TODO print all the student information in acending order by names
  printf("The following is a list of all the student information:\n");
  for (int i = 0; i < number_of_students; i++)
    printf("%s %d %lf\n", students[i].name, students[i].age, students[i].gpa);

  free(students);
  fclose(fp);
}
