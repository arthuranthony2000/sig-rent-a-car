#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidocrud.h"
#include "verificacpf.h"


void cadastraPedido(void) {
  fflush(stdin);
  Pedido* ped;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  CADASTRO PEDIDO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("= = = = = = = = = = = \n");
  ped = (Pedido*) malloc(sizeof(Pedido));
  printf("Informe o id do Pedido: \n>>> ");
  scanf(" %59[^\n]", ped->id);
  getchar();
  printf("Informe o CPF do cliente: \n>>> ");
  scanf(" %39[^\n]", ped->cpf_cliente);
  getchar();
  printf("Informe data inicial: \n>>> ");
  scanf(" %14[^\n]", ped->data_inicio);
  getchar();
  ped->km_rodados_pedido = 0;
  ped->status = '1';
  printf("###############################\n");
  exibePedido(ped);
  printf("###############################\n");
  gravaPedido(ped);
  fflush(stdin);
}

void gravaPedido(Pedido* ped) {
  FILE* fp;
  fp = fopen("pedido.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(ped, sizeof(Pedido), 1, fp);
  fclose(fp);
}

void exibePedido(Pedido* ped) {
  printf("id: %s\n", ped->id);
  printf("CPF Cliente: %s\n", ped->cpf_cliente);
  printf("Data do inicio: %s\n", ped->data_inicio);
  printf("Status: %c\n", ped->status);
  getchar();
  printf("\n");
}

void editaPedido(void) {
  FILE* fp;
  Pedido* ped;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("pedido.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  EDITAR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o id do Pedido a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  ped = (Pedido*) malloc(sizeof(Pedido));
  achou = 0;
  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibePedido(ped);
    getchar();
    printf("Deseja realmente editar este Pedido (s/n)? ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("Informe o id do Pedido: ");
      scanf(" %14[^\n]", ped->id);
      printf("Informe CPF do cliente: ");
      scanf(" %14[^\n]", ped->cpf_cliente);
      printf("Informe o telefone do Pedido: ");
      scanf(" %10[^\n]", ped->data_inicio);
      getchar();
      ped->status = '1';
      fseek(fp, -1*sizeof(Pedido), SEEK_CUR);
      fwrite(ped, sizeof(Pedido), 1, fp);
      printf("\nPedido editado com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
  } else {
    printf("O Pedido %s não foi encontrado...\n", procurado);
  }
  free(ped);
  fclose(fp);
}

void buscaPedido(void) {
  FILE* fp;
  Pedido* ped;
  int achou;
  char procurado[15];
  fp = fopen("pedido.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  BUSCAR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do Pedido a ser buscado:\n ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ped = (Pedido*) malloc(sizeof(Pedido));
  achou = 0;
  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
  fclose(fp);
  if (achou) {
    exibePedido(ped);
  } else {
    printf("O Pedido %s não foi encontrado...\n", ped->id);
  }
  free(ped);
}

void listaPedido(void) {
  FILE* fp;
  Pedido* ped;
  fp = fopen("pedido.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  EXIBIR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ped = (Pedido*) malloc(sizeof(Pedido));
  while(fread(ped, sizeof(Pedido), 1, fp)) {
    if (ped->status == '1') {
      exibePedido(ped);
    }
  }
  fclose(fp);
  free(ped);
}

void excluiPedido(void) {
  FILE* fp;
  Pedido* ped;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("pedido.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o ID do Pedido a ser apagado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ped = (Pedido*) malloc(sizeof(Pedido));
  achou = 0;
  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibePedido(ped);
    printf("Deseja realmente apagar este Pedido (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      ped->status = '0';
      fseek(fp, -1*sizeof(Pedido), SEEK_CUR);
      fwrite(ped, sizeof(Pedido), 1, fp);
      printf("\nPedido excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O Pedido %s não foi encontrado...\n", ped->id);
  }
  fclose(fp);
  free(ped);
}