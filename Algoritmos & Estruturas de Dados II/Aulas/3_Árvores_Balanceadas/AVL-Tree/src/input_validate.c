#include "input_validate.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define EMPTY_ERROR -2
#define INVALID_ERROR -1

//#define INT_MAX_DIGITS 21 // Número máximo de dígitos de um inteiro em 64bits + '\0'.
#define INT_MAX_DIGITS 9 // Número máximo de dígitos de um inteiro + '\0'.

/* Faz a validação de uma entrada inteira.
Retorno: EMPTY_ERROR, INVALID_ERROR, TRUE */
static int validate_integer(int *value)
{
	// int input, check;
	// check = scanf("%d", &input);
	char input[INT_MAX_DIGITS] = {'\0'};
	int output, i = 0;

	// Trim spaces.
	while ((input[0] = (char)getchar()) == ' ' || input[0] == '\t') {
	}

	// Captura o sinal.
	if (input[0] == '-' || input[0] == '+') {
		++i;
		// Trim spaces, após o sinal.
		while ((input[i] = (char)getchar()) == ' ' || input[i] == '\t') {
		}
	}

	if (input[i] == '\n')
		return EMPTY_ERROR;

	// No final, `fgets` só me atrapalhou :v
	// fgets(&input[1], INT_MAX_DIGITS - 1, stdin);

	// Valida os caracteres entrados, até encontrar '\n' ou atingir o limite do inteiro.
	int consume_buffer = FALSE;
	int out_of_bounds = FALSE;
	int is_invalid = FALSE;

	do {
		if (consume_buffer)
			continue;

		if (!isdigit(input[i])) {

			if (input[i] == ' ' || input[i] == '\t') { // Ignora tudo após o espaço.
				consume_buffer = TRUE;
				continue;
			}
			else {
				consume_buffer = is_invalid = TRUE;
				continue;
			}
		}
		// Se o último elemento foi analisado.
		if (!(i < INT_MAX_DIGITS)) {
			consume_buffer = out_of_bounds = TRUE;
			continue;
		}

		++i;
	} while ((input[i] = (char)getchar()) != '\n');

	if (is_invalid)
		return INVALID_ERROR;

	// Converte a string para inteiro.
	char *buff;
	input[i] = '\0';
	output = (int)strtol(input, &buff, 10);
	*value = output;

	if (out_of_bounds) {
		// fputs("", text_yellow(stdout));
		fprintf(
			text_yellow(stdout), "O valor entrado está além dos limites %d, será usado.\n", *value);
		reset_colors(stdout);
	}

	return TRUE;
}


static int _input_integer_emphasis(
	char *message, char *invalid_input_message, char *empty_input_message, int emphasis)
{
	int value, check;
	fprintf(emphasis ? text_magenta(stdout) : text_blue(stdout), "%s ", message);
	reset_colors(stdout);

	while ((check = validate_integer(&value)) != TRUE)

		switch (check) {
			case EMPTY_ERROR: {
				fprintf(text_red(stdout), "%s ", empty_input_message);
				reset_colors(stdout);
			} break;
			case INVALID_ERROR: {
				fprintf(text_red(stdout), "%s ", invalid_input_message);
				reset_colors(stdout);
			} break;
		}

	return value;
}


/* Faz a validação persistente de uma entrada inteira, apresentando mensagens no terminal.
Retorna o valor da entrada. */
static int _input_integer(char *message, char *invalid_input_message, char *empty_input_message)
{
	_input_integer_emphasis(message, invalid_input_message, empty_input_message, FALSE);
}


int input_integer_range(int min, int max, char *message, char *invalid_input_message,
	char *empty_input_message, char *out_of_range_message)
{
	int value = _input_integer(message, invalid_input_message, empty_input_message);

	while (value < min || value > max)
		value = _input_integer_emphasis(
			out_of_range_message, invalid_input_message, empty_input_message, TRUE);

	return value;
}


int input_min_integer(int min, char *message, char *invalid_input_message,
	char *empty_input_message, char *out_of_range_message)
{
	int value = _input_integer(message, invalid_input_message, empty_input_message);

	while (value < min)
		value = _input_integer_emphasis(
			out_of_range_message, invalid_input_message, empty_input_message, TRUE);

	return value;
}
