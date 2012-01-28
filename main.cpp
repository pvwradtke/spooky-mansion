/* 
 * File:   main.cpp
 * Author: pvwradtke
 *
 * Created on 28 de Janeiro de 2012, 02:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <c2d2/chien2d2.h>
#include <c2d2/chienaudio2.h>
#include "defines.h"

//void DesenhaSpriteReduzido(unsigned int )

int main(int ac, char **av) {
    // A resolução da tela
    int width = NETBOOK_WIDTH;
    int height = NETBOOK_HEIGHT;
    // The files to load
    char scenario[NUM_CENARIO][30] = {"./graphics/back_main.png", "./graphics/back_stairs.png",
        "./graphics/rails_left.png", "./graphics/rails_right.png",
        "./graphics/rails_middle.png", "./graphics/door_a.png",
        "./graphics/door_b.png", "./graphics/door_c.png", "./graphics/door_d.png",
        "./graphics/door_e.png", "./graphics/door_f.png", "./graphics/door_g.png", 
        "./graphics/door_h.png"
    };
    int posicoes[NUM_CENARIO][2] = { {0, 0}, {685, 389}, {0, 314}, {1107, 314}, 
    {683, 328}, {22, 834}, {498, 515}, {1328, 516}, {1843, 838}, {74, 217}, 
    {674, 71}, {1187, 74}, {1795, 217}};
    unsigned int scene[NUM_CENARIO];
    
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
                C2D2_DesenhaSprite(scene[i], 0, posicoes[i][0], posicoes[i][1]);
            C2D2_Sincroniza(C2D2_FPS_PADRAO);
        }
    }
    printf("Quitting\n");
    // Encerra tudo
    CA2_Encerra();
    C2D2_Encerra();
    return 0;
}
