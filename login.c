#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admcrud.h"

void cadastraUsuarioInicial(void) {
  fflush(stdin);
  Usuario* user;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO USUARIO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  user = (Usuario*) malloc(sizeof(Usuario));
  printf("Informe seu nome de usuário: \n>>> ");
  scanf(" %39[^\n]", user->username);
  getchar();
  
  printf("Informe a sua senha: \n>>> ");
  scanf(" %39[^\n]", user->senha);
  getchar();
  user->tipoUsuario = '1'; 
  user->status = '1';
  user->cadastroFisico = '0';
  printf("###############################\n");
  exibeUsuario(user);
  printf("###############################\n");
  gravaUsuario(user);
  cadastraAdministradorInicial(user);

  fflush(stdin);
  free(user);
}

void buscaUsuario(void){
    FILE* fp;
    Usuario* user;
    int achou;
    char procurado[40];
    fp = fopen("usuario.dat", "rb");
    if (fp == NULL) {
      printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
      printf("Não é possível continuar o programa...\n");
      exit(1);
    }
    printf("\n\n");
    printf("####################################\n");
    printf("######  MENU BUSCAR USUARIO ########\n");
    printf("####################################\n");
    printf("######### SIG RENT A CAR ###########\n");
    printf("####################################\n");
    printf("Informe o cpf do Cliente a ser buscado:\n ");
    scanf(" %39[^\n]", procurado);
    getchar();
    user = (Usuario*) malloc(sizeof(Usuario));
    achou = 0;
    while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
    if ((strcmp(user->username, procurado) == 0) && (user->status == '1')) {
      achou = 1;
    }
    fclose(fp);
    if (achou) {
      exibeUsuario(user);
    } else {
      printf("O usuario %s não foi encontrado...\n", user->username);
    }
    free(user);
    }
  }


void editaUsuario(void){
  FILE* fp;
  Usuario* user;
  int achou;
  char resp;
  char procurado[40];
  fp = fopen("usuario.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR USUARIO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o username: ");
  scanf(" %39[^\n]", procurado);
  user = (Usuario*) malloc(sizeof(Usuario));
  achou = 0;
  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
   if ((strcmp(user->username, procurado) == 0) && (user->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibeUsuario(user);
    getchar();
    printf("Deseja realmente editar este usuario (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("O que você deseja alterar? \n1) Username \n2)Senha \n3) Tipo do Usuario \n4)Tudo \n>>>");
      scanf("%c", &resp);
      switch(resp){
        case '1':
            do{
            printf("Informe o username: ");
            scanf(" %39[^\n]", user->username);
            getchar();
            }while(existUser(user->username));
            break;
        case '2':
            printf("Informe a nova senha: ");
            scanf(" %39[^\n]", user->senha);
            break;        
        case '3':
            printf("Informe o tipo: \n1) Administrador \n2) Operador\n");
            scanf(" %c", &user->tipoUsuario);
            break;
        default:
            do{
            printf("Informe o username: ");
            scanf(" %39[^\n]", user->username);
            getchar();
            }while(existUser(user->username));

            printf("Informe a nova senha: ");
            scanf(" %39[^\n]", user->senha);
            getchar();
            printf("Informe o tipo: \n1) Administrador \n2) Operador\n");
            scanf(" %c", &user->tipoUsuario);
            break;
      }
      user->status = '1';
      fseek(fp, -1*sizeof(Usuario), SEEK_CUR);
      fwrite(user, sizeof(Usuario), 1, fp);
      printf("\nUsuario editado com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
  } else {
    printf("O usuario %s não foi encontrado...\n", procurado);
  }
  free(user);
  fclose(fp);
}

void cadastraUsuario(void){
  fflush(stdin);
  
  Usuario* user;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO USUARIO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  user = (Usuario*) malloc(sizeof(Usuario));
  do{
  printf("Informe seu nome de usuário: \n>>> ");
  scanf(" %39[^\n]", user->username);
  getchar();
  }while(existUser(user->username));
  
  printf("Informe a sua senha: \n>>> ");
  scanf(" %39[^\n]", user->senha);
  getchar();
  printf("Qual o tipo de usuario? \n1)ADM \n2)OPERADOR\n>>>");
  scanf(" %c", &user->tipoUsuario);
  
  user->status = '1';
  user->cadastroFisico = '0';
  printf("###############################\n");
  exibeUsuario(user);
  printf("###############################\n");
  gravaUsuario(user);
  fflush(stdin);
  free(user);
}

void excluiUsuario(void){

}

void listaUsuario(void){

}

void exibeUsuario(Usuario* user){
  printf("Nome: %s\n", user->username);
  printf("Senha: %s\n", user->senha);
  if(user->tipoUsuario == '1'){
    printf("É um administrador !.\n");
  }
  else{
    printf("É um operador !.\n");
  }
  getchar();
  printf("\n");
}

void gravaUsuario(Usuario* user){
  FILE* fp;
  fp = fopen("usuario.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(user, sizeof(Usuario), 1, fp);
  fclose(fp);
}

int existUser(char username_procurado[40]){
  FILE* fp;
  Usuario* user;
  fp = fopen("usuario.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  user = (Usuario*) malloc(sizeof(Usuario));
  while((fread(user, sizeof(Usuario), 1, fp))) {
   if ((strcmp(user->username, username_procurado) == 0) && (user->status == '1')) {
     return 1;
   }
  }
  return 0;
}