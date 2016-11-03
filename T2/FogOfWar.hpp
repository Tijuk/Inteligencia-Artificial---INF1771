#pragma once
#include <stdio.h>
#include "Graphics.h"
#include <stdlib.h>
#include "Global.hpp"

class FOW_cls
{
public:
	FOW_cls();
	void load_fow(void);
	void atualiza_fow(void);
	void imprime_fow(void);
	void getLastVisitedTile(int *i, int *j);
	void getCurrentTile(int *i, int *j);
	int _fow[LN][COL];
	void exibe_fow(void);
};
