#include <stdlib.h>
#include <stdio.h>
#include "admcrud.h"
#include "clientecrud.h"
#include "operadorcrud.h"
#include "veiculocrud.h"
#include "pedidocrud.h"
#include "login.h"
#include <string.h>
#include "index.h"


void menuInicial(void){
  int op;
  FILE* user;
  user = fopen("usuario.dat", "r+b");
  if (user == NULL) {
    cadastraUsuarioInicial();
  }else{
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  INICIAL ######################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");    
        printf("####### 1 - LOGIN ############################\n");
        printf("####### 2 - SAIR #############################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        switch(op){
          case 1:
            system("clear");
            menuLogin();
            break;
          default:
            break; 
        }
    }while(op != 2);
  }
}

void menuLogin(){
  FILE* fp;
  Usuario* user;
  int achou;
  char procurado[40];
  char password[40];
  fp = fopen("usuario.dat", "rb");
  if (fp == NULL){
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU LOGIN #################\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o username:\n ");
  scanf(" %39[^\n]", procurado);
  getchar();
  printf("Informe a senha:\n ");
  scanf(" %39[^\n]", password);
  getchar();
  user = (Usuario*) malloc(sizeof(Usuario));
  achou = 0;

  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
    if ((strcmp(user->username, procurado) == 0) && (strcmp(user->senha, password) == 0) && (user->status == '1')) {
      achou = 1;
    }
  }
  
  if (achou) {
    if(user->cadastroFisico == '1'){
      if(user->tipoUsuario == '1'){
      menuAdministrativo();
    }else {
      menuOperativo();        
    }
    }
  else {
    if(user->tipoUsuario == '1'){
        cadastraAdministradorInicial(user);
    }else {
        cadastraOperadorInicial(user);       
    }
  }
        
  } else{
    printf("O usuario %s não foi encontrado...\n", user->username);
  }
  free(user);
  fclose(fp);
}


void menuOperativo(void){
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  OPERADOR #####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CLIENTE ####################\n");
        printf("####### 2 - PEDIDO #####################\n");
        printf("####### 3 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("clear");
            menuOperativoUsuario();
            break;
        
        case 2:
            system("clear");
            menuOperativoPedido();
            break;
        default:
            break;
        }
    }while(op != 3);
}


void menuOperativoPedido(void){
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  OPERADOR #####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CADASTRAR PEDIDO ###################\n");
        printf("####### 2 - ACESSAR PEDIDO #####################\n");
        printf("####### 3 - ALTERAR PEDIDO #####################\n");
        printf("####### 4 - LISTAR PEDIDO ######################\n");
        printf("####### 5 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("clear");
            cadastraPedido();
            break;
        
        case 2:
            system("clear");
            buscaPedido();
            break;
        
        case 3:
            system("clear");
            editaPedido();
            break;
        
        case 4:
            system("clear");
            listaPedido();
            break;
        default:
            break;
        }
    }while(op != 5);
}

void menuOperativoUsuario(void){
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  OPERADOR #####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CADASTRAR CLIENTE ###################\n");
        printf("####### 2 - ACESSAR CLIENTE #####################\n");
        printf("####### 3 - ALTERAR CLIENTE #####################\n");
        printf("####### 4 - LISTAR CLIENTE ######################\n");
        printf("####### 5 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        switch (op) {
        case 1:
            system("clear");
            cadastraCliente();
            break;
        
        case 2:
            system("clear");
            buscaCliente();
            break;
        
        case 3:
            system("clear");
            editaCliente();
            break;
        
        case 4:
            system("clear");
            listaClientes();
            break;
        default:
            system("clear");
            menuInicial();
            break;
        }
    }while(op != 5);
}

void menuAdministrativo(void){
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  PRINCIPAL ####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CADASTRAR DADO ###################\n");
        printf("####### 2 - ACESSAR DADO #####################\n");
        printf("####### 3 - ALTERAR DADO #####################\n");
        printf("####### 4 - LISTAR DADO #####################\n");
        printf("####### 5 - DELETAR DADO #####################\n");
        printf("####### 6 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("clear");
            menuCadastrarDado();
            break;
        
        case 2:
            system("clear");
            menuAcessarDado();
            break;
        
        case 3:
            system("clear");
            menuAlterarDado();
            break;
        
        case 4:
            system("clear");
            menuListarDado();
            break;
        case 5:
            system("clear");
            menuDeletarDado();
            break;
        default:
            system("clear");
            menuInicial();
            break;
        }
    }while(op != 6);
}





