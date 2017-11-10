#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>    //funcao memset


using namespace std;


int main(void){

	char resposta[100];
	int socketlocal  = socket(AF_INET, SOCK_STREAM	, 0);
	int socketcliente;

	//verificaca a criacao do socket 

	if( socketlocal == -1){
	  	cout << "Erro ao criar socket!" << endl;
	  	return 1;
	}



	struct sockaddr_in local_address; 
	struct sockaddr_in remote_address;


	local_address.sin_family = AF_INET; 
	local_address.sin_port = htons(1234); 
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(&local_address.sin_zero, 0, sizeof(local_address.sin_zero));  //preencehe o resto com 0 


	// bind e checagem 

	if(bind(socketlocal, (struct sockaddr *) &local_address, sizeof(local_address)) == -1 ) {

		cout << "Falha na funcao Bind()" << endl;
		return 1;
	}


	// listen com tamanho da fila 1
	
	if(listen(socketlocal,1) == -1) {
  		cout << "Falha na funcao listen()" << endl;
  		return 1;
  	}
  	

  	cout << "Aguardando conexoes ... " << endl; 

  	socketcliente = accept(socketlocal, 0, 0);

  	if( socketlocal == -1){
  		cout << "Erro na funcao accept" <<endl; 
  	}

  	cout << "Conectado a Xaan!" << endl; 

  	int bytes = recv(socketcliente,resposta,100,0);



  	if(bytes==-1){
  		cout << "Erro ao receber Dados" << endl; 
  	}else{
  		cout << "Xaan: " << resposta << endl;
  	}


	close(socketlocal);


	return 0; 
}







