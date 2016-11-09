#include <string.h>
#include "Message.hpp"

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
	_warn = 0;
	_start = 0;
	_delay = 0;
}
void TextCls::load_message(void)
{
	MBox.LoadPNGImage("Sprites\\MessageBox\\BigMB.png");
}
int TextCls::get_status(void)
{
	return _status;
}
void TextCls::set_status(int n)
{
	_status = n;
}
void TextCls::writeText(Graphics& mensagem, int timer)
{
	if(_elemento != 'E')
	{
		mensagem.DrawImage2D(MyZeroX+DFLTSIZE-20, MyZeroX, 650, 150, MBox);
		mensagem.SetTextFont("Pokemon R/S",30, false, false, false);
		mensagem.SetColor(100,100,100);
		write1char(_elemento, mensagem);
	}
	else
	{
		_status = 0;
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
		printf("Modulo: Message\nFuncao char2string:\tElemento Invalido\n");
		exit(1);
	}
	tamanho = (strlen(prestr) + strlen(s) + strlen(posstr)) + (1 - 3);
	result = (char*)malloc(tamanho * sizeof(char));
	strcpy(result, prestr);
	strcat(result, s);
	strcat(result, posstr);
	_delay = (2 * strlen(result)) + 50;
	return result;
/*	char *s;
	s = (char*)malloc(200*sizeof(char));
	strcpy(s,"A wild buraco has appeared!!");
	return s;*/
}
void TextCls::write1char(char elemento,Graphics& mensagem)
{
	int i;
	int spaceX = (_distX - _sizeNC);
	int spaceY;
	char *s;
	int size;
	int sizechar = _sizeNC;
	if(_uob == 'u')
	{
		spaceY = _distY;
		s = char2string(elemento);
	}
	else
	{
		spaceY = _distY - 35;
		s = getBotString(elemento);
	}
	if(_concluido < (int)strlen(s))
	{
		_concluido++;
	}
	else
	{
		_concluido = 0;
		if(_uob == 'u')
		{
			_uob = 'b';
		}
		else
		{
			_uob = ' ';
		}
		return;
	}
	size = _concluido;
	if(_uob == 'u')
	{
		for(i=0; i< size; i++)
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
		writestring(elemento, 'u', mensagem);
		for(i=0; i<  size; i++)
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
void TextCls::writestring(char elemento, char uob,Graphics& mensagem)
{
	int i;
	int spaceX = (_distX - _sizeNC);
	int spaceY;
	char *str;
	int size;
	int sizechar = _sizeNC;
	if(uob == 'u')
	{
		spaceY = _distY;
		str = char2string(elemento);
	}
	else if(uob == 'b')
	{
		spaceY = _distY - 35;
		str = getBotString(elemento);
		writestring(elemento, 'u',mensagem);
	}
	size = (int)strlen(str);
	for(i=0; i < size; i++)
	{
		if(i > 0)
		{
			if((str[i-1] == 'i') || (str[i-1] == 'l'))
			{
				sizechar = _sizeSC;
			}
			else if(str[i-1] == 'r')
			{
				sizechar = 10;
			}
			else
			{
				sizechar = _sizeNC;
			}
		}
		spaceX += sizechar;
		mensagem.DrawText2D(spaceX, spaceY, "%c", str[i]);
	}
}
char* TextCls::getBotString(char elemento)
{
	char *string;
	if(elemento == 'P')
	{
		string = (char*)malloc(sizeof("You died!!"));
		strcpy(string,"You died!!");
	}
	else if(elemento == 'U' || elemento == 'O')
	{
		string = (char*)malloc(sizeof("Press G to grab it."));
		strcpy(string,"Press G to grab it.");
	}
	else if(elemento == 'D' || elemento == 'd')
	{
		string = (char*)malloc(sizeof("Press W to bathe in the blood of your enemy"));
		strcpy(string,"Press W to bathe in the blood of your enemy");
	}
	else if(elemento == 'T')
	{
		string = (char*)malloc(sizeof("Start praying!!"));
		strcpy(string,"Start praying!!");
	}
	return string;
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
void TextCls::show_warning(char elemento, Graphics& mensagem,  AgenteCls &agnt)
{
	int i;
	int spaceX = (_distX - _sizeNC);
	int spaceY = _distY;
	int sizechar = _sizeNC;
	int size;
	char s[200];
	if(elemento == 'O')
	{
		strcpy(s,"Ouro obtained!!");
	}
	else if( elemento == 'U')
	{
		strcpy(s,"Player!! This isnt the time to do that!!");
	}
	else if(agnt._health <= 0)
	{
		strcpy(s,"Oh... Im afraid you died!! Press R to restart");
	}
	size = strlen(s);
	if(_concluido < size)
	{
		_concluido++;
	}
	else
	{
		_warn = 0;
	}
	for(i=0; i < _concluido; i++)
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
void TextCls::set_gowarn(int n)
{
	_gowarn = n;
}
void TextCls::readytext(char elemento, Graphics &mensagem)
{
	int i;
	int space = (_distX - _sizeNC);
	char *upper;
	char *bottom;
	upper = char2string(elemento);
	bottom = getBotString(elemento);
	mensagem.DrawImage2D(MyZeroX+DFLTSIZE-20, MyZeroX, 650, 150, MBox);
	mensagem.SetTextFont("Pokemon R/S",30, false, false, false);
	mensagem.SetColor(100,100,100);
	//mensagem.DrawText2D(_distX, _distY, "%s", upper);
	//mensagem.DrawText2D(_distX, _distY - 35, "%s", bottom);
	for(i=0; i< (int)strlen(upper); i++)
	{
		if(i > 0)
		{
			if((upper[i-1] == 'i') || (upper[i-1] == 'l'))
			{
				space += _sizeSC;
			}
			else if(upper[i-1] == 'r')
			{
				space += 10;
			}
			else
			{
				space += _sizeNC;
			}
		}
		else
		{
			space += _sizeNC;
		}
		mensagem.DrawText2D(space, _distY, "%c", upper[i]);
	}
	space = (_distX - _sizeNC);
	for(i=0; i< (int)strlen(bottom); i++)
	{
		if(i > 0)
		{
			if((bottom[i-1] == 'i') || (bottom[i-1] == 'l'))
			{
				space += _sizeSC;
			}
			else if(bottom[i-1] == 'r')
			{
				space += 10;
			}
			else
			{
				space += _sizeNC;
			}
		}
		else
		{
			space += _sizeNC;
		}
		mensagem.DrawText2D(space, _distY - 35, "%c", bottom[i]);
	}
	_waiting = 1;
	_concluido = 0;
}
void TextCls::set_sucess(int n)
{
	_sucess = n;
}
/*
void TextCls::staticText(Graphics &mensagem, char elemento, float timer)
{
	int i;
	int duration;
	char *upper;
	char *bottom;
	duration = 3;
	upper = char2string(elemento);
	bottom = getBotString(elemento);
	mensagem.DrawImage2D(MyZeroX+DFLTSIZE-20, MyZeroX, 650, 150, MBox);
	mensagem.SetTextFont("Pokemon R/S",30, false, false, false);
	mensagem.SetColor(100,100,100);
	if(timer%(duration*1000) <= duration)
	{
		mensagem.DrawText2D(_distX, _distY, "%s", upper);
		mensagem.DrawText2D(_distX, _distY - 35, "%s", bottom);
	}
}*/