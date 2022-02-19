
#include "cliente.h"
#include "medico.h"


typedef struct all_meds{
	Medico *especialistas;
	int tamanho;
}AllMeds;

typedef struct consulta{
	Cliente *atendido;
	int tam;
}Consulta;

typedef struct msg{
	int pid;
	char mensagem[40];
}MSG;

typedef struct filas{
	Cliente *geral;
	int geralTam;
	Cliente *totais;
	int toTam;
	Cliente *oftalmologia;
	int oftTam;
	Cliente *neurologia;
	int neuTam;
	Cliente *estomatologia;
	int estTam;
	Cliente *ortopedia;
	int ortTam;
	//5 é o numero maximo de fila por especialidade
}Filas;

typedef struct repeat{
	int continua;
	Cliente *geral;
	int geralTam;
	Cliente *totais;
	int toTam;
	Cliente *oftalmologia;
	int oftTam;
	Cliente *neurologia;
	int neuTam;
	Cliente *estomatologia;
	int estTam;
	Cliente *ortopedia;
	int ortTam;
	int tempo;
}Repeat;