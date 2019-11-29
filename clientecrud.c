#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientecrud.h"

void cadastraCliente(void) {
  fflush(stdin);
  Cliente* clien;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO CLIENTE ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  clien = (Cliente*) malloc(sizeof(Cliente));
  printf("Informe o nome do Cliente: \n>>> ");
  scanf(" %39[^\n]", clien->nome);
  getchar();
  
  printf("Informe o email do cliente: \n>>> ");
  scanf(" %39[^\n]", clien->email);
  getchar();

  printf("Informe o telefone do cliente: \n>>> ");
  scanf(" %14[^\n]", clien->telefone);
  getchar();
  do{
  printf("Informe o cpf do cliente: \n>>> ");
  scanf(" %14[^\n]", clien->cpf);
  getchar();
  }while(existClient(clien->cpf));
  clien->status = '1';
  printf("###############################\n");
  exibeCliente(clien);
  printf("###############################\n");
  gravaCliente(clien);
  fflush(stdin);
}

void gravaCliente(Cliente* clien) {
  FILE* fp;
  fp = fopen("cliente.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  } 
  fwrite(clien, sizeof(Cliente), 1, fp);
  fclose(fp);
}

void editaCliente(void) {
  FILE* fp;
  Cliente* clien;
  int achou;
  char resp;
  char procurado[11];
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR CLIENTE ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o CPF do Cliente a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  clien = (Cliente*) malloc(sizeof(Cliente));
  achou = 0;
  while((!achou) && (fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, procurado) == 0) && (clien->status == '1')) {
     achou = 1;
   }
  if (achou) {
    exibeCliente(clien);
    printf("Deseja realmente editar este Cliente (s/n)? ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("O que você deseja editar?. \n(1) nome\n(2) email\n(3) telefone\n(4) cpf\n>>> ");
      scanf(" %c", &resp);
      switch(resp){
        case '1':
        printf("Informe o nome do cliente: ");
        scanf(" %39[^\n]", clien->nome);
        break;
        case '2':
        printf("Informe o email do cliente: \n>>> ");
        scanf(" %39[^\n]", clien->email);
        break;
        case '3':
        printf("Informe o telefone do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->telefone);
        break;
        case '4':
        do{
        printf("Informe o cpf do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->cpf); 
        getchar();
        }while(existClient(clien->cpf));
        default:
        printf("Informe o nome do cliente: ");
        scanf(" %39[^\n]", clien->nome);
        getchar();

        printf("Informe o email do cliente: \n>>> ");
        scanf(" %39[^\n]", clien->email);
        getchar();
      
        printf("Informe o telefone do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->telefone);
        getchar();
        do{
        printf("Informe o cpf do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->cpf); 
        getchar();
        }while(existClient(clien->cpf));
        break;
      }

      getchar();
      clien->status = '1';
      fseek(fp, -1*sizeof(Cliente), SEEK_CUR);
      fwrite(clien, sizeof(Cliente), 1, fp);
      printf("\nCliente editado com sucesso!!!\n");
      } else {
      printf("\nOk, os dados não foram alterados\n");
      }    
    }else {
      printf("O Cliente %s não foi encontrado...\n", clien->nome);
    }
  free(clien);
  fclose(fp);
  }
}


void exibeCliente(Cliente* clien){

  printf("Nome: %s\n", clien->nome);
  printf("Email: %s\n", clien->email);
  printf("Telefone: %s\n", clien->telefone);
  printf("Cpf: %s\n", clien->cpf);
  printf("Status: %c\n", clien->status);
  getchar();
  printf("\n");
}

void buscaCliente(void) {
  FILE* fp;
  Cliente* clien;
  int achou;
  char procurado[15];
  fp = fopen("cliente.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR CLIENTE ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do Cliente a ser buscado:\n ");
  scanf(" %14[^\n]", procurado);
  getchar();
  clien = (Cliente*) malloc(sizeof(Cliente));
  achou = 0;
  while((!achou) && (fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, procurado) == 0) && (clien->status == '1')) {
     achou = 1;
   }
  fclose(fp);
  if (achou) {
    exibeCliente(clien);
  } else {
    printf("O Cliente %s não foi encontrado...\n", clien->nome);
  }
  free(clien);
  }
}
void listaClientes(void) {
  FILE* fp;
  Cliente* clien;
  fp = fopen("cliente.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EXIBIR CLIENTE ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  clien = (Cliente*) malloc(sizeof(Cliente));
  while(fread(clien, sizeof(Cliente), 1, fp)) {
    if (clien->status == '1') {
      exibeCliente(clien);
    }
  }
  getchar();
  fclose(fp);
  free(clien);
}

void excluiCliente(void) {
  FILE* fp;
  Cliente* clien;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR CLIENTE #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do Cliente a ser apagado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  clien = (Cliente*) malloc(sizeof(Cliente));
  achou = 0;
  while((!achou) && (fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, procurado) == 0) && (clien->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibeCliente(clien);
    printf("Deseja realmente apagar este Cliente (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      clien->status = '0';
      fseek(fp, -1*sizeof(Cliente), SEEK_CUR);
      fwrite(clien, sizeof(Cliente), 1, fp);
      printf("\nCliente excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O clieninitrador %s não foi encontrado...\n", clien->nome);
  }
  fclose(fp);
  free(clien);
}

int existClient(char cpf_procurado[11]){
  FILE* fp;
  Cliente* clien;
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  clien = (Cliente*) malloc(sizeof(Cliente));
  while((fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, cpf_procurado) == 0) && (clien->status == '1')) {
     return 1;
   }
  }
  return 0;
}