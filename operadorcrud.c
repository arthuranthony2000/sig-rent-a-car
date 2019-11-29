#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operadorcrud.h"
#include "index.h"



void cadastraOperador(void) {
  fflush(stdin);
  Operador* ope;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO OPERADOR #####\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ope = (Operador*) malloc(sizeof(Operador));
  printf("Informe o nome do operador: \n>>> ");
  scanf(" %39[^\n]", ope->nome);
  getchar();
  
  printf("Informe o email do operador: \n>>> ");
  scanf(" %39[^\n]", ope->email);
  getchar();



  printf("Informe o telefone do operador: \n>>> ");
  scanf(" %39[^\n]", ope->telefone);
  getchar();



  printf("Informe o cpf do operador: \n>>> ");
  scanf(" %14[^\n]", ope->cpf);
  getchar();

  ope->status = '1';
  printf("###############################\n");
  exibeOperador(ope);
  printf("###############################\n");
  gravaOperador(ope);
  fflush(stdin);
  free(ope);
}

void cadastraOperadorInicial(Usuario* user){
  fflush(stdin);
  int achou;
  Operador* ope;
  FILE* fp;  
  
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO OPERADOR #####\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ope = (Operador*) malloc(sizeof(Operador));
  printf("Informe o nome do Operador: \n>>> ");
  scanf(" %39[^\n]", ope->nome);
  getchar();
  printf("Informe o email do Operador: \n>>> ");
  scanf(" %39[^\n]", ope->email);
  getchar();
  printf("Informe o telefone do Operador: \n>>> ");
  scanf(" %14[^\n]", ope->telefone);
  getchar();
  printf("Informe o cpf do Operador: \n>>> ");
  scanf(" %14[^\n]", ope->cpf);
  getchar();  
  ope->status = '1';
  fp = fopen("usuario.dat", "r+b");
  strcpy(user->username , ope->username);
  user->cadastroFisico = '1';
  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
  if ((strcmp(user->username, ope->username) == 0) && (ope->status == '1')) {
    fseek(fp, -1*sizeof(Usuario), SEEK_CUR);
    fwrite(user, sizeof(Usuario), 1, fp);  
    achou = 1;
  }
  }
  free(user);
  fclose(fp);
  printf("###############################\n");
  exibeOperador(ope);
  printf("###############################\n");
  gravaOperador(ope);
   
  fflush(stdin);
  menuOperativo();
}


void gravaOperador(Operador* ope) {
  FILE* fp;
  fp = fopen("operador.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(ope, sizeof(Operador), 1, fp);
  fclose(fp);
}

void exibeOperador(Operador* ope) {
  printf("Nome: %s\n", ope->nome);
  printf("Email: %s\n", ope->email);
  printf("Telefone: %s\n", ope->telefone);
  printf("Cpf: %s\n", ope->cpf);
  printf("Status: %c\n", ope->status);
  getchar();
  printf("\n");
}

void editaOperador(void) {
  FILE* fp;
  Operador* ope;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("operador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR OPERADOR #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o CPF do Operador a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  ope = (Operador*) malloc(sizeof(Operador));
  achou = 0;
  while((!achou) && (fread(ope, sizeof(Operador), 1, fp))) {
   if ((strcmp(ope->cpf, procurado) == 0) && (ope->status == '1')) {
     achou = 1;
   }
  if (achou) {
    exibeOperador(ope);
    getchar();
    printf("Deseja realmente editar este Operador (s/n)? ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("Informe o nome do Operador: ");
      scanf(" %14[^\n]", ope->nome);
      printf("Informe o email do operador: \n>>> ");
      scanf(" %39[^\n]", ope->email);
      getchar();
      
      
      printf("Informe o telefone do operador: \n>>> ");
      scanf(" %39[^\n]", ope->telefone);
      getchar();
      
      
      
      printf("Informe o cpf do operador: \n>>> ");
      scanf(" %14[^\n]", ope->cpf);
      getchar();
    
      ope->status = '1';
      fseek(fp, -1*sizeof(Operador), SEEK_CUR);
      fwrite(ope, sizeof(Operador), 1, fp);
      printf("\nOperador editado com sucesso!!!\n");
      }else {
      printf("\nOk, os dados não foram alterados\n");
      }
    }else {
      printf("O Operador %s não foi encontrado...\n", procurado);
    }
  free(ope);
  fclose(fp);
  }
}

void buscaOperador(void){
  FILE* fp;
  Operador* ope;
  int achou;
  char procurado[15];
  fp = fopen("operador.dat", "rb");
  if (fp == NULL){
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR OPERADOR #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do operador a ser buscado:\n ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ope = (Operador*) malloc(sizeof(Operador));
  achou = 0;

  while((!achou) && (fread(ope, sizeof(Operador), 1, fp))) {
    if ((strcmp(ope->cpf, procurado) == 0) && (ope->status == '1')) {
      achou = 1;
    }
  }
  
  if (achou) {
    exibeOperador(ope);
  } else {
    printf("O operador %s não foi encontrado...\n", ope->nome);
  }
  free(ope);
  fclose(fp);
}

void listaOperador(void) {
  FILE* fp;
  Operador* ope;
  fp = fopen("operador.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU LISTAR OPERADOR #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ope = (Operador*) malloc(sizeof(Operador));
  while(fread(ope, sizeof(Operador), 1, fp)) {
    if (ope->status == '1') {
      exibeOperador(ope);
    }
  }
  fclose(fp);
  free(ope);
}

void excluiOperador(void) {
  FILE* fp;
  Operador* ope;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("operador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR OPERADOR ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do operador a ser apagado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ope = (Operador*) malloc(sizeof(Operador));
  achou = 0;
  while((!achou) && (fread(ope, sizeof(Operador), 1, fp))) {
   if ((strcmp(ope->cpf, procurado) == 0) && (ope->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibeOperador(ope);
    printf("Deseja realmente apagar este operador (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      ope->status = '0';
      fseek(fp, -1*sizeof(Operador), SEEK_CUR);
      fwrite(ope, sizeof(Operador), 1, fp);
      printf("\nOperador excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O operador %s não foi encontrado...\n", ope->nome);
  }
  fclose(fp);
  free(ope);
}

int existOperador(char cpf_procurado[11]){
  FILE* fp;
  Operador* ope;
  fp = fopen("operador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  ope = (Operador*) malloc(sizeof(Operador));
  while((fread(ope, sizeof(Operador), 1, fp))) {
   if ((strcmp(ope->cpf, cpf_procurado) == 0) && (ope->status == '1')) {
     return 1;
   }
  }
  return 0;
}