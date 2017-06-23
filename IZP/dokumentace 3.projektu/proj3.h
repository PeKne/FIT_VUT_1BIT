/**
 * Kostra hlavickoveho souboru 3. projekt IZP 2015/16
 * a pro dokumentaci Javadoc.
 */

/** 
  * \defgroup funkce funkce_programu
  * \defgroup konstanty
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

/** Inicializuje novy cluster s urcitou kapacitou
 *  \ingroup funkce
 *  \post vznikne cluster s danou kapacitou
 *  \param c ukazatel na adresu kde se ma cluster vytvorit
 *  \param cap kapacita clusteru neboli velikost alokovane pameti
 */
void init_cluster(struct cluster_t *c, int cap);

/** vymaze hodnoty daneho clusteru a uvolni adresu na ktere je ulozen
 *  \ingroup funkce
 *  \pre existuje dany cluster ktery chceme uvolnit
 *  \post prazdne misto na predchozi adrese cluster
 *  \param c adresa daneho clusteru
 */  
void clear_cluster(struct cluster_t *c);

/** konstanta vyuzivana k rozsireni clusteru
  * /ingroup konstanty
  *
  */
extern const int CLUSTER_CHUNK;

/** Meni velikost daneho clusteru na kapacitu danou promennou new_cap
  * \ingroup funkce
  * \pre existujici cluster
  * \post rozsireny cluster
  * \param c ukazatel na cluster ktery se ma zmenit
  * \param new_cap nova kapacita clusteru neboli velikost alokovane pameti
  * \return vraci rozsireny cluster
  */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/** do daneho clusteru prida dany objekt
  * \ingroup funkce
  * \pre existuje cluster a objekt ktery do nej chceme pridat
  * \post objekt je soucasti clusteru
  * \param c ukazatel na cluster kam chceme pridat prvek
  * \param obj objekt ktery chceme pridat do clusteru
  * 
  */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/** Do jednoho clusteru(c1) prida objekty z clusteru(c2) druheho,
  * pokud se prvky doclusteru nevejdou, cluster se rozsiri.
  * Objekty v clusteru c1 se vzestupne seradi podle identifikacniho cisla.
  * \ingroup funkce
  * \pre existuji dva clustery
  * \post do clusteru jsou pridany objekty z druheho clusteru, druhy cluster je nezmenen
  * \param c1 ukazatel na prvni cluster
  * \param c2 ukazatel na druhy cluster
  * 
  */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/** Odstrani cluster z pole clusteru
  * \ingroup funkce
  * \pre existuje pole clusteru ve kterem se vyskytuje prvek ktery chceme odstranit
  * \post pole clusteru bez odstraneneho prvku
  * \param carr pole clusteru
  * \param narr pocet clusteru v poli narr
  * \param idx index na kterem se vyskytue prvek ktery chceme odstranit
  * \return vraci novy pocet clusteru v poli
  */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/** Pocita Euklidovskou vzdalenost dvou objektu.
  * \ingroup funkce
  * \pre existuji dva objekty objekty
  * \param o1 prvni objekt
  * \param o2 druhy objekt
  * \return vzdalenost objektu
  */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/** Pocita Euklidovskou vzdalenost dvou clusteru
  * \ingroup funkce
  * \pre existuji dva clustery
  * \param c1 prvni cluster
  * \param c2 druhy cluster
  * \return vzdalenost clusteru
  */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/** Nachazi dva nejblizsi clustery v poli clusteru 'narr'. Nelezene clusteru ulozi do pameti na adresu 'c1' a 'c2'.
  * \ingroup funkce
  * \pre existuje pole clusteru s minimalne dvema prvky
  * \post nejblizsi clustery se ulozi na adresu 'c1' a 'c2'
  * \param carr pole clusteru
  * \param narr velikost pole clusteru
  * \param c1 adresa kam se ulozi prvni nalezeny cluster
  * \param c2 adresa kam se ulozi druhy nalezeny cluster
  */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/** seradi objekty v clusteru vzestupne podle identifikacniho cisla 
  * \ingroup funkce
  * \pre existuje cluster
  * \post serazeny cluster
  * \param c cluster, ktery chceme seradit
  *
  */
void sort_cluster(struct cluster_t *c);

/** Tiskne cluster
  * \ingroup funkce
  * \pre existuje dany cluster
  * \post na stdout se vytiskne dany cluster
  * \param c cluster ktery chceme vytisknout
  *
  */
void print_cluster(struct cluster_t *c);

/** Cte objekty ze souboru. Pro kazdy objekt vytvori vlastni cluster a ulozi ho do
  * pole clusteru. Alokuje pamet pro pole vsech clusteru a ukazatel na tuto pamet
  * ulozi do pameti do promene 'arr 
  * \ingroup funkce
  * \pre existuje soubor ve kterem jsou vypsany objekty
  * \post pole clusteru
  * \param filename nazev souboru s objekty
  * \param arr ukazatel do ktereho se ulozi vytvorene pole clusteru
  * \return pocet nactenych objektu ze souboru
  */
int load_clusters(char *filename, struct cluster_t **arr);

/** Tiskne pole clusteru.
  * \ingroup funkce
  * \pre existuje pole clusteru
  * \post na stdout se vytiskne pole clusteru
  * \param carr ukazatel na prvni polozku pole clusteru
  * \param narr pocet clusteru ktere chceme vytisknout na stdout
  *
  */
void print_clusters(struct cluster_t *carr, int narr);
