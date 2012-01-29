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

Porta portas[NUM_PORTAS] = { {0, DIREITA, 0}, {7, BAIXO, 3}, {8, BAIXO, 8}, {4, ESQUERDA, 6}, 
        {9, DIREITA, 19}, {13, BAIXO, 16}, {16, BAIXO, 11}, {19, ESQUERDA, 14}};

Aresta arestas[NUM_ARESTAS] ={
    {50, LATERAL, 0, 1},        // I    0
    {50, LATERAL, 1, 2},        // II   1
    {50, VERTICAL, 1, 5},       // III  2
    {50, VERTICAL, 5, 7},       // IV   3
    {50, LATERAL, 5, 6},        // V    4
    {50, LATERAL, 2, 3},        // VI   5
    {50, LATERAL, 3, 4},        // VII  6
    {50, VERTICAL, 3, 6},       // VIII 7
    {50, VERTICAL, 6, 8},       // IX   8
    {50, VERTICAL, 2, 14},      // X    9
    {50, LATERAL, 14, 15},      // XI   10
    {50, VERTICAL, 15, 16},     // XII  11
    {50, LATERAL, 15, 17},      // XIII 12
    {50, LATERAL, 17, 18},      // XIV  13
    {50, VERTICAL, 18, 19},     // XV   14
    {50, LATERAL, 14, 12},      // XVI  15
    {50, VERTICAL, 12, 13},     // XVII 16
    {50, LATERAL, 12, 11},      // XVIII        17
    {50, LATERAL, 11, 10},      // XIX  18
    {50, VERTICAL, 10, 9}       // XX   19
};
// Os vizinhos de um nó em cada direção
//cima, baixo, esquerda, direita;
Vizinhos vizinhos[NUM_NOS]={ {-1, -1, -1, 0},   // 0
                             {2, -1, 0, 1},     // 1
                             {9, -1, 1, 5},     // 2
                             {7, -1, 5, 6},     // 3
                             {-1, -1, 6, -1},   // 4
                             {3, 2, -1, 4},     // 5
                             {8, 7, 4, -1},     // 6
                             {-1, 3, -1, -1},   // 7
                             {-1, 8, -1, -1},   // 8
                             {-1, -1, -1, 19},  // 9
                             {18, -1, 19, -1},  // 10
                             {-1, 18, -1, 17},  // 11
                             {16, -1, 17, 15},  // 12
                             {-1, 16, -1, -1},  // 13
                             {-1, 9, 15, 10},   // 14
                             {11, -1, 10, 12},  // 15
                             {-1, 11, -1, -1},  // 16
                             {-1, 13, 12, -1},  // 17
                             {13, -1, -1, 14},  // 18
                             {-1, -1, 14, -1}   // 19
};

Caminho caminhos[22]={
    { PORTA_A, PORTA_B, 3,{0, 2, 3}},
    { PORTA_A, PORTA_C, 4,{0, 2, 4, 8}},
    { PORTA_A, PORTA_D, 4,{0, 1, 5, 6}},
    { PORTA_A, PORTA_E, 7,{0, 1, 9, 15, 17, 18, 19}},
    { PORTA_A, PORTA_F, 5,{0, 1, 9, 15, 16}},
    { PORTA_A, PORTA_G, 5,{0, 1, 9, 10, 11}},
    { PORTA_A, PORTA_H, 7,{0, 1, 9, 10, 12, 13, 14}},
    
    { PORTA_B, PORTA_C, 3,{3, 4, 8}},
    { PORTA_B, PORTA_D, 4,{3, 4, 7, 6}},
    { PORTA_B, PORTA_E, 8,{3, 2, 1, 9, 15, 17, 18, 19}},
    { PORTA_B, PORTA_F, 6,{3, 2, 1, 9, 15, 16}},
    { PORTA_B, PORTA_G, 6,{3, 2, 1, 9, 10, 11}},
    { PORTA_B, PORTA_H, 8,{3, 2, 1, 9, 10, 12, 13, 14}},
    
    { PORTA_C, PORTA_D, 3,{8, 7, 6}},
    { PORTA_C, PORTA_E, 8,{8, 7, 5, 9, 15, 17, 18, 19}},
    { PORTA_C, PORTA_F, 6,{8, 7, 5, 9, 15, 16}},
    { PORTA_C, PORTA_G, 6,{8, 7, 5, 9, 10, 11}},
    { PORTA_C, PORTA_H, 8,{8, 7, 5, 9, 10, 12, 13, 14}},
    
    { PORTA_D, PORTA_E, 7,{6, 5, 9, 15, 17, 18, 19}},
    { PORTA_D, PORTA_F, 5,{6, 5, 9, 15, 16}},
    { PORTA_D, PORTA_G, 5,{6, 5, 9, 10, 11}},
    { PORTA_D, PORTA_E, 7,{6, 5, 9, 10, 13, 14, 15}},
    
    { PORTA_E, PORTA_F, 4,{19, 18, 17, 16}},
    { PORTA_E, PORTA_G, 6,{19, 18, 17, 15, 10, 11}},
    { PORTA_E, PORTA_H, 8,{19, 18, 17, 15, 10, 12, 13, 14}},
    
    { PORTA_F, PORTA_G, 4,{16, 15, 10, 11}},
    { PORTA_F, PORTA_H, 6,{16, 15, 10, 12, 13, 14}},
    
    { PORTA_G, PORTA_H, 4,{11, 12, 13 ,14}}
};

    int origem;
    int destino;
    int numarestas;
    int arestas[8];

