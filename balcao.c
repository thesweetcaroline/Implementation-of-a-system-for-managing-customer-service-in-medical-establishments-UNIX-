#include "balcao.h"


void ListaUtentes(Filas f,Consulta s){
printf("\n---------Utentes em espera---------\n");
	for(int i=0;i<f.toTam;i++){
		printf("\n\n Cliente numero %d \n Nome: %s \n Sintomas: %s Especialidade: %s \n Prioridade: %d \n Numero de Senha: %d\n",i, f.totais[i].nome,f.totais[i].sintomas,f.totais[i].especialidade,f.totais[i].prioridade,f.totais[i].numero_senha);
	}

printf("\n---------Utentes em consulta---------\n");
	for(int i=0;i<s.tam;i++){
		printf("\n\n Cliente numero %d \n Nome: %s \n Sintomas: %s Especialidade: %s \n Prioridade: %d \n Numero de Senha: %d\n",i, s.atendido[i].nome,s.atendido[i].sintomas,s.atendido[i].especialidade,s.atendido[i].prioridade,s.atendido[i].numero_senha);
	}
}

int ContaEspecialistas(AllMeds a,Cliente c){
	int contador=0;
	for(int i=0;i<a.tamanho;i++){
		if(strcmp(c.especialidade,a.especialistas[i].especialidade)==0)
			contador++;
	}
	return contador;
}

void MudaDisponibilidade(AllMeds *a,int id_medico){
	for(int i=0;i<a->tamanho;i++){
		if(a->especialistas[i].id_medico==id_medico){
			if(a->especialistas[i].disponibilidade==1)
				a->especialistas[i].disponibilidade=0;
			else
				a->especialistas[i].disponibilidade=1;
			break;
		}
	}
}

void AdicionaConsulta(Consulta *s,Filas f,int ncliente){
	printf("\n\n%d\n\n",f.geralTam);
	int pos=0;
	for(pos=0;pos<=f.toTam;pos++){
		if(f.totais[pos].numero_senha==ncliente){
			break;
		}
	}
	Consulta *aux = NULL;
    	aux = (Consulta *) realloc(s->atendido, (s->tam + 1)*sizeof(Consulta));
    		if(aux == NULL){
				printf("erro354\n");
				return 0;
			}
    		s->atendido = aux;
    		strcpy(s->atendido[s->tam].nome,f.totais[pos].nome);
    		strcpy(s->atendido[s->tam].especialidade,f.totais[pos].especialidade);
    		strcpy(s->atendido[s->tam].sintomas,f.totais[pos].sintomas);
    		s->atendido[s->tam].prioridade= f.totais[pos].prioridade;
			s->atendido[s->tam].numero_senha=f.totais[pos].numero_senha;
			(s->tam++);
}

int contaUtentes(Filas f,Cliente c,int maxclientes){
	for(int i=0;i<maxclientes;i++){
		if(strcmp(c.especialidade,"ortopedia")==0 && f.ortopedia[i].numero_senha==c.numero_senha){
			return i;
		}else if(strcmp(c.especialidade,"geral")==0 && f.geral[i].numero_senha==c.numero_senha){
			return i;
		}
		else if(strcmp(c.especialidade,"neurologia")==0 && f.neurologia[i].numero_senha==c.numero_senha){
			return i;
		}else if(strcmp(c.especialidade,"Estomatologia")==0 && f.estomatologia[i].numero_senha==c.numero_senha){
			return i;
		}else if(strcmp(c.especialidade,"oftalmologia")==0 && f.oftalmologia[i].numero_senha==c.numero_senha){
			return i;
		}
	}	
}

void ListaEspecialistas(AllMeds a){
	printf("\n---------Lista de Especialistas---------\n");
	for(int i=0;i<a.tamanho;i++){
		printf("\n\nNome: %s \nEspecialidade: %s \nID do Medico: %d", a.especialistas[i].nome, a.especialistas[i].especialidade, a.especialistas[i].id_medico);
		if(a.especialistas[i].disponibilidade==1)
			printf("\nDisponivel\n");
			else
			printf("\nEm Consulta\n");
	}
}



