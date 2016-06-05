#include "../includes/config.h"
#include "../includes/registro.h"

void menuSolicitacao(){
	int opcao;
	limparTela();
	printf("\n 1 - FAZER NOVA SOLICITACAO");
	printf("\n 2 - CHECAR SITUACAO DAS SOLICITACOES");
	printf("\n 3 - CHECAR SITUACOES FINALIZADAS");
	printf("\n\n OPCAO: ");
	scanf (" %d", &opcao);
	switch(opcao){
		case 1: registroDeSolicitacoes();
			break;
		case 2: checarSolicitacoes();
			break;
		case 3: checarSolicitacoesF();
			break;
	}
	menuSolicitacao();
}

void registroDeSolicitacoes(){
	int codigo = 0;
	time_t t = time(NULL);
	struct tm tm;
	Solicitacao aux;
	Solicitacao solicitacao;
	FILE *file_block;
	FILE *file_solicitacao;
    if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return;
    }
	file_solicitacao = fopen("../DB/solicitacoes.bin", "ab+");
	file_block = fopen("../DB/block.bin", "ab");
	fclose(file_block);
	limparTela();
	while(fread(&aux,sizeof(Solicitacao),1,file_solicitacao) == 1){
		codigo++;
	}
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	codigo++;
	solicitacao.codigoSol = codigo;
	solicitacao.situacao = 'A';
	printf(" NOME DA EMPRESA: ");
	scanf(" %[^\n]s", solicitacao.empresa);
	stringMaiusculo(solicitacao.empresa);
	printf(" NOME DO SETOR: ");
	scanf(" %[^\n]s", solicitacao.setor);
	stringMaiusculo(solicitacao.setor);
	printf(" NOME DO SOLICITANTE: ");
	scanf(" %[^\n]s", solicitacao.solicitante);
	stringMaiusculo(solicitacao.solicitante);
	printf(" TELEFONE DE CONTATO: ");
	scanf(" %[^\n]s", solicitacao.telefone);
	printf(" EMAIL: ");
	scanf(" %[^\n]s", solicitacao.email);
	stringMaiusculo(solicitacao.email);
	printf(" DESCRICAO DO PROBLEMA: \n   ");
	scanf(" %[^\n]s", solicitacao.descricaoProblema);
	stringMaiusculo(solicitacao.descricaoProblema);
	tm = *localtime(&t);
	solicitacao.data.dia = tm.tm_mday;
	solicitacao.data.mes = tm.tm_mon + 1;
	solicitacao.data.ano = tm.tm_year + 1900;
	solicitacao.data.hora = tm.tm_hour;
	solicitacao.data.minuto = tm.tm_min;
	
	if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return;
    }
	file_solicitacao = fopen("../DB/solicitacoes.bin", "ab");
	file_block = fopen("../DB/block.bin", "ab");
	fclose(file_block);
	if(fwrite(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) != 0){
		printf("\n CADASTRADO COM SUCESSO!\n");
	}else{
		printf("\n CADASTRO NAO REALIZADO!\n");
	}
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	menuSolicitacao();
}

void checarSolicitacoes(){
	int encontrou = 0;
	char nomeEmpresa[30];
	char nomeSetor[30];
	char nomeSolicitante[30];
	Solicitacao solicitacao;
	FILE *file_block;
	FILE *file_solicitacao;
    if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return;
    }
    file_block = fopen("../DB/block.bin", "ab");
    fclose(file_block);
	limparTela();
	printf(" DIGITE O NOME DA EMPRESA: ");
	scanf(" %[^\n]s", nomeEmpresa);
	stringMaiusculo(nomeEmpresa);
	printf(" DIGITE O NOME DO SETOR: ");
	scanf(" %[^\n]s", nomeSetor);
	stringMaiusculo(nomeSetor);
	printf(" DIGITE O NOME DO SOLICITANTE: ");
	scanf(" %[^\n]s", nomeSolicitante);
	stringMaiusculo(nomeSolicitante);
	file_solicitacao = fopen("../DB/solicitacoes.bin","ab+");
	while(fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
		if(solicitacao.situacao == 'F' && 
		  (strcmp(nomeEmpresa, solicitacao.empresa) == 0) &&
		  (strcmp(nomeSetor, solicitacao.setor) == 0) &&
		  (strcmp(nomeSolicitante, solicitacao.solicitante) == 0)){
			printf(" SITUACAO: %C\n", solicitacao.situacao);
			printf(" DATA: %d/%d/%d   %d:%d\n", solicitacao.data.dia, solicitacao.data.mes, solicitacao.data.ano, 
												solicitacao.data.hora, solicitacao.data.minuto);
			printf(" NOME DA EMPRESA: %s\n", solicitacao.empresa);
			printf(" SETOR: %s\n", solicitacao.setor);
			printf(" NOME DO SOLICITANTE: %s\n", solicitacao.solicitante);
			printf(" DESCRICAO: \n   %s\n\n", solicitacao.descricaoProblema);
			encontrou = 1;
		}
	}
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	if (!encontrou) printf(" NAO HA NOVAS SOLICITACOES\n");
	pausar();
}

void checarSolicitacoesF(){
	char nomeEmpresa[30];
	char nomeSetor[30];
	char nomeSolicitante[30];
	int encontrou = 0;
	Solicitacao solicitacao;
	FILE *file_block;
	FILE *file_solicitacao;
    if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return;
    }
    file_block = fopen("../DB/block.bin", "ab");
    fclose(file_block);
	limparTela();
	printf(" DIGITE O NOME DA EMPRESA: ");
	scanf(" %[^\n]s", nomeEmpresa);
	stringMaiusculo(nomeEmpresa);
	printf(" DIGITE O NOME DO SETOR: ");
	scanf(" %[^\n]s", nomeSetor);
	stringMaiusculo(nomeSetor);
	printf(" DIGITE O NOME DO SOLICITANTE: ");
	scanf(" %[^\n]s", nomeSolicitante);
	stringMaiusculo(nomeSolicitante);
	file_solicitacao = fopen("../DB/solicitacoes.bin","ab+");
	while(fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
		if(solicitacao.situacao == 'F' && 
		  (strcmp(nomeEmpresa, solicitacao.empresa) == 0) &&
		  (strcmp(nomeSetor, solicitacao.setor) == 0) &&
		  (strcmp(nomeSolicitante, solicitacao.solicitante) == 0)){
			printf(" DATA: %d/%d/%d   %d:%d\n", solicitacao.data.dia, solicitacao.data.mes, solicitacao.data.ano, 
												solicitacao.data.hora, solicitacao.data.minuto);
			printf(" NOME DA EMPRESA: %s\n", solicitacao.empresa);
			printf(" SETOR: %s\n", solicitacao.setor);
			printf(" NOME DO SOLICITANTE: %s\n", solicitacao.solicitante);
			printf(" DESCRICAO: \n   %s\n", solicitacao.descricaoProblema);
			printf(" SOLUCAO: \n   %s\n\n", solicitacao.solucaoProblema);
			encontrou = 1;
		}
	}
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	if (!encontrou) printf(" NAO HA NOVAS SOLICITACOES FINALIZADAS\n");
	pausar();
}

int main(){
	menuSolicitacao();
	return 0;
}
