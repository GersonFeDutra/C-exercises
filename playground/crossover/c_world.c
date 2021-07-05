#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void run()
{
	printf("Hello world from C!\n");
}

char *ask()
{
	char *text = (char *)malloc(sizeof(char) * 29);
	strcpy(text, "Is this a crossover episode?");

	return text;
}

void answer(char *text)
{
	printf("From Python to C: %s\n", text);
}
