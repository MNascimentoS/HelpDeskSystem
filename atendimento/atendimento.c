#include "../includes/config.h"
#include "../includes/registro.h"

void menuAtendimento(){
	int opcao;
	limparTela();
	fazerLogin();
	limparTela();
	if(estaLogado){
		printf("\n1 - LISTAR SOLICITACOES AGUARDANDO ATENDIMENTO");
		printf("\n2 - LISTAR SOLICITACOES EM ATENDIMENTO");
		printf("\n3 - LISTAR SOLICITACOES RESOLVIDAS");
		printf("\n4 - SOLUCIONAR PROBLEMA");
		printf("\n\nOPCAO: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1: listarAAtendimento();
				break;
			case 2: listarEAtendimento();
				menuAtendimento();
				break;
			case 3: listarFAtendimento();
				break;
			case 4: solucionarProblema();
				break;
		}
	}
}

void listarAAtendimento(){
	int codigoSol;
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
	file_solicitacao = fopen("../DB/solicitacoes.bin","ab+");
	while(fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
		if(solicitacao.situacao == 'A'){
			printf(" CODIGO: %d\n", solicitacao.codigoSol);
			printf(" DATA: %d/%d/%d   %d:%d\n", solicitacao.data.dia, solicitacao.data.mes, solicitacao.data.ano, 
												solicitacao.data.hora, solicitacao.data.minuto);
			printf(" NOME DA EMPRESA: %s\n", solicitacao.empresa);
			printf(" SETOR: %s\n", solicitacao.setor);
			printf(" NOME DO SOLICITANTE: %s\n", solicitacao.solicitante);
			printf(" EMAIL: %s\n", solicitacao.email);
			printf(" TELEFONE: %s\n", solicitacao.telefone);
			printf(" DESCRICAO: \n   %s\n\n", solicitacao.descricaoProblema);
			encontrou = 1;
		}
	}
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	if (encontrou){
		printf(" DIGITE O CODIGO DA SOLICITACAO QUE DESEJA ATENDER: ");
		scanf ("%d", &codigoSol);
		emAtendimento(codigoSol);
		pausar(); 
		menuAtendimento();
	}else{
		printf(" NAO HA NENHUMA SOLICITACAO ESPERANDO ATENDIMENTO.\n");
		pausar();
		menuAtendimento();
	}
	
}

int listarEAtendimento(){
	int encontrou = 0;
	Solicitacao solicitacao;
	FILE *file_block;
	FILE *file_solicitacao;
    if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return 0;
    }
    file_block = fopen("../DB/block.bin", "ab");
    fclose(file_block);
	limparTela();
	file_solicitacao = fopen("../DB/solicitacoes.bin","rb+");
	while(fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
		if(solicitacao.situacao == 'E' && m_codigoFun == solicitacao.codigoFun){
			printf(" CODIGO: %d\n", solicitacao.codigoSol);
			printf(" DATA: %d/%d/%d   %d:%d\n", solicitacao.data.dia, solicitacao.data.mes, solicitacao.data.ano, 
												solicitacao.data.hora, solicitacao.data.minuto);
			printf(" NOME DA DATA: %s\n", solicitacao.empresa);
			printf(" SETOR: %s\n", solicitacao.setor);
			printf(" NOME DO SOLICITANTE: %s\n", solicitacao.solicitante);
			printf(" EMAIL: %s\n", solicitacao.email);
			printf(" TELEFONE: %s\n", solicitacao.telefone);
			printf(" DESCRICAO: \n   %s\n\n", solicitacao.descricaoProblema);
			encontrou = 1;
		}
	}
	
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	file_solicitacao = NULL;
	if (!encontrou){
		printf(" NAO HA NENHUMA SOLICITACAO EM ATENDIMENTO.\n");
		pausar();
		menuAtendimento();
		return 0;
	}else{
		pausar();
		return 1;
	}
}

