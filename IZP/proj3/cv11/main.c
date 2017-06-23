#include<stdio.h>

#include "struct.h"
#include "array.h"

/**
 * Hlavni program.
 */
int main()
{
	/*
	printf("STRUKTURY\n------------\n");
	// vytvoreni objektu
	Object o1 = object_ctor(10,"Alice");
	Object o2 = object_ctor(20,"Petr");
    // vypiseme objekty
	print_object(&o1);
	print_object(&o2);

	printf("------------\nVymena objektu\n------------\n");
	object_swap(&o1,&o2);

	print_object(&o1);
	print_object(&o2);

    printf("------------\nKopie objektu\n------------\n");
	Object o3;
	o3 = object_ctor(0, NULL);
	item_cpy(&o3, &o1);
    print_object(&o3);

	// dealokace pameti
	object_dtor(&o1);
	object_dtor(&o2);
	object_dtor(&o3);
    //////////////////////////////////////////////////
	printf("POLE\n------------\n");
	// vytvoreni pole
	Array arr = array_ctor(5);

	array_print("Nove inicializovane pole\n------------\n", &arr);

	Object ao1 = object_ctor(110,"Ananas");
	Object ao2 = object_ctor(240,"Broskev");
	Object ao3 = object_ctor(80,"Citron");
	Object ao4 = object_ctor(60,"Hruska");
	Object ao5 = object_ctor(20,"Meloun");

	int status = 0;
	status = array_insert_item(&arr, &ao1, 0);
	if (status == -1)
		return -1;

	status = array_insert_item(&arr, &ao2, 1);
	if (status == -1)
		return -1;

	status = array_insert_item(&arr, &ao3, 2);
	if (status == -1)
		return -1;

	status = array_insert_item(&arr, &ao4, 3);
	if (status == -1)
		return -1;

	status = array_insert_item(&arr, &ao5, 4);
	if (status == -1)
		return -1;

	array_print("------------\nPole s inicializovanymi polozkami\n------------\n", &arr);

    // rozsireni pole - 7 polozek
	arr = array_resize(&arr, 7);
	array_print("------------\nRozsirene pole\n------------\n", &arr);
    // zmenseni pole - 2 polozky
	arr = array_resize(&arr, 2);
	array_print("------------\nZmensene pole\n------------\n", &arr);
    // nastaveni pole na puvodni velikost
	arr = array_resize(&arr, 5);
	array_print("------------\nRozsirene pole na puvodni velikost\n------------\n", &arr);

	// otestujeme, jestli funguje vlozeni prvku na obsazenou polozku
	Object ao6 = object_ctor(70, "Jablko");
	status = array_insert_item(&arr, &ao6, 1);

	if (status == -1)
		return -1;

	array_print("------------\nPole s dalsim prvkem\n------------\n", &arr);
    // vkladani za meze pole
	printf("------------\nExperiment s vlozenim za meze pole\n------------\n");
	Object ao7 = object_ctor(70, "Mandarinka");

	status = array_insert_item(&arr, &ao7, 20);
	if (status == -1)
	{
		fprintf(stderr,"Chyba pri vlozeni.\n");
		object_dtor(&ao7);
	}

	// zmenseni pole - 3 prvky
	arr = array_resize(&arr, 3);
	array_print("------------\nZmensene pole na 3 prvky\n------------\n", &arr);
    // vyhledani objektu s nejmensim ID a se zadanym nazvem
	printf("------------\nObjekt s nejmensim ID\n------------\n\n");
	print_object(&arr.items[array_find_min(&arr)]);

	int findID = 240;
	printf("------------\nObjekt s ID %d\n------------\n", findID);
	print_object(&arr.items[array_find_id(&arr, findID)]);

	char* findName = "Broskev";
	printf("------------\nObjekt se jmenem  %s\n------------\n", findName);
	print_object(&arr.items[array_find_name(&arr, findName)]);

	// serazeni pole
	array_sort_bubble(&arr);
	// pripadne: array_sort_select(&arr);
	array_print("------------\nSerazene pole\n------------\n", &arr);

    // uvolneni pameti
	array_dtor(&arr);

	*/
	return 0;
}
