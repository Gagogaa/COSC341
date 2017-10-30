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
   RIGHT_BRACKET, LEFT_PAREN, RIGHT_PAREN, EQUALS, INT_LITERAL,
   SEMICOLON, SCANOFF, MINUSOP, PLUSOP, MULTOP, DIVOP, GTOP, LTOP,
   EQUOP, GTEQUOP, LTEQUOP, ASSIGNOP */

/* TODO: put a link to the websight where I found this trick. */

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
  apply(EQUALS)\
  apply(INT_LITERAL)\
  apply(SEMICOLON)\
  apply(SCANOFF)\
  apply(MINUSOP)\
  apply(PLUSOP)\
  apply(MULTOP)\
  apply(DIVOP)\
  apply(GTOP)\
  apply(LTOP)\
  apply(EQUOP)\
  apply(GTEQUOP)\
  apply(LTEQUOP)\
  apply(ASSIGNOP)

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
  char *ptr;
  ptr = strchr(cont->token_buffer, '\0');
  *ptr = character;
  *(ptr+1) = '\0';
}

token scanner(CONTEXT *cont)
{
  /* TODO: Think about moveing this to the main. */
  if (cont->fp == NULL)
  {
    cont->error = TRUE;

    /* TODO: change the content of this string. Or move it to the lexical_error function. */
    strcpy(*cont->error_msg, "File Not Found\n");
    return SCANOFF;
  }

  char character;

  // TODO does this really need to be in a while loop?
  while (TRUE)
  {
    character = getc(cont->fp);
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

      /* Check for operators. */
    case '+': return PLUSOP;
    case '-': return MINUSOP;
    case '*': return MULTOP;

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
	return DIVOP;
      }
      break;

      /* Check for assignment operator. */
    case ':':
      character = getc(cont->fp);
      if (character == '=')
	return ASSIGNOP;

      /*
	TODO: make a testfile with these conditions.
	e.g. ":6" won't throw an error or ":<" so maybe
	this should throw an error.

	These should be lexical errors.
      */

      /* Put the character back because ":" by itself should throw an error. */
      character = ':';
      ungetc(character, cont->fp);
      break;

      /* Check for relatinal operators. */
    case '<':
      character = getc(cont->fp);
      if (character == '=')
	return LTEQUOP;

      ungetc(character, cont->fp);
      return LTOP;
      break;

    case '>':
      character = getc(cont->fp);
      if (character == '=')
	return GTEQUOP;

      ungetc(character, cont->fp);
      return GTOP;
      break;

    case '=':
      character = getc(cont->fp);

      if (character == '=')
	return EQUOP;

      /* Put the character back because "=" by itself should throw an error. */
      character = '=';
      ungetc(character, cont->fp);
      break;

    case '!':
      character = getc(cont->fp);

      if (character == '=')
	return EQUOP;

      /* Put the character back because "!" by itself should throw an error. */
      character = '!';
      ungetc(character, cont->fp);
      break;
    }

    clear_buffer(cont);

    /* Check for an identifier or keyword. */
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
    /* Invalid input. */
    else
    {
      // TODO call lexical error and return from the function.
    }
  }

  return SCANOFF;
}

/* TODO create the menu for this application. */
int main()
{
  CONTEXT cont;
  cont.line_number = 1;

  /* char in_file[100], out_file[100]; */

  /* printf("Please enter a file name to parse:\n"); */
  /* scanf("%s", in_file); */
  /* printf("Please enter an output file:\n"); */
  /* scanf("%s", out_file); */

  cont.fp = fopen("test-files/test.xmicro", "r");

  FILE *fout;
  fout = fopen("test.out", "w");

  token tok;

  do
  {
    tok = scanner(&cont);

    fprintf(fout, "%s ", TokenStrings[(int)tok]);
  }
  while (tok != SCANOFF);

  printf("DONE\n");

  return 0;
}
