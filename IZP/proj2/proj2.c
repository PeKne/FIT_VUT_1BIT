/******************************************************/
/* * *             Projekt c.2 - IZP              * * */
/* * *                                            * * */
/* * *            Petr Knetl(xknetl00)            * * */
/* * *                                            * * */
/* * *               listopad 2016                * * */
/* * *                                            * * */
/******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);
int main(int argc, char **argv)
{
    char *argX_control;
    double X = strtod(argv[2],&argX_control);

    if(*argX_control != '\0') //kontrola zda argument X konci nul. znakem
    {
        fprintf(stderr,"neplatna hodnota argumentu\n");
         return -2;
    }

    if(strcmp ("--log",argv[1])==0) // probehne vypocet logaritmu
    {
        if(argc != 4) //kontrola poctu argumentu
        { 
            fprintf(stderr,"spatny pocet argumentu\n"); 
            return -1;
        }

        char *argN_control;
        int N =strtol(argv[3], &argN_control,10);
        if(*argN_control != '\0') // kontrola zda arg. konci nul. znakem
        {
             fprintf(stderr,"neplatna hodnota argumentu\n");
             return -2;
        }
        printf("       log(%g) = %.12g\n",X,log(X));            // tisk  vyslednych hodnot spocitanych pomoci volanych funkci
        printf(" cfrac_log(%g) = %.12g\n",X, cfrac_log(X,N));
        printf("taylor_log(%g) = %.12g\n",X, taylor_log(X,N));
    }
    if(strcmp ("--pow",argv[1])==0) //probehne vypocet mocniny
    {
        if(argc != 5)//kontrola poctu argumentu
        {
            fprintf(stderr,"spatny pocet argumentu\n");
            return -1;
        }

        char *argN_control;
        int N =strtol(argv[4], &argN_control,10);
        if(*argN_control != '\0')// kontrola zda arg. konci nul. znakem
        {
             fprintf(stderr,"neplatna hodnota argumentu\n");
             return -2;
        }
        char *argY_control;
        double Y =strtod(argv[3],&argY_control);
        if(*argY_control != '\0')// kontrola zda arg. konci nul. znakem
        {
             fprintf(stderr,"neplatna hodnota argumentu\n");
             return -2;
        }
        printf("         pow(%g,%g) = %.12g\n",X, Y, pow(X,Y));          // tisk  vyslednych hodnot spocitanych pomoci volanych funkci
        printf("  taylor_pow(%g,%g) = %.12g\n",X ,Y, taylor_pow(X,Y,N)); 
        printf("taylorcf_pow(%g,%g) = %.12g\n", X, Y, taylorcf_pow(X,Y,N));
        
    }
   return 0;
}
double taylor_log(double x, unsigned int n) //funkce pocita logaritmus pomoci taylorova polynomu
{
   unsigned int i = 1; //urcuje pocet jiz provedenych cyklu a hodnotu jmenovatele
   double numer = 1; // hondota citatele
   double value=0; // vysledek po i(n) iteracich

   if(x == NAN)
   return NAN;
   
   if(x == 0)
   return -INFINITY;
   
   if (x == 1) 
   return +0;
   
   if (x== INFINITY)
   return INFINITY;
       
   if(0<x)
   {   
      if (x < 1) // podle hodnoty X rozhodne pomoci jakeho vzorce bude vypocet resen
      {
        while(i <= n) //probiha dokud neprovede pozadovany pocet iteraci
        {
           numer = numer * (1-x);
           value = value -(numer/i);
           i++;
        }
        return value;
      }
      if (x > 1) // podle hodnoty X rozhodne pomoci jakeho vzorce bude vypocet resen
      {
        while(i <= n)
        {
           numer = numer * ((x-1)/x);       
           value = value +  (numer/i);
           i++;
        }  
        return value; 
      }
      return 0; // navrati vysledek

   }
   return NAN;
}

double cfrac_log(double x, unsigned int n) //funkce pro vypocet logaritmu pomoci retezenych zlomku
{
   int a;
   double b=0; 
   double sum = 1;
   
   if(x == NAN)
   return NAN;
   
   if (x == 1) 
   return +0;
   
   if(x == 0)
   return -INFINITY;
   
   if (x== INFINITY)
   return INFINITY;
   
   if (x > 0)
   {
       x = (x-1)/(x+1);
       double sqr_x = x*x; //kvadrat x
       a= 2*n-1;
       sum = a;
       while(n!=1)
       {
          a= a-2;
          n--;
          b= (n*n*sqr_x);
          sum = (n*n*sqr_x)/sum;          //cf= fa(n) / (fb(n) - cf)
          sum = a + sum;
          printf("a=%d\nb=%f\nn=%d\nsum=%f\nvysledek=%f\n",a,b,n,sum,2*x/sum);
       }
       return 2*x/sum;
   }
   return NAN;    
}
double taylor_pow(double x, double y, unsigned int n) //funkce pro vypocet mocniny pomoci taylorova polynomu
{
   unsigned int i = 1;
   int fac = 1;
   double pow = 1;
   double sum = 1;
   double log = taylor_log(x,n);
   double pow_log = 1;
   
   if (x == 1 || y == 0)
   return 1.0;
   
   if ( x == NAN && y== NAN)
   return NAN;
   
   //TODO mezni hodnoty
  
   
   

   if(x>0)
   {       
      while(i<n)
      {
         pow_log = pow_log * log;
         fac = fac * i;
         pow = pow * y;
         sum = sum + pow*pow_log/fac;
         i++;
      }
      return sum; //navrati vysledek
   }
return -NAN; 
}
double taylorcf_pow(double x, double y, unsigned int n)// funkce pro vypocet mocniny pomoci zretezenych zlomku
{
   unsigned int i = 1;
   int fac = 1;
   double pow = 1;
   double sum = 1;
   double log = cfrac_log(x,n);
   double pow_log = 1;
   if(x>0)
   {       
      while(i<n)
      {
         pow_log = pow_log * log;
         fac = fac * i;
         pow = pow * y;
         sum = sum + pow*pow_log/fac;
         i++;
      }
      return sum; //navrati vysledek
   }
return -NAN; 
}





















