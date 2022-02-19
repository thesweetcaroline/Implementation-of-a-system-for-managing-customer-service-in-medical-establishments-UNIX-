#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>

#define FIFO_SERV "balc"
#define FIFO_CLI "utente%d"
#define FIFO_MED "espec%d"
#define FIFO_SERV2 "balcmed"
#define FIFO_MEDC "especcom%d"
#define FIFO_CLIC "utentecom%d"


typedef struct cliente{
	char nome[40];
	char sintomas[70];
	char especialidade[30];
	int prioridade;
	int numero_senha; //pid
}Cliente;

typedef struct tdados{
	int continua;
/*	struct cliente *geral; //geral=filas.geral
//	struct cliente totais[atoi(getenv("MAXCLIENTES"))];
	struct cliente oftalmologia[5];
	struct cliente neurologia[5];
	struct cliente estomatologia[5];
	struct cliente ortopedia[5];	*/
	pthread_mutex_t *trinco;
}TDados;

