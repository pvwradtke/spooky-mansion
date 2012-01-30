/* 
 * File:   main.cpp
 * Author: pvwradtke
 *
 * Created on 28 de Janeiro de 2012, 02:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>
#include <c2d2/chienaudio2.h>
#include "defines.h"

// As dimensoes da tela
int width, height;
// As proporções da tela
double xprop;
double yprop;

// O estado do jogo
int estado_atual;

No nos[NUM_NOS] = {
    {141, 897, SEM_PORTA, 100}, // 0
    {460, 784, SEM_PORTA, 100}, // 1
    {644, 711, SEM_PORTA, 100}, // 2
    {1314, 494, SEM_PORTA, 100}, // 3
    {1422, 429, PORTA_F, 100}, // 4
    {1450, 592, SEM_PORTA, 100}, // 5
    {1587, 819, SEM_PORTA, 100}, // 6
    {1716, 752, PORTA_G, 100}, // 7
    {1101, 1152, SEM_PORTA, 100}, // 8
    {939, 915, SEM_PORTA, 100}, // 9
    {585, 1095, PORTA_C, 100}, // 10
    {1206, 738, PORTA_E, 100}, // 11
    {741, 573, SEM_PORTA, 100}, // 12
    {1122, 360, SEM_PORTA, 100}, // 13
    {1197, 297, PORTA_D, 100}, // 14
    {213, 297, SEM_PORTA, 100}, // 15
    {132, 63, PORTA_A, 100}, // 16
    {480, 111, PORTA_B, 100}, // 17
    {513, 210, SEM_PORTA, 100}, // 18
    {678, 144, SEM_PORTA, 100}, // 19
    {1200, -160, SEM_PORTA, 100}, // 20
    {1698, 120, SEM_PORTA, 100}, // 21
    {1824, 12, SEM_PORTA, 100} // 22
};

Porta portas[NUM_PORTAS] = {
    {16, BAIXO, 16},
    {17, BAIXO, 17},
    {10, DIREITA, 10},
    {14, ESQUERDA, 14},
    {11, ESQUERDA, 9},
    {4, ESQUERDA, 3},
    {7, ESQUERDA, 6}
};

Aresta arestas[NUM_ARESTAS] = {
    {50, LATERAL, 0, 1}, // I    0
    {50, LATERAL, 1, 2}, // II   1
    {50, LATERAL, 2, 3}, // III  2
    {50, LATERAL, 3, 4}, // IV   3
    {50, VERTICAL, 3, 5}, // V    4
    {50, VERTICAL, 5, 6}, // VI   5
    {50, LATERAL, 6, 7}, // VII  6
    {50, LATERAL, 6, 8}, // VIII 7
    {50, VERTICAL, 8, 9}, // IX   8
    {50, LATERAL, 9, 11}, // X    9
    {50, LATERAL, 9, 10}, // XI   10
    {50, VERTICAL, 9, 12}, // XII  11
    {50, LATERAL, 12, 13}, // XIII 12
    {50, VERTICAL, 13, 3}, // XIV  13
    {50, LATERAL, 13, 14}, // XV   14
    {50, VERTICAL, 1, 15}, // XVI  15
    {50, VERTICAL, 15, 16}, // XVII 16
    {50, VERTICAL, 17, 18}, // XVIII        17
    {50, LATERAL, 18, 19}, // XIX  18
    {50, LATERAL, 19, 20}, // XX   19
    {50, VERTICAL, 20, 21}, // XXI   20
    //    {50, VERTICAL, 21, 23},       // XXII  21
    {50, LATERAL, 21, 22}, // XXIII   21
    {1, LATERAL, 22, 0} // XXIV 22 ===>>> WARP ZONE
};
// Os vizinhos de um nó em cada direção
//cima, baixo, esquerda, direita;
Vizinhos vizinhos[NUM_NOS] = {
    {-1, -1, 22, 0}, // 0
    {15, -1, 0, 2}, // 1
    {-1, -1, 1, 2}, // 2
    {13, 4, 2, 3}, // 3
    {-1, -1, 3, -1}, // 4
    {4, 5, -1, -1}, // 5
    {5, -1, 7, 6}, // 6
    {-1, 6, -1, -1}, // 7
    {8, -1, -1, 7}, // 8
    {11, 8, 10, 9}, // 9
    {-1, -1, -1, 9}, // 10
    {-1, -1, 9, -1}, // 11
    {-1, 11, -1, 12}, // 12
    {-1, 13, 12, 14}, // 13
    {-1, -1, 14, -1}, // 14
    {16, 15, -1, -1}, // 15
    {-1, 16, -1, -1}, // 16
    {-1, 17, -1, -1}, // 17
    {17, -1, -1, 18}, // 18
    {-1, -1, 18, 19}, // 19

    {-1, -1, 19, 20}, // 20
    {-1, -1, 20, 21}, // 21
    {-1, -1, 21, 22}, // 22


};

Caminho caminhos[NUM_CAMINHOS] = {
    { PORTA_A, PORTA_B, 9,
        {16, 15, 0, 22, 21, 20, 19, 18, 17}},
    { PORTA_A, PORTA_C, 9,
        {16, 15, 1, 2, 4, 5, 7, 8, 10}},
    { PORTA_A, PORTA_D, 6,
        {16, 15, 1, 2, 13, 14}},
    { PORTA_A, PORTA_E, 8,
        {16, 15, 1, 2, 13, 12, 11, 9}},
    { PORTA_A, PORTA_F, 5,
        {16, 15, 1, 2, 3}}, // 4
    { PORTA_A, PORTA_G, 7,
        {16, 15, 1, 2, 4, 5, 6}},

    { PORTA_B, PORTA_C, 13,
        {17, 18, 19, 20, 21, 22, 0, 1, 2, 13, 12, 11, 10}},
    { PORTA_B, PORTA_D, 11,
        {17, 18, 19, 20, 21, 22, 0, 1, 2, 13, 14}},
    { PORTA_B, PORTA_E, 13,
        {17, 18, 19, 20, 21, 22, 0, 1, 2, 13, 12, 11, 9}},
    { PORTA_B, PORTA_F, 10,
        {17, 18, 19, 20, 21, 22, 0, 1, 2, 3}},
    { PORTA_B, PORTA_G, 12,
        {17, 18, 19, 20, 21, 22, 0, 1, 2, 4, 5, 6}},

    { PORTA_C, PORTA_D, 4,
        {10, 11, 12, 14}},
    { PORTA_C, PORTA_E, 2,
        {10, 9}},
    { PORTA_C, PORTA_F, 5,
        {10, 11, 12, 13, 3}},
    { PORTA_C, PORTA_G, 4,
        {10, 8, 7, 6}},

    { PORTA_D, PORTA_E, 4,
        {14, 12, 11, 9}},
    { PORTA_D, PORTA_F, 3,
        {14, 13, 3}},
    { PORTA_D, PORTA_G, 5,
        {14, 13, 4, 5, 6}},

    { PORTA_E, PORTA_F, 5,
        {9, 11, 12, 13, 3}},
    { PORTA_E, PORTA_G, 4,
        {9, 8, 7, 6}},

    { PORTA_F, PORTA_G, 4,
        {3, 4, 5, 6}}

};

// The files to load
char scenario[NUM_CENARIO][50] = {"./graphics/layout_final_background.png",
        "./graphics/layout_final_bridge.png"}; //, "./graphics/back_stairs.png",
//"./graphics/rails_left.png", "./graphics/rails_right.png",
//"./graphics/rails_middle.png"};//, "./graphics/door_a.png",
//"./graphics/door_b.png", "./graphics/door_c.png", "./graphics/door_d.png",
//"./graphics/door_e.png", "./graphics/door_f.png", "./graphics/door_g.png", 
//"./graphics/door_h.png"
//};
// The files positions on screen
int posicoes[NUM_CENARIO][2] = {
    {0, 0}
}; //, {685, 389}, {0, 314}, {1107, 314}, 
//{683, 328} }; //, {22, 834}, {498, 515}, {1328, 516}, {1843, 838}, {74, 217}, 
//{674, 71}, {1187, 74}, {1795, 217}};
// The scenery goes here
unsigned int scene[NUM_CENARIO];

unsigned int spgirl, spghost;

unsigned int fonte;

unsigned int abertura, start, overporta, overestouro;

FilaMenina fila;

int recorde = 5;

void IniciaFila(FilaMenina *f);
bool Enfileira(FilaMenina *f, int porta1, int porta2);
bool TiraFila(FilaMenina *f, int *porta1, int *porta2);

void DesenhaSpriteEscala(unsigned int spriteset, unsigned int frame, int x, int y,
        double xproportion, double yproportion);

void DesenhaPersonagem(unsigned int sprite, Personagem *p, No *nos, Aresta *arestas, double xproportion, double yproportion);
bool MovimentaJogador(Personagem *p, No *nos, Aresta *arestas, FilaMenina *f);
void MovimentaMenina(Personagem *p, No *nos, Aresta *arestas, Caminho *caminhos, FilaMenina *f);
void InverteJogador(Personagem *p);
bool PortasFantasma(Personagem *p);
bool PortasSegue(Personagem *p, FilaMenina *f, bool &acertou);
bool Jogo();

bool Enfileira(FilaMenina *f, int porta1, int porta2)
{
    if(f->tamanho<PORTAS_LEMBRAR)
    {
        // Incrementa o tamanho
        f->tamanho++;
        // Incrementa o fim para a posição final real
        f->fim=(f->fim+1)%PORTAS_LEMBRAR;
        f->fila[f->fim][0] = porta1;
        f->fila[f->fim][1] = porta2;
        return true;
    }
    else
    {
        f->estouro=true;
        return false;
    }
}


void IniciaFila(FilaMenina *f)
{
    f->inicio=0;
    f->fim=-1;
    f->tamanho=0;
    f->estouro=false;
}
bool TiraFila(FilaMenina *f, int *porta1, int *porta2)
{
    if(f->tamanho>0)
    {
        *porta1 = f->fila[f->inicio][0];
        *porta2 = f->fila[f->inicio][1];
        f->tamanho--;
        f->inicio=(f->inicio+1)%PORTAS_LEMBRAR;
        return true;
    }
    else
        return false;
}


void DesenhaSpriteEscala(unsigned int spriteset, unsigned int frame, int x, int y,
        double xproportion, double yproportion, int yoff) {
    int largura, altura;
    if (C2D2_DimensoesSprite(spriteset, &largura, &altura)) {
        int xc[4], yc[4];
        xc[0] = xc[3] = x*xproportion;
        xc[1] = xc[2] = xc[0] + largura*xproportion;
        yc[0] = yc[1] = yoff + y*yproportion;
        yc[2] = yc[3] = yoff + yc[0] + altura*yproportion;
        C2D2_DesenhaSpriteEfeito(spriteset, frame, xc, yc, 255, 255, 255, 255);
    }
}

void DesenhaPersonagem(unsigned int sprite, Personagem *p, No *nos, Aresta *arestas, double xproportion, double yproportion) {
    // Escolhe se é na horizontal ou na vertical a aresta
    int xpers, ypers;
    int origem, destino;
    
    origem = p->no_origem;
    destino = p->no_destino;
    xpers = nos[origem].x + ((double) p->distancia / arestas[p->aresta].distancia)*
            (nos[destino].x - nos[origem].x);
    ypers = nos[origem].y + ((double) p->distancia / arestas[p->aresta].distancia)*
            (nos[destino].y - nos[origem].y);
    // Atualiza os frames do personagem
    p->delay++;
    if(p->delay >= p->framedelay)
    {
        p->delay = 0;
        p->frame = (p->frame+1)%p->totalframes;
    }
    if (!sprite)
        C2D2P_CirculoPintado(xpers * xproportion, ypers * yproportion, 30 * xproportion, 255, 0, 0);
    else
    {
        int base=0;
        switch(p->direcao)
        {
            case DIREITA:
                base = 2;
                break;
            case ESQUERDA:
                base = 0;
                break;
            case CIMA:
                base = 3;
                break;
            case BAIXO:
                base = 1;
                break;
        }
        DesenhaSpriteEscala(sprite, (base*p->totalframes)+p->frames[p->frame], xpers-p->xgravidade, ypers-p->ygravidade, xproportion, yproportion,0);
        //C2D2_DesenhaSprite(sprite, p->frame, (xpers-p->xgravidade)*xproportion, (ypers-p->ygravidade)*yproportion);
        //C2D2P_CirculoPintado(xpers*xproportion, ypers*yproportion, 30 * xproportion, 0, 255, 0);
    }
}

void InverteJogador(Personagem *p) {
    p->distancia = arestas[p->aresta].distancia - p->distancia;
    int temp = p->no_destino;
    p->no_destino = p->no_origem;
    p->no_origem = temp;
    if (p->direcao == CIMA)
        p->direcao = BAIXO;
    else if (p->direcao == BAIXO)
        p->direcao = CIMA;
    else if (p->direcao == DIREITA)
        p->direcao = ESQUERDA;
    else if (p->direcao == ESQUERDA)
        p->direcao = DIREITA;
}

void MovimentaMenina(Personagem *p, No *nos, Aresta *arestas, Caminho *caminhos, FilaMenina *f) {
    int origem = arestas[p->aresta].origem;
    int destino = arestas[p->aresta].destino;
        
    if(arestas[p->aresta].angulo==LATERAL)
    {
        if(nos[p->no_origem].x < nos[p->no_destino].x)
            p->direcao = DIREITA;
        else
            p->direcao = ESQUERDA;
    }
    else
    {
        if(nos[p->no_origem].y < nos[p->no_destino].y)
            p->direcao = BAIXO;
        else
            p->direcao = CIMA;
    }
                
    // Aumenta a distância
    if (p->distancia < arestas[p->aresta].distancia)
        p->distancia++;
    // Lógica para trocar de aresta
    if (p->distancia >= arestas[p->aresta].distancia) {
        int noatual = p->no_destino;

        // Testa com o movimento atual do personagem
        p->indice++;
        if (p->indice == caminhos[p->caminho].numarestas) {
            int porta1, porta2;
            int porta_entrada = nos[p->no_destino].porta;
            if(porta_entrada == PORTA_C)
                printf("Chegou!");
            //chegou na porta
            do {
                porta1 = random() % NUM_PORTAS;
            } while (porta1 == nos[p->no_destino].porta);
            int origem, destino;

            Enfileira(f, porta_entrada, porta1);
            //chegou na porta
            do {
                porta2 = random() % NUM_PORTAS;
            } while (porta2 == porta1 || porta2 == nos[p->no_destino].porta);

            for (int i = 0; i < NUM_CAMINHOS; i++) {
                if ((caminhos[i].origem == porta1 && caminhos[i].destino == porta2)
                        || (caminhos[i].origem == porta2 && caminhos[i].destino == porta1)) {
                    //se nao esta invertido
                    if (porta2 > porta1) {
                        p->invertido = false;
                        p->no_origem = portas[porta1].no;
                        if(arestas[caminhos[i].arestas[0]].origem == p->no_origem)
                                p->no_destino = arestas[caminhos[i].arestas[0]].destino;
                        else
                            p->no_destino = arestas[caminhos[i].arestas[0]].origem;
                    } else {
                        p->invertido = true;
                        p->no_origem = portas[porta1].no;
                        int idx = caminhos[i].numarestas - 1;
                        if(arestas[caminhos[i].arestas[idx]].origem == p->no_origem)
                                p->no_destino = arestas[caminhos[i].arestas[idx]].destino;
                        else
                            p->no_destino = arestas[caminhos[i].arestas[idx]].origem;
                    }
                    p->indice = 0;
                    p->caminho = i;
                    p->distancia = 0;
                    break;
                }
                // Acha em qual nó está essa porta
                /*p->no_origem = portas[porta].no;
                p->aresta = portas[porta].aresta;
                p->direcao = portas[porta].direcao;
                p->distancia = 0;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;*/
            }

        } else {
            p->distancia = 0;
            if (!p->invertido)
                p->aresta = caminhos[p->caminho].arestas[p->indice];
            else
                p->aresta = caminhos[p->caminho].arestas[caminhos[p->caminho].numarestas - 1 - p->indice];

            p->no_origem = noatual;
            if (p->no_origem == arestas[p->aresta].origem)
                p->no_destino = arestas[p->aresta].destino;
            else
                p->no_destino = arestas[p->aresta].origem;

        }

    }
}

