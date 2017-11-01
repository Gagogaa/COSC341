/*
   Gregory Mann
   Fall 2017
   COSC 341
   Project 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char *String;
typedef int bool;
#define TRUE 1
#define FALSE 0

/* Create the enum of Tokens. */
typedef enum {
  MAIN, WHILE, READ, WRITE, IF, ELSE, IDENTIFIER, LEFT_BRACKET,
  RIGHT_BRACKET, LEFT_PAREN, RIGHT_PAREN, INT_LITERAL, SEMICOLON,
  SCANOFF, MINUS_OP, PLUS_OP, MULT_OP, DIV_OP, GT_OP, LT_OP, EQU_OP,
  GTEQU_OP, LTEQU_OP, NOTEQU_OP, ASSIGN_OP, COMMA
} token;

/* Create an array of strings matching the tokens for pretty printing. */
static String TokenStrings[] = {
  "MAIN", "WHILE", "READ", "WRITE", "IF", "ELSE", "IDENTIFIER",
  "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PAREN", "RIGHT_PAREN",
  "INT_LITERAL", "SEMICOLON", "SCANOFF", "MINUS_OP", "PLUS_OP",
  "MULT_OP", "DIV_OP", "GT_OP", "LT_OP", "EQU_OP", "GTEQU_OP",
  "LTEQU_OP", "NOTEQU_OP", "ASSIGN_OP", "COMMA"
};

/* Globals for the program. */
FILE *file_in;
token next_tok;
char token_buffer[100];
int line_number = 1;
bool error = FALSE;

/* Functions for main. */
void scan_file();
void parse_file();

/* Functions for scanner. */
token scanner();
token check_reserved();
void clear_buffer();
void buffer_char(char character);
void lexical_error();

/* Functions for Parser. */
void match(token tok);
void parser();
void program();
void statment_list();
void statment();
void read_statment();
void write_statment();
void if_statment();
void while_statment();
void assignment_stmt();
void boolean_expression();
void relatinal_operator();
void operand();
void expression();
void term();
void factor();
void syntax_error(token expected);

int main()
{
  printf("Select: \n\
1: Scan a file for tokens.\n\
2: Parse a file.\n");

  int user_input = 0;

  scanf("%d", &user_input);

  switch (user_input)
  {
  case 1: scan_file(); break;
  case 2: parse_file(); break;
  default: printf("Invalid option %d\n", user_input); break;
  }

  return 0;
}

/*
   Takes in user input to read from a source file and pretty print the
   token list to a out file.
*/
void scan_file()
{
  char in_file[100], out_file[100];

  printf("Please enter a file to scan:\n");
  scanf("%s", in_file);
  printf("Please enter an output file:\n");
  scanf("%s", out_file);

  file_in = fopen(in_file, "r");

  FILE *fout = fopen(out_file, "w");

  token tok;

  do
  {
    tok = scanner();

    fprintf(fout, "%s\n", TokenStrings[(int)tok]);
  }
  while (tok != SCANOFF);

  fclose(file_in);
  fclose(fout);
}

/*
  Takes in a file to parse and prints out syntax and lexical errors or
  a success message.
*/
void parse_file()
{
  char in_file[100];
  printf("Please enter a file to parse:\n");
  scanf("%s", in_file);

  file_in = fopen(in_file, "r");
  parser();

  fclose(file_in);

  if (!error)
    printf("Parsing successful!\n");
}

/* Checks if the word just read in is an identifier or a keyword. */
token check_reserved()
{
  /* Check for one of the keywords. */
  if (strcmp("while", token_buffer) == 0) return WHILE;
  if (strcmp("if",    token_buffer) == 0) return IF;
  if (strcmp("else",  token_buffer) == 0) return ELSE;
  if (strcmp("read",  token_buffer) == 0) return READ;
  if (strcmp("write", token_buffer) == 0) return WRITE;
  if (strcmp("main",  token_buffer) == 0) return MAIN;

  return IDENTIFIER;
}

