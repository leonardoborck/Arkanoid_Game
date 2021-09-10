#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define LARGURA_TELA 900
#define ALTURA_TELA 700
#define PAREDE_ESQUERDA 20
#define PAREDE_DIREITA 660
#define PAREDE_CIMA 18
#define DIREITA 0
#define ESQUERDA 1
#define TAM_L 5
#define TAM_C 10
#define FPS 60.0
#define LARGURA_PLATAFORMA 120
#define ALTURA_PLATAFORMA 20
#define SAI -2000
using namespace std;

struct posicao1 {

	int PiX, PiY, X, Y, LB, AB;

};


void bubblesort1(int vet[18], int n) {
	int i, j, cond, temp;
	cond = 1;
	for (i = n - 1; (i >= 1) && (cond == 1); i--) {
		cond = 0;
		for (j = 0; j < i; j++) {
			if (vet[j + 1] < vet[j]) {
				temp = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = temp;
				cond = 1;
			}
		}
	}
}

void sorteio(int vet[18]) {
	srand(time(NULL));
	int a = 0;
	int randomico;
	while (a < 18) {
		randomico = rand() % 30;
		int check = 0;
		while (check < a) {
			if (vet[check] == randomico) {
				randomico = rand() % 30;
				check = 0;
			}
			check++;
		}
		vet[a] = randomico;
		a++;
	}
	a = 0;
	bubblesort1(vet, 18);
}

void frames(posicao1 blocos[TAM_L][TAM_C], ALLEGRO_BITMAP *bola, ALLEGRO_BITMAP *plataforma, ALLEGRO_BITMAP *fundo, ALLEGRO_BITMAP *itens, int plat_x, int plat_y, int bola_x, int bola_y, float velx, float vely, int vidas, ALLEGRO_BITMAP *vidaimg1, ALLEGRO_BITMAP *vidaimg2, ALLEGRO_BITMAP *vidaimg3, ALLEGRO_FONT *fonte, int pontuacao) {

	al_draw_bitmap(fundo, 0, 0, 0);
	if (vidas == 3) al_draw_bitmap(vidaimg1, 743, 500 , 0);
	else if (vidas == 2) al_draw_bitmap(vidaimg2, 743, 500 , 0);
	else if (vidas == 1) al_draw_bitmap(vidaimg3, 743, 500 , 0);
	al_draw_textf(fonte ,al_map_rgb(0,0,0),785,310,ALLEGRO_ALIGN_CENTER,"%d", pontuacao);
	for (int linha = 0; linha < TAM_L; linha++) {
		for (int coluna = 0; coluna < TAM_C; coluna++) {


			al_draw_bitmap_region(itens, blocos[linha][coluna].PiX, blocos[linha][coluna].PiY, blocos[linha][coluna].LB, blocos[linha][coluna].AB, blocos[linha][coluna].X, blocos[linha][coluna].Y, 0);

		}
	}
	al_draw_bitmap(plataforma, plat_x, plat_y, 0);
	al_draw_bitmap(bola, bola_x, bola_y, 0);
	al_flip_display();
}

