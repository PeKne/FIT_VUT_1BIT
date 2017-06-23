/******************************************************/
/* * *             Projekt c.1 - IZP              * * */
/* * *                                            * * */
/* * *                Petr Knetl                  * * */
/* * *                                            * * */
/* * *            rijen/listopad 2016             * * */
/* * *                                            * * */
/******************************************************/



#include <stdio.h>
#include <stdlib.h>
int num_arg1, num_arg2;
int get_arg(int argc, char *argv[]);
int main(int argc, char* argv[])
{
    switch(get_arg(argc, argv))                                       
    {                                                                 /*   pomoci funkce switch volame      */
                                                                      /*   vlastni funkci get_arg. Podle    */
    case -1:  // chybne argumenty                                     /*  navracene hodnoty funkce get_arg  */
    {                                                                 /*  swith rozhodne o dalsim chovani   */
                                                                      /*             programu.              */
        fprintf(stderr, "chybne zadane argumenty\n");                  
        break;
    }
    case 0:   // zadne argumenty
    {
        int c;
        char line[17];
        for(int i =0; (i<16) && ((c = getchar()) != EOF); i++)
        {
            line[i] = c;
            if(i==0)
            {
                printf("AAAAAAAA ");
            }
            printf("%02x ",c);
            if(i==15)
            {
                line[17] = '\0' ;
                printf("|%s|\n",line);
                i = -1;
            }
        }

        break;

    }
    case 1:   // argument "-x"
    {
        int c;
        for(int i =0; ((c = getchar()) != EOF); i++)
        {
            printf("%02x",c);
        }
        printf("\n");
        break;
    }
    case 2:   // argument "-r"
    {
        printf("argument -r funguje\n");
        break;
    }
    case 3:   // argumenty "-s N"
    {
        printf("ciselny argument je %d \n",num_arg1);
        break;
    }
    case 4:   //argumenty "-n M"
    {
        printf("ciselny argument je %d \n",num_arg1);
        break;
    }
    case 5:   //argumenty "-S N"
    {
        int i=0;
        int c;
        while((c=getchar()) != EOF || i < num_arg1)
        {
            if(c=='\0')
            {
                printf("\n");
                i++;
            }
            else
            {
                putchar(c);
            }
        } 
        break;
    }
    case 6:   //argumenty "-s N -n M"
    {
        printf("ciselne argumenty jsou: %d, %d \n",num_arg1,num_arg2);
        break;
    }
    }
    return 0;
}

int get_arg(int argc, char *argv[])                          
{                                                            /* Funkce get_arg zjistuje */
                                                             /*   jake argumenty byly   */
    if(argc==1)                                              /*    zadany na vstupu.    */
    {                                                        /*     Podle zadanych      */
                                                             /* argumentu vraci hodnotu.*/
        return 0; //zadne zadane argumenty                   
    }                                                        
    if(argv[1][0] != '-' || argv[1][2] != '\0')
    {
        return -1; //chyba v argumentech
    }
    if(argv[1][1] == 'x' || argv[1][1] == 'r')
    {
        if(argc!=2)
        {
            return -1; //chyba v argumentech
        }
        if(argv[1][1] == 'x')
        {
            return 1; // zadan argument -x
        }
        if(argv[1][1] == 'r')
        {
            return 2;//zadan argument -r
        }
    }
    if(argv[1][1] == 's' || argv[1][1] == 'n'|| argv[1][1] == 'S')
    {
        if(argc == 3)
        {
            char *kontrola_strtol;
            num_arg1 = strtol(argv[2], &kontrola_strtol, 10);

            if(*kontrola_strtol!= '\0')
            {
                return -1;//chybne zadany argument
            }
            if(argv[1][1] == 's')
            {
                return 3;//zadany argumenty -s M
            }
            if(argv[1][1] == 'n')
            {
                return 4;//zadany argumenty -n N
            }
            if( argv[1][1] == 'S')
            {
                if (num_arg1<=0 || num_arg1>=200)
                {
                    return -1;//chybne zadany argument
                }
                return 5;//zadany argumenty -S M
            }

        }
    }

    if(argc == 5 && argv[1][0] == '-' && argv[1][1] == 's' && argv[1][2] == '\0' &&
            argv[3][0] == '-' && argv[3][1] == 'n' && argv[3][2] == '\0')
    {
        char *kontrola_strtol1;
        char *kontrola_strtol2;
        num_arg1 = strtol(argv[2], &kontrola_strtol1, 10);
        num_arg2 = strtol(argv[4], &kontrola_strtol2, 10);
        if(*kontrola_strtol1!='\0' ||* kontrola_strtol2!='\0')
        {
            return -1;//chybne zadany argument
        }
        return 6;//zadany argumenty -s M -n N
    }
    else

    {
        return -1;//chybne zadany argument
    }

}

