#include "Global.hpp"

int SW = 1400;
int SH = 1000;
int posInicialX = 1;
int posInicialY = 1;
int MyZeroX = 10;
int MyZeroY = 100 - (MyZeroX - 2);
int mapEdgeX = ((LN+1)*DFLTSIZE) + MyZeroX;
int mapEdgeY = ((LN+1)*DFLTSIZE) + MyZeroY;
char UltimaCasaAcessada = 0;
char CasaAtual = 0;
int NLoop = 0;
int GAME_STATE = 0;

void le_mapa(void)
{
	int i = 0;
	int j = 0;
	FILE *arq;
	arq = fopen("mapa.txt", "r");
	//fscanf(arq, "%c", &wut);
	//printf("Valor de i = %c\n",wut);
	for(i=0; i<LN; i++)
	{
		for(j=0; j<LN; j++)
		{
			fscanf(arq," %c", &mapa_global[LN-(i+1)][j]);
		}
	}
}

void passa_mapa(char matriz[LN][COL])
{
	int i = 0;
	int j = 0;
	for(i=0; i<LN; i++)
	{
		for(j=0; j<LN; j++)
		{
			matriz[i][j] = mapa_global[i][j];
		}
	}
}