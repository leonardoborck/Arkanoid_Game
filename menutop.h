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
#include "carrega.h"
int menu(ALLEGRO_DISPLAY *janela = NULL)
{

	int inicio = 0;
	int posicao = 1;
	int a = 0;
	///DECLARA OS PONTEIROS-------------------
	ALLEGRO_BITMAP *imagem1 = NULL;
	ALLEGRO_FONT *fonte = NULL;
	ALLEGRO_EVENT_QUEUE *fila = NULL;
	ALLEGRO_SAMPLE *sommenu1 = NULL;
	ALLEGRO_SAMPLE *sommenu2 = NULL;
	ALLEGRO_AUDIO_STREAM *musicatop = NULL;
	///INICIA AS FUNÇOES NECESSARIAS-----------------
	al_init_font_addon();
	al_init_ttf_addon();
	al_init();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);
	al_init_image_addon();
	///DESIGNA UM ENDEREÇO PARA CADA PONTEIRO-----------
	imagem1 = al_load_bitmap("img/menu.png");
	fonte = al_load_font("img/fonte.ttf", 30, 0);
	sommenu1 = al_load_sample("menu1.ogg");
	sommenu2 = al_load_sample("menu2.ogg");
	musicatop = al_load_audio_stream("musicatop.ogg", 4, 1024);
	///-------------------------------------------------
	al_draw_bitmap(imagem1, 0, 0, 0);///DESENHA A IMAGEM DO MENU
	fila = al_create_event_queue();///CRIA UMA FILA DE EVENTOS
	al_register_event_source(fila, al_get_keyboard_event_source());///ABRE UMA FUNÇÃO QUE REGISTRA EVENTOS



	while (inicio == 0)///ENTRA NUM LOOP, ATÉ RECEBER ALGUM VALOR
	{
		al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "PRESS START");///------------------------------------------
		al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 450, ALLEGRO_ALIGN_CENTRE, "SHOP");///------------COMEÇA COM O MENU PADRÃO PRE SETADO--
		al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "EXIT");///-------------------------------------------------
		al_flip_display();///ATUALIZA A JANELA
		al_attach_audio_stream_to_mixer(musicatop, al_get_default_mixer());///DEFINE A MUSICA PARA TOCAR DE FUNDO
		al_set_audio_stream_gain(musicatop, 0.3);///REGULA O VOLUME DA MUSICA
		al_set_audio_stream_playmode(musicatop, ALLEGRO_PLAYMODE_LOOP);///COLOCA PARA PLAYMODE E DEFINE QUE TOCARA EM LOOP
		while (a<2000)///COMEÇA UM CONTADOR QUE VAI ALTERAR DE ACESO PARA APAGADO
                      ///DIVIDE ESSA CONTAGEM EM DUAS PARTES, ANTES DE 1000 TODOS ESTÃO AINDA APAGADOS, DEPOIS DE 1000 ACENDE EM RELAÇÃO A POSIÇÃO
		{

			while (!al_is_event_queue_empty(fila))
			{
				ALLEGRO_EVENT evento;///CRIA UM LUGAR PARA ARMAZENAR OS EVENTOS
				al_wait_for_event(fila, &evento);

				if (evento.type == ALLEGRO_EVENT_KEY_DOWN)///SE O EVENTO FOR UM EVENTO DE PRESSIONAR UMA TECLA
				{
					switch (evento.keyboard.keycode)///VERIFICA QUAL TECLA FOI PRESSIONADA E MUDA A VARIAVEL "POSIÇÃO" QUE MAPEIA A POSIÇÃO DO SELETOR
					{
					case ALLEGRO_KEY_UP:///VERIFICA SE A TECLA PRESSIONADA FOI A SETA PRA CIMA
						if (posicao == 1)
						{
							posicao = 3;
							a = 1000;///SETA O CONTADOR PARA QUE ELE VÁ PARA A SEGUNDA PARTE DA CONTAGEM
						}
						else if (posicao == 2)
						{
							posicao = 1;
							a = 1000;///SETA O CONTADOR PARA QUE ELE VÁ PARA A SEGUNDA PARTE DA CONTAGEM
						}
						else
						{
							posicao = 2;
							a = 1000;///SETA O CONTADOR PARA QUE ELE VÁ PARA A SEGUNDA PARTE DA CONTAGEM
						}
						al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);///SETA QUE QUANDO APERTAR A TECLA TOCA A SAMPLE
						break;
					case ALLEGRO_KEY_DOWN:///VERIFICA SE A TECLA PRESSIONADA FOI A SETA PRA BAIXO
						if (posicao == 1)
						{
							posicao = 2;
							a = 1000;///SETA O CONTADOR PARA QUE ELE VÁ PARA A SEGUNDA PARTE DA CONTAGEM
						}
						else if (posicao == 2)
						{
							posicao = 3;
							a = 1000;///SETA O CONTADOR PARA QUE ELE VÁ PARA A SEGUNDA PARTE DA CONTAGEM
						}
						else
						{
							posicao = 1;
							a = 1000;///SETA O CONTADOR PARA QUE ELE VÁ PARA A SEGUNDA PARTE DA CONTAGEM
						}
						al_play_sample(sommenu2, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);///SETA QUE QUANDO APERTAR A TECLA TOCA A SAMPLE
						break;
					case ALLEGRO_KEY_ESCAPE:///VERIFICA SE A TECLA APERTADA FOI O ESCAPE
						inicio = 1;///SETA A VARIAVEL INICIO PARA 1
						break;
					case ALLEGRO_KEY_ENTER:///VERIFICA SE A TECLA APERTADA FOI ENTER E TAMBEM A POSIÇÃO DELA
						if (posicao == 3) {///SE A POSIÇÃO FOR 3 ELE SAI DO JOGO
							inicio = 1;
						}
						else if (posicao == 1) {///SE A POSIÇÃO FOR 1 ELE ENTRA NO JOGO
                            carrega();
                            al_destroy_audio_stream(musicatop);
                            return 1;
						}
						al_play_sample(sommenu1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);///TOCA A SAMPLE DE SELEÇÃO
						break;
					}
				}
			}
			if (a<1000)///PRIMEIRA PARTE DA DIVISÃO, TODOS APAGADOS
			{
				al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "PRESS START");
				al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 450, ALLEGRO_ALIGN_CENTRE, "SHOP");
				al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "EXIT");
			}
			else if (a >= 1000)///SEGUNDA PARTE DA DIVISÃO, APENAS O QUE VERIFICA COM A POSIÇÃO ACESO, E O RESTO APAGADO
			{
				if (posicao == 1)
				{
					al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 450, ALLEGRO_ALIGN_CENTRE, "SHOP");
					al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "EXIT");
					al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "PRESS START");

					al_flip_display();
				}
				else if (posicao == 2)
				{
					al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "EXIT");
					al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "PRESS START");
					al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 450, ALLEGRO_ALIGN_CENTRE, "SHOP");
					al_flip_display();
				}
				else
				{
					al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "PRESS START");
					al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 450, ALLEGRO_ALIGN_CENTRE, "SHOP");
					al_draw_text(fonte, al_map_rgb(255, 0, 0), 450, 500, ALLEGRO_ALIGN_CENTRE, "EXIT");
					al_flip_display();
				}
			}

			al_flip_display();
			a++;
		}

		a = 0;
	}
	al_destroy_bitmap(imagem1);
	al_destroy_audio_stream(musicatop);

	return 0;
}

