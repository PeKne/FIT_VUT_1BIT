#include <stdio.h>
#include <stdlib.h>
int strComp(char* str);

int main(int argc, char *argv[])
{
  switch (argc)
  {
      case 1 :                        //program bezi bez zadani argumentu
        {
         printf("funguju bez argumentu/n");
        }
      case 2 :                        
        {
         int strComp_return;
         
         strComp_return = strComp(argv[1]);
         
         switch(strComp_return)
         {
            case 1:      //byl zadan arg. "-x"
              {
              
              }
            case 2:      //byl zadan arg. "-S"
              {
              
              }
            case 3:      //byl zadan arg. "-r"
              {
              
              }
            case 4:      //byl zadan arg. "-s"
              {
              
              }
            case 5:      //byl zadan arg. "-n"
              {
              
              }
            default:     //argumenty byli spatne zadany
              {
              
              }            
        }

      case 4 :
        {

        }
      default:
        {

        }
       }
  }
  return 0;
}

int strComp(char *str)                 
{                                       
 int i=0;
 char *arg_x = "-x";
 char *arg_S = "-S";
 char *arg_r = "-r";
 char *arg_s = "-s";
 char *arg_n = "-n";                     

 for(i=0; str[i] != '\0' && arg_x[i] !='\0'; i++)
 {
   if(str[i] != arg_x[i])
   {
     for(i=0; str[i] != '\0' && arg_S[i] !='\0'; i++)
     {
       if(str[i] != arg_S[i])
        {
          for(i=0; str[i] != '\0' && arg_r[i] !='\0'; i++)
          {
            if(str[i] != arg_r[i])
            {
              for(i=0; str[i] != '\0' && arg_x[i] !='\0'; i++)
              {
                if(str[i] != arg_s[i])
                {
                  for(i=0; str[i] != '\0' && arg_s[i] !='\0'; i++)
                  {
                    if(str[i] != arg_s[i])
                    {
                      for(i=0;str[i] != '\0' && arg_n[i] !='\0'; i++)
                      {
                        if(str[i] != arg_n[i])
                        {
                          printf("spatne zadane argumenty");
                        }
                      }
                      return 0;

                    }
                  }
                  return 5;
                }
               } 
               return 4;
            }
          }
          return 3;
        }
     }
     return 2;
   }
 }
 return 1;
}



