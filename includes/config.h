#ifndef CONFIG_H
#define CONFIG_H

#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef
struct Login{
	int codigoFun;
	int senhaFun;
}Login;

int m_codigoFun;
int estaLogado = 0;

int checkSO(){
	#ifdef __unix__
		return 0;
	#elif defined(_WIN32) || defined(WIN32)
		return 1;
	#endif
}

void limparTela(){
	int SO;
	SO = checkSO();
	if(SO==0) system("clear");
	else system("cls");
	return;
}

void stringMaiusculo(char *string) { 
	while(*string) { 
		*string=toupper(*string); 
		string++; 
	} 
} 

void pausar(){
	if(checkSO())
		system("pause");
	else
		system("read -p \" PRESSIONE ENTER\" SAINDO");
}

void marca(){
	printf("\t\t      _____________________");
	printf("\n\t\t      ______Help Desk______");
	printf("\n\t\t      _____________________\n\n");
}

void fazerLogin(){
	if(!estaLogado){
		int opcao, i, encontrou = 0;
		int codigoFun;
		char senhaFun[10];
		int senhaCript;
		int tam;
		Login login, aux;
		FILE *file_login;
		limparTela();
		printf("\t\t      _____________________");
		printf("\n\t\t      ________Login________");
		printf("\n\t\t      _____________________\n\n");
		printf("\t\t1 - CADASTRAR NOVO FUNCIONARIO\n");
		printf("\t\t2 - FAZER LOGIN\n");
		printf("\n\t\tOpcao: ");
		scanf (" %d", &opcao);
		while(opcao != 1 && opcao != 2){
			printf(" OPCAO INVALIDA!\n");
			printf(" OPCAO: ");
			scanf (" %d", &opcao);
		}
		if(opcao == 1){
			printf("\n      DIGITE UM NUMERO PARA SER SEU NUMERO DE FUNCIONARIO: ");
			scanf(" %d", &aux.codigoFun);
			printf("      DIGITE UMA SENHA: ");
			scanf (" %s", senhaFun);
			tam = strlen(senhaFun);
			for(i=0;i<tam;i++){
				senhaCript += (int) senhaFun[i];
				senhaCript *= 10;
			}
			aux.senhaFun = senhaCript;
			file_login = fopen("../DB/login.bin", "ab+");
			while(fread(&login,sizeof(Login),1,file_login) == 1){
				if (login.codigoFun == aux.codigoFun){
					encontrou = 1;
				}
			}
			fclose(file_login);
			file_login = fopen("../DB/login.bin", "ab+");
			if(!encontrou){
				if (fwrite(&aux,sizeof(Login),1,file_login) != 0){
					printf("\n      CADASTRO REALIZADO COM SUCESSO!\n");
					m_codigoFun = aux.codigoFun;
					estaLogado = 1;
				}
			}
			fclose(file_login);
		}else if(opcao == 2){
			printf("\n\t      DIGITE O SEU CODIGO DE FUNCIONARIO: ");
			scanf(" %d", &codigoFun);
			printf("\t      DIGITE SUA SENHA: ");
			scanf (" %s", senhaFun);
			tam = strlen(senhaFun);
			for(i=0;i<tam;i++){
				senhaCript += (int) senhaFun[i];
				senhaCript *= 10;
			}
			file_login = fopen("../DB/login.bin", "rb+");
			while(fread(&login,sizeof(Login),1,file_login) == 1){
				if (login.codigoFun == codigoFun && login.senhaFun == senhaCript){
					m_codigoFun = codigoFun;
					estaLogado = 1;
				}else{
					printf("\t      O CODIGO E A SENHA NAO COINCIDEM\n");
				}
			}
			fclose(file_login);
		}
	}
}

#endif
