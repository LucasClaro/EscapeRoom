#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#ifndef Struct_H
#define Struct_H

// Tamanho da tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

#define SOME_HEADER_GUARD_WITH_UNIQUE_NAME

typedef struct Obj
{
	ALLEGRO_BITMAP* beatmap;
	int x;
	int y;
	int largura;
	int altura;
	int cliqueX;
	int cliqueY;
} Objeto;

#endif