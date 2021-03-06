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

	char resposta[100] = "Qualquer Coisa!";
	char destinIP[10];
	int port;

	int socketlocal = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP), slen = sizeof(socketlocal);

	if( socketlocal == -1){
	  	cout << "Erro ao criar socket!" << endl;
	  	return 1;
	}


	struct sockaddr_in destino;
	struct sockaddr_in local_address;
	struct sockaddr_in teste;


	local_address.sin_family = AF_INET; 
	local_address.sin_port = htons(1234); 
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(&local_address.sin_zero, 0, sizeof(local_address.sin_zero));  //preencehe o resto com 0

	// bind e checagem 
/*
	if(bind(socketlocal, (struct sockaddr *) &local_address, sizeof(local_address)) == -1 ) {

		cout << "Falha na funcao Bind()" << endl;
		return 1;
	}

*/

	//interaçao com o usuario

	cout << "Digite o endereco IP do Host Remoto:" << endl;
	cin >> destinIP;

	cout << "Digite a porta para tentativa de conexão" << endl;
	cin >> port;
	
	//preenchendo informaçoes 

	destino.sin_family = AF_INET; 
	destino.sin_port = htons(port); 
	destino.sin_addr.s_addr = inet_addr(destinIP);

	memset(&destino.sin_zero, 0, sizeof(destino.sin_zero));  //preencehe o resto com 0 




	cout << "Tentando se conectar .. " << endl;

	
	sendto(socketlocal, resposta, sizeof(resposta), 0, (struct sockaddr *) &destino, sizeof(destino));

	recvfrom(socketlocal, resposta, 100, 0, (struct sockaddr *) &teste, (socklen_t *) &slen);

	cout << resposta << endl;



	close(socketlocal);

	return 0; 
}