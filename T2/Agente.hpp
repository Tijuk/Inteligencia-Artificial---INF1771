#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Global.hpp"

class AgenteCls
{
public:
	int pos2index(int pos, int axis);
	AgenteCls();
	int _posX;
	int _posY;
	float _scale;
	int _spritesize;
	int _state;
	int _health;
	int _gold;
	void insereAgente(void);
	char checa_casa_atual(void);
	int checkWin(void);
	void agente_load(void);
};
