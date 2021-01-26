#include <stdio.h>
#include <locale.h>

struct dma {
	int dia;
	int mes;
	int ano;
};
struct horas {
	int hora;
	int minuto;
	int segundo;
};
struct data_e_hora {
	struct dma data;
	struct horas horario;
};


int main() {
	setlocale(LC_ALL, "Portuguese");

	struct data_e_hora evento;
	evento.data.dia = 1;
	evento.data.mes = 9;
	evento.data.ano = 2019;
	evento.horario.hora = 14;
	evento.horario.minuto = 30;
	evento.horario.segundo = 0;
	
	printf("Dia do evento: %d\n", evento.data.dia);
	printf("Mês do evento: %d\n", evento.data.mes);
	printf("Hora: %d\n", evento.horario.hora);

	return 0;
}
