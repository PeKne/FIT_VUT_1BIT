/******************************************************/
/* * *             Projekt c.3 - IZP              * * */
/* * *                                            * * */
/* * *            Petr Knetl(xknetl00)            * * */
/* * *                                            * * */
/* * *               prosinec 2016                * * */
/* * *                                            * * */
/******************************************************/
/**
 * Kostra programu pro 3. projekt IZP 2015/16
 *
 * Jednoducha shlukova analyza
 * Complete linkage
 * http://is.muni.cz/th/172767/fi_b/5739129/web/web/clsrov.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*m
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap) 
{
    assert(c != NULL);
    assert(cap >= 0);
    
	c->capacity = cap;
	c->size = 0;
	c->obj = malloc(cap*sizeof(struct obj_t));
}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
   free(c->obj);

    c -> size = 0;
    c -> obj = NULL;
    c -> capacity = 0;
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{

	if((c->size)<(c->capacity))
	{
        c->obj[c->size] = obj;
        c->size++;
    }
    else
    {
        resize_cluster(c,c->capacity+CLUSTER_CHUNK);
        c->obj[c->size] = obj;
        c->size++;
    }

}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);
    int newSize = c1->size + c2->size;
    int i =0;
    
    
    if(newSize > c1->capacity)
    {
	int new_cap = newSize - c1->capacity;
	resize_cluster(c1,c1->capacity + new_cap);
	}
    while(i < c2->size)
    {
		append_cluster(c1,c2->obj[i]);
		i++;
	}
	c1->size = newSize;
    sort_cluster(c1);
}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);
    int i = idx;
    int ret;

    // TODO
    while (i < narr)
    {
        clear_cluster(&carr[i]);
        merge_clusters(&carr[i], &carr[i+1]);
        i++;
    }

    clear_cluster(&carr[narr-1]);
    ret = narr-1;
    return ret;
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    // TODO
    float a,b,d;
    if(o1->x == o2->x)
    {
		d = fabs(o1->x - o2->x);
	}
	else if(o1->y == o2->y)
	{
		d = fabs(o1->y - o2->y);
	}
	else
	{
		a=fabs(o1->x - o2->x);
		a= a*a;
		b=fabs(o1->y - o2->y);
		b=b*b;
		d = sqrt(a+b);
	}
	return d;	
}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);

    // TODO
    float d = obj_distance(&c1->obj[0], &c2->obj[0]);
    int x = 0;

    while(x < c1->size)
    {
        int y = 0;
        while( y < c2->size)
        {
            float newDistance = obj_distance(&c1->obj[x], &c2->obj[y]);

            if(d < newDistance)
            {
                d = newDistance;
            }
            y++;
        }
        x++;
    }

    return d;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);

    // TODO
    float d = cluster_distance(&carr[0], &carr[1]);
    
    int c1_index = 0;
    int c2_index = 0;
    int x = 0;

    while(x < narr)
    {
        int y = x + 1;
        while(y < narr)
        {
            float newDistance = cluster_distance(&carr[x], &carr[y]);
            if(d >= newDistance)
            {
                d = newDistance;
                c1_index = x;
                c2_index = y;
            }
            y++;
        }
        x++;
    }

    *c1 = c1_index;
    *c2 = c2_index;
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = a;
    const struct obj_t *o2 = b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);

    // TODO
    int N, id;
    int i = 0;
    int idx_number = 0;
    float x,y;

    
    FILE* file = fopen(filename, "r");
    
    if(file==NULL)
    {
        return 1;
    }
    fscanf(file, "%*[^=]=%d", &N);
    if (N<=0)
    {
    	return 2;
    }
    
    *arr = malloc(sizeof(struct cluster_t)*N);
    if(arr == NULL)
    {
        return 3;
    }
    
    while(i < N)
    { 
        fscanf(file, "%d %f %f", &id, &x, &y);

        struct obj_t temporary_obj;
            temporary_obj.id = id;
            temporary_obj.x = x;
            temporary_obj.y = y;

        init_cluster((*arr)+idx_number, 1);

        append_cluster((*arr)+idx_number, temporary_obj);

        idx_number++;
        i++;
    }

    fclose(file);
    return N;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main(int argc, char *argv[])
{
    struct cluster_t *CLUSTS;
    int c1;
    int c2;   
    int cluster_count;
    char *strCheck;
    if(argc == 3){
            cluster_count = strtol(argv[2], &strCheck, 10);
            if(strlen(strCheck)!=0)
            {
                fprintf(stderr, "chybne parametry\n");
                return 3;
            }
        }
    else if(argc == 2){
            cluster_count = 1;
        }
    else{
        fprintf(stderr, "spatny pocet parametru programu\n");
        return 3;
    }

    int size = load_clusters(argv[1], &CLUSTS);
    switch(size)
    {
    case 3:
   
            fprintf(stderr, "chyba pri alokaci pameti\n");
            return 2;
    case 1:
        
            fprintf(stderr, "nastala chyba pri otevirani souboru\n");
            return 1;
        
    case 2:
        
            fprintf(stderr, "CHYBA:hodnota druheho parametru musi byt vetsi nez 0\n");
            return 4;
        
    }    
    if (size<cluster_count || cluster_count <= 0){
    	fprintf(stderr, "nelze zobrazit vice clusteru nez celkovy pocet objektu\n");
    	return 5;
    }

    while(size > cluster_count){
            find_neighbours(CLUSTS, size, &c1, &c2);
            merge_clusters(&CLUSTS[c1], &CLUSTS[c2]);
            remove_cluster(CLUSTS, size, c2);
            size--;
        }
    
    print_clusters(CLUSTS, size);

    int i= 0;
    while(i<size)
    {
        clear_cluster(&CLUSTS[i]);
        i++;
    }
    free(CLUSTS);


    return 0;
}
