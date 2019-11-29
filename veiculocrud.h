#ifndef VEICULOCRUD_H_INCLUDED
#define VEICULOCRUD_H_INCLUDED


typedef struct veiculo Veiculo;

struct veiculo {
  int tipoVeiculo;
  char nome[40];
  char estoque[40];
  char descricao[40];
  float precoLocacao;
  char placa[11];
  int kmRodadosVeiculo;
  char status;
};



void menuPVeiculo(void);
void cadastraVeiculo(void);
void buscaVeiculo(void);
void editaVeiculo(void);
void excluiVeiculo(void);
void listaVeiculos(void);
void exibeVeiculo(Veiculo*);
void sobre(void);
void gravaVeiculo(Veiculo*);
int existVeiculo(char placa_procurado[11]);

#endif