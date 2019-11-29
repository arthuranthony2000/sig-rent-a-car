#ifndef PEDIDOCRUD_H_INCLUDED
#define PEDIDOCRUD_H_INCLUDED
#include "veiculocrud.h"

typedef struct pedido Pedido;

struct pedido{
    char id[10];
    char cpf_cliente[11];
    char data_inicio[10];
    char data_final[10];
    Veiculo* veic[10];
    char status;
    int km_rodados_pedido;  
};

void cadastraPedido(void);
void buscaPedido(void);
void editaPedido(void);
void excluiPedido(void);
void listaPedido(void);
void exibePedido(Pedido*);
void gravaPedido(Pedido*);


#endif



