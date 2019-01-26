#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_ {
    int* data;
    int size;
    int count;
} vector;

void vector_init(vector*);
int vector_count(vector*);
void vector_add(vector*, int);
void vector_set(vector*, int, int);
int vector_get(vector*, int);
void vector_delete(vector*, int);
void vector_free(vector*);

#endif