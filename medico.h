#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

typedef struct medico{
	char nome[40];
	char especialidade[70];
	bool disponibilidade;
	int id_medico;
}Medico;


