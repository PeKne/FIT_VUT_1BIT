#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Struktura pro objekt
 */
typedef struct
{
  int id;       /// ID
  char *name;   /// nazev
} Object;

/**
 * Inizializace objektu. Nazev objektu kopiruje. Objekt bude mit nazev
 * roven NULL, pokud se inicializace nezdarila.
 */
Object object_ctor(int id, char *name);

/**
 * Zamena dat dvou objektu.
 */
void object_swap(Object *i1, Object *i2);

/**
 * Hluboka kopie objektu src na dst. Vraci dst, pokud se operace povedla,
 * jinak NULL.
 */
Object *item_cpy(Object *dst, Object *src);

/**
 * Uvolni objekt (resp. jeho jmeno) z pameti.
 */
void object_dtor(Object *o);

/**
* Pomocne funkce pro vypis objektu (hodnota a ukazatel)
*/
void print_object(Object* o);

#endif // STRUCT_H
