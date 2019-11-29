#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculocrud.h"

void cadastraVeiculo(void) {
  fflush(stdin);
  Veiculo* veiculo;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO VEICULO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));
  printf("Informe o nome do veiculo: \n>>> ");
  scanf(" %39[^\n]", veiculo->nome);
  getchar();
  printf("Informe a quantidade do veiculo: \n>>> ");
  scanf(" %39[^\n]", veiculo->estoque);
  getchar();
  printf("Informe uma descrição breve do veiculo: \n>>> ");
  scanf(" %39[^\n]", veiculo->descricao);
  getchar();
  printf("Informe o preço de locação do veiculo: \n>>> ");
  scanf(" %f", &veiculo->precoLocacao);
  getchar();
  printf("Informe a placa de locação do veiculo: \n>>> ");
  scanf(" %14[^\n]", veiculo->placa);
  getchar();  
  veiculo->status = '1';
  veiculo->kmRodadosVeiculo = 0;
  printf("Digite o tipo de veiculo: \n0) CARRO\n1) MOTO\n>>>");
  scanf(" %d", &veiculo->tipoVeiculo);
  getchar();  
  printf("###############################\n");
  exibeVeiculo(veiculo);
  printf("###############################\n");
  gravaVeiculo(veiculo);
  fflush(stdin);
  free(veiculo);
}

void gravaVeiculo(Veiculo* veiculo) {
  FILE* fp;
  fp = fopen("veiculo.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(veiculo, sizeof(Veiculo), 1, fp);
  fclose(fp);
}

void editaVeiculo(void) {
  FILE* fp;
  Veiculo* veiculo;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("veiculo.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR VEICULO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe a placa do veiculo a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));
  achou = 0;
  while((!achou) && (fread(veiculo, sizeof(Veiculo), 1, fp))) {
   if ((strcmp(veiculo->placa, procurado) == 0) && (veiculo->status == '1')) {
     achou = 1;
   }
  if (achou) {
    exibeVeiculo(veiculo);
    getchar();
    printf("Deseja realmente editar este veiculo (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      veiculo = (Veiculo*) malloc(sizeof(Veiculo));
      printf("Informe o nome do veiculo: \n>>> ");
      scanf(" %39[^\n]", veiculo->nome);
      getchar();
      printf("Informe a quantidade do veiculo: \n>>> ");
      scanf(" %39[^\n]", veiculo->estoque);
      getchar();
      printf("Informe uma descrição breve do veiculo: \n>>> ");
      scanf(" %39[^\n]", veiculo->descricao);
      getchar();
      printf("Informe o preço de locação do veiculo: \n>>> ");
      scanf(" %f", &veiculo->precoLocacao);
      getchar();
      printf("Informe a placa do veiculo: \n>>> ");
      scanf(" %14[^\n]", veiculo->placa);
      getchar();      
      veiculo->status = '1';
      printf("Digite o tipo de veiculo: \n0) CARRO\n1) MOTO\n>>>");
      scanf(" %d",&veiculo->tipoVeiculo);
      getchar();
      fseek(fp, (-1)*sizeof(Veiculo), SEEK_CUR);
      fwrite(veiculo, sizeof(Veiculo), 1, fp);
      printf("\nVeiculo editado com sucesso!!!\n");
      } else {
      printf("\nOk, os dados não foram alterados\n");
      }    
    }else {
      printf("O veiculo %s não foi encontrado...\n", procurado);
    }
  free(veiculo);
  fclose(fp);
  }
}


void exibeVeiculo(Veiculo* veiculo){
  printf("Nome: %s\n", veiculo->nome);
  printf("Estoque: %s\n", veiculo->estoque);
  printf("Descrição: %s\n", veiculo->descricao);
  printf("Status: %c\n", veiculo->status);
  printf("Placa: %s\n", veiculo->placa);
  printf("Km Rodados: %d", veiculo->kmRodadosVeiculo);
  printf("Preço Locação: %f", veiculo->precoLocacao);
  printf("Tipo de veiculo: %d\n", veiculo->tipoVeiculo);
  getchar();
  printf("\n");
}

void buscaVeiculo(void) {
  FILE* fp;
  Veiculo* veiculo;
  int achou;
  char procurado[15];
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR VEICULO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe a placa do veiculo a ser buscado:\n ");
  scanf(" %14[^\n]", procurado);
  getchar();
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));
  achou = 0;
  while((!achou) && (fread(veiculo, sizeof(Veiculo), 1, fp))) {
   if ((strcmp(veiculo->placa, procurado) == 0) && (veiculo->status == '1')) {
     achou = 1;
   }
  fclose(fp);
  if (achou) {
    exibeVeiculo(veiculo);
  } else {
    printf("O veiculo %s não foi encontrado...\n", veiculo->placa);
  }
  free(veiculo);
  }
}
void listaVeiculos(void) {
  FILE* fp;
  Veiculo* veiculo;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EXIBIR VEICULO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veiculo, sizeof(Veiculo), 1, fp)) {
    if (veiculo->status == '1') {
      exibeVeiculo(veiculo);
    }
  }
  fclose(fp);
  free(veiculo);
}

void excluiVeiculo(void) {
  FILE* fp;
  Veiculo* veiculo;
  int achou;
  char resp;
  char procurado[15];
  fp = fopen("veiculo.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }else{
    printf("\n\n");
    printf("####################################\n");
    printf("######  MENU DELETAR VEICULO #######\n");
    printf("####################################\n");
    printf("######### SIG RENT A CAR ###########\n");
    printf("####################################\n");
    printf("Informe a placa do veiculo a ser apagado: ");
    scanf(" %14[^\n]", procurado);
    getchar();
    veiculo = (Veiculo*) malloc(sizeof(Veiculo));
    achou = 0;
    while((!achou) && (fread(veiculo, sizeof(Veiculo), 1, fp))) {
    if ((strcmp(veiculo->placa, procurado) == 0) && (veiculo->status == '1')) {
      achou = 1;
    }
    }
    
    if (achou) {
      exibeVeiculo(veiculo);
      printf("Deseja realmente apagar este Veiculo (s/n)? ");
      scanf("%c", &resp);
      if (resp == 's' || resp == 'S') {
        veiculo->status = '0';
        fseek(fp, -1*sizeof(Veiculo), SEEK_CUR);
        fwrite(veiculo, sizeof(Veiculo), 1, fp);
        printf("\nVeiculo excluído com sucesso!!!\n");
      } else {
        printf("\nOk, os dados não foram alterados\n");
      }
    } else {
      printf("O Veiculo %s não foi encontrado...\n", veiculo->nome);
    }
    fclose(fp);
    free(veiculo);
  }
}

int existVeiculo(char placa_procurado[11]){
  FILE* fp;
  Veiculo* veic;
  fp = fopen("veiculo.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while((fread(veic, sizeof(Veiculo), 1, fp))) {
   if ((strcmp(veic->placa, placa_procurado) == 0) && (veic->status == '1')) {
     return 1;
   }
  }
  return 0;
}