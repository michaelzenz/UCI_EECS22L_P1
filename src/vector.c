#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void vector_init(vector *v)
{
    v->data = NULL;
    v->size = 0;
    v->count = 0;
}

int vector_count(vector *v)
{
    return v->count;
}

void vector_add(vector *v, int p)
{
    if (v->size == 0) {
        v->size = 8;
        v->data = malloc(sizeof(int) * v->size);
    }

    if (v->size == v->count) {
        v->size *= 2;
        v->data = realloc(v->data, sizeof(int) * v->size);
    }

    v->data[v->count] = p;
    v->count++;
}

void vector_set(vector *v, int index, int p)
{
    if (index >= v->count) {
        return;
    }

    v->data[index] = p;
}

int vector_get(vector *v, int index)
{
    if (index >= v->count) {
        return NULL;
    }

    return v->data[index];
}

void vector_delete(vector *v, int index)
{
    if (index >= v->count) {
        return;
    }

    for (int i = index, j = index; i < v->count; i++) {
        v->data[j] = v->data[i];
        j++;
    }

    v->count--;
}

void vector_free(vector *v)
{
    free(v->data);
}