void menuCadastrarDado(void){
    fflush(stdin);
    system("clear");
    int op;
    printf("##########################################\n");
    printf("######  MENU  CADASTRO DADO ##############\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("VOCE DESEJA CADASTRAR O QUE? \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR\n4) VEICULO\n5) USUARIO\n>>> ");
    scanf("%d", &op);
    switch (op)    {
    case 1:
        system("clear");
        cadastraAdministrador();
        break;

    case 2:
        system("clear");
        cadastraCliente();
        break;

    case 3:
        system("clear");
        cadastraOperador();
        break;

    case 4:
        system("clear");
        cadastraVeiculo();
        break;
    case 5:
        cadastraUsuario();
    default:
        break;
    }
}

void menuAcessarDado(void){
    fflush(stdin);
    system("clear");
    int op;
    printf("##########################################\n");
    printf("######  MENU  ACESSAR DADO ###############\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("VOCE DESEJA ACESSAR O QUE? \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR\n4) VEICULO\n>>> ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        system("clear");
        buscaAdministrador();
        break;
    case 2:
        system("clear");
        buscaCliente();
        break;
    case 3:
        system("clear");
        buscaOperador();
        break;
    case 4:
        system("clear");
        buscaVeiculo();
        break;    
    default:
        break;
    }
}

void menuAlterarDado(void){
    fflush(stdin);
    system("clear");
    int op;
    printf("##########################################\n");
    printf("######  MENU  EDITAR DADO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("VOCE DESEJA ALTERAR O QUE? \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR\n4) VEICULO\n>>> ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        system("clear");
        editaAdministrador();
        break;
    case 2:
        system("clear");
        editaCliente();
        break;
    case 3:
        system("clear");
        editaOperador();
        break;
    case 4:
        system("clear");
        editaVeiculo();
        break;
    default:
        break;
    }
}


void menuDeletarDado(void){
    int op;
    int id;
    char cpf[11];
    system("clear");
    printf("##########################################\n");
    printf("######  MENU DELETAR DADO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("INSIRA O TIPO DE DADO QUE DESEJA DELETAR \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR \n4)VEICULO\n>>> ");
    scanf("%d", &op);
    switch (op){
    case 1:
        system("clear");
        excluiAdministrador();       
        // IRA DELETAR O ADMINISTRADOR COM O MODULO DELETE //
        printf("ADMINISTRADOR DELETADO COM SUCESSO !.");
        break;
    
    case 2:
        system("clear");
        excluiCliente();
        // IRA DELETAR O CLIENTE COM O MODULO DELETE 
        printf("CLIENTE DELETADO COM SUCESSO !.");
        break;
    case 3:
        system("clear");
        excluiOperador();
        printf("OPERADOR DELETADO CCOM SUCESSO !.");
        break;
    case 4:
        system("clear");
        excluiVeiculo();
        // IRA DELETAR O VEICULO COM O MODULO DELETE //
        printf("VEICULO DELETADO COM SUCESSO !.");
        break;
    
    default:
        break;
    }
}

void menuListarDado(void){
    int op;
    int id;
    char cpf[11];
    system("clear");
    printf("##########################################\n");
    printf("######  MENU DELETAR DADO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("INSIRA O TIPO DE DADO QUE DESEJA LISTAR \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR \n4) VEICULO\n 5) PEDIDO>>> ");
    scanf("%d", &op);
    switch (op){
    case 1:
        system("clear");
        listaAdministradores();       
        break;
    
    case 2:
        system("clear");
        listaClientes();       
        break;
    case 3:
        system("clear");
        listaOperador();
        break;
    case 4:
        system("clear");
        listaVeiculos();
        break;
    case 5:
        system("clear");
        listaPedido();
    default:
        break;
    }

}