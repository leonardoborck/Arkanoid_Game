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

void poscredito(){

    ALLEGRO_FONT *fonte = NULL;///MESMA LOGICA UTILIZADA NO CARREGA, MAS PARA APARECER OS CREDITOS AOS POUCOS
    ALLEGRO_SAMPLE *sommenu2 = NULL;
    sommenu2 = al_load_sample("menu2.ogg");
    fonte = al_load_font("img/fonte.ttf", 30, 0);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    int i = 0;
    while (i<1){
    Sleep(5);

    al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 100, ALLEGRO_ALIGN_CENTRE, "ARKANOID");
    al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_flip_display();
    Sleep(1000);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 200, ALLEGRO_ALIGN_CENTRE, "JOGO FEITO POR");
    al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_flip_display();
    Sleep(1000);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 300, ALLEGRO_ALIGN_CENTRE, "GABRIEL MAFRA");
    al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_flip_display();
    Sleep(1000);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "LEONARDO BORCK");
    al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_flip_display();
    Sleep(1000);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "LEONARDO HOLZ");
    al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_flip_display();
    Sleep(1000);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 600, ALLEGRO_ALIGN_CENTRE, "ALPHA VERSION 0.1");
    al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_flip_display();
    Sleep(5000);
    i++;
    }
}