Cliente* reordena(Cliente *lista,int tam){
	//printf("Entrei aqui\n");
	Cliente *ordenado = malloc(sizeof(Cliente)*tam);
	int a=0;
	for(int i=0;i<tam;i++){
		if(lista[i].prioridade==1){
			strcpy(ordenado[a].nome,lista[i].nome);
            strcpy(ordenado[a].especialidade,lista[i].especialidade);
            strcpy(ordenado[a].sintomas,lista[i].sintomas);
            ordenado[a].prioridade=lista[i].prioridade;
			ordenado[a].numero_senha=lista[i].numero_senha;

			a++;
		}
	}
	for(int i=0;i<tam;i++){
		if(lista[i].prioridade==2){
			strcpy(ordenado[a].nome,lista[i].nome);
            strcpy(ordenado[a].especialidade,lista[i].especialidade);
            strcpy(ordenado[a].sintomas,lista[i].sintomas);
            ordenado[a].prioridade=lista[i].prioridade;
			ordenado[a].numero_senha=lista[i].numero_senha;
			a++;
		}
	}
	for(int i=0;i<tam;i++){
		if(lista[i].prioridade==3){
			strcpy(ordenado[a].nome,lista[i].nome);
            strcpy(ordenado[a].especialidade,lista[i].especialidade);
            strcpy(ordenado[a].sintomas,lista[i].sintomas);
            ordenado[a].prioridade=lista[i].prioridade;
			ordenado[a].numero_senha=lista[i].numero_senha;

			a++;
		}
	}
	//printf("Cheguei aqui \n");
	return ordenado;
}

