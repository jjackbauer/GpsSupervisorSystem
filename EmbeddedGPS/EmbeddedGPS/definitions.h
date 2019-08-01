/*
 * definitions.h
 *
 * Created: 01/08/2019 09:13:42
 *  Author: jzrhard03
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define FCPU 84000000				//define a frequencia da CPU - 84 MHz - ALTERAR TB NA LINHA DE BAIXO!

asm (".equ fcpu, 84000000  \n\t");	//diretiva para usar fcpu em assembly

#include "sam.h"					//definições para o componente especificado

//Definições de macros para o trabalho com bits

#define	set_bit(y,bit)	(y|=(1<<bit))	//coloca em 1 o bit x da variável Y
#define	clr_bit(y,bit)	(y&=~(1<<bit))	//coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) 	(y^=(1<<bit))	//troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) 	(y&(1<<bit))	//retorna 0 ou 1 conforme leitura do bit

#endif /* DEFINITIONS_H_ */