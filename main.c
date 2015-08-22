#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dec_binary(int num,char bin[15])
{
    int i,mod;

    for(i=0;i<15;i++)
        bin[i]='0';

    i--;

    while(num)
    {
        mod=num%2;

        if(mod)
            bin[i]='1';

        num/=2;
        i--;
    }
}

void scan1(FILE *fptr,FILE *inptr)
{
    int pc=0;
    char c;
    bool newlineFlag=true;

    while(fscanf(fptr,"%c",&c)!=EOF)
        if(c=='\n'&&!newlineFlag)
            {
                newlineFlag=true;
                fprintf(inptr,"\n");
                pc++;
            }

        else
            if(c!='\n')
        switch(c)
        {
            case '/':   fscanf(fptr,"%c",&c);
                        if(c=='/')
                            while(c!='\n')
                                fscanf(fptr,"%c",&c);
                            if(!newlineFlag)
                            fprintf(inptr,"\n");
                            break;

            case ' ': break;
            default: fprintf(inptr,"%c",c);
                     newlineFlag=false;
                     break;
        }

        printf("PC: %d",pc);
}


int main()
{
    FILE *fptr,*inptr;
    char fname[20];

    printf("Enter the filename: ",fname);
    scanf("%s",fname);

    fptr=fopen(fname,"r");
    inptr=fopen("main.asm","w");

    if(!fptr&&!inptr)
    return 1;

    else
    scan1(fptr,inptr);
    return 0;
}
