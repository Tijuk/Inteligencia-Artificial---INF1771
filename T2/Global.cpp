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
int MESSAGE_STATE = 0;
static char mapa_global[LN][COL];
static char mapa_global_backup[LN][COL];

void le_mapa(void)
{
	int i = 0;
	int j = 0;
	FILE *arq;
	arq = fopen("mapa.txt", "r");
	for(i=0; i<LN; i++)
	{
		for(j=0; j<LN; j++)
		{
			fscanf(arq," %c", &mapa_global[LN-(i+1)][j]);
			//mapa_global[i][j] = '.';
			//if(i==j) mapa_global[i][j] = 'T';
			if((LN-(j+1))==1 && i==1)
			{
				mapa_global[LN-(i+1)][j] = 'E';
			}
			//mapa_global[i][j] = '.';
			mapa_global_backup[LN-(i+1)][j]=mapa_global[LN-(i+1)][j];
		}
	}
	fclose(arq);
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
void deleta_ponto(int x, int y)
{
	mapa_global[x][y] = CasaVazia;
}
void passa_backup(char matriz[LN][COL])
{
	int i = 0;
	int j = 0;
	for(i=0; i<LN; i++)
	{
		for(j=0; j<LN; j++)
		{
			matriz[i][j] = mapa_global_backup[i][j];
		}
	}
}
int in_range(int time, int min, int max)
{
	if(time >= min && time <= max) 
	{
		return 1;
	}
	return 0;
}
int get_range(int duration, int nframes)
{
	int value;
	value = (duration/nframes);
	return value;
}
void adjust_scale(float scale, int tile_size, int* x, int *y, int *size)
{
	float posfixer;
	posfixer = ( (1.f - scale)/2.f )* (float)tile_size;
	*x = *x + (int)posfixer;
	*y = *y + (int)posfixer;
	*size = (int)((float)(*size) * scale);
}
int in_range_delayed(int _time, int prop, int acclrt)
{
	int time;
	time = (_time / acclrt)%100;
	if(time <= (prop/acclrt)) 
	{
		return 1;
	}
	return 0;
}


