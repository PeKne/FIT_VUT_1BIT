#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"

/**
 * Struktura reprezentujici pole
 */
typedef struct
{
  unsigned size; /// velikost pole
  Object *items; /// pole objektu (pole struktur)
} Array;

/**
 * Konstruktor pole. Vytvori pole o velikosti size a kazdy prvek
 * v nem inicializuje na hodnoty 0, NULL.
 */
Array array_ctor(unsigned size);

/**
 * Uvolni pole (a vsechny jeho objekty) z pameti.
 */
void array_dtor(Array *arr);

/**
 * Zmena velikosti pole. Zmeni/realokuje zadane pole na novou velikost.
 * V pripade zvetseni jeste inicializuje kazdy prvek na hodnoty 0, NULL.
 * V pripade zmenseni uvolni objekty odstranene z pole.
 */
Array array_resize(Array *arr, unsigned size);

/**
 * Hledani prvku v poli podle identifikatoru prvku. Vraci index prvku v poli
 * nebo -1, pokud prvek pole neobsahuje.
 */
int array_find_id(Array *arr, int id);

/**
 * Hledání prvku v poli podle názvu. Vraci index prvku v poli
 * nebo -1, pokud prvek pole neobsahuje.
 */
int array_find_name(Array *arr, char *name);

/**
 * Vlozeni prvku do pole na zadany index. Pokud je index obsazen, funkce posune zbytek pole.
 *  Vraci index vlozeneho prvku (idx) nebo -1, pokud se operace nezdarila.
 */
int array_insert_item(Array *arr, Object *item, unsigned idx);

/**
 * Hledani prvku s nejmensim identifikatorem. Vraci index prvku nebo -1,
 * pokud je pole prazdne.
 */
int array_find_min(Array *arr);

/**
 * Funkce otestuje, zda je pole prazdne.
 * Pokud ano, funkce vrati 1, jinak vrati 0.
 */
bool array_empty(Array* arr);

/**
 * Razeni prvku v poli podle jejich identifikatoru. (bubble sort)
 */
void array_sort_bubble(Array *arr);

/**
 *  Razeni prvku v poli podle jejich identifikatoru. (select sort)
 */
 void array_sort_select(Array *arr);

/**
 * Vypis vsech prvku pole.
 */
void array_print(char* str, Array* arr);
#endif