/*
  Clears the Token buffer by placing a NULL character at the beginning
  of the array.
*/
void clear_buffer()
{
  token_buffer[0] = '\0';
}

/* Adds a character to the buffer ensuring a NULL character follows it. */
void buffer_char(char character)
{
  char *ptr = strchr(token_buffer, '\0');
  *ptr = character;
  *(ptr+1) = '\0';
}

/* Prints a lexical error to the screen including a line number. */
void lexical_error()
{
  error = TRUE;
  printf("lexical error on line %d\n", line_number);
}

/*
   A state machine that returns the next locigal token in a xmicro
   source file.
*/
token scanner()
{
  char character;

  while (TRUE)
  {
    character = getc(file_in);

    clear_buffer();

    /* Check for Identifiers. */
    if (isalpha(character))
    {
      do
      {
        buffer_char(character);
        character = getc(file_in);
      }
      while (isalnum(character));

      ungetc(character, file_in);
      return check_reserved();
    }
    /* Check for int literals. */
    else if (isdigit(character))
    {
      do
      {
        buffer_char(character);
        character = getc(file_in);
      }
      while (isdigit(character));

      ungetc(character, file_in);
      return INT_LITERAL;
    }

    /*  */
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
      character = getc(file_in);
      if (character == '/')
      {
        do
          character = getc(file_in);
        while (character != '\n' && character != EOF);
      }
      else
      {
        ungetc(character, file_in);
        return DIV_OP;
      }
      break;

      /* Check for assignment operator. */
    case ':':
      character = getc(file_in);
      if (character == '=')
        return ASSIGN_OP;

      ungetc(character, file_in);

      /* Put the character back because ":" by itself should throw an error. */
      character = ':';
      break;

      /* Check for relatinal operators. */
    case '<':
      character = getc(file_in);
      if (character == '=')
        return LTEQU_OP;

      ungetc(character, file_in);
      return LT_OP;
      break;

    case '>':
      character = getc(file_in);
      if (character == '=')
        return GTEQU_OP;

      ungetc(character, file_in);
      return GT_OP;
      break;

    case '=':
      character = getc(file_in);

      if (character == '=')
        return EQU_OP;

      /* Put the character back because "=" by itself should throw an error. */
      character = '=';
      break;

    case '!':
      character = getc(file_in);

      if (character == '=')
        return NOTEQU_OP;

      ungetc(character, file_in);

      /* Put the character back because "!" by itself should throw an error. */
      character = '!';
      break;
    }

    /* Check for space or throw lexical error. */
    if (isspace(character))
    {
      if (character == '\n')
        line_number++;
    }
    else
      /* Invalid input. */
      lexical_error();
  }

  return SCANOFF;
}

/* Match the next token and throw an error if it's not the expected value. */
void match(token tok)
{
  if (tok != next_tok)
  {
    syntax_error(tok);
  }

  next_tok = scanner();
}

/* Set up variables and match the end of file. */
void parser()
{
  next_tok = scanner();
  program();
  match(SCANOFF);
}

/* <program> -> main <lb> <stmt-list> <rb> */
void program()
{
  match(MAIN);
  match(LEFT_BRACKET);
  statment_list();
  match(RIGHT_BRACKET);
}

/* <stmt-list> -> {<stmt>}+ */
void statment_list()
{
  while (
    next_tok == READ ||
    next_tok == WRITE ||
    next_tok == IF ||
    next_tok == WHILE ||
    next_tok == IDENTIFIER)
    statment();
}

/* <stmt> -> ( <read-stmt>  | <write-stmt> | <if-stmt>
             | <while-stmt> | <assignment-stmt>) */
void statment()
{
  switch (next_tok)
  {
  case READ: read_statment(); break;
  case WRITE: write_statment(); break;
  case IF: if_statment(); break;
  case WHILE: while_statment(); break;
  case IDENTIFIER: assignment_stmt(); break;
  default: {}; break;           /* Make the compiler happy. */
  }
}

