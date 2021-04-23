/* Persiste na captura e verificação de uma entrada inteira dentro de um determinado intervalo
(inclusiva). */
int input_integer_range(int min, int max, char *message, char *invalid_input_message,
	char *empty_input_message, char *out_of_range_message);

/* O restante das funções foram enviadas para um .c para encapsular informações desnecessários às
outras funções. Métodos que não foram usados foram comentadas também nesse arquivo. */

// Faz a validação persistente de uma entrada inteira com um tamanho mínimo,
// apresentando mensagens no terminal. Retorna uma entrada válida.
int input_min_integer(int min, char *message, char *invalid_input_message,
	char *empty_input_message, char *out_of_range_message);
