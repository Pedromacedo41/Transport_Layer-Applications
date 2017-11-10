#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <thread>
#include <arpa/inet.h>
#include <string.h>    //funcao memset
#define BFLEN 100


using namespace std;

//declaracao das variaveis globais


char resposta[BFLEN] = "", resposta2[BFLEN],  destinIP[15];   // le a string do endereco IP
int socketlocal;  
int port; // le a porta destino
bool flag =true;
string Resposta;
struct sockaddr_in local_address; 
struct sockaddr_in remote_address;

int slen = sizeof(remote_address), opcao;



void ler(string userA) {
	while(1){
		recvfrom(socketlocal, resposta, BFLEN, 0, (struct sockaddr *) &remote_address, (socklen_t *) &slen);
		cout << userA << " : " << resposta << endl;
	}

}



void escrever(string userA) {
	string auxiliar;
	while(1){
		cin >> resposta2;
		sendto(socketlocal, resposta2, sizeof(resposta), 0, (struct sockaddr *) &remote_address, sizeof(remote_address));
    }

}

void barra(){

	cout << "------------------------------------------------------------------" <<endl;
}


int main(void){

	socketlocal = socket(AF_INET, SOCK_DGRAM	, IPPROTO_UDP);  
	//verificaca a criacao do socket 

	if( socketlocal == -1){
	  	cout << "Erro ao criar socket!" << endl;
	  	return 1;
	}

	cout << "Aguardar conexao (1) ou iniciar uma conexao (2) :" ;
	cin >> opcao;

	local_address.sin_family = AF_INET; 
	local_address.sin_port = htons(1234+opcao);                          //a porta usada para conexao sera 1235,1236
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&local_address.sin_zero, 0, sizeof(local_address.sin_zero));  //preencehe o resto com 0 

	// bind e checagem 

	if(bind(socketlocal, (struct sockaddr *) &local_address, sizeof(local_address)) == -1 ) {

		cout << "Falha na funcao Bind()" << endl;
		return 1;
	}


	if(opcao==1){


		cout << "Aguardando conexao ..." << endl; 

		int bytes= recvfrom(socketlocal, resposta, BFLEN, 0, (struct sockaddr *) &remote_address, (socklen_t *) &slen);
		cout << "Pedro se conectou ao Chat" << endl;
		strcpy(resposta, "Conectado a XAAN\n");
		sendto(socketlocal, resposta, sizeof(resposta), 0, (struct sockaddr *) &remote_address, sizeof(remote_address));

		thread leitura (ler, "Pedro");
		thread escrita (escrever, "XAAN : ");
		thread barr (barra);

		leitura.join();
		escrita.join();
		barr.join();


		
	}
	else{

		//interaçao com o usuario
		cout << "Digite o endereco IP do Host Remoto:" ; 
		cout << "(E preciso que a outra maquina esteja em espera)" << endl; 
		cin >> destinIP;

		port=1235;
		
		//preenchendo informaçoes 
		remote_address.sin_family = AF_INET; 
		remote_address.sin_port = htons(port); 
		remote_address.sin_addr.s_addr = inet_addr(destinIP);

		memset(&remote_address.sin_zero, 0, sizeof(remote_address.sin_zero));  //preencehe o resto com 0 

		cout << "Tentando se conectar .. " << endl;	
 
 		
		sendto(socketlocal, resposta, sizeof(resposta), 0, (struct sockaddr *) &remote_address, sizeof(remote_address));

		recvfrom(socketlocal, resposta, BFLEN, 0, (struct sockaddr *) &remote_address, (socklen_t *) &slen);
		cout << resposta << endl;


		if(resposta == ""){ cout << "Nao houve resposta a sua solicitacao " << endl ;   //caso nao haja conexao
		}

		else{

			thread escrita (escrever, "Pedro : ");
			thread leitura (ler, "XAAN");
			thread barr (barra);
			
			escrita.join();
			leitura.join();
			barr.join();
		    

			
		}
		
	}


	return 0;

}