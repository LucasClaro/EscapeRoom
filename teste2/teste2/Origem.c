#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

// Tamanho da tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480
 
typedef struct Objeto
{
	int x;
	int y;
	int largura;
	int altura;
} Objeto;

// Nossa conhecida função main...
int main(void)
{
	//////////////////////////////////////////////////////////////////
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;

	// Variável para imagem
	ALLEGRO_BITMAP *imagem = NULL;
	ALLEGRO_BITMAP *botao = NULL;

	//declara a fila de eventos
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
 
	//////////////////////////////////////////////////////////////////
    // Inicializamos a biblioteca
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
	al_set_window_title(janela, "Usando o Mouse");
 
	Objeto dedede;
	dedede.x = 0;
	dedede.y = 0;
	dedede.largura = 100;
	dedede.altura = 100;
	// Carrega a imagem
	imagem = al_load_bitmap("Imgs/photo.bmp");
	if (!imagem) {
		fprintf(stderr, "Falha ao iniciar imagem\n");
		al_destroy_display(janela);
		return -1;
	}	

	Objeto btn;
	btn.x = LARGURA_TELA - 200;
	btn.y = ALTURA_TELA - 150;
	btn.largura = LARGURA_TELA - 100;
	btn.altura = ALTURA_TELA - 50;
	botao = al_create_bitmap(btn.x,btn.y);
	if (!botao)
	{
		fprintf(stderr, "Falha ao iniciar imagem\n");
		al_destroy_display(janela);
		al_destroy_bitmap(imagem);
		return -1;
	}

	//cria fila de eventos
	fila_eventos = al_create_event_queue();
	if (!fila_eventos) {
		fprintf(stderr, "Falha ao iniciar imagem\n");
		al_destroy_display(janela);
		al_destroy_bitmap(imagem);
		al_destroy_bitmap(botao);
		return -1;
	}

	// Torna apto o uso de mouse na aplicação
	if (!al_install_mouse()) {
		fprintf(stderr, "Falha ao iniciar o mouse\n");
		al_destroy_display(janela);
		al_destroy_bitmap(imagem);
		al_destroy_bitmap(botao);
		return -1;
	}
	// Atribui o cursor padrão do sistema para ser usado
	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
		fprintf(stderr, "Falha ao atribur ponteiro ao mouse\n");
		al_destroy_display(janela);
		al_destroy_bitmap(imagem);
		al_destroy_bitmap(botao);
		return -1;
	}

	//registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	//registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	//////////////////////////////////////////////////////////////////	

	// Preenchemos a janela de branco
	al_clear_to_color(al_map_rgb(255, 255, 255));

	//desenha a imagem na tela
	al_draw_bitmap(imagem, dedede.x, dedede.y, 0);
 
    // Atualiza a tela
    al_flip_display();

	int gameOver = 0;
	int Dentro = 0;
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
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (IsInside(evento.mouse.x, evento.mouse.y, dedede))
				{
					dedede.x++;
				}
				else
				{
					dedede.y++;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
				if (IsInside(evento.mouse.x, evento.mouse.y, btn))
				{
					Dentro = 1;
				}
				else
				{
					Dentro = 0;
				}
			}
		}		


		al_clear_to_color(al_map_rgb(255, 255, 255));//Define a cor do fundo

		al_set_target_bitmap(botao);//Define o beatmap em edição
		if (Dentro)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		else {
			al_clear_to_color(al_map_rgb(100, 100, 100));
		}
		
		al_set_target_bitmap(al_get_backbuffer(janela));//Define a janela com em edição
		//Coloca as imagens
		al_draw_bitmap(imagem, dedede.x, dedede.y, 0);
		al_draw_bitmap(botao, btn.x, btn.y, 0);		

		al_flip_display();
	}
 
    // Segura a execução por 10 segundos
    //al_rest(10.0);
 
    // Finaliza a janela
    al_destroy_display(janela);

	// Finaliza imagem
	al_destroy_bitmap(imagem);
	al_destroy_bitmap(botao);

	// Finaliza fila de eventos
	al_destroy_event_queue(fila_eventos);
 
    return 0;
}

int IsInside(int x, int y, Objeto objeto) {
	if (x >= objeto.x && x <= (objeto.x + objeto.largura) && y >= objeto.y && y <= (objeto.y + objeto.altura)) {
		return 1;
	}
	return 0;
}
