//Inclusão da biblioteca gráfica da PlayLib
#include "Graphics.h"
#include "interface.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Global.hpp"
#include "Message.hpp"
#include "FogOfWar.hpp"
#include "Agente.hpp"

static Graphics graphics;
static InterGraf graf;
static FOW_cls fogow;
static AgenteCls agnt;
static EndGameCls endgame;
static TextCls text;
static char mapa[LN][COL];

Image MapFloor,Grade;
Image RightWall, LeftWall, TopWall, DownWall, TLCorner, TRCorner, DLCorner, DRCorner;
Image Ouro;
Image BigEnemy;
Image SmallEnemy;
Image PowerUp;
Image Teleport;
Image Buraco;
Image MarcaBuraco;
Image MarcaInimigo;
Image MarcaTeleport;
Image HealthHUD[11];

void sleep(int time);
void le_mapa();
//void KeyboardSpecialInput(int key, int x, int y);
void teclado(int key, int state, int x, int y);

int gS = 1; //gS = gridSize
 
void MainLoop()
{
	graf.insereHealthHUD();
	graf.iniciaMapa();
	agnt.insereAgente();
	CasaAtual = agnt.checa_casa_atual();
	fogow.atualiza_fow();
	fogow.imprime_fow();
	if(agnt.checkWin() == 1 || agnt._health <= 0)
	{
		endgame.finalizaJogo();
	}
	if(GAME_STATE == 1)
	{
		fogow.exibe_fow();
		text.writeText();
	}
	NLoop++;
}
InterGraf::InterGraf()
{
	GAME_STATE = 0;
}
void InterGraf::executa()
{
	le_mapa();
	passa_mapa(mapa);
	graf.iniciaGraficos(FS);
	graf.carregaImagens();
	fogow.load_fow();
	graphics.SetKeyboardInput(teclado);
	graphics.SetMainLoop(MainLoop);
	graphics.StartMainLoop();
}
void InterGraf::iniciaGraficos(int FlSn)
{
	graphics.CreateMainWindow(SW, SH, "Teste");
	graphics.SetBackgroundColor(40,40,40);
	//graphics.SetBackgroundColor(200,200,200);
	if(FlSn == 1)
	{
		graphics.SetFullscreen(true);
	}
}
void InterGraf::carregaImagens(void)
{
	//MapFloor;
	//RightWall, LeftWall, TopWall, DownWall, TLCorner, TRCorner, DLCorner, DRCorner;
	MapFloor.LoadPNGImage("Sprites\\Floor\\Floor.png");
	RightWall.LoadPNGImage("Sprites\\Wall\\RightWall.png");
	LeftWall.LoadPNGImage("Sprites\\Wall\\LeftWall.png");
	TopWall.LoadPNGImage("Sprites\\Wall\\TopWall.png");
	DownWall.LoadPNGImage("Sprites\\Wall\\DownWall.png");
	TLCorner.LoadPNGImage("Sprites\\Wall\\TLCorner.png");
	TRCorner.LoadPNGImage("Sprites\\Wall\\TRCorner.png");
	DLCorner.LoadPNGImage("Sprites\\Wall\\DLCorner.png");
	DRCorner.LoadPNGImage("Sprites\\Wall\\DRCorner.png");
	Ouro.LoadPNGImage("Sprites\\Ouro\\Coin1.png");
	BigEnemy.LoadPNGImage("Sprites\\Inimigos\\InimigoGrande.png");
	SmallEnemy.LoadPNGImage("Sprites\\Inimigos\\InimigoPequeno.png");
	PowerUp.LoadPNGImage("Sprites\\PowerUp\\PU12.png");
	Teleport.LoadPNGImage("Sprites\\Teleport\\Teleport1.png");
	Buraco.LoadPNGImage("Sprites\\Buraco\\Buraco.png");
	Grade.LoadPNGImage("Sprites\\grid.png");
	MarcaBuraco.LoadPNGImage("Sprites\\Marks\\HoleMark.png");
	MarcaInimigo.LoadPNGImage("Sprites\\Marks\\SwordMark.png");
	MarcaTeleport.LoadPNGImage("Sprites\\Marks\\Portal.png");
	HealthHUD[0].LoadPNGImage("Sprites\\HUDHP\\HUD_0.png");
	HealthHUD[1].LoadPNGImage("Sprites\\HUDHP\\HUD_1.png");
	HealthHUD[2].LoadPNGImage("Sprites\\HUDHP\\HUD_2.png");
	HealthHUD[3].LoadPNGImage("Sprites\\HUDHP\\HUD_3.png");
	HealthHUD[4].LoadPNGImage("Sprites\\HUDHP\\HUD_4.png");
	HealthHUD[5].LoadPNGImage("Sprites\\HUDHP\\HUD_5.png");
	HealthHUD[6].LoadPNGImage("Sprites\\HUDHP\\HUD_6.png");
	HealthHUD[7].LoadPNGImage("Sprites\\HUDHP\\HUD_7.png");
	HealthHUD[8].LoadPNGImage("Sprites\\HUDHP\\HUD_8.png");
	HealthHUD[9].LoadPNGImage("Sprites\\HUDHP\\HUD_9.png");
	HealthHUD[10].LoadPNGImage("Sprites\\HUDHP\\HUD_10.png");
}
void InterGraf::iniciaMapa()
{
	int i;
	int j;
	int coordX;
	int coordY;
	graf.insereChao();
	for(i=1; i<LN+1; i++)
	{
		for(j=1; j<COL+1; j++)
		{
			coordX = (j*DFLTSIZE)+MyZeroX;
			coordY = (i*DFLTSIZE)+MyZeroY;
			graf.insereMarcas(mapa[i-1][j-1], coordX, coordY);
		}
	}
	for(i=1; i<LN+1; i++)
	{
		for(j=1; j<COL+1; j++)
		{
			coordX = (j*DFLTSIZE)+MyZeroX;
			coordY = (i*DFLTSIZE)+MyZeroY;
			graf.insereElementos(mapa[i-1][j-1], coordX, coordY);
		}
	}
	graf.insereParedes();
	graphics.DrawImage2D(MyZeroX+DFLTSIZE,MyZeroY+DFLTSIZE,mapEdgeX-MyZeroX,mapEdgeY-MyZeroY, Grade);
}
void InterGraf::exibeMapa()
{
	int i,j;
	for(i=0; i<LN; i++)
	{
		for(j=0; j<COL; j++) printf("%c", mapa[LN-(i+1)][j]);
		printf("\n");
	}
	return;
}
void InterGraf::insereElementos(char elemento, int coordX, int coordY)
{
	if(elemento == 'U') // PowerUp
	{
		graphics.DrawImage2D(coordX,coordY,DFLTSIZE,DFLTSIZE, PowerUp);
	}
	else if(elemento == 'T') // Teletransporte
	{
		graphics.DrawImage2D(coordX,coordY,DFLTSIZE,DFLTSIZE, Teleport);
	}
	else if(elemento == 'D') // Inimigo Grande
	{
		graphics.DrawImage2D(coordX,coordY,DFLTSIZE,DFLTSIZE, BigEnemy);
	}
	else if(elemento == 'd') // Inimigo Pequeno
	{
		graphics.DrawImage2D(coordX,coordY,DFLTSIZE,DFLTSIZE, SmallEnemy);
	}
	else if(elemento == 'O') // Ouro
	{
		graphics.DrawImage2D(coordX,coordY,DFLTSIZE/2,DFLTSIZE/2, Ouro);
	}
	else if(elemento == 'P') //Buraco
	{
		graphics.DrawImage2D(coordX,coordY,DFLTSIZE,DFLTSIZE, Buraco);
	}
}
void InterGraf::insereMarcas(char elemento, int coordX, int coordY)
{
	int tile = DFLTSIZE;
	int posX;
	int posY;
	if(elemento == 'P') //Buraco
	{
		int posMB_x,posMB_y;
		posMB_x = 0;
		posMB_y = 0;
		posX = coordX + posMB_x + tile;
		posY = coordY + posMB_y;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaBuraco);
		posX = coordX + posMB_x;
		posY = coordY + posMB_y + tile;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaBuraco);
		posX = coordX + posMB_x - tile;
		posY = coordY + posMB_y;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaBuraco);
		posX = coordX + posMB_x;
		posY = coordY + posMB_y - tile;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaBuraco);
	}
	else if(elemento == 'T') //Portal
	{
		int posMT_x,posMT_y;
		posMT_x = 47;
		posMT_y = 47;

		posX = coordX + posMT_x + tile;
		posY = coordY + posMT_y;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaTeleport);

		posX = coordX + posMT_x;
		posY = coordY + posMT_y + tile;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaTeleport);

		posX = coordX + posMT_x - tile;
		posY = coordY + posMT_y;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaTeleport);

		posX = coordX + posMT_x;
		posY = coordY + posMT_y - tile;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaTeleport);
	}
	else if(elemento == 'D' || elemento == 'd') //inimigo
	{
		int posMI_x, posMI_y;
		posMI_x = 1;
		posMI_y = 47;

		posX = coordX + posMI_x + tile;
		posY = coordY + posMI_y;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaInimigo);

		posX = coordX + posMI_x;
		posY = coordY + posMI_y + tile;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaInimigo);

		posX = coordX + posMI_x - tile;
		posY = coordY + posMI_y;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaInimigo);

		posX = coordX + posMI_x;
		posY = coordY + posMI_y - tile;
		graphics.DrawImage2D(posX,posY, 16,16, MarcaInimigo);
	}
}
void InterGraf::insereParedes(void)
{
	int i;
	graphics.DrawImage2D(MyZeroX,MyZeroY,DFLTSIZE,DFLTSIZE, DLCorner);
	graphics.DrawImage2D(mapEdgeX,MyZeroY,DFLTSIZE,DFLTSIZE, DRCorner);
	graphics.DrawImage2D(MyZeroX,mapEdgeY,DFLTSIZE,DFLTSIZE, TLCorner);
	graphics.DrawImage2D(mapEdgeX,mapEdgeY,DFLTSIZE,DFLTSIZE, TRCorner);
	for(i=1; i<COL+1; i++)
	{
		graphics.DrawImage2D((i*64)+MyZeroX,mapEdgeY,DFLTSIZE,DFLTSIZE, TopWall);
		graphics.DrawImage2D(mapEdgeX,(i*64)+MyZeroY,DFLTSIZE,DFLTSIZE, RightWall);
		graphics.DrawImage2D(MyZeroX,(i*64)+MyZeroY,DFLTSIZE,DFLTSIZE, LeftWall);
		graphics.DrawImage2D((i*64)+MyZeroX,MyZeroY,DFLTSIZE,DFLTSIZE, DownWall);

	}
}
void InterGraf::insereChao(void)
{
	int i;
	int j;
	int coordX;
	int coordY;
	for(i=1; i<LN+1; i++)
	{
		for(j=1; j<COL+1; j++)
		{
			coordX = (j*DFLTSIZE)+MyZeroX;
			coordY = (i*DFLTSIZE)+MyZeroY;
			graphics.DrawImage2D(coordX, coordY, DFLTSIZE,DFLTSIZE, MapFloor);
		}
	}
}
void InterGraf::teclado_jogo(int *_key, int *_state, int *x, int *y)
{
	int key, state;
	key = *_key;
	state = *_state;
	//if(agnt._state != 1)
	{
		if (key == KEY_RIGHT)
		{
			agnt._state = 0;
			if(agnt._posX < mapEdgeX - DFLTSIZE)
				agnt._posX += MOVSPD;
		}
		else if (key == KEY_LEFT)
		{
			agnt._state = 0;
			if(agnt._posX > MyZeroX + DFLTSIZE)
				agnt._posX -= MOVSPD;
		}
		else if (key == KEY_DOWN)
		{
			agnt._state = 0;
			agnt._posY -= MOVSPD;
		}
		else if (key == KEY_UP)
		{
			agnt._state = 0;
			agnt._posY += MOVSPD;
		}
		else if(key == 'r') //resetGame
		{
			endgame.reset();
		}
		else if(key == 'w')//fight
		{
			printf("LOOK MOMMA, IM FIGHTNING DRAGONS 'N STUFF\n");
		}
		else if(key == 'e')//leaveCave
		{
			if(agnt.checkWin() == 1)
			{
				endgame.finalizaJogo();
			}
		}
	}
}
void InterGraf::teclado_message(int *_key, int *_state, int *x, int *y)
{
	int key;
	key = *_key;
	if(key == ' ')
	{
		GAME_STATE = 0;
	}
	else if(key == KEY_ENTER)
	{
		if(text._uob == 'u' && text._waiting == 1)
		{
			text._uob = 'b';
			text._waiting = 0;
			NLoop = 0;
		}
		else if(text._uob == 'b' && text._waiting == 1)
		{
			text._uob = 'u';
			GAME_STATE = 0;
			NLoop = 0;
		}
	}
	else if(key == 'g')//grab
	{
		if(text._uob == 'b' && text._waiting == 1)
		{
			if(agnt.checa_casa_atual() == 'O')//Ouro
			{
				int x,y;
				y = agnt.pos2index(agnt._posX,0);
				x = agnt.pos2index(agnt._posY,1);
				mapa[x][y] = CasaVazia;
				agnt._gold++;
			}
			else if(agnt.checa_casa_atual() == 'U')//PowerUp
			{
				int x,y;
				y = agnt.pos2index(agnt._posX,0);
				x = agnt.pos2index(agnt._posY,1);
				mapa[x][y] = CasaVazia;
				agnt._health += 30;
				if(agnt._health > 100) agnt._health = 100;
			}
		}
	}
	else if(key == 'v')
	{
		text.exibePrivate();
	}
}
void teclado(int key, int state, int x, int y)
{
	if (state == KEY_STATE_UP)
		return;
	if(GAME_STATE == 0)
	{
		graf.teclado_jogo(&key, &state, &x, &y);
	}
	else if(GAME_STATE == 1)
	{
		graf.teclado_message(&key, &state, &x, &y);
	}
	if(key == 'h') //help
	{
		printf("Agente:\n");
		printf("HP: %d\n", agnt._health);
		printf("Gold: %d\n",agnt._gold);
		printf("PosX: %d\n",agnt._posX);
		printf("PosY: %d\n",agnt._posY);
		printf("Inimigos Derrotados: %d\n",0);
		printf("index X: %d\n",agnt.pos2index(agnt._posX,0));
		printf("index Y: %d\n",agnt.pos2index(agnt._posY,1));

		printf("Mapa:\n");
		graf.exibeMapa();

		printf("Fog of War:\n");
		fogow.exibe_fow();
	}
	else if(key == KEY_ESC)
	{
		exit(0);
	}
}
void InterGraf::insereHealthHUD(void)
{
	int HUDWidth;
	int HUDHeight;
	int coordX, coordY;
	HUDWidth = 351;
	HUDHeight = 126;
	coordX = mapEdgeX + 100;
	coordY = mapEdgeY - HUDHeight;
	graphics.DrawImage2D(coordX,coordY,HUDWidth,HUDHeight,HealthHUD[agnt._health/10]);
}

