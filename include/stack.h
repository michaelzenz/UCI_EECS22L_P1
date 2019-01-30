#include<string.h>
#include"jsmn.h"
#include"struct.h"
#include<stdio.h>
#include <stdlib.h>
#ifndef STACK_H
#define STACK_H



void stack_push(Node** head_ref, char* new_log, size_t data_size);
char* stack_pop();
int stack_get_size();
void move2string(char* str_move, Move *move);
Move string2move(char* str_move);
static int dump(const char *js, jsmntok_t *t, size_t count, int indent);
void stack_init();

#endif