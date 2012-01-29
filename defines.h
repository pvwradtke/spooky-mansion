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
#define NUM_CENARIO     2
#define NUM_NOS         23
#define NUM_ARESTAS     23
#define NUM_CAMINHOS    21
#define PORTAS_LEMBRAR  2
    
#define VEL_INI         2
#define DIV_PLACAR      3
    
enum{ LATERAL, VERTICAL};

enum{SEM_PORTA=-1, PORTA_A, PORTA_B, PORTA_C, PORTA_D, PORTA_E, PORTA_F, PORTA_G,
NUM_PORTAS};

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
    int xgravidade, ygravidade;
    int caminho;
    int indice;
    bool invertido;

    int frame;    
    int delay;
    int frames[10];
    int totalframes;
    int framedelay;
}Personagem;
    
typedef struct Caminho
{
    int origem;
    int destino;
    int numarestas;
    int arestas[13];
}Caminho;

typedef struct FilaMenina
{
    int fila[PORTAS_LEMBRAR][2];
    int inicio, fim, tamanho;
    bool estouro;
}FilaMenina;
    
enum {TELA_SPLASD, TELA_MENU, TELA_ABOUT, TELA_HELP, TELA_JOGO};

#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