void EndGameCls::finalizaJogo(void)
{
	int agntposfinalX, agntposfinalY;
	agntposfinalY = agnt.pos2index(agnt._posX,0);
	agntposfinalX = agnt.pos2index(agnt._posY,1);
	if(agnt._health > 0 && agnt._gold == 3 && agntposfinalX == posInicialX && agntposfinalY == posInicialY)//vitoria
	{
		printf("PARABENS!! VOCE VENCEU\n");
		exit(0);
	}
	else if(agnt._health <= 0) //defeat
	{
		printf("PARABENS!! VOCE PERDEU\n");
		exit(0);
	}
	else //erro
	{
		printf("Errmmm... Voce nao deveria estar aqui!! - EndGame::finalizaJogo\n");
		exit(1);
	}
}
void EndGameCls::reset(void)
{
	printf("---- PROGRAMA REINICIADO ----\n\n");
	int i,j;
	float posfixer;
	//resetaFOW
	for(i=0; i<LN; i++)
	{
		for(j=0; j<COL; j++)
		{
			fogow._fow[i][j] = 0;
		}
	}
	i = posInicialX;
	j = LN-posInicialY-1;
	fogow._fow[i][j] = 2;
	fogow.exibe_fow();

	//reseta jogador
	agnt._gold = 0;
	agnt._health = 100;
	posfixer = ((1-agnt._scale)/2)*DFLTSIZE;
	agnt._posX = (COL-1)* DFLTSIZE + MyZeroX + (int)posfixer;
	agnt._posY = (LN-1)* DFLTSIZE + MyZeroY + (int)posfixer;

	//reseta mapa
	for(i=0; i<LN; i++)
	{
		for(j=0; j<COL; j++)
		{
			passa_mapa(mapa);
		}
	}
	graf.exibeMapa();
}

