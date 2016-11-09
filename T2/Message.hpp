#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Global.hpp"
#include "Graphics.h"
#include "Agente.hpp"

class TextCls
{
private:
	int _status;
	char* char2string(char elemento);
	int _distX;
	int _distY;
	int _sizeNC;
	int _sizeSC;
	char _elemento;
	int _delay;
	int _sucess;
public:
	void set_sucess(int n);
	int _start;
	int _porqn;
	int _concluido;
	int _gowarn;
	void load_message(void);
	int _warn;
	TextCls();
	char _uob;
	int _waiting;
	int get_status(void);
	void set_gowarn(int n);
	void set_status(int n);
	void writeText(Graphics& mensagem, int timer);
	void write1char(char elemento,Graphics& mensagem);
	void writestring(char elemento, char uob,Graphics& mensagem);
	char* getBotString(char elemento);
	void exibePrivate(void);
	void show_warning(char elemento, Graphics& mensagem,AgenteCls &agnt);
	void readytext(char elemento, Graphics &mensagem);
};