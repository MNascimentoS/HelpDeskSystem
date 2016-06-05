#ifndef REGISTRO_H
#define REGISTRO_H

#define TAM 30
#define TAMDES 500

typedef
struct Data{
	int dia;
	int mes;
	int ano;
	int hora;
	int minuto;
}Data;

typedef
struct Solicitacao{
	/*Solicitante*/
	int codigoSol;
	char empresa[TAM];
	char setor[TAM];
	char solicitante[TAM];
	char email[TAM];
	char descricaoProblema[TAMDES];
	char telefone[TAM];
	Data data;
	/*Atendente*/
	int codigoFun;
	char situacao;
	char solucaoProblema[TAMDES];
}Solicitacao;

void menuSolicitacao();
void registroDeSolicitacoes();
void checarSolicitacoes();
void checarSolicitacoesF();

void menuAtendimento();
void listarAAtendimento();
int listarEAtendimento();
int listarFAtendimento();
void solucionarProblema();
int emAtendimento(int codigoSol);

#endif
