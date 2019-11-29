#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admcrud.h"
#include "login.h"
#include "index.h"

void cadastraAdministrador(void) {
  fflush(stdin);
  Administrador* adm;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO ADM ##########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  adm = (Administrador*) malloc(sizeof(Administrador));
  printf("Informe o nome do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->nome);
  getchar();
  printf("Informe o username do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->username);
  getchar();
  printf("Informe o email do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->email);
  getchar();
  printf("Informe o telefone do administrador: \n>>> ");
  scanf(" %14[^\n]", adm->telefone);
  getchar();
  do{
  printf("Informe o cpf do administrador: \n>>> ");
  scanf(" %14[^\n]", adm->cpf);
  getchar();
  }while(existAdm(adm->cpf));
  adm->status = '1';
  printf("###############################\n");
  exibeAdministrador(adm);
  printf("###############################\n");
  gravaAdministrador(adm);
  fflush(stdin);
  
}

void cadastraAdministradorInicial(Usuario* user){
  fflush(stdin);
  int achou;
  FILE* fp;
  Administrador* adm;  
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO ADM ##########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  adm = (Administrador*) malloc(sizeof(Administrador));
  printf("Informe o nome do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->nome);
  getchar();
  printf("Informe o email do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->email);
  getchar();
  printf("Informe o telefone do administrador: \n>>> ");
  scanf(" %14[^\n]", adm->telefone);
  getchar();
  printf("Informe o cpf do administrador: \n>>> ");
  scanf(" %14[^\n]", adm->cpf);
  getchar();  
  adm->status = '1';
  fp = fopen("usuario.dat", "r+b");
  strcpy(adm->username, user->username);
  user->cadastroFisico = '1';
  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
  if ((strcmp(user->username, adm->username) == 0) && (adm->status == '1')) {
    fseek(fp, -1*sizeof(Usuario), SEEK_CUR);
    fwrite(user, sizeof(Usuario), 1, fp);  
    achou = 1;
  }
  }
  free(user);
  fclose(fp);

  printf("###############################\n");
  exibeAdministrador(adm);
  printf("###############################\n");
  gravaAdministrador(adm);
  
  fflush(stdin);
  menuAdministrativo();
}

void gravaAdministrador(Administrador* adm) {
  FILE* fp;
  fp = fopen("administrador.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(adm, sizeof(Administrador), 1, fp);
  fclose(fp);
}

void exibeAdministrador(Administrador* adm) {
  printf("Nome: %s\n", adm->nome);
  printf("Email: %s\n", adm->email);
  printf("Username: %s\n", adm->username);
  printf("Telefone: %s\n", adm->telefone);
  printf("Cpf: %s\n", adm->cpf);
  printf("Status: %c\n", adm->status);
  getchar();
  printf("\n");
}

void editaAdministrador(void) {
  FILE* fp;
  Administrador* adm;
  int achou;
  char resp;
  char procurado[11];
  fp = fopen("administrador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR ADM ############\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o CPF do administrador a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  adm = (Administrador*) malloc(sizeof(Administrador));
  achou = 0;
  while((!achou) && (fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, procurado) == 0) && (adm->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibeAdministrador(adm);
    getchar();
    printf("Deseja realmente editar este administrador (s/n)? ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("O que você deseja editar?. (1) nome\n(2) username\n(3) email\n(4) telefone\n(5) cpf\n>>> ");
      scanf(" %c", &resp);
      switch(resp){
        case '1':
        printf("Informe o nome do administrador: ");
        scanf(" %14[^\n]", adm->nome);
        getchar();
        break;
        case '2':
        printf("Informe o username do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->username);
        getchar();
        break;
        case '3':
        printf("Informe o email do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->email);
        getchar();
        break;
        case '4':
        printf("Informe o telefone do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->telefone);
        getchar();
        break;
        case '5':
        do {
        printf("Informe o cpf do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->cpf);
        getchar();
} while(existAdm(adm->cpf));
        
        default:
        printf("Informe o nome do administrador: ");
        scanf(" %14[^\n]", adm->nome);
        getchar();

        printf("Informe o username do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->username);
        getchar();
      
        printf("Informe o email do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->email);
        getchar();
      
        printf("Informe o telefone do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->telefone);
        getchar();
      
        do{
        printf("Informe o cpf do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->cpf);
        getchar();
}while(existAdm(adm->cpf));
        break;
      }
      fseek(fp, -1*sizeof(Administrador), SEEK_CUR);
      fwrite(adm, sizeof(Administrador), 1, fp);
      printf("\nAdministrador editado com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
  } else {
    printf("O administrador %s não foi encontrado...\n", procurado);
  }
  free(adm);
  fclose(fp);
}

void buscaAdministrador(void) {
  FILE* fp;
  Administrador* adm;
  int achou;
  char procurado[15];
  fp = fopen("administrador.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR ADM ############\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do administrador a ser buscado:\n ");
  scanf(" %14[^\n]", procurado);
  getchar();
  adm = (Administrador*) malloc(sizeof(Administrador));
  achou = 0;
  while((!achou) && (fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, procurado) == 0) && (adm->status == '1')) {
     achou = 1;
   }
  }
  fclose(fp);
  if (achou) {
    exibeAdministrador(adm);
  } else {
    printf("O administrador %s não foi encontrado...\n", adm->cpf);
  }
  free(adm);
}

void listaAdministradores(void) {
  FILE* fp;
  Administrador* adm;
  fp = fopen("administrador.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EXIBIR ADM ############\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  adm = (Administrador*) malloc(sizeof(Administrador));
  while(fread(adm, sizeof(Administrador), 1, fp)) {
    if (adm->status == '1') {
      exibeAdministrador(adm);
    }
  }
  fclose(fp);
  free(adm);
}

void excluiAdministrador(void) {
  FILE* fp;
  Administrador* adm;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("administrador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR ADM ###########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do administrador a ser apagado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  adm = (Administrador*) malloc(sizeof(Administrador));
  achou = 0;
  while((!achou) && (fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, procurado) == 0) && (adm->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibeAdministrador(adm);
    printf("Deseja realmente apagar este administrador (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      adm->status = '0';
      fseek(fp, -1*sizeof(Administrador), SEEK_CUR);
      fwrite(adm, sizeof(Administrador), 1, fp);
      printf("\nAdministrador excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O adminitrador %s não foi encontrado...\n", adm->nome);
  }
  fclose(fp);
  free(adm);
}

int existAdm(char cpf_procurado[11]){
  FILE* fp;
  Administrador* adm;
  fp = fopen("administrador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  adm = (Administrador*) malloc(sizeof(Administrador));
  while((fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, cpf_procurado) == 0) && (adm->status == '1')) {
     return 1;
   }
  }
  return 0;
}