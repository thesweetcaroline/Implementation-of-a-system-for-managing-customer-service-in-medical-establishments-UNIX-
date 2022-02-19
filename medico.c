#include "balcao.h"
void sair(int s){
	printf("O especialista saiu.");
	exit(0);
}

void max_especs(int fc){
	printf("O Sistema atingiu lotacao maxima de medicos. Volte mais tarde.");
	exit(0);
}

int main(int argc, char *argv[]){
	Medico m;
	MSG mensag;
	int pidRecebido=0;
	signal(SIGUSR1, max_especs);
	signal(SIGUSR2,sair);
	char str[40];
	char msgparacli[40];
	char pipe[40];
	int fdboth;
	char cmd[40];
	int res, estado, n,fd,fd_both;
	int cliac;
	int validacao;
	int fopenff;
	fd_set fds;
	struct timeval tempo = {5,0};
	if(argc!=3){
		printf("Erro. Nr de args. \n");
		printf("	./medico <\"Nome\"> <\"Especialidade\"> \n");
	}
	else{
	if(access(FIFO_SERV2, F_OK) != 0){
		printf("[ERRO] O fifo ainda nao existe!\n");
		exit(1);
   	}
//CRIAR O FIFO...
	 strcpy(m.nome,argv[1]);
	 strcpy(m.especialidade,argv[2]);
	 m.disponibilidade = true; 
	 m.id_medico=getpid();
	 sprintf(str,FIFO_MED,m.id_medico);
	 mkfifo(str,0700);
	 int fifm=open(str,O_RDWR);
	 printf("Criei o fifo...\n");
	 sprintf(pipe,FIFO_MEDC,m.id_medico);
	 mkfifo(pipe,0700);
	 int op=open(pipe,O_RDWR);


//ABRIR O FIFO...
    fd = open(FIFO_SERV2, O_WRONLY);     // O_RDONLY
    printf("Abri o fifo...\n");
	n = write(fd, &m, sizeof(Medico));
	//printf("Fiz a escrita");
	do{
	FD_ZERO(&fds);
	FD_SET(0, &fds);	//TECLADO
	FD_SET(fifm,&fds);	//FIFO
	FD_SET(op,&fds);
	tempo.tv_sec=5;
	tempo.tv_usec=0;
	fdboth=(fifm>op)? fifm:op;
	res=select(fdboth+1,&fds,NULL,NULL,&tempo);
	if(res==0){

	}else if(res>0 && FD_ISSET(0,&fds)){
		scanf(" %[^\n]",cmd);
		if(strcmp(cmd,"sair")==0){
	
		}else{
			strcpy(mensag.mensagem,cmd);
			sprintf(msgparacli,FIFO_CLIC,pidRecebido);
			pidRecebido=m.id_medico;
			fopenff=open(msgparacli,O_WRONLY);
			printf("%s",msgparacli);
			int xa= write(fopenff,&mensag,sizeof(MSG));
			close(fopenff);
		}
	}else if(res>0 && FD_ISSET(fifm,&fds)){
		int n=read(fifm,&mensag,sizeof(MSG));
		printf("%d",mensag.pid);
		sprintf(msgparacli,FIFO_CLIC,mensag.pid);
		fopenff=open(msgparacli,O_WRONLY);
		//strcpy(mensag.mensagem,"inicia");
		mensag.pid=m.id_medico;
		int xa= write(fopenff,&mensag,sizeof(MSG));
		printf("Comunicacao estabelecida com o cliente");
		close(fopenff);
	}else if(res>0 && FD_ISSET(op,&fds)){
		int x=read(fopenff,&mensag,sizeof(MSG));
		//printf("%s",mensag.mensagem);
		if(strcmp(mensag.mensagem,"inicia")==0){
			printf("Entrei");
			strcpy(mensag.mensagem,"teste");
			pidRecebido = mensag.pid;
			fflush(stdout); 
		}else{
		//if(validacao==1){
			printf("Mensagem recebida: %s",mensag.mensagem);

		//}
		}
	}
	
	
	}while(strcmp(cmd,"sair")!=0);
	close(fd);
	//close(fd_mc);
}
}