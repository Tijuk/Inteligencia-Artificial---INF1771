#include <string.h>
#include "Agente.hpp"
#include "Graphics.h"

static Graphics agent_pkm;
static AgenteCls agnt;
static Image Agent;

void AgenteCls::agente_load(void)
{
	Agent.LoadPNGImage("Sprites\\Agente\\AgentSD.png");
}

void AgenteCls::insereAgente(void)
{
	agent_pkm.DrawImage2D(_posX,_posY,_spritesize,_spritesize,Agent);
}
AgenteCls::AgenteCls()
{
	float posfixer;
	_scale = 0.75f;
	posfixer = ((1-_scale)/2)*DFLTSIZE;
	_posX = (COL-1)* DFLTSIZE + MyZeroX + (int)posfixer;
	_posY = (LN-1)* DFLTSIZE + MyZeroY + (int)posfixer;
	_spritesize = (int)(_scale * (float)DFLTSIZE);
	_state = -1;
	_health = 100;
	_gold = 0;
}
char AgenteCls::checa_casa_atual(void)
{
	int indexX;
	int indexY;
	char a_map[LN][COL];
	passa_mapa(a_map);
	indexY = agnt.pos2index(_posX,0);
	indexX = agnt.pos2index(_posY,1);
	//printf("%d - %d\n", _posX, _posY);
	//printf("%d - %d\n", indexX, indexY);
	if(agnt._state == 0)
	{
		if(a_map[indexX][indexY] != '.')
		{
			GAME_STATE = 1;
		}
		if(a_map[indexX][indexY] == 'P')
		{
			agnt._state = 1;
			//printf("Buraco\n");
			agnt._health = 10;
			UltimaCasaAcessada = 'P';
		}
		else if(a_map[indexX][indexY] == 'O')
		{
			agnt._state = 1;
			printf("Ouro\n");
			UltimaCasaAcessada = 'O';
		}
		else if(a_map[indexX][indexY] == 'D')
		{
			agnt._state = 1;
			agnt._health -= 20;
			printf("Inimigo Grande\n");
			UltimaCasaAcessada = 'D';
		}
		else if(a_map[indexX][indexY] == 'd')
		{
			agnt._state = 1;
			agnt._health -= 10;
			printf("Inimigo Pequeno\n");
			UltimaCasaAcessada = 'd';
		}
		else if(a_map[indexX][indexY] == 'T')
		{
			agnt._state = 1;
			printf("Teletransporte\n");
			UltimaCasaAcessada = 'T';
		}
		else if(a_map[indexX][indexY] == 'U')
		{
			agnt._state = 1;
			printf("PowerUp\n");
			UltimaCasaAcessada =  'U';
		}
		else if(a_map[indexX][indexY] == '.')
		{
			agnt._state = 1;
			UltimaCasaAcessada = CasaVazia;
		}
	}
	return UltimaCasaAcessada;
}
int AgenteCls::pos2index(int pos, int axis)
{
	if(axis == 0) return ((pos - MyZeroX)/DFLTSIZE)-1;
	else if(axis == 1) return ((pos - MyZeroY)/DFLTSIZE)-1;
	return -1;
}
int AgenteCls::checkWin(void)
{
	int a = 0;
	if(agnt._gold == 3) a++; //Pegou todos os Ouros
	if(agnt.pos2index(agnt._posY,1) == posInicialX) a++; //Voltou ao Inicio
	if(agnt.pos2index(agnt._posX,0) == posInicialY) a++; //Voltou ao Inicio
	if(a == 3) return 1;
	return 0;
}
