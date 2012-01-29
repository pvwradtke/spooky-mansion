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

No nos[NUM_NOS] = {{141, 897, SEM_PORTA, 100},     // 0
                {460, 784, SEM_PORTA, 100},     // 1
                {644, 711, SEM_PORTA, 100},     // 2
                {1314, 494, SEM_PORTA, 100},    // 3
                {1422, 429, PORTA_F, 100},      // 4
                {1450, 592, SEM_PORTA, 100},      // 5
                {1587, 819, SEM_PORTA, 100},     // 6
                {1716, 752, PORTA_G, 100},        // 7
                {1101, 1152, SEM_PORTA, 100},       // 8
                {939, 915, SEM_PORTA, 100},         // 9
                {585, 1095, PORTA_C, 100},      // 10
                {1206, 738, PORTA_E, 100},      // 11
                {741, 573, SEM_PORTA, 100},      // 12
                {1122, 360, SEM_PORTA, 100},        // 13
                {1197, 297, PORTA_D, 100},      // 14
                {213, 297, SEM_PORTA, 100},     // 15
                {132, 63, PORTA_A, 100},       // 16
                {480, 111, PORTA_B, 100},     // 17
                {513, 210, SEM_PORTA, 100},     // 18
                {678, 144, SEM_PORTA, 100},        // 19
                {1200, -160, SEM_PORTA, 100},        // 20
                {1698, 120, SEM_PORTA, 100},        // 21
                {1824, 12, SEM_PORTA, 100}        // 22
};

Porta portas[NUM_PORTAS] = { {16, BAIXO, 16}, {17, BAIXO, 17}, {10, DIREITA, 10}, 
{14, ESQUERDA, 14}, {11, ESQUERDA, 9}, {4, ESQUERDA, 3}, {7, ESQUERDA, 6}};

Aresta arestas[NUM_ARESTAS] ={
    {50, LATERAL, 0, 1},        // I    0
    {50, LATERAL, 1, 2},        // II   1
    {50, LATERAL, 2, 3},       // III  2
    {50, LATERAL, 3, 4},       // IV   3
    {50, VERTICAL, 3, 5},        // V    4
    {50, VERTICAL, 5, 6},        // VI   5
    {50, LATERAL, 6, 7},        // VII  6
    {50, LATERAL, 6, 8},       // VIII 7
    {50, VERTICAL, 8, 9},       // IX   8
    {50, LATERAL, 9, 11},      // X    9
    {50, LATERAL, 9, 10},      // XI   10
    {50, VERTICAL, 9, 12},     // XII  11
    {50, LATERAL, 12, 13},      // XIII 12
    {50, VERTICAL, 13, 3},      // XIV  13
    {50, LATERAL, 13, 14},     // XV   14
    {50, VERTICAL, 1, 15},      // XVI  15
    {50, VERTICAL, 15, 16},     // XVII 16
    {50, VERTICAL, 17, 18},      // XVIII        17
    {50, LATERAL, 18, 19},      // XIX  18
    {50, LATERAL, 19, 20},       // XX   19
    {50, VERTICAL, 20, 21},       // XXI   20
//    {50, VERTICAL, 21, 23},       // XXII  21
    {50, LATERAL, 21, 22},       // XXIII   21
    {1, LATERAL, 22, 0}        // XXIV 22 ===>>> WARP ZONE
};
// Os vizinhos de um nó em cada direção
//cima, baixo, esquerda, direita;
Vizinhos vizinhos[NUM_NOS]={ {-1, -1, 22, 0},   // 0
                             {15, -1, 0, 2},     // 1
                             {-1, -1, 1, 2},     // 2
                             {13, 4, 2, 3},     // 3
                             {-1, -1, 3, -1},   // 4
                             {4, 5, -1, -1},     // 5
                             {5, -1, 7, 6},     // 6
                             {-1, 6, -1, -1},   // 7
                             {8, -1, -1, 7},   // 8
                             {11, 8, 10, 9},  // 9
                             {-1, -1, -1, 9},  // 10
                             {-1, -1, 9, -1},  // 11
                             {-1, 11, -1, 12},  // 12
                             {-1, 13, 12, 14},  // 13
                             {-1,-1, 14, -1},   // 14
                             {16, 15, -1, -1},  // 15
                             {-1, 16, -1, -1},  // 16
                             {-1, 17, -1, -1},  // 17
                             {17, -1, -1, 18},  // 18
                             {-1, -1, 18, 19},   // 19
                             
                             {-1, -1, 19, 20},  // 20
                             {-1, -1, 20, 21},  // 21
                             {-1, -1, 21, 22},  // 22

                             
};

