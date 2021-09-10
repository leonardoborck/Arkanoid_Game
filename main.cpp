#include <iostream>
#include <allegro5/allegro.h>
#include <time.h>
#include <Windows.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "menutop.h"
#include "jogo.h"
#include "poscredito.h"
///JOGO FEITO POR : LEONARDO HOLZ, LEONARDO BORCK, GABRIEL MAFRA

int main()
{
    ALLEGRO_DISPLAY *janela = NULL;///CRIA UM PONTEIRO PARA JANELA
    al_init();///INICIA O ALLEGRO
    janela = al_create_display(900, 700);///DEFINE O TAMANHO DA JANLA
    int roda = menu(janela);///CRIA E VERIFICA O VALOR RETORNADO NA FUNÇÃO MENU
    while (roda >0) {///SE O VALOR RETORNADO FOR >0 ELE ENTROU NO JOGO
        roda = jogo(janela);///DEPOIS DE ENTRAR NO JOGO VERIFICA O VALOR RETORNADO DA FUNÇÃO JOGO
        if (roda == 1) roda = menu(janela);///SE A FUNÇÃO JOGO RETURNAR 1, VOLTA PARA O MENU, SE RETORNAR 0 SAI DO WHILE
    }
    poscredito();///SOLTA OS CREDITOS DO JOGO
    al_destroy_display(janela);///DESTROI A JANELA
    return 0;
}