int checabloco(posicao1 blocos[TAM_L][TAM_C], int &bola_x, int &bola_y, float &velx, float &vely, int pontos[TAM_L][TAM_C], int &pontuacao) {

    int ganhou=0;
	for (int linha = 0; linha < TAM_L; linha++) {
		for (int coluna = 0; coluna < TAM_C; coluna++) {

            if ((bola_x + 12 > blocos[linha][coluna].X + blocos[linha][coluna].LB and bola_x + 12 < blocos[linha][coluna+1].X) and (bola_y <= blocos[linha][coluna].Y + blocos[linha][coluna].AB and bola_y >= blocos[linha][coluna].Y)){
                vely = -vely;
				if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
				else pontuacao = pontuacao + 5;
				if (pontos[linha][coluna+1]== 5) pontuacao = pontuacao + 10;
				else pontuacao = pontuacao + 5;

				blocos[linha][coluna].X = SAI;
				blocos[linha][coluna].Y = SAI;
				blocos[linha][coluna+1].X = SAI;
				blocos[linha][coluna+1].Y = SAI;

            }

            else if ((bola_x + 12 > blocos[linha][coluna].X and bola_x + 12 < blocos[linha][coluna].X + blocos[linha][coluna].LB) and (bola_y <= blocos[linha][coluna].Y + blocos[linha][coluna].AB and bola_y >= blocos[linha][coluna].Y)) {
                vely = -vely;
                if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
				else pontuacao = pontuacao + 5;
				blocos[linha][coluna].X = SAI;
				blocos[linha][coluna].Y = SAI;

			}
			else if ((bola_y + 12 >= blocos[linha][coluna].Y and bola_y + 12 <= (blocos[linha][coluna].Y + blocos[linha][coluna].AB)) and (bola_x + 24 >= blocos[linha][coluna].X and bola_x + 24 <= blocos[linha][coluna].X + blocos[linha][coluna].LB)) {
				velx = -velx;
                if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
				else pontuacao = pontuacao + 5;
				blocos[linha][coluna].X = SAI;
				blocos[linha][coluna].Y = SAI;
			}
			else if ((bola_y + 12 > blocos[linha][coluna].Y and bola_y + 12 < (blocos[linha][coluna].Y + blocos[linha][coluna].AB)) and (bola_x > blocos[linha][coluna].X and bola_x < blocos[linha][coluna].X + blocos[linha][coluna].LB)) {
                velx = -velx;
                if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
				else pontuacao = pontuacao + 5;
				blocos[linha][coluna].X = SAI;
				blocos[linha][coluna].Y = SAI;

			}
			else if ((bola_x + 12 >= blocos[linha][coluna].X and bola_x + 12 <= blocos[linha][coluna].X + blocos[linha][coluna].LB) and (bola_y + 24 >= blocos[linha][coluna].Y and bola_y + 24 <= blocos[linha][coluna].Y + blocos[linha][coluna].AB)){
                vely = -vely;
                if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
				else pontuacao = pontuacao + 5;
				blocos[linha][coluna].X = SAI;
				blocos[linha][coluna].Y = SAI;
            }
		if (blocos[linha][coluna].X==SAI) ganhou++;
		else ganhou=0;
		if (ganhou==30) return 2;
		}

	}
}

void checaplataforma(int &bola_x, int &bola_y, int &plat_x , int &plat_y ,float &velx, float &vely, int &a) {


	if ((bola_x + 12 > plat_x and bola_x + 12 < plat_x + LARGURA_PLATAFORMA) and bola_y >= plat_y - ALTURA_PLATAFORMA)
	{

		if ((bola_x + 12 > plat_x + 51 and bola_x + 12 < plat_x + 60) and bola_y >= plat_y - ALTURA_PLATAFORMA)
		{
			velx = 0;
			vely = -vely;
		}
		else if (((bola_x + 12 > plat_x and bola_x + 12 < plat_x + 50) and bola_y >= plat_y - ALTURA_PLATAFORMA) and velx >= 0)
		{
			if (velx == 0)
				velx = 3;
			velx = -velx;
			vely = -vely;
		}
		else if (((bola_x + 12 > plat_x && bola_x + 12 < plat_x + 50) && bola_y >= plat_y - ALTURA_PLATAFORMA) and velx <= 0)
		{
			vely = -vely;
		}
		else if (((bola_x + 12 > plat_x + 60 && bola_x + 12< plat_x + 120) && bola_y >= plat_y - ALTURA_PLATAFORMA) and velx >= 0)
		{
			if (velx == 0)
				velx = 3;
			vely = -vely;
		}
		else if (((bola_x + 12> plat_x + 60 && bola_x + 12 < plat_x + 121) && bola_y >= plat_y - ALTURA_PLATAFORMA) and velx <= 0)
		{
			if (velx == 0)
				velx = -3;
			velx = -velx;
			vely = -vely;
		}
		else
			vely = -vely;
        if (a == 9){
            velx = velx * 140/100;
            vely = vely * 140/100;
        }
        a++;
	}

}

void movimentabola(int &bola_x, int &bola_y, float &velx, float &vely, int plat_x, int plat_y, posicao1 blocos[TAM_L][TAM_C], int &vidas, bool &soltabola, int &a, int pontos[TAM_L][TAM_C], int &pontuacao) {


	if (bola_y+12 > plat_y + ALTURA_PLATAFORMA){
        vidas --;
        velx = -3;
        vely = -5;
        a = 0;
        soltabola = false;

    }

	else if (bola_x <= PAREDE_ESQUERDA or bola_x + 24 >= PAREDE_DIREITA) {
		velx = -velx;
	}
	else if (bola_y <= PAREDE_CIMA and (bola_x > PAREDE_ESQUERDA and bola_x < PAREDE_DIREITA)) vely = -vely;

    else {
	checaplataforma(bola_x, bola_y, plat_x, plat_y, velx, vely, a);
	checabloco(blocos, bola_x, bola_y, velx, vely,pontos,pontuacao);

    }

	bola_x += velx;
	bola_y += vely;

}




