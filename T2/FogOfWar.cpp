#include "FogOfWar.hpp"
#include "Graphics.h"
#include "Agente.hpp"

static Graphics fog;
static AgenteCls agnt;
static Image FOW1;
static Image FOW2;

static char backup_mapa[LN][COL];

FOW_cls::FOW_cls()
{
	int i, j;
	int x,y;
	for(i=0; i<LN; i++)
	{
		for(j=0; j<COL;j++)
		{
			_fow[i][j] = 0;
		}
	}
	x = posInicialX;
	y = LN-posInicialY-1;
	_fow[x][y] = 2;
}
void FOW_cls::load_fow(void)
{
	FOW1.LoadPNGImage("Sprites\\FOW\\FOW.png");
	FOW2.LoadPNGImage("Sprites\\FOW\\FOW2.png");
}
void FOW_cls::atualiza_fow(void)
{
	int i,j;
	i = 0, j = 0;
	getLastVisitedTile(&i,&j);
	_fow[i][j] = 1;

	getCurrentTile(&i,&j);
	_fow[i][j] = 2;
}
void FOW_cls::imprime_fow(void)
{
	int i,j;
	int coordX;
	int coordY;
	for(i=0; i<LN; i++)
	{
		for(j=0; j<COL;j++)
		{
			coordX = ((j+1)*DFLTSIZE)+MyZeroX;
			coordY = ((LN - i)*DFLTSIZE)+MyZeroY;
			if(_fow[i][j] == 0)
			{
				fog.DrawImage2D(coordX, coordY, DFLTSIZE,DFLTSIZE, FOW1);
			}
			else if(_fow[i][j] == 1)
			{

				fog.DrawImage2D(coordX, coordY, DFLTSIZE,DFLTSIZE, FOW2);
			}
		}
	}
}
void FOW_cls::getLastVisitedTile(int *i, int *j)
{
	int iaux, jaux;
	for(iaux=0; iaux<LN; iaux++)
	{
		for(jaux=0; jaux<COL; jaux++)
		{
			if(_fow[iaux][jaux] == 2)
			{
				*i = iaux;
				*j = jaux;
				return;
			}
		}
	}
	//exibe_fow();
	printf("Errmmm.... Nao foi achada a ultima casa visitada\n");
	exit(1);
}
void FOW_cls::getCurrentTile(int *i, int *j)
{
	int cmpX, cmpY;
	cmpX = agnt.pos2index(agnt._posX,0);
	cmpY = agnt.pos2index(agnt._posY,1);
	*j = cmpX;
	*i = (LN-cmpY-1);
	//printf("%d - %d\n", cmpX, cmpY);
	if(cmpX < 0 || cmpY < 0)
	{
		printf("Errmmm.... Houston, perdemos o jogador!!\n");
		exit(1);
	}
	return;
}
void FOW_cls::exibe_fow(void)
{
	int i,j;
	for(i=0; i<LN; i++)
	{
		for(j=0; j<COL; j++)
		{
			printf("[%d]", _fow[i][j]);
		}
		printf("\n");
	}
}