int listarFAtendimento(){
	int encontrou = 0;
	Solicitacao solicitacao;
	FILE *file_block;
	FILE *file_solicitacao;
    if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return 0;
    }
    file_block = fopen("../DB/block.bin", "ab");
    fclose(file_block);
	limparTela();
	file_solicitacao = fopen("../DB/solicitacoes.bin","ab+");
	while(fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
		if(solicitacao.situacao == 'F'){
			printf(" CODIGO: %d\n", solicitacao.codigoSol);
			printf(" DATA: %d/%d/%d   %d:%d\n", solicitacao.data.dia, solicitacao.data.mes, solicitacao.data.ano, 
												solicitacao.data.hora, solicitacao.data.minuto);
			printf(" NOME DA EMPRESA: %s\n", solicitacao.empresa);
			printf(" SETOR: %s\n", solicitacao.setor);
			printf(" NOME DO SOLICITANTE: %s\n", solicitacao.solicitante);
			printf(" EMAIL: %s\n", solicitacao.email);
			printf(" TELEFONE: %s\n", solicitacao.telefone);
			printf(" DESCRICAO DO PROBLEMA: \n   %s\n", solicitacao.descricaoProblema);
			printf(" DESCRICAO DA SOLUCAO: \n   %s\n\n", solicitacao.solucaoProblema);
			encontrou = 1;
		}
	}
	
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	file_solicitacao = NULL;
	if (encontrou){
		pausar();
		menuAtendimento();
		return 1;
	}else{
		printf(" NAO HA NENHUMA SOLICITACAO FINALIZADA.\n");
		pausar();
		menuAtendimento();
		return 0;
	}
	
}

int emAtendimento(int codigoSol){
	char opcao;
	int encontrou = 0;
	Solicitacao solicitacao;
	FILE *file_block;
	FILE *file_solicitacao;
    if ((file_block = fopen("../DB/block.bin", "r"))){
        fclose(file_block);
        printf("O ARQUIVO ESTA EM USO");
        return 0;
    }
    file_block = fopen("../DB/block.bin", "ab");
    fclose(file_block);
	file_solicitacao = fopen("../DB/solicitacoes.bin","rb+");
	if(fseek(file_solicitacao, sizeof(Solicitacao)*(codigoSol-1), SEEK_SET) == 0){
		if (fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
			fseek(file_solicitacao, sizeof(Solicitacao)*(codigoSol-1), SEEK_SET);
			if(solicitacao.situacao == 'A'){
				solicitacao.situacao = 'E';
				solicitacao.codigoFun = m_codigoFun;
				printf(" DESEJA SOLUCIONAR O PROBLEMA (s/n): ");
				scanf(" %c", &opcao);
				opcao = toupper(opcao);
				if(opcao != 'N'){
					printf(" DIGITE A SOLUCAO DO PROBLEMA: \n\t");
					scanf(" %[^\n]s", solicitacao.solucaoProblema);
					solicitacao.situacao = 'F';
				}
				encontrou = 1;
				fwrite(&solicitacao,sizeof(Solicitacao),1,file_solicitacao);
			}else{
				printf(" A SOLICITACAO NAO ESTA AGUARDANDO ATENDIMENTO!\n");
			}
		}else{
			printf(" CODIGO INVALIDO!\n");
		}
	}
	fclose(file_solicitacao);
	remove("../DB/block.bin");
	if (!encontrou) return 0;
	return 1;	
}

void solucionarProblema(){
	int codigoSol;
	Solicitacao solicitacao;
	limparTela();
	printf ("\n\t ESTAS SAO AS SOLICITACOES EM ATENDIMENTO \n");
	if (listarEAtendimento()){
		printf(" QUAL O PROBLEMA DESEJA SOLUCIONAR? \n");
		printf(" CODIGO DA SOLICITACAO: ");
		scanf("%d", &codigoSol);
		limparTela();
		FILE *file_block;
		FILE *file_solicitacao;
		if ((file_block = fopen("../DB/block.bin", "r"))){
			fclose(file_block);
			printf("O ARQUIVO ESTA EM USO");
			return;
		}
		file_block = fopen("../DB/block.bin", "ab");
		fclose(file_block);
		file_solicitacao = fopen("../DB/solicitacoes.bin","rb+");
		if(fseek(file_solicitacao, sizeof(Solicitacao)*(codigoSol-1), SEEK_SET) == 0){
			if (fread(&solicitacao,sizeof(Solicitacao),1,file_solicitacao) == 1){
				fseek(file_solicitacao, sizeof(Solicitacao)*(codigoSol-1), SEEK_SET);
				if(solicitacao.situacao == 'E'){ 
					if(solicitacao.codigoFun == m_codigoFun){
						printf(" DIGITE A SOLUCAO DO PROBLEMA: \n\t");
						scanf(" %[^\n]s", solicitacao.solucaoProblema);
						stringMaiusculo(solicitacao.solucaoProblema);
						solicitacao.codigoFun = m_codigoFun;
						solicitacao.situacao = 'F';
					}else{
						printf(" CODIGO DO FUNCIONARIO INVALIDO!");
					}
				}else{
					printf(" ESTA SOLICITACAO NAO ESTA EM ATENDIMENTO! ");
				}
				fwrite(&solicitacao,sizeof(Solicitacao),1,file_solicitacao);
			}
		}
		fclose(file_solicitacao);
		remove("../DB/block.bin");
	}
	menuAtendimento();
}

int main(){
	menuAtendimento();
	return 0;
}

