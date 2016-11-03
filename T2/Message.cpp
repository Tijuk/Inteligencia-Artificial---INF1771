#include <string.h>
#include "Message.hpp"
#include "Graphics.h"

static Graphics mensagem;
static TextCls text;

static Image MBox;

TextCls::TextCls()
{
	_status = 0;
	_distX = 50 + MyZeroX + DFLTSIZE;
	_distY = 95;
	_sizeNC = 12;
	_sizeSC = 8;
	_elemento = '.';
	_uob = 'u';
	_concluido = 0;
	_waiting = 0;
	_loader = 0;
}
void TextCls::load_message(void)
{
	if(_loader == 0)
	{
		_loader = 1;
		MBox.LoadPNGImage("Sprites\\MessageBox\\BigMB.png");
	}
}

int TextCls::get_status(void)
{
	return _status;
}
void TextCls::set_status(int n)
{
	_status = n;
}
void TextCls::writeText(void)
{
	if(_status == 0)	
	{
		NLoop = 0;
		_status = 1;
		_concluido = 0;
		_waiting = 0;
	}
	load_message();
	_elemento = CasaAtual;
	mensagem.DrawImage2D(MyZeroX+DFLTSIZE-20, MyZeroX, 650, 150, MBox);
	mensagem.SetTextFont("Pokemon R/S",30, false, false, false);
	mensagem.SetColor(100,100,100);
	if(_waiting == 0) 
	{
		write1char(_elemento);
	}
	else if(_waiting == 1)
	{
		writestring(_elemento,_uob);
	}
}
char* TextCls::char2string(char elemento)
{
	char *result;
	char *s;
	char prestr[10] = "A wild ";
	char posstr[20] = " has appeared!!";
	int tamanho;
	if(elemento == 'P')
	{
		s = (char*)malloc(sizeof("Buraco"));
		strcpy(s,"buraco");
	}
	else if(elemento == 'O')
	{
		s = (char*)malloc(sizeof("Ouro"));
		strcpy(s,"ouro");
	}
	else if(elemento == 'D')
	{
		s = (char*)malloc(sizeof("Inimigo Grande"));
		strcpy(s,"inimigo grande");	
	}
	else if(elemento == 'd')
	{
		s = (char*)malloc(sizeof("Inimigo Pequeno"));
		strcpy(s,"inimigo pequeno");
	}
	else if(elemento == 'T')
	{
		s = (char*)malloc(sizeof("Teleporte"));
		strcpy(s,"teleporte");	
	}
	else if(elemento == 'U')
	{
		s = (char*)malloc(sizeof("Power Up"));
		strcpy(s,"power up");		
	}
	else
	{
		printf("Elemento Invalido\n");
		exit(1);
	}
	tamanho = (strlen(prestr) + strlen(s) + strlen(posstr)) + (1 - 3);
	result = (char*)malloc(tamanho * sizeof(char));
	strcpy(result, prestr);
	strcat(result, s);
	strcat(result, posstr);
	return result;
/*	char *s;
	s = (char*)malloc(200*sizeof(char));
	strcpy(s,"A wild buraco has appeared!!");
	return s;*/
}
void TextCls::write1char(char elemento)
{
	int i;
	int spaceX = (_distX - _sizeNC);
	int spaceY;
	char *s;
	int size;
	int sizechar = _sizeNC;;
	if(_uob == 'u')
	{
		spaceY = _distY;
		s = char2string(elemento);
		size = (int)strlen(s);
	}
	else if(_uob == 'b')
	{
		spaceY = _distY - 35;
		s = getBotString(elemento);
		size = (int)strlen(s);
	}
	_concluido++;
	if(_concluido == size)
	{
		_concluido = 0;
		_waiting = 1;
	}
	else
	{
		if(_uob == 'u')
		{
			for(i=0; i< NLoop+1; i++)
			{
				if(i > 0)
				{
					if((s[i-1] == 'i') || (s[i-1] == 'l'))
					{
						sizechar = _sizeSC;
					}
					else if(s[i-1] == 'r')
					{
						sizechar = 10;
					}
					else
					{
						sizechar = _sizeNC;
					}
				}
				spaceX += sizechar;
				mensagem.DrawText2D(spaceX, spaceY, "%c", s[i]);
			}
		}
		else if(_uob == 'b')
		{
			writestring(elemento, 'u');
			for(i=0; i< NLoop+1; i++)
			{
				if(i > 0)
				{
					if((s[i-1] == 'i') || (s[i-1] == 'l'))
					{
						sizechar = _sizeSC;
					}
					else if(s[i-1] == 'r')
					{
						sizechar = 10;
					}
					else
					{
						sizechar = _sizeNC;
					}
				}
				spaceX += sizechar;
				mensagem.DrawText2D(spaceX, spaceY, "%c", s[i]);
			}
		}
	}
}
void TextCls::writestring(char elemento, char uob)
{
	int i;
	int spaceX = (_distX - _sizeNC);
	int spaceY;
	char *s;
	int size;
	int sizechar = _sizeNC;
	if(uob == 'u')
	{
		spaceY = _distY;
		s = char2string(elemento);
	}
	else if(uob == 'b')
	{
		spaceY = _distY - 35;
		s = getBotString(elemento);
		writestring(elemento, 'u');
	}
	size = (int)strlen(s);
	for(i=0; i < size; i++)
	{
		if(i > 0)
		{
			if((s[i-1] == 'i') || (s[i-1] == 'l'))
			{
				sizechar = _sizeSC;
			}
			else if(s[i-1] == 'r')
			{
				sizechar = 10;
			}
			else
			{
				sizechar = _sizeNC;
			}
		}
		spaceX += sizechar;
		mensagem.DrawText2D(spaceX, spaceY, "%c", s[i]);
	}
}
char* TextCls::getBotString(char elemento)
{
	char *s;
	if(elemento == 'P')
	{
		s = (char*)malloc(sizeof("You died!!"));
		strcpy(s,"You died!!");
	}
	else if(elemento == 'U' || elemento == 'O')
	{
		s = (char*)malloc(sizeof("Press G to grab it."));
		strcpy(s,"Press G to grab it.");
	}
	else if(elemento == 'D' || elemento == 'd')
	{
		s = (char*)malloc(sizeof("Press W to bathe in the blood of your enemy"));
		strcpy(s,"Press W to bathe in the blood of your enemy");
	}
	else if(elemento == 'T')
	{
		s = (char*)malloc(sizeof("Start praying!!"));
		strcpy(s,"Start praying!!");
	}
	return s;
}
void TextCls::exibePrivate(void)
{
	printf("Text:\n");
	printf("Status: %d\n", _status);
	printf("UOB: %c\n", _uob);
	printf("Waiting: %d\n", _waiting);
	printf("Concluido: %d\n", _concluido);
	printf("Elemento: %c\n", _elemento);
}
