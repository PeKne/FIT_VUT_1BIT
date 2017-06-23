#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
int main(int argc, char **argv)
{
    char *argX_control;
    double X = strtod(argv[2],&argX_control);

    if(*argX_control != '\0')
    {
        fprintf(stderr,"neplatna hodnota argumentu\n");
         return -2;
    }

    if(strcmp ("--log",argv[1])==0) // probehne funkce  logaritmu
    {
        if(argc != 4)
        {
            fprintf(stderr,"spatny pocet argumentu\n");
            return -1;
        }

        char *argN_control;
        int N =strtol(argv[3], &argN_control,10);
        if(*argN_control != '\0')
        {
             fprintf(stderr,"neplatna hodnota argumentu\n");
             return -2;
        }
        printf("taylor_log = %.12g\n", taylor_log(X,N));
        printf("cfrac_log = %.12g\n", cfrac_log(X,N));
    }
    if(strcmp ("--pow",argv[1])==0) //probehne funkce mocniny
    {
        if(argc != 5)
        {
            fprintf(stderr,"spatny pocet argumentu\n");
            return -1;
        }

        char *argN_control;
        int N =strtol(argv[4], &argN_control,10);
        if(*argN_control != '\0')
        {
             fprintf(stderr,"neplatna hodnota argumentu\n");
             return -2;
        }
        char *argY_control;
        double Y =strtod(argv[3],&argY_control);
        if(*argY_control != '\0')
        {
             fprintf(stderr,"neplatna hodnota argumentu\n");
             return -2;
        }
    }
   return 0;
}
double taylor_log(double x, unsigned int n)
{
   unsigned int i = 1; //urcuje pocet provedenych cyklu a hodnotu jmenovatele
   double pow = 1;
   double value=0;

   if(0<x&&x<2)
   {
      while(i <= n)
      {
         pow = pow * (1-x);
         value = value -(pow/i);
         i++;
      }

       return value;

   }
   return -3;
}
double fa(int n)
{
    int i


}
double fb(int n)
{

}
double cfrac_log(double x, unsigned int n)
{
   double cf = 0;
   while(n>=1)
   {
      cf= fa(n) / (fb(n) - cf);
      n--;
   }








return value;
}























