#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>

int strlen(char *cp)
{
    char* temp=cp;
    int i=0;
    while(*temp++)i++;
    return i;
}

int main()
{
    char* pNumber1="2945714556002451";
    char* pNumber2="20003154611";
    int leng1=strlen(pNumber1);
    int leng2=strlen(pNumber2);
    int leng3=((leng1>=leng2)?(leng1):(leng2))+1;
    char* pNumber3=(char*)malloc(leng3);

   *(pNumber3+leng3)='\0';

    char *index1=(pNumber1+leng1-1);
    char *index2=(pNumber2+leng2-1);
    char *index3=(pNumber3+leng3-1);

    int cary=0;
    while (pNumber3!=index3)
    {
          int temp1;
          if(index1>=pNumber1)temp1=*index1-48;else temp1=0;
          int temp2;;
          if(index2>=pNumber2)temp2=*index2-48;else temp2=0;

          *index3=(temp1+temp2+cary)%10+48;

          cary=(temp1+temp2)/10;
          index1--;
          index2--;
          index3--;
    }

    pNumber3=(index3+1);
    printf("%s+%s=%s",pNumber1,pNumber2,pNumber3);
    pNumber3=(index3+1);
    getch();
    free(pNumber3);
    return(0);
}