Caminho caminhos[21]={
    { PORTA_A, PORTA_B, 8,{16, 15, 0,20,19,18,17}},
    { PORTA_A, PORTA_C, 9,{16, 15, 1, 2,4,5,7,8,9,10}},
    { PORTA_A, PORTA_D, 6,{16, 15, 1, 2,13,14}},
    { PORTA_A, PORTA_E, 8,{16, 15, 1, 2, 13, 12, 11,9}},
    { PORTA_A, PORTA_F, 5,{16, 15, 1, 2, 3}},
    { PORTA_A, PORTA_G, 7,{16, 15, 1, 2, 4,5,6}},
    
    { PORTA_B, PORTA_C, 12,{17, 18, 19,20,22,0,1,2,13,12,11,10}},
    { PORTA_B, PORTA_D, 10,{17, 18, 19,20,22,0,1,2,13,14}},
    { PORTA_B, PORTA_E, 12,{17, 18, 19,20,22,0,1,2,13,12,11,9}},
    { PORTA_B, PORTA_F, 9,{17, 18, 19,20,22,0,1,2,3}},
    { PORTA_B, PORTA_G, 11,{17, 18, 19,20,22,0,1,2,4,5,6}},
    
    { PORTA_C, PORTA_D, 4,{10, 11, 12,14}},
    { PORTA_C, PORTA_E, 2,{10,9}},
    { PORTA_C, PORTA_F, 5,{10,11,12,13,4}},
    { PORTA_C, PORTA_G, 4,{10,8,7,6}},
    
    { PORTA_D, PORTA_E, 4,{14,12,11,9}},
    { PORTA_D, PORTA_F, 3,{14,13,3}},
    { PORTA_D, PORTA_G, 5,{14,13,4,5,6}},
    
    { PORTA_E, PORTA_F, 5,{9,11,12,13,3}},
    { PORTA_E, PORTA_G, 4,{9,8,7,6}},
    
    { PORTA_F, PORTA_G, 4,{3,4,5,6}}
    
};

// The files to load
char scenario[NUM_CENARIO][30] = {"./graphics/screenshot.png"}; //, "./graphics/back_stairs.png",
        //"./graphics/rails_left.png", "./graphics/rails_right.png",
        //"./graphics/rails_middle.png"};//, "./graphics/door_a.png",
        //"./graphics/door_b.png", "./graphics/door_c.png", "./graphics/door_d.png",
        //"./graphics/door_e.png", "./graphics/door_f.png", "./graphics/door_g.png", 
        //"./graphics/door_h.png"
    //};
// The files positions on screen
    int posicoes[NUM_CENARIO][2] = { {0, 0} }; //, {685, 389}, {0, 314}, {1107, 314}, 
    //{683, 328} }; //, {22, 834}, {498, 515}, {1328, 516}, {1843, 838}, {74, 217}, 
    //{674, 71}, {1187, 74}, {1795, 217}};
    

void DesenhaSpriteEscala(unsigned int spriteset, unsigned int frame, int x, int y, 
        double xproportion, double yproportion);

void DesenhaPersonagem(Personagem *p, No *nos, Aresta *arestas, double xproportion, double yproportion);
void MovimentaJogador(Personagem *p, No *nos, Aresta *arestas);
void movimentaMenina(Personagem *p, No *nos, Aresta *arestas, Caminho *caminhos);
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
    C2D2P_CirculoPintado(xpers*xproportion, ypers*yproportion, 30*xproportion, 255, 0, 0);
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
