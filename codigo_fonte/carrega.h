
///FUNÇÃO DE LOADING DA TELA
void carrega(){

	ALLEGRO_FONT *fonte = NULL;///SETA O PONTEIRO DAS FONTES
	ALLEGRO_SAMPLE *sommenu1 = NULL;///SETA O PONTEIRO DA SAMPLE
	al_reserve_samples(5);///NECESSARIO PARA ARMAZENAR A SAMPLE
	al_init_image_addon();///COMEÇA AS IMAGENS
	fonte = al_load_font("img/fonte.ttf", 30, 0);///SETA A FONTE PARA A DESEJADA
	sommenu1 = al_load_sample("menu1.ogg");///SETA A SAMPLE PARA A DESEJADA
    al_play_sample(sommenu1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);///TOCA A SAMPLE
    al_clear_to_color(al_map_rgb(0,0,0));///SETA A JANELA PARA FICAR TODA PRETA
    al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "LOADING");///DEMONSTRA UM LOADING TODO APAGADO QUE VAI FICANDO "ACENDENDO" AOS POUCOS
    al_flip_display();
    int i = 0;
    while (i<1){
    Sleep(5);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "L");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "LO");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "LOA");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "LOAD");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "LOADI");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "LOADIN");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 386, 400, 0, "LOADING");
    al_flip_display();
    Sleep(500);
    al_draw_text(fonte, al_map_rgb(128, 0, 0), 450, 400, ALLEGRO_ALIGN_CENTRE, "LOADING");
    al_flip_display();
    i++;
    }
}
