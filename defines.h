/* 
 * File:   defines.h
 * Author: pvwradtke
 *
 * Created on 28 de Janeiro de 2012, 03:07
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FULLHD_WIDTH    1920
#define FULLHD_HEIGHT   1080
#define HD_WIDTH        1280
#define HD_HEIGHT       720
#define NETBOOK_WIDTH   1024
#define NETBOOK_HEIGHT  600
#define DESKTOP_WIDTH   1280
#define DESKTOP_HEIGHT  1024
#define NUM_CENARIO     5
#define NUM_NOS         20
#define NUM_ARESTAS     20

enum{ LATERAL, VERTICAL};

enum{SEM_PORTA=-1, PORTA_A, PORTA_B, PORTA_C, PORTA_D, PORTA_E, PORTA_F, PORTA_G,
PORTA_H, NUM_PORTAS};

enum {DIREITA, ESQUERDA, CIMA, BAIXO};

typedef struct No
{
    int x, y, porta, zoom;
}No;

typedef struct Vizinhos
{
    int cima, baixo, esquerda, direita;
}Vizinhos;

typedef struct Aresta 
{
    int distancia;
    int angulo;
    int origem, destino;
}Aresta;

typedef struct Porta
{
    int no, direcao, aresta;
}Porta;

typedef struct Personagem
{
    int aresta;
    int no_origem, no_destino;
    int distancia;
    int direcao;
    int caminho;
    int aresta;
    bool invertido;
}Personagem;
    
typedef struct Caminho
{
    int origem;
    int destino;
    int numarestas;
    int arestas[8];
}Caminho;
    
#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

