#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Funcoes.h"
#include "Struct.h"
#include "Fase1.h"

int main(void) {
	ALLEGRO_DISPLAY* janela = NULL;

	Objeto saida1;
	// Variável para imagem
	saida1.beatmap = NULL;
	saida1.x = 0;
	saida1.y = 0;
	saida1.largura = 100;
	saida1.altura = 100;

	Objeto mensagem;
	mensagem.beatmap = NULL;
	mensagem.x = LARGURA_TELA/2 - 100;
	mensagem.y = ALTURA_TELA - 100;
	mensagem.largura = 200;
	mensagem.altura = 100;

	Objeto mensagemTravada;
	mensagemTravada.beatmap = NULL;
	mensagemTravada.x = LARGURA_TELA/2 - 100;
	mensagemTravada.y = ALTURA_TELA - 100;
	mensagemTravada.largura = 200;
	mensagemTravada.altura = 100;

	//declara a fila de eventos
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

	if (!al_init()) {
		fprintf(stderr, "Falha ao iniciar Allegro\n");
		return -1;
	}
	// Inicializa o add-on para utilização de imagens
	al_init_image_addon();

	// Criamos a nossa janela - dimensões de 640x480 px
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!janela) {
		fprintf(stderr, "Falha ao iniciar janela\n");
		return -1;
	}
	// Configura o título da janela
	al_set_window_title(janela, "Arrastar coisas");

	saida1.beatmap = al_load_bitmap("Imgs/esquerda.png");
	mensagem.beatmap = al_load_bitmap("Imgs/mensagem.png");
	mensagemTravada.beatmap = al_load_bitmap("Imgs/mensagemtravada.png");
	if (!saida1.beatmap || !mensagem.beatmap || !mensagemTravada.beatmap) {
		fprintf(stderr, "Falha ao iniciar imagem\n");
		al_destroy_display(janela);
		return -1;
	}

	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		fprintf(stderr, "Falha ao criar fila de evento\n");
		al_destroy_display(janela);
		al_destroy_bitmap(saida1.beatmap);
		al_destroy_bitmap(mensagem.beatmap);
		al_destroy_bitmap(mensagemTravada.beatmap);
		return -1;
	}

	// Torna apto o uso de mouse na aplicação
	if (!al_install_mouse()) {
		fprintf(stderr, "Falha ao iniciar o mouse\n");
		al_destroy_display(janela);
		al_destroy_bitmap(saida1.beatmap);
		al_destroy_bitmap(mensagem.beatmap);
		al_destroy_bitmap(mensagemTravada.beatmap);
		return -1;
	}
	// Atribui o cursor padrão do sistema para ser usado
	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
		fprintf(stderr, "Falha ao atribur ponteiro ao mouse\n");
		al_destroy_display(janela);
		al_destroy_bitmap(saida1.beatmap);
		al_destroy_bitmap(mensagem.beatmap);
		al_destroy_bitmap(mensagemTravada.beatmap);
		return -1;
	}

	//registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	//registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	////////////////////////////////////////////////

	// Preenchemos a janela de branco
	al_clear_to_color(al_map_rgb(255, 255, 255));

	//desenha a imagem na tela
	al_draw_bitmap(saida1.beatmap, saida1.x, saida1.y, 0);
	al_draw_bitmap(mensagem.beatmap, mensagem.x, mensagem.y, 0);
	al_draw_bitmap(mensagemTravada.beatmap, mensagemTravada.x, mensagemTravada.y, 0);

	// Atualiza a tela
	al_flip_display();

	int gameOver = 0;
	int acerto = 0;
	while (!gameOver)
	{
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
				if (IsInside(evento.mouse.x, evento.mouse.y, saida1)) {
					acerto = JogarFase1(janela, fila_eventos, acerto);
				}
			}
		}

		al_clear_to_color(al_map_rgb(255, 255, 255));

		al_draw_bitmap(saida1.beatmap, saida1.x, saida1.y, 0);
		if (acerto) {
			al_draw_bitmap(mensagem.beatmap, mensagem.x, mensagem.y, 0);
		}
		else
		{
			al_draw_bitmap(mensagemTravada.beatmap, mensagemTravada.x, mensagemTravada.y, 0);
		}

		al_flip_display();

	}
}