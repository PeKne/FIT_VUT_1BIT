#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int get_arg(int argc, char *argv[], int num_arg1, int num_arg2);
int main(int argc, char* argv[])
{
    int num_arg1, *p_num_arg1;
    int num_arg2, *p_num_arg2;
    p_num_arg1 = &num_arg1;
    p_num_arg2 = &num_arg2;


    switch(get_arg(argc, argv, *p_num_arg1,*p_num_arg2))
    {
    case -1:  // chybne argumenty
    {

    }
    case 0:   // zadne argumenty
    {

    }
    case 1:   // argument "-x"
    {

    }
    case 2:   // argument "-r"
    {

    }
    case 3:   // argumenty "-s N"
    {

    }
    case 4:   //argumenty "-n M"
    {

    }
    case 5:   //argumenty "-S N"
    {

    }
    case 6:   //argumenty "-s N -n M"
    {

    }
    }
    return 0;
}

int get_arg(int argc, char *argv[], int num_arg1, int num_arg2)
{
    if(argc==1)
    {
        return 0; //zadne argumenty
    }
    if(argv[1][0] != '-' && argv[1][2] != '\0')
    {
        return -1; //chyba
    }
    if(argv[1][1] == 'x' || argv[1][1] == 'r')
    {
        if(argc!=2)
        {
            return -1; //chyba
        }
        if(argv[1][1] == 'x')
        {
            return 1; //funkce hexa_print
        }
        if(argv[1][1] == 'r')
        {
            return 2;//funkce -r
        }
    }
    if(argv[1][1] == 's' || argv[1][1] == 'n'|| argv[1][1] == 'S')
    {
        if(argc == 3)
        {
            int num_arg1 = strtol(argv[2],nodigit, 10);
            if(argv[1][1] == 's')
            {
                return 3;//funkce skip
            }
            if(argv[1][1] == 'n')
            {
                return 4;//funkce pocet znaku
            }
            if( argv[1][1] == 'S')
            {
                if (0>=num_arg1 || num_arg1>=200)
                {
                    return -1;//chyba
                }
                return 5;//funkce strings
            }
        }
        if(argc == 5 && argv[1][0] == '-' && argv[1][1] == 's' && argv[1][2] == '\0' &&
                argv[3][0] == '-' && argv[3][1] == 'n' && argv[3][2] == '\0')
        {
            int num_arg1 = strtol(argv[2],nodigit1,10);
            int num_arg2 = strtol(argv[4],nodigit2,10);
            return 6;
        }
    }
    return -1;
}

