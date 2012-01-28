/* 
 * File:   main.cpp
 * Author: pvwradtke
 *
 * Created on 28 de Janeiro de 2012, 02:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>
#include <c2d2/chienaudio2.h>
#include "defines.h"


#define NUM_NOS         20
#define NUM_ARESTAS     20

enum{ LATERAL, VERTICAL};

enum{SEM_PORTA=-1, PORTA_A, PORTA_B, PORTA_C, PORTA_D, PORTA_E, PORTA_F, PORTA_G,
PORTA_H, NUM_PORTAS};

enum {DIREITA, ESQUERDA, CIMA, BAIXO};

typedef struct No
{
    int x, y, zoom;
    int porta;
    int custo;
}No;

typedef struct Aresta 
{
    int distancia;
    int angulo;
    int origem, destino;
}Aresta;

typedef struct Personagem
{
    int aresta;
    int no_origem, no_destino;
    int distancia;
    int direcao;
};

No nos[NUM_NOS] = {{24, 981, PORTA_A, 100},     // 0
                {426, 993, SEM_PORTA, 100},     // 1
                {945, 984, SEM_PORTA, 100},     // 2
                {1428, 987, SEM_PORTA, 100},    // 3
                {1869, 999, PORTA_D, 100},      // 4
                {537, 747, SEM_PORTA, 70},      // 5
                {1374, 744, SEM_PORTA, 70},     // 6
                {558, 645, PORTA_B, 67},        // 7
                {1368, 642, PORTA_C, 67},       // 8
                {84, 378, PORTA_E, 90},         // 9
                {168, 447, SEM_PORTA, 90},      // 10
                {288, 252, SEM_PORTA, 65},      // 11
                {702, 297, SEM_PORTA, 65},      // 12
                {717, 213, PORTA_F, 60},        // 13
                {969, 312, SEM_PORTA, 65},      // 14
                {1227, 309, SEM_PORTA, 65},     // 15
                {1221, 219, PORTA_G, 60},       // 16
                {1623, 279, SEM_PORTA, 65},     // 17
                {1782, 477, SEM_PORTA, 90},     // 18
                {1854, 408, PORTA_H, 90}        // 19
};

Aresta arestas[NUM_ARESTAS] ={
    {50, LATERAL, 0, 1},        // I
    {50, LATERAL, 1, 2},        // II
    {50, VERTICAL, 1, 5},       // III
    {50, VERTICAL, 5, 7},       // IV
    {50, LATERAL, 5, 6},        // V
    {50, LATERAL, 2, 3},        // VI
    {50, LATERAL, 3, 4},        // VII
    {50, VERTICAL, 3, 6},       // VII
    {50, VERTICAL, 6, 8},       // IX
    {50, VERTICAL, 2, 14},      // X
    {50, LATERAL, 14, 15},      // XI
    {50, VERTICAL, 15, 16},     // XII
    {50, LATERAL, 15, 17},      // XIII
    {50, LATERAL, 17, 18},      // XIV
    {50, VERTICAL, 18, 19},     // XV
    {50, LATERAL, 14, 12},      // XVI
    {50, VERTICAL, 12, 13},     // XVII
    {50, LATERAL, 12, 11},      // XVIII
    {50, LATERAL, 11, 10},      // XIX
    {50, VERTICAL, 10, 9}       // XX
};

// The files to load
char scenario[NUM_CENARIO][30] = {"./graphics/back_main.png", "./graphics/back_stairs.png",
        "./graphics/rails_left.png", "./graphics/rails_right.png",
        "./graphics/rails_middle.png", "./graphics/door_a.png",
        "./graphics/door_b.png", "./graphics/door_c.png", "./graphics/door_d.png",
        "./graphics/door_e.png", "./graphics/door_f.png", "./graphics/door_g.png", 
        "./graphics/door_h.png"
    };
// The files positions on screen
    int posicoes[NUM_CENARIO][2] = { {0, 0}, {685, 389}, {0, 314}, {1107, 314}, 
    {683, 328}, {22, 834}, {498, 515}, {1328, 516}, {1843, 838}, {74, 217}, 
    {674, 71}, {1187, 74}, {1795, 217}};
    

void DesenhaSpriteEscala(unsigned int spriteset, unsigned int frame, int x, int y, 
        double xproportion, double yproportion);

void DesenhaSpriteEscala(unsigned int spriteset, unsigned int frame, int x, int y, 
        double xproportion, double yproportion, int yoff)
{
    int largura, altura;
    if(C2D2_DimensoesSprite(spriteset, &largura, &altura))
    {
        int xc[4], yc[4];
        xc[0]=xc[3]=x*xproportion;
        xc[1]=xc[2]=xc[0]+largura*xproportion;        
        yc[0]=yc[1]=yoff+y*yproportion;
        yc[2]=yc[3]=yoff+yc[0]+altura*yproportion;
        C2D2_DesenhaSpriteEfeito(spriteset, frame, xc, yc, 255, 255, 255, 255);
    }
}


int main(int ac, char **av) {
    // A resolução da tela
    int width = NETBOOK_WIDTH;
    int height = NETBOOK_HEIGHT;
    // The scenery goes here
    unsigned int scene[NUM_CENARIO];
    Personagem jogador = {0, 0, 1, 0, DIREITA};
    ////////////////////////////
    //tela escolha resolução //
    //////////////////////////
    if (!C2D2_Inicia(width, height, C2D2_JANELA, C2D2_DESENHO_OPENGL, (char*) "Spooky Mansion")) {
        printf("Nao conseguiu iniciar a tela. Encerrando.\n");
        return 1;
    }
    // inicializa áudio
    CA2_Inicia();
    // Recupera o teclado
    C2D2_Botao *teclado = C2D2_PegaTeclas();
    // Sem erros
    bool erro = false;
    // Loads graphics
    for(int i=0;i<NUM_CENARIO && !erro;i++)
    {
        if((scene[i] = C2D2_CarregaSpriteSet(scenario[i], 0, 0)) == 0)
            erro=true;
    }
    
    if(!erro)
    {
        while(!teclado[C2D2_ESC].pressionado && !teclado[C2D2_ENCERRA].pressionado)
        {
            // As proporções da tela
            double xprop = (double)width/FULLHD_WIDTH;
            double yprop = (double)height/FULLHD_HEIGHT;
            for(int i=0;i<NUM_CENARIO;i++)
                DesenhaSpriteEscala(scene[i], 0, posicoes[i][0], posicoes[i][1], xprop, yprop, 2);
                //C2D2_DesenhaSprite(scene[i], 0, posicoes[i][0], posicoes[i][1]);
            // Desenha as arestas
            for(int i=0;i<NUM_ARESTAS;i++)
            {
                int origem = arestas[i].origem;
                int destino = arestas[i].destino;
                C2D2P_Linha(nos[origem].x*xprop, nos[origem].y*yprop, 
                        nos[destino].x*xprop, nos[destino].y*yprop, 
                        0, 0, 255);
            }
            C2D2_Sincroniza(C2D2_FPS_PADRAO);
        }
    }
    printf("Quitting\n");
    // Encerra tudo
    CA2_Encerra();
    C2D2_Encerra();
    return 0;
}
