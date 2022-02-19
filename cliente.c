#include "balcao.h"

//int server_fifo_fd, client_fifo_fd;
//char *client_Path;

void desistir(int d){
	printf("O cliente saiu.");
	exit(0);
}

void fila_cheia(int fc){
	printf("O Sistema atingiu a sua lotacao maxima. Por favor dirija-se a outra unidade medica ou tente de novo mais tarde.");
	exit(0);
}

int main(int argc, char *argv[]){
	Cliente c;
	MSG mensag;
	int pidRecebido=0;
	char str[40];
	char nomefifo[40];
	char comando[40];
	char clientecom[40];
	int fdboth;
	signal(SIGUSR1, fila_cheia);
	signal(SIGUSR2,desistir);
	fd_set fds;
	struct timeval tempo = {5,0};
	int estado,n,numero;
	int fd_comunicacao;
	int validacao=0;
	float res;
	if(argc!=2){
		printf("Erro. Nr de args. \n");
		printf("	./cliente <\"Nome\"> \n");
	}
	else{

	if(access(FIFO_SERV, F_OK) != 0){
		printf("[ERRO] O fifo ainda nao existe!\n");
		exit(1);
   	}
     //CRIAR O FIFO...
	 strcpy(c.nome,argv[1]);
	c.numero_senha=getpid();
	//FIFO para Cliente
	sprintf(nomefifo,FIFO_CLI,c.numero_senha);
	mkfifo(nomefifo,0700);
	int fd_cli=open(nomefifo,O_RDWR);
	//FIFO para Mensagem do Cliente
	sprintf(str,FIFO_CLIC,c.numero_senha);
	mkfifo(str,0700);
	int fd_climsg=open(str,O_RDWR);
	 printf("Criei o fifo...\n");

   //ABRIR O FIFO...
   int fd = open(FIFO_SERV, O_WRONLY);     // O_RDONLY
   printf("Abri o fifo...\n");
   /*do{
	FD_ZERO(&fds);
	FD_SET(0, &fds);	//TECLADO
	FD_SET(fd,&fds);	//FIFO
	tempo.tv_sec=5;
	tempo.tv_usec=0;
	res=select(fd+1,&fds,NULL,NULL,&tempo);*/
	   
   
	printf("Introduza os seus sintomas: ");
	scanf(" %[^\n]",c.sintomas);
	if(strcmp(c.sintomas,"#fim")==0){
		exit(0);
	}
	n = write(fd, &c, sizeof(Cliente));
	//int fd_retorno=open(str,O_RDONLY);
	//n=read(fd_retorno, &c, sizeof(Cliente));
	
	do{
	FD_ZERO(&fds);
	FD_SET(0, &fds);	//TECLADO
	FD_SET(fd_cli,&fds);	//FIFO
	FD_SET(fd_climsg,&fds);
	tempo.tv_sec=5;
	tempo.tv_usec=0;
	fdboth=(fd_cli>fd_climsg)? fd_cli:fd_climsg;
	res=select(fdboth+1,&fds,NULL,NULL,&tempo);

	if(res==0){
		printf("%d",pidRecebido);

	}else if(res>0 && FD_ISSET(0,&fds)){
		scanf(" %[^\n]",comando);
		if(strcmp(comando,"adeus")==0){
			printf("Vou sair");
			
		}else{
			strcpy(mensag.mensagem,comando);
			sprintf(clientecom,FIFO_MEDC,pidRecebido);
			mensag.pid=c.numero_senha;
			fd_comunicacao=open(clientecom,O_WRONLY);
			//./clprintf("%s",clientecom);
			int x=write(fd_comunicacao,&mensag,sizeof(MSG));
			close(fd_comunicacao);
		}
	}else if(res>0 && FD_ISSET(fd_cli,&fds)){
    //Espera pela resposta da balcão
    n=read(fd_cli, &c, sizeof(Cliente));
    int nclifrente;
    int nmeddisp;
    nmeddisp=c.prioridade%100;
    c.prioridade=c.prioridade/100;
    nclifrente=c.prioridade%10;
    c.prioridade=c.prioridade/10;
    printf("Deve dirigir-se à especialidade -> %s com nivel %d de prioridade!Tem %d pessoas para serem atendidas primeiro e %d medicos disponiveis.\nAguarde pelo médico especialista. . .\n",c.especialidade,c.prioridade,nclifrente,nmeddisp);
    }
	else if(res>0 && FD_ISSET(fd_climsg,&fds)){
		int n=read(fd_climsg,&mensag,sizeof(MSG));
		if(strcmp(mensag.mensagem,"inicia")==0){
			printf("Conexao estabelecida com o especialista");
			pidRecebido = mensag.pid; 
			//sprintf(clientecom,FIFO_MEDC,mensag.pid);
			//fd_comunicacao=open(clientecom,O_WRONLY);
					//strcpy(mensag.mensagem,"ola");
			//close(fd_comunicacao);
		}
			printf("Mensagem do Medico: %s",mensag.mensagem);
		
	}
	
	}while(strcmp(comando,"adeus")!=0);
   
   close(fd);
	
	unlink(str);

		exit(0);
}
}
