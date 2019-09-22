#include <stdio.h>
// Inclui o arquivo de cabeçalho da biblioteca Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui a coisa do mouse
#include <allegro5/allegro_native_dialog.h>

#include "Struct.h"

#ifndef Funcoes_H
#define Funcoes_H


int IsInside(int x, int y, Objeto objeto) {
	if (x >= objeto.x && x <= (objeto.x + objeto.largura) && y >= objeto.y && y <= (objeto.y + objeto.altura)) {
		return 1;
	}
	return 0;
}

int MapearDistancia(int ponto, int x) {
	return ponto - x;
}

int VerificarBordas(int x, int y, Objeto imagem) {
	if (x - imagem.cliqueX <= 0 || x - imagem.cliqueX + imagem.largura >= LARGURA_TELA || y - imagem.cliqueY <= 0 || y - imagem.cliqueY + imagem.altura >= ALTURA_TELA) {
		return 1;
	}
	return 0;
}

int IsInsideImagem(Objeto menor, Objeto maior) {
	if (menor.x >= maior.x && menor.x + menor.largura <= maior.x + maior.largura && menor.y >= maior.y && menor.y + menor.altura <= maior.y + maior.altura) {
		return 1;
	}
	return 0;
}

#endif