#include <stdio.h>


int main() {
	//printf("\033[32m[\aA\bB\cC\dD\eE\fF\gG\hH\iI\jJ\kK\lL\mM\nN\oO\pP\qQ\rR\sS\tT\uU\vV\wW\xX\yY\zZ]!\033[m\n");
	//printf("\033[32m[\aA\bBCD\eE\fFGHIJKLMNOPQRSTUVWXYZ]!\033[m\n");
	printf("\033[32m[\aA\bBCDE\fFGHIJKLM\nNOPQ\rRS\tTU\vVWXYZ]!\033[m\n");
    /* Reference: <https://en.wikipedia.org/wiki/Escape_sequences_in_C>
    \a	07	Alert (Beep, Bell) (added in C89)[1]
    \b	08	Backspace
    \e	1B	Escape character
    \f	0C	Formfeed Page Break
    \n	0A	Newline (Line Feed);
    \r	0D	Carriage Return
    \t	09	Horizontal Tab
    \v	0B	Vertical Tab
    \\	5C	Backslash
    \'	27	Apostrophe or single quotation mark
    \"	22	Double quotation mark
    \?	3F	Question mark (used to avoid trigraphs)
    \nnn	any	The byte whose numerical value is given by nnn interpreted as an octal number
    \xhh…	any	The byte whose numerical value is given by hh… interpreted as a hexadecimal number
    \uhhhh	none	Unicode code point below 10000 hexadecimal (added in C99)[1]: 26 
    \Uhhhhhhhh	none	Unicode code point where h is a hexadecimal digit
    */
	return 0;
}

