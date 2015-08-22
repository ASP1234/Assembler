#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void modifyName(char *fname)
{
    int i=0;

    while(fname[i]!='.')
        i++;

    fname[++i]='h';
    fname[++i]='a';
    fname[++i]='c';
    fname[++i]='k';
    fname[++i]='\0';
}

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

void aInstruction(FILE *fptr,FILE *outPtr)
{
    int i=0,num;
    char bin[15],dec[6],c;

    do
    {
        fscanf(fptr,"%c",&c);

        if(c=='\n')
            dec[i]='\0';
        else
            dec[i]=c;
        i++;

    }while(c!='\n');

    num=atoi(dec);
    dec_binary(num,bin);

    for(i=0;i<15;i++)
        fprintf(outPtr,"%c",bin[i]);

    fprintf(outPtr,"\n");

}


void scan1(FILE *fptr,FILE *outPtr)
{
    int pc=0;
    char c;
    bool newlineFlag=true;

    while(fscanf(fptr,"%c",&c)!=EOF)
        if(c=='\n'&&!newlineFlag)
            {
                newlineFlag=true;
                fprintf(outPtr,"\n");
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
                            fprintf(outPtr,"\n");
                            break;

            case ' ': break;
            default: fprintf(outPtr,"%c",c);
                     newlineFlag=false;
                     break;
        }

        printf("PC: %d",pc);
}


void scan2(FILE *fptr,FILE *outPtr)
{
    char c;

    while(fscanf(fptr,"%c",&c)!=EOF)
        if(c=='@')
        {
            fprintf(outPtr,"0");
            aInstruction(fptr,outPtr);
        }
}

int main()
{
    FILE *fptr,*outPtr;
    char fname[20];

    printf("Enter the filename: ",fname);
    scanf("%s",fname);

    fptr=fopen(fname,"r");
    outPtr=fopen("main.asm","w");

    if(!fptr&&!outPtr)
        return 1;

    else
        scan1(fptr,outPtr);

    fclose(fptr);
    fclose(outPtr);

    fptr=fopen("main.asm","r");
    modifyName(fname);
    outPtr=fopen(fname,"w");

    if(!fptr&&!outPtr)
        return 2;

    else
        scan2(fptr,outPtr);

    return 0;
}
