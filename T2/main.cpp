#include <stdio.h>
#include <stdlib.h>
//#include "interface.hpp"
#include "Global.hpp"

int main(void)
{
	char mapa[12][12];
	//InterGraf graf;
	//graf.executa();
	le_mapa;
	passa_mapa(mapa);
	int i,j;
	for(i=0; i<12;i++)
	{
		for(j=0; j<12; j++)
		{
			//printf("%d",i+j);
			printf("%c", mapa[i][j]);
		}
		printf("\n");
	}
	return 0;
}
