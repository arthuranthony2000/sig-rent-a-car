#include "verificasenha.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


int VerificaSenha(char num[40]){
    int i;
    if (strlen(num) > 4){
        for (i = 0; i < strlen(num); i++) {
            if ((isdigit(num[i])== 0)){
                return FALSE;
            }
        }
        return TRUE;
    }   
    return FALSE; 
    
}