// The files to load
char scenario[NUM_CENARIO][30] = {"./graphics/back_main.png", "./graphics/back_stairs.png",
        "./graphics/rails_left.png", "./graphics/rails_right.png",
        "./graphics/rails_middle.png"};//, "./graphics/door_a.png",
        //"./graphics/door_b.png", "./graphics/door_c.png", "./graphics/door_d.png",
        //"./graphics/door_e.png", "./graphics/door_f.png", "./graphics/door_g.png", 
        //"./graphics/door_h.png"
    //};
// The files positions on screen
    int posicoes[NUM_CENARIO][2] = { {0, 0}, {685, 389}, {0, 314}, {1107, 314}, 
    {683, 328} }; //, {22, 834}, {498, 515}, {1328, 516}, {1843, 838}, {74, 217}, 
    //{674, 71}, {1187, 74}, {1795, 217}};
    

void DesenhaSpriteEscala(unsigned int spriteset, unsigned int frame, int x, int y, 
        double xproportion, double yproportion);

void DesenhaPersonagem(Personagem *p, No *nos, Aresta *arestas, double xproportion, double yproportion);
void MovimentaJogador(Personagem *p, No *nos, Aresta *arestas);
void movimentaMenina(Personagem *p, No *nos, Arestas *arestas, Caminho *caminhos);
void InverteJogador(Personagem *p);
void PortasFantasma(Personagem *p);

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

void DesenhaPersonagem(Personagem *p, No *nos, Aresta *arestas, double xproportion, double yproportion)
{
    // Escolhe se é na horizontal ou na vertical a aresta
    int xpers, ypers;
    int origem, destino;

    origem = p->no_origem;
    destino = p->no_destino;
    xpers = nos[origem].x + ((double)p->distancia/arestas[p->aresta].distancia)*
                    (nos[destino].x - nos[origem].x);
    ypers = nos[origem].y + ((double)p->distancia/arestas[p->aresta].distancia)*
                    (nos[destino].y - nos[origem].y);
    C2D2P_CirculoPintado(xpers*xproportion, ypers*yproportion, 30*xproportion, 0, 0, 0);
}

void InverteJogador(Personagem *p)
{
        p->distancia = arestas[p->aresta].distancia - p->distancia;
        int temp = p->no_destino;
        p->no_destino=p->no_origem;
        p->no_origem=temp;
        if(p->direcao==CIMA)
            p->direcao=BAIXO;
        else if(p->direcao==BAIXO)
            p->direcao=CIMA;
        else if(p->direcao==DIREITA)
            p->direcao=ESQUERDA;
        else if(p->direcao==ESQUERDA)
            p->direcao=DIREITA;
}

void movimentaMenina(Personagem *p, No *nos, Aresta *arestas, Caminho *caminhos)
{
    
}

