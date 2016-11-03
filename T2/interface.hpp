#pragma once
#include <stdio.h>

#define _LN 12
#define _COL 12

class InterGraf 
{
private:
	void insereElementos(char elemento, int coordX, int coordY);
	void insereMarcas(char elemento, int coordX, int coordY);
	void insereParedes(void);
	void insereChao(void);
	void carregaImagens(void);

public:
	InterGraf();
	void iniciaGraficos(int FlSn);
	void insereHealthHUD(void);
	void executa(void);
	void iniciaMapa(void);
	void exibeMapa(void);
	void teclado_jogo(int *key, int *state, int *x, int *y);
	void teclado_message(int *key, int *state, int *x, int *y);
};

class ElementosCls{
public:
	void atualizaOuro(void);
};

class EndGameCls
{
private:
	void load_eg(void);
	void show_result(void);
	void victory(void);
	void defeat(void);
public:
	void finalizaJogo(void);
	void reset(void);
};
