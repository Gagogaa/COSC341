#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char *String;
typedef int bool;
#define TRUE 1
#define FALSE 1

/* List of Tokens:
   MAIN, WHILE, READ, WRITE, IF, ELSE, IDENTIFIER, LEFT_BRACKET,
   RIGHT_BRACKET, LEFT_PAREN, RIGHT_PAREN, INT_LITERAL,
   SEMICOLON, SCANOFF, MINUS_OP, PLUS_OP, MULT_OP, DIV_OP, GT_OP, LT_OP,
   EQU_OP, GTEQU_OP, LTEQU_OP, ASSIGN_OP */

/* I found this macro idea here: http://www.drdobbs.com/cpp/the-x-macro/228700289 */

/* TODO: explain the macros in depth. */
/* Create the list of tokens. Apply is a macro thats applied to each of the tokens. */
#define TOKENS\
  apply(MAIN)\
  apply(WHILE)\
  apply(READ)\
  apply(WRITE)\
  apply(IF)\
  apply(ELSE)\
  apply(IDENTIFIER)\
  apply(LEFT_BRACKET)\
  apply(RIGHT_BRACKET)\
  apply(LEFT_PAREN)\
  apply(RIGHT_PAREN)\
  apply(INT_LITERAL)\
  apply(SEMICOLON)\
  apply(SCANOFF)\
  apply(MINUS_OP)\
  apply(PLUS_OP)\
  apply(MULT_OP)\
  apply(DIV_OP)\
  apply(GT_OP)\
  apply(LT_OP)\
  apply(EQU_OP)\
  apply(GTEQU_OP)\
  apply(LTEQU_OP)\
  apply(NOTEQU_OP)\
  apply(ASSIGN_OP)\
  apply(COMMA)

/* Create the enum of Tokens. */
#define apply(a) a,
  typedef enum { TOKENS } token;
#undef apply

/* Create an array of strings matching the tokens for pretty printing. */
#define apply(a) #a,
static String TokenStrings[] = { TOKENS };
#undef apply

typedef struct
{
  FILE *fp;
  token next_tok;
  char token_buffer[100];
  String error_msg[100];
  int line_number;
  bool error;
} CONTEXT;

void scan_file(CONTEXT *cont);
void parse_file(CONTEXT *cont);

/* Functions for scanner. */
token scanner(CONTEXT *cont);
token check_reserved(CONTEXT *cont);
void clear_buffer(CONTEXT *cont);
void buffer_char(CONTEXT *cont, char character);
void lexical_error(CONTEXT *cont);

/* Functions for Parser. */
void parser(CONTEXT *cont);
void match(token tok, CONTEXT *cont);
void program(CONTEXT *cont);
void statment_list(CONTEXT *cont);
void statment(CONTEXT *cont);
void assignment_stmt(CONTEXT *cont);
void read_statment(CONTEXT *cont);
void write_statment(CONTEXT *cont);
void while_statment(CONTEXT *cont);
void if_statment(CONTEXT *cont);
void boolean_expression(CONTEXT *cont);
void relatinal_operator(CONTEXT *cont);
void operand(CONTEXT *cont);
void int_literal(CONTEXT *cont);
void expression(CONTEXT *cont);
void term(CONTEXT *cont);
void factor(CONTEXT *cont);
void syntax_error(token expected, CONTEXT *cont);

/*
  bool CheckToUpperCase(String str)
  {
  while (*str != NULL)
  if (isUpper(*str))
  return FALSE;
  else
  *str = toupper(*str);
  return TRUE;
  }
*/

/*
  TODO: maybe write a toLower / toUpper function for strings so I can do
  the macro thing with keywords too.
*/
token check_reserved(CONTEXT *cont)
{
  /* Check for one of the keywords. */
  if (strcmp("while", cont->token_buffer) == 0) return WHILE;
  if (strcmp("if",    cont->token_buffer) == 0) return IF;
  if (strcmp("else",  cont->token_buffer) == 0) return ELSE;
  if (strcmp("read",  cont->token_buffer) == 0) return READ;
  if (strcmp("write", cont->token_buffer) == 0) return WRITE;
  if (strcmp("main",  cont->token_buffer) == 0) return MAIN;

  return IDENTIFIER;
}

void clear_buffer(CONTEXT *cont)
{
  cont->token_buffer[0] = '\0';
}

void buffer_char(CONTEXT *cont, char character)
{
  char *ptr = strchr(cont->token_buffer, '\0');
  *ptr = character;
  *(ptr+1) = '\0';
}

void lexical_error(CONTEXT *cont)
{
  printf("lexical error on line %d\n", cont->line_number);
}