void MovimentaJogador(Personagem *p, No *nos, Aresta *arestas)
{
    C2D2_Botao *teclado = C2D2_PegaTeclas();
    // O movimento é de acordo com o eixo (saco!)
    if(arestas[p->aresta].angulo == LATERAL)
    {
        // Sabendo que é na lateral, sabe se ir para a esquerda ou direita aumenta/diminui a distância
        if(p->direcao==DIREITA && teclado[C2D2_ESQUERDA].pressionado  && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        else if(p->direcao==ESQUERDA && teclado[C2D2_DIREITA].pressionado  && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        // Os nós de origem e destino
        int origem = arestas[p->aresta].origem;
        int destino = arestas[p->aresta].destino;
//        if(nos[origem].x < nos[destino].x)
//        {
            if(p->distancia < arestas[p->aresta].distancia)
                p->distancia++;
//        }
//        else
//        {
//            if(p->distancia > 0)
//                p->distancia--;
//        }
    }
    else
    {
        // Sabendo que é na lateral, sabe se ir para a esquerda ou direita aumenta/diminui a distância
        if(p->direcao==CIMA && teclado[C2D2_BAIXO].pressionado && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        else if(p->direcao==BAIXO && teclado[C2D2_CIMA].pressionado && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        // Os nós de origem e destino
        int origem = arestas[p->aresta].origem;
        int destino = arestas[p->aresta].destino;
//        if(nos[origem].y > nos[destino].y)
//        {
            if(p->distancia < arestas[p->aresta].distancia)
                p->distancia++;
//        }
//        else
//        {
//            if(p->distancia > 0)
//                p->distancia--;
//        }
    }
    // Lógica para trocar de aresta
    if(p->distancia == arestas[p->aresta].distancia)
    {   
        int noatual = p->no_destino;
        // Testa primeiro se troca com o teclado
        if(teclado[C2D2_CIMA].ativo)
        {
            if(vizinhos[noatual].cima != -1)
            {
                p->direcao=CIMA;
                p->distancia=0;
                p->aresta = vizinhos[noatual].cima;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }else if(teclado[C2D2_BAIXO].ativo)
        {
            if(vizinhos[noatual].baixo != -1)
            {
                p->direcao=BAIXO;
                p->distancia=0;
                p->aresta = vizinhos[noatual].baixo;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }else if(teclado[C2D2_ESQUERDA].ativo)
        {
            if(vizinhos[noatual].esquerda != -1)
            {
                p->direcao=ESQUERDA;
                p->distancia=0;
                p->aresta = vizinhos[noatual].esquerda;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }else if(teclado[C2D2_DIREITA].ativo)
        {
            if(vizinhos[noatual].direita != -1)
            {
                p->direcao=DIREITA;
                p->distancia=0;
                p->aresta = vizinhos[noatual].direita;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }
        // Testa agora com o movimento atual do jogador
        else if(p->direcao == CIMA)
        {
            if(vizinhos[noatual].cima != -1)
            {
                p->distancia=0;
                p->aresta = vizinhos[noatual].cima;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }else if(p->direcao == BAIXO)
        {
            if(vizinhos[noatual].baixo != -1)
            {
                p->distancia=0;
                p->aresta = vizinhos[noatual].baixo;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }else if(p->direcao == ESQUERDA)
        {
            if(vizinhos[noatual].esquerda != -1)
            {
                p->distancia=0;
                p->aresta = vizinhos[noatual].esquerda;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }else if(p->direcao==DIREITA)
        {
            if(vizinhos[noatual].direita != -1)
            {
                p->distancia=0;
                p->aresta = vizinhos[noatual].direita;
                p->no_origem = noatual;
                if(p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }
        
    }
}

void PortasFantasma(Personagem *p)
{
    // Se o fantasma está numa porta porque acabou de percorrer a distância total
    if(p->distancia == arestas[p->aresta].distancia && nos[p->no_destino].porta != SEM_PORTA)
    {
        // Sorteia uma nova porta!!!
        int porta;
        // Repete o sorteio até achar uma porta diferente da atual
        do
        {
            porta=random()%NUM_PORTAS;
        }
        while(porta==nos[p->no_destino].porta);
        // Acha em qual nó está essa porta
        p->no_origem = portas[porta].no;
        p->aresta = portas[porta].aresta;
        p->direcao = portas[porta].direcao;
        p->distancia = 0;
        if(p->no_origem == arestas[p->aresta].origem)
            p->no_destino = arestas[p->aresta].destino;
        else
            p->no_destino = arestas[p->aresta].origem;
    }
}

int main(int ac, char **av) {
    // A resolução da tela
    int width = NETBOOK_WIDTH;
    int height = NETBOOK_HEIGHT;
    // The scenery goes here
    unsigned int scene[NUM_CENARIO];
    Personagem jogador = {0, 0, 1, 0, DIREITA};
    srand(time_t(NULL));
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
            // Lógica
            MovimentaJogador(&jogador, nos, arestas);
            // Lógica da porta (DEPOIS de mover o personagem)
            PortasFantasma(&jogador);
            // As proporções da tela
            double xprop = (double)width/FULLHD_WIDTH;
            double yprop = (double)height/FULLHD_HEIGHT;
            for(int i=0;i<NUM_CENARIO;i++)
            {
                DesenhaSpriteEscala(scene[i], 0, posicoes[i][0], posicoes[i][1], xprop, yprop, 2);                
                //C2D2_DesenhaSprite(scene[i], 0, posicoes[i][0], posicoes[i][1]);
            }
            DesenhaPersonagem(&jogador, nos, arestas, xprop, yprop);
            
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
