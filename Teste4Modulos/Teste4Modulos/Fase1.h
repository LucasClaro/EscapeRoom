#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"

int JogarFase1(ALLEGRO_DISPLAY *janela, ALLEGRO_EVENT_QUEUE* fila_eventos, int acerto) {
	Objeto imagem;
	// Variável para imagem
	imagem.beatmap = NULL;
	imagem.x = 0;
	imagem.y = 0;
	imagem.largura = 100;
	imagem.altura = 100;

	Objeto retangulo;
	retangulo.beatmap = NULL;
	retangulo.x = LARGURA_TELA - 150;
	retangulo.y = ALTURA_TELA - 150;
	retangulo.altura = 150;
	retangulo.largura = 150;

	Objeto saida;
	saida.beatmap = NULL;
	saida.x = LARGURA_TELA - 100;
	saida.y = 0;
	saida.largura = 100;
	saida.altura = 100;

	Objeto certo;
	certo.beatmap = NULL;
	certo.x = 0;
	certo.y = ALTURA_TELA - 100;
	certo.altura = 100;
	certo.largura = 100;

	imagem.beatmap = al_load_bitmap("Imgs/photo.bmp");
	retangulo.beatmap = al_load_bitmap("Imgs/ret.bmp");
	saida.beatmap = al_load_bitmap("Imgs/direita.png");
	certo.beatmap = al_load_bitmap("Imgs/ok.bmp");
	if (!imagem.beatmap || !retangulo.beatmap || !saida.beatmap) {
		fprintf(stderr, "Falha ao iniciar imagem\n");
		al_destroy_display(janela);
		return -1;
	}

	////////////////////////////////////////////////

	// Preenchemos a janela de branco
	al_clear_to_color(al_map_rgb(255, 255, 255));

	if (acerto)
	{
		imagem.x = retangulo.x + 10;
		imagem.y = retangulo.y + 10;
	}

	//desenha a imagem na tela
	al_draw_bitmap(imagem.beatmap, imagem.x, imagem.y, 0);
	al_draw_bitmap(retangulo.beatmap, retangulo.x, retangulo.y, 0);
	al_draw_bitmap(saida.beatmap, saida.x, saida.y, 0);

	// Atualiza a tela
	al_flip_display();

	int gameOver = 0;
	int Arrastando = 0;
	while (!gameOver) {
		while (!al_is_event_queue_empty(fila_eventos))
		{
			//Cria um evento
			ALLEGRO_EVENT evento;
			//espero por um evento da fila, e guarda em evento
			al_wait_for_event(fila_eventos, &evento);

			//se teve eventos e foi um evento de fechar janela, encerra repetição			
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				gameOver = 1;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (IsInside(evento.mouse.x, evento.mouse.y, saida))
				{
					return acerto;
				}
				else if (IsInside(evento.mouse.x, evento.mouse.y, imagem) && !Arrastando) {
					Arrastando = 1;
					imagem.cliqueX = MapearDistancia(evento.mouse.x, imagem.x);
					imagem.cliqueY = MapearDistancia(evento.mouse.y, imagem.y);
				}
				else
				{
					Arrastando = 0;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				Arrastando = 0;
			}

			ALLEGRO_MOUSE_STATE state;


			al_get_mouse_state(&state);
			if (state.buttons & 1 && Arrastando) {
				/* Primary (e.g. left) mouse button is held. */
				if (!VerificarBordas(evento.mouse.x, evento.mouse.y, imagem)) {
					imagem.x = evento.mouse.x - imagem.cliqueX;
					imagem.y = evento.mouse.y - imagem.cliqueY;
				}
			}
			if (Arrastando && IsInsideImagem(imagem, retangulo)) {
				acerto = 1;
			}
			else if (Arrastando && !IsInsideImagem(imagem, retangulo)) {
				acerto = 0;
			}
		}

		al_clear_to_color(al_map_rgb(255, 255, 255));

		al_draw_bitmap(retangulo.beatmap, retangulo.x, retangulo.y, 0);
		al_draw_bitmap(imagem.beatmap, imagem.x, imagem.y, 0);
		if (acerto) {
			al_draw_bitmap(certo.beatmap, certo.x, certo.y, 0);
		}
		al_draw_bitmap(saida.beatmap, saida.x, saida.y, 0);

		al_flip_display();
	}
}