token scanner(CONTEXT *cont)
{

  /* /\* TODO: Think about moveing this to the main. *\/ */
  /* if (cont->fp == NULL) */
  /* { */
  /*   cont->error = TRUE; */

  /*   /\* TODO: change the content of this string. Or move it to the lexical_error function. *\/ */
  /*   strcpy(*cont->error_msg, "File Not Found\n"); */
  /*   return SCANOFF; */
  /* } */

  char character;

  while (TRUE)
  {
    character = getc(cont->fp);

    clear_buffer(cont);

    if (isalpha(character))
    {
      do
      {
	buffer_char(cont, character);
	character = getc(cont->fp);
      }
      while (isalnum(character));

      ungetc(character, cont->fp);
      return check_reserved(cont);
    }
    /* Check for int literals. */
    else if (isdigit(character))
    {
      do
      {
	buffer_char(cont, character);
	character = getc(cont->fp);
      }
      while (isdigit(character));

      ungetc(character, cont->fp);
      return INT_LITERAL;
    }

    switch (character)
    {
      /* Check for the end of file. */
    case EOF: return SCANOFF;

      /* Check for parens. */
    case '(': return LEFT_PAREN;
    case ')': return RIGHT_PAREN;

      /* Check for left brackets. */
    case '{': return LEFT_BRACKET;
    case '}': return RIGHT_BRACKET;

      /* Check for semicolon. */
    case ';': return SEMICOLON;

      /* Check for the comma. */
    case ',': return COMMA;

      /* Check for operators. */
    case '+': return PLUS_OP;
    case '-': return MINUS_OP;
    case '*': return MULT_OP;

      /* Check for comment or division operator. */
    case '/':
      character = getc(cont->fp);
      if (character == '/')
      {
	do
	  character = getc(cont->fp);
	while (character != '\n' && character != EOF);
      }
      else
      {
	ungetc(character, cont->fp);
	return DIV_OP;
      }
      break;

      /* Check for assignment operator. */
    case ':':
      character = getc(cont->fp);
      if (character == '=')
	return ASSIGN_OP;

      /*
	TODO: make a testfile with these conditions.
	e.g. ":6" won't throw an error or ":<" so maybe
	this should throw an error.

	These should be lexical errors.
      */

      /* Put the character back because ":" by itself should throw an error. */
      character = ':';
      /* ungetc(character, cont->fp); */
      break;

      /* Check for relatinal operators. */
    case '<':
      character = getc(cont->fp);
      if (character == '=')
	return LTEQU_OP;

      ungetc(character, cont->fp);
      return LT_OP;
      break;

    case '>':
      character = getc(cont->fp);
      if (character == '=')
	return GTEQU_OP;

      ungetc(character, cont->fp);
      return GT_OP;
      break;

    case '=':
      character = getc(cont->fp);

      if (character == '=')
	return EQU_OP;

      /* Put the character back because "=" by itself should throw an error. */
      character = '=';
      /* ungetc(character, cont->fp); */
      break;

    case '!':
      character = getc(cont->fp);

      if (character == '=')
	return NOTEQU_OP;

      /* Put the character back because "!" by itself should throw an error. */
      character = '!';
      /* ungetc(character, cont->fp); */
      break;
    }

    /* Check for an identifier or keyword. */
    if (isspace(character))
    {
      if (character == '\n')
	cont->line_number++;
    }
    else
      /* Invalid input. */
      lexical_error(cont);
  }

  return SCANOFF;
}

void match(token tok, CONTEXT *cont)
{
  if (tok != cont->next_tok)
  {
    /* TODO: remove this line. */
    syntax_error(tok, cont);
  }

  cont->next_tok = scanner(cont);
}

/* Set up variables and match the end of file. */
void parser(CONTEXT *cont)
{
  cont->next_tok = scanner(cont);
  program(cont);
  match(SCANOFF, cont);
}

/* <program> -> main <lb> <stmt-list> <rb> */
void program(CONTEXT *cont)
{
  match(MAIN, cont);
  match(LEFT_BRACKET, cont);
  statment_list(cont);
  match(RIGHT_BRACKET, cont);
}

/* <stmt-list> -> {<stmt>}+ */
void statment_list(CONTEXT *cont)
{
  while (
    cont->next_tok == READ ||
    cont->next_tok == WRITE ||
    cont->next_tok == IF ||
    cont->next_tok == WHILE ||
    cont->next_tok == IDENTIFIER)
    statment(cont);
}

/* <stmt> -> (<read-stmt> | <write-stmt> | <if-stmt> | <while-stmt> | <assignment-stmt>) */
void statment(CONTEXT *cont)
{
  switch (cont->next_tok)
  {
  case READ: read_statment(cont); break;
  case WRITE: write_statment(cont); break;
  case IF: if_statment(cont); break;
  case WHILE: while_statment(cont); break;
  case IDENTIFIER: assignment_stmt(cont); break;
  default: {}; break;
  }
}

void read_statment(CONTEXT *cont)
{
  match(READ, cont);
  match(LEFT_PAREN, cont);
  match(IDENTIFIER, cont);
  while (cont->next_tok == COMMA)
  {
    match(COMMA, cont);
    match(IDENTIFIER, cont);
  }
  match(RIGHT_PAREN, cont);
  match(SEMICOLON, cont);
}