/* <read-stmt> -> read <lp> <identifier> {,<identifier>} <rp>; */
void read_statment()
{
  match(READ);
  match(LEFT_PAREN);
  match(IDENTIFIER);
  while (next_tok == COMMA)
  {
    match(COMMA);
    match(IDENTIFIER);
  }
  match(RIGHT_PAREN);
  match(SEMICOLON);
}

/* <write-stmt> -> write <lp> <identifier> {,<identifier>} <rp>; */
void write_statment()
{
  match(WRITE);
  match(LEFT_PAREN);
  match(IDENTIFIER);
  while (next_tok == COMMA)
  {
    match(COMMA);
    match(IDENTIFIER);
  }
  match(RIGHT_PAREN);
  match(SEMICOLON);
}

/* <if-stmt> -> if <lp> <boolean-expr> <rp> <lb> <stmt-list> <rb>
                [else <lb> <stmt-list> <rb>] */
void if_statment()
{
  match(IF);
  match(LEFT_PAREN);
  boolean_expression();
  match(RIGHT_PAREN);
  match(LEFT_BRACKET);
  statment_list();
  match(RIGHT_BRACKET);
  if (next_tok == ELSE)
  {
    match(ELSE);
    match(LEFT_BRACKET);
    statment_list();
    match(RIGHT_BRACKET);
  }
}

/* <while-stmt> -> while <lp> <boolean-expr> <rp> <lb> <stmt-list> <rb> */
void while_statment()
{
  match(WHILE);
  match(LEFT_PAREN);
  boolean_expression();
  match(RIGHT_PAREN);
  match(LEFT_BRACKET);
  statment_list();
  match(RIGHT_BRACKET);
}

/* <assignment-stmt> -> <identifier> := <expr>; */
void assignment_stmt()
{
  match(IDENTIFIER);
  match(ASSIGN_OP);
  expression();
  match(SEMICOLON);
}

/* <boolean-expr> -> <operand> <relational-operator> <operand> */
void boolean_expression()
{
  operand();
  relatinal_operator();
  operand();
}

/* <relational-operator> -> (< | > | <= | >= | == | !=) */
void relatinal_operator()
{
  if (
    next_tok == LT_OP ||
    next_tok == GT_OP ||
    next_tok == LTEQU_OP ||
    next_tok == GTEQU_OP ||
    next_tok == EQU_OP ||
    next_tok == NOTEQU_OP)
    match(next_tok);
}

/* <operand> -> (<identifier> | <integer-literal>) */
void operand()
{
  if (next_tok == IDENTIFIER)
    match(IDENTIFIER);
  else
    match(INT_LITERAL);
}

/* <expr> -> <term> {(+|-) <term>} */
void expression()
{
  term();
  while (
    next_tok == PLUS_OP ||
    next_tok == MINUS_OP)
  {
    match(next_tok);
    term();
  }
}

/* <term> -> <factor> {(*|/) <factor>} */
void term()
{
  factor();
  while (
    next_tok == MULT_OP ||
    next_tok == DIV_OP)
  {
    match(next_tok);
    factor();
  }
}

/* <factor> -> <operand> | <lp> <expr> <rp> */
void factor()
{
  if (next_tok == LEFT_PAREN)
  {
    match(LEFT_PAREN);
    expression();
    match(RIGHT_PAREN);
  }
  else
    operand();
}

/*
   Prints a syntax error to the screen containing the line number, the
   expected token, and the received token.
*/
void syntax_error(token expected)
{
  error = TRUE;

  printf(
    "Syntax error on line %d GOT: %s EXPECTED: %s\n",
    line_number,
    TokenStrings[next_tok],
    TokenStrings[(int)expected]);

  /* "Eat" the token. In some cases this can prevent a cascade of errors. */
  next_tok = scanner();
}
