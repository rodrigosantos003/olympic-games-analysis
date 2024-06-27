/**
 * @file input.c
 * @authors João Fernandes (202100718), Rodrigo Santos (202100722), Rúben Dâmaso (202100723) [Turma 1ºL_EI-08 - Prof. Patrícia Macedo]
 * @brief Provides an implementation of input.h.
 *
 * Relies in always reading text and converting to the appropriate
 * data type. Some straighforward validations are implemented.
 * Does not allow trailing spaces in the formats.
 *
 * @version 2
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "input.h"

static bool validIntegerFormat(const char *s);
static bool validDoubleFormat(const char *s);
static void removeNewline(char *s);

bool readInteger(int *ptVal)
{
	char str[20];
	fgets(str, sizeof(str), stdin);
	removeNewline(str);

	if (!validIntegerFormat(str))
		return false;

	*ptVal = atoi(str);
	return true;
}

bool readDouble(double *ptVal)
{
	char str[20];
	fgets(str, sizeof(str), stdin);
	removeNewline(str);

	if (!validDoubleFormat(str))
		return false;

	*ptVal = atof(str);
	return true;
}

bool readChar(char *ptVal)
{
	char line[20];
	fgets(line, sizeof(line), stdin);
	removeNewline(line);

	int len = strlen(line);
	/* we only take the fist character */
	if (len > 0)
	{
		*ptVal = line[0];
		return true;
	}
	return false; /* no characters were read */
}

void readString(char *charArr, unsigned int maxChars)
{
	fgets(charArr, maxChars, stdin);
	removeNewline(charArr); /* modifies in-place*/
}

char **splitString(char *string, int nTokens, const char *delim)
{
	char **tokens = (char **)malloc(sizeof(char *) * nTokens);
	int index = 0;
	int len = strlen(string);

	// Discard newline, if present
	if (string[len - 1] == '\n')
	{
		string[len - 1] = '\0';
		len--;
	}

	// Discard carriage return, if present, e.g., CRLF formats
	if (string[len - 1] == '\r')
	{
		string[len - 1] = '\0';
		len--;
	}

	tokens[index++] = &string[0];
	for (int i = 0; i < len; i++)
	{
		if (string[i] == delim[0])
		{
			string[i] = '\0';
			tokens[index++] = &string[i] + (i < len - 1 ? 1 : 0);
		}
	}
	return tokens;
}

static bool validIntegerFormat(const char *s)
{
	const char *start = s;
	for (const char *c = s; *c != '\0'; c++)
	{
		if (c == start && *c == '-')
			continue;
		if (!isdigit(*c))
			return false;
	}
	return true;
}

static bool validDoubleFormat(const char *s)
{
	int dotCount = 0;
	const char *start = s;
	for (const char *c = s; *c != '\0'; c++)
	{
		if (c == start && *c == '-')
			continue;
		if (*c == '.')
		{
			if (dotCount > 0)
				return false;
			else
				dotCount++;
			continue;
		}
		if (!isdigit(*c))
			return false;
	}
	return true;
}

static void removeNewline(char *s)
{
	int len = strlen(s);
	if (len > 0 && s[len - 1] == '\n')
	{
		s[len - 1] = '\0';
	}
}

void stringToUpperCase(char *string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		string[i] = toupper(string[i]);
	}
}