int mapa2(ALLEGRO_DISPLAY *janela= NULL) {

	///---------------DECLARAÇÃO VARIAVEIS LOCAIS------------
	bool teclas[] = { false,false };
	bool jogo = true;
	int vet[18];
	int plat_x = 265;
	int plat_y = 640;
	int bola_x = 313;
	int bola_y = 618;
	int sair = 0;
	float velx = -3;
	float vely = -5;
	int vidas = 3;
	bool desenha = true;
	bool soltabola = false;
	int a = 0;
	int rond=0;
	int randomico;
	int pontuacao=0;
	int pontos[TAM_L][TAM_C];
	int mapa = 1;
	posicao1 blocos[TAM_L][TAM_C];
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_FONT *fonte = NULL;
	ALLEGRO_BITMAP *bola, *plataforma, *fundo, *itens, *vidaimg1, *vidaimg2, *vidaimg3;
	ALLEGRO_TIMER *timer = NULL;



	/// --------------------------------------------------------

	///-------------INICIALIZAR ADDONS -------------------------

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_keyboard();
	srand(time(NULL));
	fila_eventos = al_create_event_queue();

	/// --------------------------------------------------------

	///------------------FILA DE EVENTOS-------------------------


	/// --------------------------------------------------------

	///------------------CRIAR IMAGENS--------------------------

	fundo = al_load_bitmap("img/fundo.png");
	plataforma = al_load_bitmap("img/plataforma.png");
	bola = al_load_bitmap("img/bolinha.png");
	itens = al_load_bitmap("img/blocos.bmp");
	vidaimg1 = al_load_bitmap("img/BOLINHAS.png");
	vidaimg2 = al_load_bitmap("img/BOLINHAS2.png");
	vidaimg3 = al_load_bitmap("img/BOLINHAS3.png");
	fonte = al_load_font("img/fonte.ttf",45,0);
	timer = al_create_timer(1.0 / FPS);
	/// --------------------------------------------------------

	for (int linha = 0; linha < TAM_L; linha++) {
		for (int coluna = 0; coluna < TAM_C; coluna++) {

			blocos[linha][coluna].PiX = 0 + rand() % 9 * 58;
			blocos[linha][coluna].PiY = 0;
			blocos[linha][coluna].X = 25 + coluna * 64;
			blocos[linha][coluna].Y = 32 + linha * 31;
			blocos[linha][coluna].LB = 57;
			blocos[linha][coluna].AB = 28;

		}
	}

    sorteio(vet);
    int cont=0;
    for (int linha = 0; linha < TAM_L; linha++) {
		for (int coluna = 0; coluna < TAM_C; coluna++) {

            if(cont == vet[rond]) {
                pontos[linha][coluna] = 5;
                rond++;
            }
            else {
                pontos[linha][coluna] = 1;
            }
            cont++;
        }
	}


	while (jogo == true and vidas > 0) {


		al_start_timer(timer);
		al_register_event_source(fila_eventos, al_get_keyboard_event_source());
		al_register_event_source(fila_eventos, al_get_display_event_source(janela));
		al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

		ALLEGRO_EVENT ev;
		al_wait_for_event(fila_eventos, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				jogo = false;
			}

			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				teclas[DIREITA] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				teclas[ESQUERDA] = true;
				break;
            case ALLEGRO_KEY_SPACE:
                if(soltabola==false){
                    randomico = rand()%3;
                    if (randomico == 0) velx = -3;
                    else if (randomico == 1) velx = 0;
                    else if (randomico == 2) velx = 3;
                }
                soltabola = true ;
            }

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				teclas[DIREITA] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				teclas[ESQUERDA] = false;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			jogo = false;
			return 0;
		}


		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			desenha = true;
			if (teclas[DIREITA] and plat_x + LARGURA_PLATAFORMA < PAREDE_DIREITA)
			{
				plat_x += 7;

			}
			if (teclas[ESQUERDA] and plat_x > PAREDE_ESQUERDA)
			{
				plat_x -= 7;

			}

		}
		if (al_is_event_queue_empty and desenha == true) {
			if (soltabola == true){
			movimentabola(bola_x, bola_y, velx, vely, plat_x, plat_y, blocos, vidas, soltabola,a, pontos, pontuacao);
			}
            else if (soltabola == false){
                bola_x  = plat_x + (LARGURA_PLATAFORMA/2) - 12;
                bola_y  = plat_y - 24;
				}
			frames(blocos, bola, plataforma, fundo, itens, plat_x, plat_y, bola_x, bola_y, velx, vely, vidas, vidaimg1, vidaimg2,vidaimg3, fonte, pontuacao);
			desenha = false;
		}
    }
    vidas = 3;
	return 1;
}





