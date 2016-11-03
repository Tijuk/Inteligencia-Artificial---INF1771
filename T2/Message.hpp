#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Global.hpp"

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
	int _concluido;
	void load_message(void);
	int _loader;
public:
	TextCls();
	char _uob;
	int _waiting;
	int get_status(void);
	void set_status(int n);
	void writeText(void);
	void write1char(char elemento);
	void writestring(char elemento, char uob);
	char* getBotString(char elemento);
	void exibePrivate(void);
};