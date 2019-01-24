#include"constant.h"
#include"stack.h"

#ifndef GAMEENV_H
#define GAMEENV_H

extern int playerTurn;

void env_eset();

int env_get_playerTurn();
void env_play();

#endif