void write_statment(CONTEXT *cont)
{
  match(WRITE, cont);
  match(LEFT_PAREN, cont);
  match(IDENTIFIER, cont);
  while (cont->next_tok == COMMA)
  {
    match(COMMA, cont);
    match(IDENTIFIER, cont);
  }
  match(RIGHT_PAREN, cont);
  match(SEMICOLON, cont);
}

void if_statment(CONTEXT *cont)
{
  match(IF, cont);
  match(LEFT_PAREN, cont);
  boolean_expression(cont);
  match(RIGHT_PAREN, cont);
  match(LEFT_BRACKET, cont);
  statment_list(cont);
  match(RIGHT_BRACKET, cont);
  if (cont->next_tok == ELSE)
  {
    match(ELSE, cont);
    match(LEFT_BRACKET, cont);
    statment_list(cont);
    match(RIGHT_BRACKET, cont);
  }
}

void while_statment(CONTEXT *cont)
{
  match(WHILE, cont);
  match(LEFT_PAREN, cont);
  boolean_expression(cont);
  match(RIGHT_PAREN, cont);
  match(LEFT_BRACKET, cont);
  statment_list(cont);
  match(RIGHT_BRACKET, cont);
}

void assignment_stmt(CONTEXT *cont)
{
  match(IDENTIFIER, cont);
  match(ASSIGN_OP, cont);
  expression(cont);
  match(SEMICOLON, cont);
}

void boolean_expression(CONTEXT *cont)
{
  operand(cont);
  relatinal_operator(cont);
  operand(cont);
}

/* TODO: think about removing this thing. */
void relatinal_operator(CONTEXT *cont)
{
  if (
    cont->next_tok == LT_OP ||
    cont->next_tok == GT_OP ||
    cont->next_tok == LTEQU_OP ||
    cont->next_tok == GTEQU_OP ||
    cont->next_tok == EQU_OP)
    /* cont->next_tok == NOTEQU_OP) */
    match(cont->next_tok, cont);
  /*
    yes putting the last one here is a little bit odd but this function needs to
    "eat" a token if it's not one of the relatinal operators or it throws
    a whole cascade of syntax errors.
  */
  match(NOTEQU_OP, cont);
}

void operand(CONTEXT *cont)
{
  if (cont->next_tok == IDENTIFIER)
    match(IDENTIFIER, cont);
  else
    match(INT_LITERAL, cont);
}

void expression(CONTEXT *cont)
{
  term(cont);
  while (
    cont->next_tok == PLUS_OP ||
    cont->next_tok == MINUS_OP)
  {
    match(cont->next_tok, cont);
    term(cont);
  }
}

void term(CONTEXT *cont)
{
  factor(cont);
  while (
    cont->next_tok == MULT_OP ||
    cont->next_tok == DIV_OP)
  {
    match(cont->next_tok, cont);
    factor(cont);
  }
}

void factor(CONTEXT *cont)
{
  if (cont->next_tok == LEFT_PAREN)
  {
    match(LEFT_PAREN, cont);
    expression(cont);
    match(RIGHT_PAREN, cont);
  }
  else
    operand(cont);
}

void syntax_error(token expected, CONTEXT *cont)
{
  printf(
    "Syntax error on line %d GOT: %s EXPECTED: %s\n",
    cont->line_number,
    TokenStrings[(int)cont->next_tok],
    TokenStrings[(int)expected]);
}

void parse_file(CONTEXT *cont)
{
  char in_file[100];
  printf("Please enter a file to parse:\n");
  scanf("%s", in_file);

  cont->fp = fopen(in_file, "r");
  parser(cont);

  /* TODO: Print a succssess message if the file has no errors. */
}

void scan_file(CONTEXT *cont)
{
  /* TODO: scan and print to a file. */

  char in_file[100], out_file[100];

  printf("Please enter a file to scan:\n");
  scanf("%s", in_file);
  printf("Please enter an output file:\n");
  scanf("%s", out_file);

  cont->fp = fopen(in_file, "r");

  FILE *fout = fopen(out_file, "w");

  token tok;

  do
  {
    tok = scanner(cont);

    fprintf(fout, "%s\n", TokenStrings[(int)tok]);
  }
  while (tok != SCANOFF);

  fclose(cont->fp);
  fclose(fout);
}

/* TODO create the menu for this application. */
int main()
{
  CONTEXT cont;
  cont.line_number = 1;
  cont.error = FALSE;

  printf("Select: \n\
1: Scan a file for tokens.\n\
2: Parse a file.\n");

  int user_input = 0;

  scanf("%d", &user_input);

  switch (user_input)
  {
  case 1: scan_file(&cont); break;
  case 2: parse_file(&cont); break;
  default: printf("Invalid option %d\n", user_input); break;
  }

  return 0;
}
