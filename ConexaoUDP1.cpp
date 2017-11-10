#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <string.h>    //funcao memset


using namespace std;


int main(void){

	char resposta[100];
	int socketlocal  = socket(AF_INET, SOCK_DGRAM	, IPPROTO_UDP);
	
	socklen_t buffer;

	//verificaca a criacao do socket 

	if( socketlocal == -1){
	  	cout << "Erro ao criar socket!" << endl;
	  	return 1;
	}

	struct sockaddr_in local_address; 
	struct sockaddr_in remote_address;

	int socketcliente, slen = sizeof(remote_address);

	local_address.sin_family = AF_INET; 
	local_address.sin_port = htons(1234); 

	local_address.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(&local_address.sin_zero, 0, sizeof(local_address.sin_zero));  //preencehe o resto com 0 


	// bind e checagem 

	if(bind(socketlocal, (struct sockaddr *) &local_address, sizeof(local_address)) == -1 ) {

		cout << "Falha na funcao Bind()" << endl;
		return 1;
	}




	cout << "Eu espero conexao? " << endl; 

	int bytes= recvfrom(socketlocal, resposta, 100, 0, (struct sockaddr *) &remote_address, (socklen_t *) &slen);
	strcpy(resposta, "Recebido");

	sendto(socketlocal, resposta, sizeof(resposta), 0, (struct sockaddr *) &remote_address, sizeof(remote_address));

	cout << resposta << endl;


	return 0;

}