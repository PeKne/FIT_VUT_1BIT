int strComp(char *str)                 
{                                       
 int i=0;
 char *arg_x = "-x";
 char *arg_S = "-S";
 char *arg_r = "-r";
 char *arg_s = "-s";
 char *arg_n = "-n";                     

 for(i=0; str[i] != '\0' && arg_x[i] !='\0; i++)
 {
   if(str[i] != arg_x[i])
   {
     for(i=0; str[i] != '\0' && arg_S[i] !='\0; i++)
     {
       if(str[i] != arg_S[i])
        {
          for(i=0; str[i] != '\0' && arg_r[i] !='\0; i++)
          {
            if(str[i] != arg_r[i])
            {
              for(i=0; str[i] != '\0' && arg_x[i] !='\0; i++)
              {
                if(str[i] != arg_s[i])
                {
                  for(i=0; str[i] != '\0' && arg_s[i] !='\0; i++)
                  {
                    if(str[i] != arg_s[i])
                    {
                      for(i=0;str[i] != '\0' && arg_n[i] !='\0; i++)
                      {
                        if(str[i] != arg_n[i])
                        {
                          printf("spatne zadane argumenty")
                        }
                      }
                      return 6;

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









