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
#define TAM_L 3
#define TAM_C 10
#define FPS 60.0
#define LARGURA_PLATAFORMA 120
#define ALTURA_PLATAFORMA 20
#define SAI -2000
using namespace std;
struct posicao {

	int PiX, PiY, X, Y, LB, AB;

};

void inicializar(){ ///INICIALIZA FUNÇÕES GERAIS///
    al_init(); ///INICIALIZA O ALLEGRO
	al_init_font_addon(); ///FUNÇÃO DE FONTE
	al_init_ttf_addon();  ///FUNÇÃO DE FONTE
	al_init_image_addon(); ///FUNÇÃO DE IMAGEM
	al_install_keyboard(); ///FUNÇÃO DE TECLADO
	srand(time(NULL)); ///FUNÇÃO PARA NUMERO ALEATORIO
}

void bubblesort(int vet[], int n) { ///MÉTODO DE ORDENAÇÃO ESTUDADO EM SALA
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

void sorteio(int vet[], int mapas, int ind[]) { ///SORTEIA QUAL BLOCO RECEBERÁ A PONTUAÇÃO BONUS E TAMBÉM QUAL VAI SER O BLOCO INDESTRUTIVEL
	srand(time(NULL));
	int a = 0;
	int randomico;
	if (mapas == 1){ ///CHECA EM QUAL MAPA ESTÁ
	while (a < 9 ) {
		randomico = rand() % 30; ///FAZ UM NUMERO QUE VAI DE 0 - 29 (VALOR DE POSIÇÕES NA MATRIZ DO MAPA 1)
		int check = 0;
		while (check < a) { ///VERIFICAR SE JA EXISTE UM NUMERO IGUAL NAQUELE MESMO VETOR
			if (vet[check] == randomico) { ///SE POSSUIR UM NUMERO IGUAL, GERA OUTRO E RESETA A VERIFICAÇÃO
				randomico = rand() % 30;
				check = 0;
			}
			check++;
		}
		vet[a] = randomico; ///SE NÃO TIVER NUMERO IGUAL, ARMAZENA O NUMERO GERADO NO VETOR
		a++;
	}
	}
    else {
    while (a < 18) { ///CHEGA EM QUAL MAPA ESTÁ
		randomico = rand() % 50; ///FAZ EXTAMENTE A MESMA COISA, SO QUE COM PARAMETROS PARA O SEGUNDO MAPA
		int check = 0;
		while (check < a) { ///VERIFICA SE JA EXISTE AQUELA POSIÇÃO
			if (vet[check] == randomico) {
				randomico = rand() % 50;
				check = 0;
			}
			check++;
		}
		vet[a] = randomico;
		a++;
	}
	a = 0;
	while (a < 3){  ///GERA UM VETOR PARA SABER QUAL BLOCO VAI SER INDESTRUTIVEL
        randomico = rand()%50;
        int check = 0;
        while (check < a){ ///VERIFICA SE JA EXISTE AQUELA POSIÇÃO
            if (ind[check] == randomico){
                randomico = rand()%50;
                check =0;
            }
            check++;
        }
        ind[a] = randomico;
        a++;
	}
    }
	a = 0;
	if (mapas == 1) bubblesort(vet, 9); ///CHAMA A FUNÇÃO DE ORDENAÇÃO, PARA DEIXAR O VETOR EM ORDEM CRESCENTE (IMPORTANTE PARA A LOGICA DO CODIGO)
	else if (mapas == 2) {
        bubblesort(vet, 18);
        bubblesort(ind,3);
    }
}

void selectmapa(posicao blocos[][TAM_C], int mapas, int pontos[][TAM_C], int TAMANHOL){ ///MAPEA A MATRIZ COM OS PARAMETROS DO MAPA, E TAMBEM MAPEA QUAIS SÃO OS BLOCOS BONUS E INDESTRUTIEIS EM UMA MATRIZ
    int rond = 0;
    int vet[18]; ///VAI GERAR O VETOR DE PONTUAÇÃO BONUS
    int ind[3]; ///VAI GERAR O VETOR DE BLOCOS INDESTRUTIVEIS
    if (mapas == 1) TAMANHOL = 3; ///VAI MAPEAR O CODIGO CONFORME O MAPA ATUAL
    else TAMANHOL = 5;
    for (int linha = 0; linha <  TAMANHOL; linha++) { ///MAPEIA A MATRIZ BLOCOS CONFORME O RESULTADO ANTERIOR
		for (int coluna = 0; coluna < TAM_C; coluna++) {

			blocos[linha][coluna].PiX = 0 + rand() % 9 * 58; ///POSIÇÃO X NA IMAGEM DOS BLOCOS(ONDE COMEÇA A IMPRIMIR), O RAND "SELECIONA" QUALQUER BLOCO DA IMAGEM
			blocos[linha][coluna].PiY = 0; ///POSIÇÃO Y NA IMAGEM DOS BLOCOS (ONDE COMEÇA A IMPRIMIR)
			blocos[linha][coluna].X = 25 + coluna * 64; ///POSIÇÃO X NO MAPA ONDE O BLOCO VAI COMEÇAR A IMPRIMIR
			blocos[linha][coluna].Y = 32 + linha * 31; ///POSIÇÃO Y NO MAPA ONDE O BLOCO VAI COMEÇAR A IMPRIMIR
			blocos[linha][coluna].LB = 56;  ///PARAMETRO NECESSARIO PARA SABER A LARGURA DO BLOCO
			blocos[linha][coluna].AB = 28;  ///PARAMETRO NECESSARIO PARA SABER A ALTURA DO BLOCO

		}
	}

    sorteio(vet, mapas, ind); ///CHAMA A FUNÇÃO SORTEIO
    int cont=0;
    for (int linha = 0; linha < TAMANHOL; linha++) {
		for (int coluna = 0; coluna < TAM_C; coluna++) {

            if(cont == vet[rond]) { ///INSERE AS PONTUAÇÕES BONUS DO VETOR NA MATRIZ
                pontos[linha][coluna] = 5;
                rond++;
            }
            else { ///INSERE UMA PONTUAÇÃO NORMAL
                pontos[linha][coluna] = 1;
            }
            cont++;
        }
	}
    cont = 0;   ///ZERA OS PARAMETROS
    rond = 0;
    for (int linha = 0; linha < TAMANHOL; linha++) {
		for (int coluna = 0; coluna < TAM_C; coluna++) {

            if(cont == ind[rond]) { ///INSERE AS POSIÇÕES DO BLOCO ESPECIAL NA MATRIZ
                pontos[linha][coluna] = 10;
                rond++;
            }
            cont++;
        }
	}

}

void frames(posicao blocos[][TAM_C], ALLEGRO_BITMAP *bola, ALLEGRO_BITMAP *plataforma, ALLEGRO_BITMAP *fundo, ALLEGRO_BITMAP *itens, int plat_x, int plat_y, int bola_x, int bola_y, float velx, float vely, int vidas, ALLEGRO_BITMAP *vidaimg1, ALLEGRO_BITMAP *vidaimg2, ALLEGRO_BITMAP *vidaimg3, ALLEGRO_FONT *fonte, int pontuacao, int TAMANHOL, int mapas) {

    if (mapas == 1) TAMANHOL = 3; ///MAPEIA A FUNÇÃO CONFORME O MAPA ATUAL
    else TAMANHOL = 5;
    static int highscore = 0; ///VARIAVEL PARA O SCORE MAXIMO
    if (pontuacao > highscore)  ///LOGICA USADA PARA CHECAR SE A PONTUAÇÃO ATUAL PASSOU O SCORE MAXIMO
        highscore = pontuacao;  ///SE FOR VERDADE, O SCORE MAXIMO ADERE O VALOR DA PONTUAÇÃO

	al_draw_bitmap(fundo, 0, 0, 0); ///DESENHA O FUNDO DO JOGO
	if (vidas == 3) al_draw_bitmap(vidaimg1, 743, 500 , 0); ///DESENHA A IMAGEM DA VIDA CONFORME O NUMERO DE VIDAS
	else if (vidas == 2) al_draw_bitmap(vidaimg2, 743, 500 , 0);
	else if (vidas == 1) al_draw_bitmap(vidaimg3, 743, 500 , 0);///----------------------------------------------
	al_draw_textf(fonte ,al_map_rgb(0,0,0),785,310,ALLEGRO_ALIGN_CENTER,"%d", pontuacao); ///IMPRIME A PONTUAÇÃO
	al_draw_textf(fonte ,al_map_rgb(0,0,0),785,210,ALLEGRO_ALIGN_CENTER,"%d", mapas);///IMPRIME EM QUAL MAPA ESTÁ
	al_draw_textf(fonte ,al_map_rgb(0,0,0),785,410,ALLEGRO_ALIGN_CENTER, "%d", highscore);///IMPRIME O HIGHSCORE
	for (int linha = 0; linha < TAMANHOL; linha++) { ///IMPRIME OS BLOCOS CONFORME LÓGICA DA STRUCT POSIÇÃO
		for (int coluna = 0; coluna < TAM_C; coluna++) {


			al_draw_bitmap_region(itens, blocos[linha][coluna].PiX, blocos[linha][coluna].PiY, blocos[linha][coluna].LB, blocos[linha][coluna].AB, blocos[linha][coluna].X, blocos[linha][coluna].Y, 0);
            ///REGION SIGNIFICA QUE SERA IMPRESSO APENAS UMA REGIÃO DAQUELA IMAGEM "ITENS", E OS PARAMETROS SÃO PASSADOS CONFORME AS VARIAVEIS DA STRUCT POSIÇÃO
		}
	}
	al_draw_bitmap(plataforma, plat_x, plat_y, 0); ///DESENHA A PLATAFORMA
	al_draw_bitmap(bola, bola_x, bola_y, 0);///DESENHA A BOLA
	al_flip_display();///ATUALIZA A TELA
}

int checabloco(posicao blocos[][TAM_C], int &bola_x, int &bola_y, int &velx, int &vely, int pontos[][TAM_C], int &pontuacao, int TAMANHOL, int &mapas, int &qualquervariavel, bool &jogo, int &ganhou) {
    ///VERIFICA A FISICA DOS BLOCOS
    if (mapas == 1) TAMANHOL = 3;///PASSA OS PARAMETROS PARA O CODIGO CONFORME O MAPA ATUAL
    else TAMANHOL = 5;
	for (int linha = 0; linha < TAMANHOL; linha++) {///VERIFICA NA MATRIZ BLOCOS, POSIÇÃO POR POSIÇÃO
		for (int coluna = 0; coluna < TAM_C; coluna++) {

            ///ESSA LINHA DE LOGICA LIMITA A BOLA A BATER NA PARTE DE BAIXO E TAMBÉM ENTRE DOIS BLOCOS
            ///COMO ESTÁ ENTRE DOIS BLOCOS ENTENDE-SE QUE ENTRA EM CONFLITO COM O BLOCO QUE ESTÁ, E TAMBÉM COM O POSTERIOR
            if ((bola_x + 12 > blocos[linha][coluna].X + blocos[linha][coluna].LB and bola_x + 12 < blocos[linha][coluna+1].X) and (bola_y <= blocos[linha][coluna].Y + blocos[linha][coluna].AB and bola_y >= blocos[linha][coluna].Y)){
                vely = -vely; ///VAI MUDAR A DIREÇÃO Y DA BOLA
				if (mapas == 1){ ///VERIFICA EM QUAL MAPA ESTÁ
				if(pontos[linha][coluna]==5) pontuacao = pontuacao + 5; ///ATUALIZA A PONTUAÇÃO CONFORME O VALOR SORTEADO PARA AQUELA POSIÇÃO
				else pontuacao = pontuacao + 1;
				if (pontos[linha][coluna+1]== 5) pontuacao = pontuacao + 5;
				else pontuacao = pontuacao + 1;
                blocos[linha][coluna].X = SAI; ///REMOVE DA MATRIZ A POSIÇÃO X (A QUE É USADA PARA IMPRIMIR NO MAPA)
				blocos[linha][coluna].Y = SAI; ///REMOVE DA MATRIZ A POSIÇÃO Y (A QUE É USADA PARA IMPRIMIR NO MAPA)
				blocos[linha][coluna+1].X = SAI;
				blocos[linha][coluna+1].Y = SAI;
				ganhou+=2; ///SOMA QUE 2 BLOCOS FORAM DESTRUIDOS NA VARIAVEL QUE CONTA OS BLOCOS DESTRUIDOS

				}
                else if (mapas == 2){///VERIFICA QUE ESTÁ NO MAPA 2
                    if(pontos[linha][coluna]!= 10){ ///SE A POSIÇÃO QUE ESTÁ NÃO FOR UM BLOCO INDESTRUTIVEL
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10; ///ATUALIZA A PONTUAÇÃO CONFORME VALOR SORTEADO PARA A POSIÇÃO
                    else pontuacao = pontuacao + 5;
                    blocos[linha][coluna].X = SAI; ///REMOVE OS PARAMETROS DO MAPA
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;///SOMA 1 BLOCO DESTRUIDO NA VARIAVEL QUE CONTA OS BLOCOS DESTRUIDOS
                    }
                    if(pontos[linha][coluna+1]!= 10){///SE A POSIÇÃO POSTERIOR NÃO FOR UM BLOCO INDESTRUTIVEL
                    if (pontos[linha][coluna+1]== 5) pontuacao = pontuacao + 10; ///ATUALIZA A PONTUAÇÃO CONFORME VALOR SORTEADOR PARA A POSIÇÃO
                    else pontuacao = pontuacao + 5;
                    blocos[linha][coluna+1].X = SAI; ///REMOVE OS PARAMETROS DO MAPA
                    blocos[linha][coluna+1].Y = SAI;
                    ganhou++; ///SOMA 1 BLOCO DESTRUIDO
                    }
				}
            }
            ///VERIFICA SE A BOLA ENCOSTOU NA PARTE DE BAIXO DE UM BLOCO
            else if ((bola_x + 12 > blocos[linha][coluna].X and bola_x + 12 < blocos[linha][coluna].X + blocos[linha][coluna].LB) and (bola_y <= blocos[linha][coluna].Y + blocos[linha][coluna].AB and bola_y >= blocos[linha][coluna].Y)) {
                vely = -vely; ///MUDA A DIREÇÃO
                if (mapas == 1){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 5; ///ATUALIZA PONTOS
                    else pontuacao = pontuacao + 1;
                    blocos[linha][coluna].X = SAI; ///REMOVE DA MARTIZ
                    blocos[linha][coluna].Y = SAI;
                    ganhou++; ///SOMA 1 BLOCO DESTRUIDO
				}
				else if (mapas == 2){
                    if(pontos[linha][coluna]!= 10){ ///CHECA SE O BLOCO NÃO E INDESTRUTIVEL
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10; ///ATUALIZA PONTOS
                    else pontuacao = pontuacao + 5;
                    blocos[linha][coluna].X = SAI; ///REMOVE DA MATRIZ
                    blocos[linha][coluna].Y = SAI;
                    ganhou++; ///SOMA 1 BLOCO DESTRUIDO
                    }
				}
			}
			///VERIFICA SE COLIDIU COM A LATERAL ESQUERDA DO BLOCO
			///SEGUE MESMA LINHA DE RACIOCINIO
			else if ((bola_y + 12 >= blocos[linha][coluna].Y and bola_y + 12 <= (blocos[linha][coluna].Y + blocos[linha][coluna].AB)) and (bola_x + 24 >= blocos[linha][coluna].X and bola_x + 24 <= blocos[linha][coluna].X + blocos[linha][coluna].LB)) {
				velx = -velx; ///MUDA A DIREÇÃO
                if (mapas == 1){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 5;
                    else pontuacao = pontuacao + 1;
                    blocos[linha][coluna].X = SAI;
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;
				}
				else if (mapas == 2){
                    if(pontos[linha][coluna]!= 10){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
                    else pontuacao = pontuacao + 5;
                    blocos[linha][coluna].X = SAI;
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;
                    }
				}
			}
			///VERIFICA SE COLIDIU COM A LATERAL DIREITA DO BLOCO
			///SEGUE MESMA LINHA DE RACIOCINIO
			else if ((bola_y + 12 > blocos[linha][coluna].Y and bola_y + 12 < (blocos[linha][coluna].Y + blocos[linha][coluna].AB)) and (bola_x > blocos[linha][coluna].X and bola_x < blocos[linha][coluna].X + blocos[linha][coluna].LB)) {
                velx = -velx;
                if (mapas == 1){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 5;
                    else pontuacao = pontuacao + 1;
                    blocos[linha][coluna].X = SAI;
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;
				}
				else if (mapas == 2){
                    if(pontos[linha][coluna]!= 10){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
                    else pontuacao = pontuacao + 5;
                    blocos[linha][coluna].X = SAI;
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;
                    }
				}
			}
			///VERIFICA SE COLIDIU COM A PARTE SUPERIOR DO BLOCO
			///SEGUE MESMA LINHA DE RACIOCINIO
			else if ((bola_x + 12 >= blocos[linha][coluna].X and bola_x + 12 <= blocos[linha][coluna].X + blocos[linha][coluna].LB) and (bola_y + 24 >= blocos[linha][coluna].Y and bola_y + 24 <= blocos[linha][coluna].Y + blocos[linha][coluna].AB)){
                vely = -vely;
                if (mapas == 1){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 5;
                    else pontuacao = pontuacao + 1;
                    blocos[linha][coluna].X = SAI;
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;
				}
				else if (mapas == 2){
                    if(pontos[linha][coluna]!= 10){
                    if(pontos[linha][coluna]==5) pontuacao = pontuacao + 10;
                    else pontuacao = pontuacao + 5;
                    blocos[linha][coluna].X = SAI;
                    blocos[linha][coluna].Y = SAI;
                    ganhou++;
                    }
				}
            }
        }
	}
	if (ganhou==30 and mapas == 1){ ///SE O CONTADOR QUE VERIFICA QUANDO UM BLOCO FOI QUEBRADO CHEGAR A 30 ELE GANHOU O PRIMEIRO MAPA

        mapas = 2; ///TROCA DE MAPA
        qualquervariavel = 1; ///FALA QUE É NECESSARIO A ATUALIZAÇÃO DOS PARAMETROS DO MAPA
        ganhou = 0; ///RESETA A VARIAVEL QUE CHECA OS BLOCOS QUEBRADOS
	}
	else if (ganhou == 47 and mapas == 2){ ///SE O CONTADOR QUE VERIFICA QUANDO UM BLOCO FOI QUEBRADO CHEGAR A 47 (50 BLOCOS DO MAPA - 3 INDESTRUTIVEIS) ELE GANHOU O SEGUNDO MAPA
        ganhou = 0;
        ALLEGRO_BITMAP *win = NULL; ///DEFINE UM PONTEIRO DE VITORIA
        win = al_load_bitmap("img/win.png");///DIZ QUE ELE RECEBERA A IMAGEM WIN.PNM
        al_clear_to_color(al_map_rgb(203,81,81));///SETA O FUNDO DA JANELA PARA A COR ESCOLHIDA
        al_draw_bitmap(win,ALTURA_TELA/5, LARGURA_TELA/5,0);///DESENHA A IMAGEM WIN
        al_flip_display();///ATUALIZA A JANELA
        Sleep(2000);///ESPERA POR 2 SEGUNDOS
        jogo = false;///DIZ QUE ELE GANHOU O JOGO
	}
}

void checaplataforma(int &bola_x, int &bola_y, int &plat_x , int &plat_y ,int &velx, int &vely, int &a) {
    ///VERIFICA A VISICA DA PLATAFORMA

	if ((bola_x + 12 > plat_x and bola_x + 12 < plat_x + LARGURA_PLATAFORMA) and bola_y >= plat_y - ALTURA_PLATAFORMA) ///VERIFICA SE ELE BATEU EM UMA PLATAFORMA
	{

		if ((bola_x + 12 > plat_x + 51 and bola_x + 12 < plat_x + 60) and bola_y >= plat_y - ALTURA_PLATAFORMA) ///VERIFICA SE ELE BATEU NO MEIO DA PLATAFORMA
		{
			velx = 0; ///SETA A DIREÇÃO X DELE PARA CIMA
			vely = -vely;///MUDA A DIREÇÃO Y
		}

		else if (((bola_x + 12 > plat_x and bola_x + 12 < plat_x + 50) and bola_y >= plat_y - ALTURA_PLATAFORMA) and velx >= 0)///VERIFICA SE A BOLA BATEU NO INICIO DA PLATAFORMA E ESTÁ VINDO DA DIREITA
		{
			if (velx == 0)///VERIFICA SE A DIREÇÃO X DELE ESTÁ EM 0
				velx = 3;///VOLTA PARA A DIREÇÃO NORMAL DA TRAJETORIA
			velx = -velx;///MUDA A DIREÇÃO X
			vely = -vely;///MUDA A DIREÇÃO Y
		}
		else if (((bola_x + 12 > plat_x && bola_x + 12 < plat_x + 50) && bola_y >= plat_y - ALTURA_PLATAFORMA) and velx <= 0)///VERIFICA SE A BOLA BATEU NO INICIO DA PLATAFORMA E ESTÁ VINDO DA ESQUERDA
		{
			vely = -vely; ///INVERTE A DIREÇÃO Y
		}
		else if (((bola_x + 12 > plat_x + 60 && bola_x + 12< plat_x + 120) && bola_y >= plat_y - ALTURA_PLATAFORMA) and velx >= 0)///VERIFICA SE A BOLA BATEU NO FINAL DA PLATAFORMA E ESTÁ VINDO DA ESQUERDA
		{
			if (velx == 0)///VERIFICA SE A VELOCIDADE X É 0
				velx = 3;
			vely = -vely; ///MUDA A DIREÇÃO Y
		}
		else if (((bola_x + 12> plat_x + 60 && bola_x + 12 < plat_x + 121) && bola_y >= plat_y - ALTURA_PLATAFORMA) and velx <= 0)///VERIFICA SE A BOLA BATEU NO FINAL DA PLATAFORMA E ESTÁ VINDO DA DIREITA
		{
			if (velx == 0)///VERIFICA SE A VELOCIDADE X É 0
				velx = -3;
			velx = -velx;///ALTERA A DIREÇÃO X
			vely = -vely;///ALTERA A DIREÇÃO Y
		}
		else ///SE NENHUM DOS CASOS ACIMA OCORRES E A BOLA AINDA SIM BATER NA PLATAFORMA
			vely = -vely;///ALTERA SUA DIREÇÃO Y
        if (a == 9){ ///VERIFICA SE O CONTADOR QUE ALTERA A VELOCIDADE ESTÁ EM 9
            velx = velx * 140/100;///ALTERA A VELOCIDADE EM 40%
            vely = vely * 140/100;
        }
        a++;
	}

}

void movimentabola(int &bola_x, int &bola_y, int &velx, int &vely, int plat_x, int plat_y, posicao blocos[][TAM_C], int &vidas, bool &soltabola, int &a, int pontos[][TAM_C], int &pontuacao, int TAMANHOL, int &mapas, int &qualquervariavel, bool &jogo, int &ganhou) {

    ///MOVIMENTA A BOLA
	if (bola_y+12 > plat_y + ALTURA_PLATAFORMA){ ///VERIFICA SE A BOLA NÃO PASSOU DA PLATAFORMA
        vidas --;///PERDE UMA VIDA
        velx = -3;///VOLTA A VELOCIDADE ORIGINAL
        vely = -5;
        a = 0;///RESETA O CONTADOR DE VELOCIDADE
        pontuacao = 0;///RESETA A PONTUAÇÃO
        soltabola = false;///FAZ COM QUE A BOLA FIQUE PRESA A PLATAFORMA NOVAMENTE

    }

	if (bola_x <= PAREDE_ESQUERDA or bola_x + 24 >= PAREDE_DIREITA) { ///VERIFICA SE A BOLA BATEU NA PAREDE DA DIREITA OU ESQUERDA
		velx = -velx;///MUDA SUA DIREÇÃO Y
	}
	if (bola_y <= PAREDE_CIMA and (bola_x >= PAREDE_ESQUERDA and bola_x <= PAREDE_DIREITA)) vely = -vely; ///VERIFICA SE A BOLA BATEU NO TETO E MUDA SEU SENTIDO

	checaplataforma(bola_x, bola_y, plat_x, plat_y, velx, vely, a);///CHAMA A FUNÇÃO QUE VERIFICA SE A BOLA COLIDIU COM ALGUMA PLATAFORMA
	checabloco(blocos, bola_x, bola_y, velx, vely,pontos,pontuacao, TAMANHOL, mapas, qualquervariavel, jogo, ganhou);///CHAMA A FUNÇÃO QUE VERICIA SE A BOLA COLIDIU COM ALGUM BLOCO



	bola_x += velx;///MOVIMENTA A BOLA PARA SUA DIREÇÃO X
	bola_y += vely;///MOVIMENTA A BOLA PARA SUA DIREÇÃO Y

}




int jogo(ALLEGRO_DISPLAY *janela= NULL) {

	///---------------DECLARAÇÃO VARIAVEIS LOCAIS------------
	bool teclas[] = { false,false }; ///UTILIZADA PARA SABER QUAL TECLA ESTÁ SENDO PRECIONADA
	bool jogo = true;///UTILIZADA PARA SABER SE O JOGO AINDA ESTÁ RODANDO
	int plat_x = 265;///POSIÇÃO INICIAL X DA PLATAFORMA
	int plat_y = 640;///POSIÇÃO INICIAL Y DA PLATAFORMA
	int bola_x = 313;///POSIÇÃO INICIAL X DA BOLA
	int bola_y = 618;///POSIÇÃO INICIAL Y DA BOLA
	int velx = -3;///VELOCIDADE E DIREÇÃO X DA BOLA
	int vely = -5;///VELOCIDADE E DIREÇÃO Y DA BOLA
	int vidas = 3;///NUMERO DE VIDAS
	bool desenha = true; ///VARIAVEL QUE VERIFICA SE O FRAME PRECISA SER ATUALIZADO
	bool soltabola = false; ///VARIAVEL QUE VERIFICA SE A BOLA SE SOLTOU DA PLATAFOMRA
	int a = 0; ///CONTADOR GENERICO UTILIZADO NO CODIGO
	int randomico;///VARIAVEL ACOPLADA A UM NUMERO RANDOMICO
	int pontuacao=0;///VARIAVEL QUE ARMAZENA A PONTUAÇÃO
	int pontos[5][TAM_C];///VARIAVEL QUE MAPEIA QUANTOS PONTOS VALEM CADA BLOCO
	int mapas = 1;///DEFINE QUAL O MAPA ATUAL
	int TAMANHOL;///DEFINE PARAMETROS PARA O MAPA ATUAL
	int ganhou = 0;///CONTADOR DE BLOCOS DESTRUIDOS
	int qualquervariavel = 1;///UTILIZADA PARA VERIFICAR SE É NECESSARIO ATUALIZAR AS MATRIZES
	posicao blocos[5][TAM_C];///MATRIZ DO TIPO POSICAO QUE POSSUE OS PARAMETROS DE POSICAO DE CADA BLOCO
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL; ///PONTEIRO DE FILA DE EVENTOS USADO NO ALLEGRO
	ALLEGRO_FONT *fonte = NULL; ///PONTEIRO PARA FONTE
	ALLEGRO_BITMAP *bola, *plataforma, *fundo, *itens, *vidaimg1, *vidaimg2, *vidaimg3;///PONTEIRO PARA AS IMAGENS
	ALLEGRO_TIMER *timer = NULL;///PONTEIRO PARA O TIMER/FPS

	/// --------------------------------------------------------

	///-------------INICIALIZAR ADDONS -------------------------

	inicializar();

	/// --------------------------------------------------------

	///------------------SETA ENDEREÇO DE MEMORIA DAS IMAGENS--------------------------

	fundo = al_load_bitmap("img/fundo.png");
	plataforma = al_load_bitmap("img/plataforma.png");
	bola = al_load_bitmap("img/bolinha.png");
	itens = al_load_bitmap("img/blocos.bmp");
	vidaimg1 = al_load_bitmap("img/BOLINHAS.png");
	vidaimg2 = al_load_bitmap("img/BOLINHAS2.png");
	vidaimg3 = al_load_bitmap("img/BOLINHAS3.png");
	fonte = al_load_font("img/fonte.ttf",45,0);

	/// --------------------------------------------------------

    fila_eventos = al_create_event_queue(); ///CHAMA UMA FUNÇÃO QUE CRIA UMA FILA DE EVENTOS
    timer = al_create_timer(1.0 / FPS); ///CHAMA UMA FUNÇÃO QUE FALA QUE DEFINE O FPS
	selectmapa(blocos,mapas,pontos, TAMANHOL);///CHAMA A FUNÇÃO SELECTMAPA, QUE GERA AS MATRIZES

	while (jogo == true and vidas > 0) {///ENQUANTO O JOGO ESTIVER VERDADEIRO E O JOGADOR POSSUIR VIDAS


        if (qualquervariavel == 1) { ///VERIFICA SE É NECESSARIO ATUALIZAR AS MATRIZES
            selectmapa(blocos,mapas,pontos, TAMANHOL);///CHAMA A FUNÇÃO SELECTMAPA, QUE GERA AS MATRIZES
            vidas = 3;///SE ESSA CONDIÇÃO FOI ATIVA QUER DIZER QUE O MAPA FOI ATUALIZADO, ENTÃO AS VIDAS SÃO ATUALIZADAS
            soltabola= false;///A BOLA VOLTA A SER ACOPLADA COM A PLATAFORMA
            a = 0;///RESETA O CONTADOR DA VELOCIDADE
            qualquervariavel = 0;///SETA QUE NÃO É NECESSARIO ATUALIZAR AS MATRIZES
        }

		al_start_timer(timer);///INICIA O FPS
		al_register_event_source(fila_eventos, al_get_keyboard_event_source());///FUNÇÕES NECESSARIAS PARA REGISTRAR EVENTOS
		al_register_event_source(fila_eventos, al_get_display_event_source(janela));
		al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
		ALLEGRO_EVENT ev;///CRIA UMA VARIAVEL EV QUE SERA UTILIZADA PARA ARMAZENAR OS EVENTOS
		al_wait_for_event(fila_eventos, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) ///SE O EVENTO ARMAZENADO FOR O DE PRECIONAR UMA TECLA
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) ///VERIFICA SE A TECLA PRESSIONADA FOI "ESC"
			{
				jogo = false;///VOLTA PARA O MENU
			}

			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT: ///VERIFICA SE CASO A TECLA PRESSIONADA FOI A DIREITA
				teclas[DIREITA] = true;///FALA QUE É VERDADE QUE A TECLA DA DIREITA FOI PRESSIONADA
				break;
			case ALLEGRO_KEY_LEFT:///VERIFICA SE CASO A TECLA PRESSIONADA FOI A ESQUERDA
				teclas[ESQUERDA] = true;///FALA QUE É VERDADE QUE A TECLA DA ESQUERDA FOI PRESSIONADA
				break;
            case ALLEGRO_KEY_SPACE:///VERIFICA SE CASO A TECLA ESPAÇO FOI PRESSIONADA
                if(soltabola==false){ ///VERIFICA QUE SE A BOLA TIVER ACOPLADA A PLATAFORMA, ELE VAI RANDOMIZAR UM DOS LADOS PARA SOLTAR A BOLA
                    randomico = rand()%3;
                    if (randomico == 0) velx = -3;
                    else if (randomico == 1) velx = 0;
                    else if (randomico == 2) velx = 3;
                }
                soltabola = true ;///SOLTA A BOLA
            }

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)///SE O TIPO DE EVENTO FOI O DE SOLTAR UMA TECLA
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:///SE A TECLA SOLTA FOI A DA DIREITA
				teclas[DIREITA] = false;///SE TORNA FALSO O ARGUMENTO QUE A TECLA DA DIREITA ESTAVA PRESSIONADA
				break;
			case ALLEGRO_KEY_LEFT:///SE A TECLA SOLTA FOI A DA ESQUERDA
				teclas[ESQUERDA] = false;///SE TORNA FALSO O ARGUMENTO QUE A TECLA DA ESQUERDA ESTAVA PRESSIONADA
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)///SE ELE FECHAR O JOGO PELO MOUSE
		{
			return 0;///FECHA O JOGO
		}


		else if (ev.type == ALLEGRO_EVENT_TIMER)///SE NÃO HOUVE NENHUMA TECLA PRESSIONADA ELE ACIONARA O TIMER
		{
			desenha = true;///DIRA QUE É NECESSARIO ATUALIZAR OS FRAMES
			if (teclas[DIREITA] and plat_x + LARGURA_PLATAFORMA < PAREDE_DIREITA)///DIRA QUE SE A TECLA DA DIREITA FOR VERDADE E A PLATAFORMA NÃO ESTIVER NA PAREDE
			{
				plat_x += 7;///A PLATAFORMA SE MOVERÁ PARA A DIREITA

			}
			if (teclas[ESQUERDA] and plat_x > PAREDE_ESQUERDA)///DIRA QUE SE A TECLA DA ESQUERDA FOR VERDADE E A PLATAFORMA NÃO ESTIVER NA PAREDE
			{
				plat_x -= 7;///A PLATAFORMA SE MOVERÁ PARA A ESQUERDA

			}

		}
		if (al_is_event_queue_empty and desenha == true) {///VERIFICA QUE SE A FILA DE EVENTOS ESTIVER VAZIA E QUE É NECESSARIO ATUALIZAR OS FRAMES
			if (soltabola == true){///VERIFIA SE A BOLA ESTÁ DESACOPLADA DA PLATAFORMA
			movimentabola(bola_x, bola_y, velx, vely, plat_x, plat_y, blocos, vidas, soltabola,a, pontos, pontuacao, TAMANHOL, mapas, qualquervariavel, jogo, ganhou);
			}
            else if (soltabola == false){///SE ELA ESTIVER PRESSA A PLATAFORMA SE MOVERA CONFORME A PLATAFORMA
                bola_x  = plat_x + (LARGURA_PLATAFORMA/2) - 12;
                bola_y  = plat_y - 24;
				}
            ///CHAMA A FUNÇÃO QUE ATUALIZA OS FRAMES
			frames(blocos, bola, plataforma, fundo, itens, plat_x, plat_y, bola_x, bola_y, velx, vely, vidas, vidaimg1, vidaimg2,vidaimg3, fonte, pontuacao, TAMANHOL, mapas);
			desenha = false;///FALA QUE NÃO É NECESSARIO ATUALIZAR OS FRAMES POR ENQUANTO
		}
    }
    if (vidas == 0){///VERIFICA QUE SE ELE SAIU DO JOGO E PERDEU TODAS AS VIDAS ELE "PERDEU O MAPA", IMPRIME NA TELA A FOTO DE DERROTA
        ALLEGRO_BITMAP *lose = NULL;
        al_clear_to_color(al_map_rgb(203,81,81));
        lose = al_load_bitmap("img/daninarguila.png");
        al_draw_bitmap(lose,LARGURA_TELA/5,ALTURA_TELA/5,0);
        al_flip_display();
        Sleep(2000);
    }

    vidas = 3;///RESETA AS VIDAS E VOLTA PARA O MENU

	return 1;
}