int AdicionaUtente(Filas *f,Cliente *cliente,int maxclientes){
	int maxfila=maxclientes/5;
	if(f->toTam != maxclientes){
			Cliente *aux = NULL;
    		aux = (Cliente *) realloc(f->totais, (f->toTam + 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro354\n");
				return 0;
			}
    		f->totais = aux;
    		strcpy(f->totais[f->toTam].nome,cliente->nome);
    		strcpy(f->totais[f->toTam].especialidade,cliente->especialidade);
    		strcpy(f->totais[f->toTam].sintomas,cliente->sintomas);
    		f->totais[f->toTam].prioridade= cliente->prioridade;
			f->totais[f->toTam].numero_senha=cliente->numero_senha;
			(f->toTam++);
			//f->totais=reordena(f->totais,f->toTam);
		//printf("%s%d",strcmp(cliente->especialidade, "geral"),f->geralTam);
		if(strcmp(cliente->especialidade, "geral") == 0 && f->geralTam<=maxfila) {
			Cliente *auxiliar = NULL;
			//printf("%d",f->geralTam);
    		auxiliar = (Cliente *) realloc(f->geral, (f->geralTam + 1)*sizeof(Cliente));
    		if(auxiliar == NULL){
				printf("erro2\n");
				return 0;
			}
    		f->geral = auxiliar;
    		strcpy(f->geral[f->geralTam].nome,cliente->nome);
    		strcpy(f->geral[f->geralTam].especialidade,cliente->especialidade);
    		strcpy(f->geral[f->geralTam].sintomas,cliente->sintomas);
    		f->geral[f->geralTam].prioridade= cliente->prioridade;
			f->geral[f->geralTam].numero_senha=cliente->numero_senha;
			(f->geralTam++);
			f->geral=reordena(f->geral,f->geralTam);
			return 1;
		}
		if(strcmp(cliente->especialidade, "oftalmologia")== 0 && f->oftTam<=maxfila){
			aux = NULL;
    		aux = (Cliente *) realloc(f->oftalmologia, (f->oftTam + 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro3\n");
				return 0;
			}
    		f->oftalmologia = aux;
    		strcpy(f->oftalmologia[f->oftTam].nome,cliente->nome);
    		strcpy(f->oftalmologia[f->oftTam].especialidade,cliente->especialidade);
    		strcpy(f->oftalmologia[f->oftTam].sintomas,cliente->sintomas);
    		f->oftalmologia[f->oftTam].prioridade= cliente->prioridade;
			f->oftalmologia[f->oftTam].numero_senha=cliente->numero_senha;

			(f->oftTam++);
			f->oftalmologia=reordena(f->oftalmologia,f->oftTam);
			return 1;

		}
		if(strcmp(cliente->especialidade, "neurologia")==0 && f->neuTam<=maxfila){
			aux = NULL;
    		aux = (Cliente *) realloc(f->neurologia, (f->neuTam + 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro4\n");
				return 0;
			}
    		f->neurologia = aux;
    		strcpy(f->neurologia[f->neuTam].nome,cliente->nome);
    		strcpy(f->neurologia[f->neuTam].especialidade,cliente->especialidade);
    		strcpy(f->neurologia[f->neuTam].sintomas,cliente->sintomas);
    		f->neurologia[f->neuTam].prioridade= cliente->prioridade;
			f->neurologia[f->neuTam].numero_senha=cliente->numero_senha;
			(f->neuTam++);
			f->neurologia=reordena(f->neurologia,f->neuTam);
			return 1;
		}
		else if(strcmp(cliente->especialidade, "estomatologia")==0 && f->estTam<=maxfila){
			aux = NULL;
    		aux = (Cliente *) realloc(f->estomatologia, (f->estTam + 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro5\n");
				return 0;
			}
    		f->estomatologia = aux;
    		strcpy(f->estomatologia[f->estTam].nome,cliente->nome);
    		strcpy(f->estomatologia[f->estTam].especialidade,cliente->especialidade);
    		strcpy(f->estomatologia[f->estTam].sintomas,cliente->sintomas);
    		f->estomatologia[f->estTam].prioridade= cliente->prioridade;
			f->estomatologia[f->estTam].numero_senha=cliente->numero_senha;
			(f->estTam++);
			f->estomatologia=reordena(f->estomatologia,f->estTam);
			return 1;
		}
		else if(strcmp(cliente->especialidade, "Ortopedia")==0 && f->ortTam<=maxfila){
			aux = NULL;
    		aux = (Cliente *) realloc(f->ortopedia, (f->ortTam + 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro6\n");
				return 0;
			}
    		f->ortopedia = aux;
    		strcpy(f->ortopedia[f->ortTam].nome,cliente->nome);
    		strcpy(f->ortopedia[f->ortTam].especialidade,cliente->especialidade);
    		strcpy(f->ortopedia[f->ortTam].sintomas,cliente->sintomas);
    		f->ortopedia[f->ortTam].prioridade= cliente->prioridade;
			f->ortopedia[f->ortTam].numero_senha=cliente->numero_senha;
			(f->ortTam++);
			f->ortopedia=reordena(f->ortopedia,f->ortTam);
			return 1;
		}
	}else{
		return 0;
	}
}

/*
int getPosicao(Cliente *c,int tam, int pidAux){
	int pos = 0;
    for(int i=0; i < tam; i++){
        if(c[i].pid == pidAux){
            pos = i;
			return pos;
        }
    }
}*/

int AdicionaEspecialista(AllMeds *a,Medico *m,int maxmedicos){
	if(a->tamanho != maxmedicos){
			Medico *aux = NULL;
			//printf("Entrei aqui");
    		aux = (Medico *) realloc(a->especialistas, (a->tamanho + 1)*sizeof(Medico));
    		if(aux == NULL){
				printf("erro1\n");
				return 1;
			}
    		a->especialistas = aux;
    		strcpy(a->especialistas[a->tamanho].nome,m->nome);
    		strcpy(a->especialistas[a->tamanho].especialidade,m->especialidade);
    		a->especialistas[a->tamanho].disponibilidade= m->disponibilidade;
			a->especialistas[a->tamanho].id_medico=m->id_medico;
			(a->tamanho++);

			return 1;
	}else{
		return 0;
	}
}

void RemoveEspecialista(AllMeds *a,int n){ 

    char str2[30];
    //printf("\n\nPID : %d",n);
    printf("%d",a->tamanho);
    if(a->tamanho > 1){
        int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
        for(int i=0; i<a->tamanho;i++){
            if(a->especialistas[i].id_medico == n){
                strcpy(str2,a->especialistas[i].especialidade);// para guardar a especialidade lg para nao terem de a passar como argumento
                pos = i; // guardar a posicao dele 
            }
        }
        for(int i = pos;i<a->tamanho; i++){ // como esta em cima ou assim vcs é q escolhem
                    a->especialistas[i] = a->especialistas[i+1];
                }
        Medico *aux = NULL;
        aux = (Medico *) realloc(a->especialistas,(a->tamanho-1)*sizeof(Medico));
            if(aux == NULL){
                printf("erro1\n");
                return ;
            }        
        a->especialistas = aux;
        (a->tamanho)--;
        return;
    }else{
        (a->tamanho--);
        return ;
    }
}

void RemoveUtente(Filas *f,int n){ 
	
	char str2[30];
	//printf("\n\nPID : %d",n);
	//printf("%d",f->toTam);
	if(f->toTam > 1){
		int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
		for(int i=0; i<f->toTam;i++){
			if(f->totais[i].numero_senha == n){
				strcpy(str2,f->totais[i].especialidade);// para guardar a especialidade lg para nao terem de a passar como argumento
				pos = i; // guardar a posicao dele 
			}
		}
	
		for(int i = pos;i<f->toTam; i++){ // como esta em cima ou assim vcs é q escolhem
					f->totais[i] = f->totais[i+1];
				}
	
		Cliente *aux = NULL;
    	aux = (Cliente *) realloc(f->totais, (f->toTam - 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro1\n");
				return ;
			}    	
		f->totais = aux;
		(f->toTam--);

		//return;
	}else if(f->toTam ==0){return;}
	else {
		strcpy(str2,f->totais[0].especialidade);
		(f->toTam--);
		//return ;

	}
	printf("Estou aqui%s",str2);
	if(strcmp(str2,"ortopedia")==0){
		if(f->ortTam==1){
			strcpy(f->ortopedia[0].nome," ");
			strcpy(f->ortopedia[0].sintomas," ");
			strcpy(f->ortopedia[0].especialidade," ");
			f->ortopedia[0].prioridade=0;
			f->ortopedia[0].numero_senha=0;
			f->ortTam=0;
		}else if(f->ortTam==0){}
		else{
			int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
			for(int i=0; i<f->ortTam;i++){
				if(f->ortopedia[i].numero_senha == n){
					pos = i; // guardar a posicao dele 
				}
			}
	
		for(int i = pos;i<f->ortTam; i++){ // como esta em cima ou assim vcs é q escolhem
					f->ortopedia[i] = f->ortopedia[i+1];
				}
	
		Cliente *aux = NULL;
    	aux = (Cliente *) realloc(f->ortopedia, (f->ortTam - 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro1\n");
				return ;
			}    	
		f->ortopedia = aux;
		(f->ortTam--);
		}
	}else if(strcmp(str2,"neurologia")==0){
		if(f->neuTam==1){
			strcpy(f->neurologia[0].nome," ");
			strcpy(f->neurologia[0].sintomas," ");
			strcpy(f->neurologia[0].especialidade," ");
			f->neurologia[0].prioridade=0;
			f->neurologia[0].numero_senha=0;
			f->neuTam=0;
		}else if(f->neuTam==0){}
		else{
			int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
			for(int i=0; i<f->neuTam;i++){
				if(f->neurologia[i].numero_senha == n){
					pos = i; // guardar a posicao dele 
				}
			}
	
		for(int i = pos;i<f->neuTam; i++){ // como esta em cima ou assim vcs é q escolhem
					f->neurologia[i] = f->neurologia[i+1];
				}
	
		Cliente *aux = NULL;
    	aux = (Cliente *) realloc(f->neurologia, (f->neuTam - 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro1\n");
				return ;
			}    	
		f->neurologia = aux;
		(f->neuTam--);
		}
	}else if(strcmp(str2,"estomatologia")==0){
		if(f->estTam==1){
			strcpy(f->estomatologia[0].nome," ");
			strcpy(f->estomatologia[0].sintomas," ");
			strcpy(f->estomatologia[0].especialidade," ");
			f->estomatologia[0].prioridade=0;
			f->estomatologia[0].numero_senha=0;
			f->estTam=0;
		}else if(f->estTam==0){}
		else{
			int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
			for(int i=0; i<f->estTam;i++){
				if(f->estomatologia[i].numero_senha == n){
					pos = i; // guardar a posicao dele 
				}
			}
	
		for(int i = pos;i<f->estTam; i++){ // como esta em cima ou assim vcs é q escolhem
					f->estomatologia[i] = f->estomatologia[i+1];
				}
	
		Cliente *aux = NULL;
    	aux = (Cliente *) realloc(f->estomatologia, (f->estTam - 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro1\n");
				return ;
			}    	
		f->estomatologia = aux;
		(f->estTam--);
		}
	}else if(strcmp(str2,"geral")==0){
		if(f->geralTam==1 ){
			strcpy(f->geral[0].nome," ");
			strcpy(f->geral[0].sintomas," ");
			strcpy(f->geral[0].especialidade," ");
			f->geral[0].prioridade=0;
			f->geral[0].numero_senha=0;
			(f->geralTam--);
		}else if(f->geralTam==0){}
		else {
			int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
			for(int i=0; i<f->geralTam;i++){
				if(f->geral[i].numero_senha == n){
					pos = i; // guardar a posicao dele 
				}
			}
	
		for(int i = pos;i<f->geralTam; i++){ // como esta em cima ou assim vcs é q escolhem
					f->geral[i] = f->geral[i+1];
				}
	
		Cliente *aux = NULL;
    	aux = (Cliente *) realloc(f->geral, (f->geralTam - 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro1\n");
				return ;
			}    	
		f->geral = aux;
		(f->geralTam--);
		}
	}else if(strcmp(str2,"oftalmologia")==0){
		if(f->oftTam==1){
			strcpy(f->oftalmologia[0].nome," ");
			strcpy(f->oftalmologia[0].sintomas," ");
			strcpy(f->oftalmologia[0].especialidade," ");
			f->oftalmologia[0].prioridade=0;
			f->oftalmologia[0].numero_senha=0;
			f->oftTam=0;
		}else if(f->oftTam==0){}
		else{
			int pos = 0; // guardar a posicao dele no array so para tornar o ciclo mais facil de perceber
			for(int i=0; i<f->oftTam;i++){
				if(f->oftalmologia[i].numero_senha == n){
					pos = i; // guardar a posicao dele 
				}
			}
	
		for(int i = pos;i<f->oftTam; i++){ // como esta em cima ou assim vcs é q escolhem
					f->oftalmologia[i] = f->oftalmologia[i+1];
				}
	
		Cliente *aux = NULL;
    	aux = (Cliente *) realloc(f->oftalmologia, (f->oftTam - 1)*sizeof(Cliente));
    		if(aux == NULL){
				printf("erro1\n");
				return ;
			}    	
		f->oftalmologia = aux;
		(f->oftTam--);
		}
	}
	//printf("PID NAO EXISTE\n");
}

int UtenteASerAtendido(Medico m,Filas f){
	//printf("Estou aqui");
	if(strcmp(m.especialidade,"ortopedia")==0 && f.ortTam!=0)
		return f.ortopedia[0].numero_senha;
	else if(strcmp(m.especialidade,"geral")==0 && f.geralTam!=0)
		return f.geral[0].numero_senha;
	else if(strcmp(m.especialidade,"oftalmologia")==0 && f.oftTam!=0)
		return f.oftalmologia[0].numero_senha;
	else if(strcmp(m.especialidade,"neurologia")==0 && f.neuTam!=0)
		return f.neurologia[0].numero_senha;
	else if(strcmp(m.especialidade,"estomatologia")==0 && f.estTam!=0)
		return f.geral[0].numero_senha;
	else
		return 0;
}


void *RepeatThread(void *rep){
	Repeat *rp=(Repeat *)rep;
	do{
		printf("Numero de utentes em fila de espera na especialidade Geral: %d\n", rp->geralTam);
		printf("Numero de utentes em fila de espera na especialidade Oftalmologia: %d\n", rp->oftTam);
		printf("Numero de utentes em fila de espera na especialidade Ortopedia: %d\n", rp->ortTam);
		printf("Numero de utentes em fila de espera na especialidade Neurologia: %d\n", rp->neuTam);
		printf("Numero de utentes em fila de espera na especialidade Estomatologia: %d\n", rp->estTam);

		sleep(rp->tempo);


	}while(rp->continua);
	pthread_exit(NULL);
}

int main(int argc, char *argv[],char *envp[]){

	int bc[2];
	int cb[2];
	int fd,fdm,fd_retorno,fdb;
	char resposta[30];
	char str[30],cmd[30];
	char *espec;
	char *com;

//	printf("Entrei no balcao");
	pipe(bc);
	pipe(cb);
	Cliente c;
	Medico m;
	MSG mens;
	Filas f;
	Consulta s;
	s.atendido=NULL;
	s.tam=0;
	AllMeds a;
	a.especialistas = NULL;
	a.tamanho=0;
	f.geral=NULL;
	f.geralTam=0;
	f.totais=NULL;
	f.toTam=0;
	f.oftalmologia=NULL;
	f.oftTam=0;
	f.neurologia=NULL;
	f.neuTam=0;
	f.estomatologia=NULL;
	f.estTam=0;
	f.ortopedia=NULL;
	f.ortTam=0;
	int maxclientes,maxmedicos;
	int res,estado,var;
	char sintomas[100];

	//Select
	int resultado,medbal;
	fd_set fds;
	struct timeval tempo = {5,0};
	struct timeval tiempo= {5,0};

	if(getenv("MAXCLIENTES") == NULL){
		maxclientes=25;
	}else
		maxclientes=atoi(getenv("MAXCLIENTES")); // converte para int
	if(getenv("MAXMEDICOS") == NULL){
		maxmedicos=5;
	}
	else
		maxmedicos=atoi(getenv("MAXMEDICOS"));
	
	Medico *medicos=malloc(sizeof(Medico)); //Criacao do array de médicos

	//strcpy(sintomas,argv[1]); - so na meta 2
	//printf("\n\n%s\n\n",sintomas);
	//fflush(stdin);

//Verificar se existe um Fifo criado anteriormente
	if(access(FIFO_SERV, F_OK) == 0){
		printf("[ERRO] O fifo ja existe!\n");
		exit(1);
   }
//Criar o FIFO
   mkfifo(FIFO_SERV2,0700);
   	fdm= open(FIFO_SERV2,O_RDWR);

   mkfifo(FIFO_SERV, 0700);
   	fd = open(FIFO_SERV, O_RDWR);

   printf("Criei o fifo...\n");
	//Abrir o fifo

	res=fork();
	if(res==0){
	
		//tratamento do pipe stdin
		close(0);
		dup(bc[0]);
		close(bc[0]);
		close(bc[1]);
		
		//tratamento do pipe stdout
		close(1);
		dup(cb[1]);
		close(cb[1]);
		close(cb[0]);
		execl("classificador","classificador",NULL);
		fprintf(stderr,"Erro na execucao do classificador");
		exit(33);
	}
	//do{
		Repeat rep[1];
		int nfreq=20;
		pthread_t t_id[1];
		pthread_create(&t_id[0], NULL, RepeatThread, (void *)&rep[0]);
		do{
			printf("\n---------Deseja executar algum comando?---------\n");
			//SELECT...
			FD_ZERO(&fds);
			FD_SET(0, &fds);	//TECLADO
			FD_SET(fd,&fds);	//FIFO
			FD_SET(fdm,&fds);
			tempo.tv_sec=15;
			tempo.tv_usec=0;

			rep[0].geralTam=f.geralTam;
			rep[0].oftTam=f.oftTam;
			rep[0].neuTam=f.neuTam;
			rep[0].ortTam=f.ortTam;
			rep[0].estTam=f.estTam;
			

			rep[0].continua=1;
			rep[0].tempo=nfreq;



			fdb=(fd>fdm)? fd:fdm;
			resultado=select(fdb+1,&fds,NULL,NULL,&tempo);
			
			if(resultado==0){
				printf("\n \n");}
			else if(resultado>0 && FD_ISSET(0,&fds)){
				scanf("%s",cmd);
	        	if(strcmp(cmd,"utentes")==0)
        	        ListaUtentes(f,s);
				else if(strcmp(cmd,"delut")==0){
					int nut;
					scanf("%d",&nut);
					RemoveUtente(&f,nut);
					kill(nut, SIGUSR2);
				}
				else if(strcmp(cmd,"especialistas")==0){
					//printf("Entrei aqui");
					ListaEspecialistas(a);
				}
				else if(strcmp(cmd,"delesp")==0){
                    int id_med;
                    scanf("%d",&id_med);
                    RemoveEspecialista(&a,id_med);
					kill(id_med, SIGUSR2);
                }
				else if(strcmp(cmd, "freq")==0){
					int freq;
					scanf("%d",&freq);
					if(freq>=0){
						nfreq=freq;
						printf("A lista de utentes passa a ser apresentada a cada %d segundos",nfreq);
					}
				}
			}
			else if(resultado>0 && FD_ISSET(fd,&fds)){
				//static int numero=0;
				//int xasasa=read(fd,&m,sizeof(Medico));
				printf("Li do cliente");
				int n=read(fd,&c,sizeof(Cliente));
				if(strcmp(c.nome,"sair")==0 || strcmp(c.nome,"#fim")==0)
					break;
				strcat(c.sintomas,"\n");
				printf("%s %s",c.nome,c.sintomas);
				int nbytes=write(bc[1],c.sintomas,strlen(c.sintomas)); //escreve para o parametro de entrada os sintomas
				printf("\nEnviei %d bytes",nbytes);
				//printf("l");
				//printf("%s",resposta);
				strcpy(resposta," ");
				nbytes=read(cb[0],resposta,sizeof(resposta));
				printf("%s",resposta);
				//printf("Lalalal");
				espec= strtok(resposta," ");
				stpcpy(c.especialidade,espec);
				espec= strtok(NULL,"\n");
				int num=atoi(espec);
				printf("%d",num);
				c.prioridade=num;
				//printf("%d",c.prioridade);
				//printf("\n%d %s ",c.prioridade,c.especialidade);
								//printf("\nRecebi %d bytes",nbytes);

				//printf("aloha");
				//flush(stdin);
				//fflush(stdout);
				int permissao=AdicionaUtente(&f,&c,maxclientes);
                int varUt=contaUtentes(f,c,maxclientes);
                int varEsp=ContaEspecialistas(a,c);
                c.prioridade=c.prioridade*1000 + varUt*100 + varEsp;
                /*if(numero==0)
                    printf("%s\n %s\n %s \n %d \n %d",f.totais[0].nome , f.totais[0].sintomas, f.totais[0].especialidade,f.totais[0].prioridade,f.totais[0].numero_senha);
                if(numero==1)
                    printf("%s\n %s\n %s \n %d \n %d",f.totais[1].nome , f.totais[1].sintomas, f.totais[1].especialidade,f.totais[1].prioridade,f.totais[1].numero_senha);

                numero++;*/
                //permissao=0;
                   if(permissao==0){
                       kill(c.numero_senha,SIGUSR1);
                       //strcpy(c.especialidade,"close");
                   }
        
                    
                
          
                sprintf(str, FIFO_CLI, c.numero_senha);
                fd_retorno=open(str,O_WRONLY);
                n=write(fd_retorno,&c,sizeof(Cliente));
                c.prioridade=c.prioridade/1000;
				/*int nuf=contaUtentes(f,c,maxclientes);
				n=write(fd_retorno,nuf,sizeof(int));
				nuf=ContaEspecialistas(a,c);
				n=write(fd_retorno,nuf,sizeof(int));*/
		
				//printf("\n\n\n\\n\n Nome: %s \n Sintomas: %s \n Especialidade: %s \n Prioridade %d \n Senha %d",c.nome,c.sintomas,c.especialidade,c.prioridade,c.numero_senha); 
				//int x=AdicionaEspecialista(&a,&m,maxmedicos);

				//Percorrer o array de médicos. Verificar se está disponivel. Se estiver consultar a fila na especialidade e aceder ao cliente no primeiro lugar (sprintf). Atualizar a fila. Mandar qlq cena para o utilizador
				}
				else if(resultado>0 && FD_ISSET(fdm,&fds)){
					printf("Entrei aqui");
					int cpa;
					//printf("Entrei aqui");
					int n=read(fdm,&m,sizeof(Medico));
					//printf("%s",m.nome);
					int respuensa=AdicionaEspecialista(&a,&m,maxmedicos);
					if(respuensa==0){
						printf("Numero de medicos maximos ativado");
					}
					char utenteParaM[40],MedicoPC[40];
					cpa=UtenteASerAtendido(m,f);
										
					if(cpa!=0){
						AdicionaConsulta(&s,f,cpa);
						MudaDisponibilidade(&a,m.id_medico);
						RemoveUtente(&f,cpa);
						//printf("%d")
						
						//AdicionaConsulta
						strcpy(mens.mensagem,"inicia");
						mens.pid=cpa;
						sprintf(utenteParaM, FIFO_MED, m.id_medico);
						fd_retorno=open(utenteParaM,O_WRONLY);
						n=write(fd_retorno,&mens,sizeof(MSG));
						close(fd_retorno);
						mens.pid=m.id_medico;
						sprintf(utenteParaM, FIFO_CLIC, cpa);
						fd_retorno=open(utenteParaM,O_WRONLY);
						//printf("Ainda nao rebentei 1");
						n=write(fd_retorno,&mens,sizeof(MSG));
						close(fd_retorno);

					

					}else
					printf("Nao existe cliente");
				}
			}while(strcmp(cmd,"encerra")!=0);
	//}while(1);//strcmp(c.nome,"sair")!=0);
	write(bc[1],"#fim\n",5);
	wait(&estado);

	rep[0].continua=0;
	close(bc[0]);
	close(cb[1]);
	close(fdb);
	unlink(fdb);
	close(fd);//Fechar o FIFO
	unlink(fd); //Apagar o FIFO
	printf("O sistema encerrou com %d.\n",WEXITSTATUS(estado));
	
	printf("[%d] THE END\n",getpid());
	exit(0);
//	return especialidade+nutentes;
}