bool MovimentaJogador(Personagem *p, No *nos, Aresta *arestas, FilaMenina *f) {
    C2D2_Botao *teclado = C2D2_PegaTeclas();
    // O movimento é de acordo com o eixo (saco!)
    if (arestas[p->aresta].angulo == LATERAL) {
        // Sabendo que é na lateral, sabe se ir para a esquerda ou direita aumenta/diminui a distância
        if (p->direcao == DIREITA && teclado[C2D2_ESQUERDA].pressionado && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        else if (p->direcao == ESQUERDA && teclado[C2D2_DIREITA].pressionado && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        // Os nós de origem e destino
        int origem = arestas[p->aresta].origem;
        int destino = arestas[p->aresta].destino;
        //        if(nos[origem].x < nos[destino].x)
        //        {
        if (p->distancia < arestas[p->aresta].distancia)
            p->distancia++;
        //        }
        //        else
        //        {
        //            if(p->distancia > 0)
        //                p->distancia--;
        //        }
    } else {
        // Sabendo que é na lateral, sabe se ir para a esquerda ou direita aumenta/diminui a distância
        if (p->direcao == CIMA && teclado[C2D2_BAIXO].pressionado && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        else if (p->direcao == BAIXO && teclado[C2D2_CIMA].pressionado && p->distancia < arestas[p->aresta].distancia)
            InverteJogador(p);
        // Os nós de origem e destino
        int origem = arestas[p->aresta].origem;
        int destino = arestas[p->aresta].destino;
        //        if(nos[origem].y > nos[destino].y)
        //        {
        if (p->distancia < arestas[p->aresta].distancia)
            p->distancia++;
        //        }
        //        else
        //        {
        //            if(p->distancia > 0)
        //                p->distancia--;
        //        }
    }
    // Lógica para trocar de aresta
    if (p->distancia == arestas[p->aresta].distancia) {
        int noatual = p->no_destino;
        // Testa primeiro se troca com o teclado
        if (teclado[C2D2_CIMA].ativo) {
            if (vizinhos[noatual].cima != -1) {
                p->direcao = CIMA;
                p->distancia = 0;
                p->aresta = vizinhos[noatual].cima;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        } else if (teclado[C2D2_BAIXO].ativo) {
            if (vizinhos[noatual].baixo != -1) {
                p->direcao = BAIXO;
                p->distancia = 0;
                p->aresta = vizinhos[noatual].baixo;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        } else if (teclado[C2D2_ESQUERDA].ativo) {
            if (vizinhos[noatual].esquerda != -1) {
                p->direcao = ESQUERDA;
                p->distancia = 0;
                p->aresta = vizinhos[noatual].esquerda;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        } else if (teclado[C2D2_DIREITA].ativo) {
            if (vizinhos[noatual].direita != -1) {
                p->direcao = DIREITA;
                p->distancia = 0;
                p->aresta = vizinhos[noatual].direita;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }// Testa agora com o movimento atual do jogador
        else if (p->direcao == CIMA) {
            if (vizinhos[noatual].cima != -1) {
                p->distancia = 0;
                p->aresta = vizinhos[noatual].cima;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        } else if (p->direcao == BAIXO) {
            if (vizinhos[noatual].baixo != -1) {
                p->distancia = 0;
                p->aresta = vizinhos[noatual].baixo;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        } else if (p->direcao == ESQUERDA) {
            if (vizinhos[noatual].esquerda != -1) {
                p->distancia = 0;
                p->aresta = vizinhos[noatual].esquerda;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        } else if (p->direcao == DIREITA) {
            if (vizinhos[noatual].direita != -1) {
                p->distancia = 0;
                p->aresta = vizinhos[noatual].direita;
                p->no_origem = noatual;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
            }
        }

    }
    return true;
}

bool PortasFantasma(Personagem *p) {
    // Se o fantasma está numa porta porque acabou de percorrer a distância total
    if (p->distancia == arestas[p->aresta].distancia && nos[p->no_destino].porta != SEM_PORTA) {
        // Sorteia uma nova porta!!!
        int porta;
        // Repete o sorteio até achar uma porta diferente da atual
        do {
            porta = random() % NUM_PORTAS;
        } while (porta == nos[p->no_destino].porta);
        // Acha em qual nó está essa porta
        p->no_origem = portas[porta].no;
        p->aresta = portas[porta].aresta;
        p->direcao = portas[porta].direcao;
        p->distancia = 0;
        if (p->no_origem == arestas[p->aresta].origem)
            p->no_destino = arestas[p->aresta].destino;
        else
            p->no_destino = arestas[p->aresta].origem;
    }
}

bool PortasSegue(Personagem *p, FilaMenina *f, bool *acertou) {
    // Por definição, não acertou a porta
    *acertou = false;
    // Se o fantasma está numa porta porque acabou de percorrer a distância total
    if (p->distancia == arestas[p->aresta].distancia && nos[p->no_destino].porta != SEM_PORTA) {
        // Recupera as portas na fila e verifica se a entrada bate com a atual
        int porta_atual = nos[p->no_destino].porta;
        int porta1, porta2;
        // Tenta tirar da fila. Se falha, é porque o outro personagem ainda
        // não entrou em nenhuma porta.
        if (TiraFila(f, &porta1, &porta2)) {
            // Compara se está entrando na porta certa (1)
            if (porta1 == porta_atual) {
                *acertou = true;
                // Acha em qual nó está essa porta de destino
                p->no_origem = portas[porta2].no;
                p->aresta = portas[porta2].aresta;
                p->direcao = portas[porta2].direcao;
                p->distancia = 0;
                if (p->no_origem == arestas[p->aresta].origem)
                    p->no_destino = arestas[p->aresta].destino;
                else
                    p->no_destino = arestas[p->aresta].origem;
                return true;
            } else
                // O cabeção errou a porta
                return false;
        } else
            return false;
    }
    return true;
}

bool Jogo() {
    // O jogador começa no nó 2, indo para a direita
    Personagem jogador = {2, 2, 3, 0, DIREITA, 146, 126};
    jogador.frame = 0;
    jogador.delay = 0;
    jogador.frames[0] = 0;
    jogador.frames[1] = 1;
    jogador.frames[2] = 2;
    jogador.frames[3] = 3;
    jogador.totalframes = 4;
    jogador.framedelay = 15;
    // A menina começa no nó 3, indo para a porta F
    Personagem menina = {3, 3, 4, 0, DIREITA,
        128, 168, 4, 4, false};
    //aresta; - no_origem -  no_destino - distancia - direcao -xgravidade, ygravidade;caminho - indice - invertido
    menina.frame = 0;
    menina.delay = 0;
    menina.frames[0] = 0;
    menina.frames[1] = 1;
    menina.frames[2] = 2;
    menina.frames[3] = 3;
    menina.totalframes = 4;
    menina.framedelay = 15;
    /*int frame;    
    int frames[10];
    int totalframes;
    int framedelay;    */

    srand(time(NULL));
    // Recupera o teclado
    C2D2_Botao *teclado = C2D2_PegaTeclas();
    bool debuggraph = false;
    bool debuggirl = false;
    bool debugcaminho = false;
    int caminho = 0;


    int placar = 0;
    int vezes = VEL_INI;
    FilaMenina f;
    IniciaFila(&f);
    bool errouporta = false;
    bool estourou = false;
    int tgameover = 240;
    char texto[100];
    int inicio=240;
    while (!teclado[C2D2_ESC].pressionado && !teclado[C2D2_ENCERRA].pressionado) {
        // Debuggin info
        if (teclado[C2D2_F1].pressionado)
            debuggraph = !debuggraph;
        if (teclado[C2D2_F2].pressionado)
            debuggirl = !debuggirl;
        if (teclado[C2D2_F3].pressionado)
            debugcaminho = !debugcaminho;
        if (teclado[C2D2_W].pressionado)
            caminho = (caminho + 1) % NUM_CAMINHOS;
        if (teclado[C2D2_Q].pressionado)
            if (--caminho == 0)
                caminho = 0;

        // Lógica
        for (int i = 0; i < vezes; i++) {
            if (!estourou && !errouporta) {
                MovimentaJogador(&jogador, nos, arestas, &f);
                MovimentaMenina(&menina, nos, arestas, caminhos, &f);
            }
            // Lógica da porta (DEPOIS de mover o personagem)
            //PortasFantasma(&jogador);
            bool marcou = false;
            if (!PortasSegue(&jogador, &f, &marcou) && !errouporta) {
                errouporta = true;
                printf("O fantasma errou a porta\n");
            }
            if (marcou) {
                placar++;
                // Testa se aumenta a velocidade
                if (vezes < VEL_INI + placar / DIV_PLACAR) {
                    printf("Speed up!\n");
                    vezes = VEL_INI + placar / DIV_PLACAR;
                }
                if (recorde < placar)
                    recorde = placar;
            }
            if (!estourou) {
                if (f.estouro) {
                    printf("O fantasma deixou de seguir a menina.\n");
                    estourou = true;
                }
            }
        }
        for (int i = 0; i < NUM_CENARIO; i++) {
            
            if (i == 1) {
                if (!errouporta && (jogador.aresta == 12 || jogador.aresta == 11))
                    DesenhaPersonagem(spghost, &jogador, nos, arestas, xprop, yprop);
                if (!estourou && (menina.aresta == 12 || menina.aresta == 11))
                    DesenhaPersonagem(spgirl, &menina, nos, arestas, xprop, yprop);
            }
            DesenhaSpriteEscala(scene[i], 0, posicoes[i][0], posicoes[i][1], xprop, yprop, 2);
            //C2D2_DesenhaSprite(scene[i], 0, posicoes[i][0], posicoes[i][1]);
        }
        if (!errouporta && jogador.aresta != 12 && jogador.aresta != 11)
            DesenhaPersonagem(spghost, &jogador, nos, arestas, xprop, yprop);
        if (!estourou && menina.aresta != 12 && menina.aresta != 11)
            DesenhaPersonagem(spgirl, &menina, nos, arestas, xprop, yprop);

        // Desenha as arestas
        if (debuggraph) {
            for (int i = 0; i < NUM_ARESTAS; i++) {
                int origem = arestas[i].origem;
                int destino = arestas[i].destino;
                C2D2P_Linha(nos[origem].x*xprop, nos[origem].y*yprop,
                        nos[destino].x*xprop, nos[destino].y*yprop,
                        0, 0, 255);
            }
        }
        // Desenha as arestas 
        if (debuggirl) {
            int caminho = menina.caminho;

            for (int i = 0; i < caminhos[caminho].numarestas; i++) {

                int aresta = caminhos[caminho].arestas[i];

                int origem = arestas[aresta].origem;
                int destino = arestas[aresta].destino;
                C2D2P_Linha(nos[origem].x*xprop, nos[origem].y*yprop,
                        nos[destino].x*xprop, nos[destino].y*yprop,
                        255, 0, 255);
            }
        }
        // Desenha as arestas 
        if (debugcaminho) {
            for (int i = 0; i < caminhos[caminho].numarestas; i++) {

                int aresta = caminhos[caminho].arestas[i];

                int origem = arestas[aresta].origem;
                int destino = arestas[aresta].destino;
                C2D2P_Linha(nos[origem].x*xprop, nos[origem].y*yprop,
                        nos[destino].x*xprop, nos[destino].y*yprop,
                        255, 255, 0);
            }
        }
        // Desenha o placar
/*        sprintf(texto, "Score: %03i", placar);
        C2D2_DesenhaTexto(fonte, 10,10, texto, C2D2_TEXTO_ESQUERDA);
        sprintf(texto, "Record: %03i", recorde);
        C2D2_DesenhaTexto(fonte, 1070,10, texto, C2D2_TEXTO_DIREITA);*/
        
        if (errouporta || estourou) {
            if (--tgameover == 0)
                break;
            if(errouporta)
                DesenhaSpriteEscala(overporta, 0, 686, 502, xprop, yprop, 0);
            if(estourou)
                DesenhaSpriteEscala(overestouro, 0, 742, 498, xprop, yprop, 0);
        }
        if(inicio>0)
        {
            inicio--;
            DesenhaSpriteEscala(start, 0, 769, 465, xprop, yprop, 0);
        }

        C2D2_Sincroniza(C2D2_FPS_PADRAO);
    }

    printf("Quitting\n");
    if (teclado[C2D2_ENCERRA].pressionado) {
        C2D2_Sincroniza(C2D2_FPS_PADRAO);
        return false;
    } else {
        C2D2_Sincroniza(C2D2_FPS_PADRAO);
        return true;
    }

}

int main(int ac, char **av) {
    // A resolução da tela
    width =  HD_WIDTH;
    height = HD_HEIGHT;
    // As proporções da tela
    xprop = (double) width / FULLHD_WIDTH;
    yprop = (double) height / FULLHD_HEIGHT;

    // Calcula as distâncias entre as arestas, menos a última, que é o warp zone
    for (int i = 0; i < NUM_ARESTAS - 1; i++) {
        int origem = arestas[i].origem;
        int destino = arestas[i].destino;
        double distancia = sqrt(pow(nos[origem].x - nos[destino].x, 2) + pow(nos[origem].y - nos[destino].y, 2));
        arestas[i].distancia = distancia / 2;
    }

    ////////////////////////////
    //tela escolha resolução //
    //////////////////////////
    if (!C2D2_Inicia(width, height, C2D2_TELA_CHEIA, C2D2_DESENHO_OPENGL, (char*) "Spooky Mansion")) {
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
    for (int i = 0; i < NUM_CENARIO && !erro; i++) {
        if ((scene[i] = C2D2_CarregaSpriteSet(scenario[i], 0, 0)) == 0)
            erro = true;
    }
    if ((spgirl = C2D2_CarregaSpriteSet("./graphics/girl_50p.png", 246, 273)) == 0)
        erro = true;
    if ((spghost = C2D2_CarregaSpriteSet("./graphics/ghost_50p.png", 246, 273)) == 0)
        erro = true;
    if ((abertura = C2D2_CarregaSpriteSet("./graphics/title2.jpg",0,0)) == 0)
        erro = true;
    if ((start = C2D2_CarregaSpriteSet("./graphics/start.png",0,0)) == 0)
        erro = true;
    if ((overporta = C2D2_CarregaSpriteSet("./graphics/over_porta.png",0,0)) == 0)
        erro = true;
    if ((overestouro = C2D2_CarregaSpriteSet("./graphics/over_estouro.png",0,0)) == 0)
        erro = true;
    
    bool roda = true;
    if (!erro) {
    
    //C2D2_Sincroniza(C2D2_FPS_PADRAO);
    //C2D2_Pausa(3000);

        int estado = TELA_MENU;
        while (roda) {
            switch (estado) {
                case TELA_JOGO:
                    roda = Jogo();
                    estado = TELA_MENU;
                    break;

                case TELA_MENU:
                    DesenhaSpriteEscala(abertura, 0, 0, 0, xprop, yprop,0);
                    C2D2_Sincroniza(C2D2_FPS_PADRAO);
                    if(teclado[C2D2_ESC].pressionado)
                        roda=false;
                    if(teclado[C2D2_ESPACO].pressionado || teclado[C2D2_ENTER].pressionado)
                        estado = TELA_JOGO;
                    break;

            }
        }
    }
    printf("Exiting game\n");
    // Encerra tudo
    CA2_Encerra();
    C2D2_Encerra();
    return 0;
}
