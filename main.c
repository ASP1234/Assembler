#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

LIST *computeList,*symbolList,*jmpList;
int varCounter=16;

typedef struct
{
    char name[60];
    char value[15];

}SYMBOL;

typedef struct
{
    char name[4];
    char value[7];

}COMPUTE;

typedef struct
{
    char name[4];
    char value[3];

}JMP;

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

int compare_symbol(void *arg1,void *arg2)
{
    char *name1=((SYMBOL*)(arg1))->name;
    char *name2=((SYMBOL*)(arg2))->name;

    return strcmp(name1,name2);
}

int compare_jmp(void *arg1,void *arg2)
{
    char *name1=((JMP*)(arg1))->name;
    char *name2=((JMP*)(arg2))->name;

    return strcmp(name1,name2);
}

int compare_compute(void *arg1,void *arg2)
{
    char *name1=((COMPUTE*)(arg1))->name;
    char *name2=((COMPUTE*)(arg2))->name;

    return strcmp(name1,name2);
}

int addComp(COMPUTE* comp,char *name,char *value,LIST *list)
{
    strcpy(comp->name,name);
    strcpy(comp->value,value);

    return addNode(comp,list);
}

int init_compute(LIST* list)
{
    COMPUTE* comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"0","0101010",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"1","0111111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"-1","0111010",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D","0001100",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"A","0110000",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"!D","0001101",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"!A","0110001",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"-D","0001111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"-A","0110011",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D+1","0011111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"A+1","0110111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D-1","0001110",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"A-1","0110010",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D+A","0000010",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D-A","0010011",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"A-D","0000111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D&A","0000000",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D|A","0010101",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"M","1110000",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"!M","1110001",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"-M","1110011",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"M+1","1110111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"M-1","1110010",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D+M","1000010",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D-M","1010011",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"M-D","1000111",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D&M","1000000",list);
    comp=(COMPUTE*)malloc(sizeof(COMPUTE));
    addComp(comp,"D|M","1010101",list);

    return 0;
}

int addJmp(JMP* jmp,char *name,char *value,LIST *list)
{
    strcpy(jmp->name,name);
    strcpy(jmp->value,value);

    return addNode(jmp,list);
}

int init_jmp(LIST* list)
{
    JMP* jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"","000",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JGT","001",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JEQ","010",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JGE","011",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JLT","100",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JNE","101",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JLE","110",list);
    jmp=(JMP*)malloc(sizeof(JMP));
    addJmp(jmp,"JMP","111",list);

    return 0;
}


int addSymbol(SYMBOL* symbol,char *name,char *value,LIST *list)
{
    strcpy(symbol->name,name);
    strcpy(symbol->value,value);

    return addNode(symbol,list);
}

int addLabel(char *name,char *value,LIST *list)
{
    SYMBOL* symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    strcpy(symbol->name,name);
    strcpy(symbol->value,value);

    return addNode(symbol,list);
}

int init_symbol(LIST* list)
{
    char bin[15];

    SYMBOL* symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(0,bin);
    addSymbol(symbol,"R0",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(1,bin);
    addSymbol(symbol,"R1",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(2,bin);
    addSymbol(symbol,"R2",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(3,bin);
    addSymbol(symbol,"R3",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(4,bin);
    addSymbol(symbol,"R4",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(5,bin);
    addSymbol(symbol,"R5",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(6,bin);
    addSymbol(symbol,"R6",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(7,bin);
    addSymbol(symbol,"R7",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(8,bin);
    addSymbol(symbol,"R8",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(9,bin);
    addSymbol(symbol,"R9",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(10,bin);
    addSymbol(symbol,"R10",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(11,bin);
    addSymbol(symbol,"R11",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(12,bin);
    addSymbol(symbol,"R12",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(13,bin);
    addSymbol(symbol,"R13",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(14,bin);
    addSymbol(symbol,"R14",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(15,bin);
    addSymbol(symbol,"R15",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(16384,bin);
    addSymbol(symbol,"SCREEN",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(24576,bin);
    addSymbol(symbol,"KBD",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(0,bin);
    addSymbol(symbol,"SP",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(1,bin);
    addSymbol(symbol,"LCL",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(2,bin);
    addSymbol(symbol,"ARG",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(3,bin);
    addSymbol(symbol,"THIS",bin,list);

    symbol=(SYMBOL*)malloc(sizeof(SYMBOL));
    dec_binary(4,bin);
    addSymbol(symbol,"THAT",bin,list);

    return 0;
}
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

void aInstruction(FILE *fptr,FILE *outPtr)
{
    int i=0,num;
    char bin[15],dec[6],c;

    fscanf(fptr,"%c",&c);

    if(c>='0'&&c<='9')
    {

        while(c!='\n')
            {
                dec[i++]=c;
                fscanf(fptr,"%c",&c);
            }

        dec[i]='\0';
        num=atoi(dec);
        dec_binary(num,bin);
    }

    else
    {
        SYMBOL *dataPtr=(SYMBOL*)malloc(sizeof(SYMBOL)),*dataOutPtr;

         while(c!='\n')
            {
                dataPtr->name[i++]=c;
                fscanf(fptr,"%c",&c);
            }

        dataPtr->name[i]='\0';

        if(searchList((void*)(&dataOutPtr),dataPtr,symbolList))
            strcpy(bin,dataOutPtr->value);

        else
        {
            dec_binary(varCounter++,dataPtr->value);
            addNode(dataPtr,symbolList);
            strcpy(bin,dataPtr->value);
        }
    }

    for(i=0;i<15;i++)
        fprintf(outPtr,"%c",bin[i]);

    fprintf(outPtr,"\n");

}

void cInstruction(FILE *fptr,FILE *outPtr,char c)
{
    char cInst[10],comp[8],dest[4]="000",jmp[3],searchStr[4];
    int i=0,j=0,dest_lim=0,comp_lim=0;

    do
    {
        switch(c)
        {
            case '=':dest_lim=i;break;
            case ';':comp_lim=i;break;
            default: cInst[i++]=c;

        }

        fscanf(fptr,"%c",&c);

    }while(c!='\n');
    cInst[i]='\0';

    for(i=0;i<dest_lim;i++)
       {
        switch(cInst[i])
        {
        case 'A':dest[0]='1';break;
        case 'M':dest[2]='1';break;
        case 'D':dest[1]='1';break;
        }
       }

    if(comp_lim)
        for(i=dest_lim;i<comp_lim;i++)
            searchStr[j++]=cInst[i];
    else
         for(i=dest_lim;cInst[i]!='\0';i++)
            searchStr[j++]=cInst[i];

    searchStr[j]='\0';

    COMPUTE *dataPtr=(COMPUTE*)malloc(sizeof(COMPUTE)),*computeOutPtr;
    strcpy(dataPtr->name,searchStr);

    searchList((void*)&computeOutPtr,dataPtr,computeList);
    strcpy(comp,computeOutPtr->value);
    free(dataPtr);

    fprintf(outPtr,"%s%s",comp,dest);

    if(comp_lim)
    {
        for(i=comp_lim,j=0;cInst[i]!='\0';i++,j++)
            searchStr[j]=cInst[i];
        searchStr[j]='\0';
    }
    else
        searchStr[0]='\0';

    JMP *jmpDataPtr=(JMP*)malloc(sizeof(JMP)),*jmpOutPtr;
    strcpy(jmpDataPtr->name,searchStr);

    searchList((void*)&jmpOutPtr,jmpDataPtr,jmpList);
    strcpy(jmp,jmpOutPtr->value);
    free(jmpDataPtr);

    fprintf(outPtr,"%s\n",jmp);
}

void scan1(FILE *fptr,FILE *outPtr)
{
    int PC=-1,i;
    char c,bin[15],name[70];
    bool newlineFlag=true;

    while(fscanf(fptr,"%c",&c)!=EOF)
        if(c=='\n'&&!newlineFlag)
            {
                newlineFlag=true;
                fprintf(outPtr,"\n");
                PC++;
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
                            {
                                fprintf(outPtr,"\n");
                                PC++;
                            }
                            break;

            case ' ': break;
            case '(': dec_binary(PC+1,bin);

                      fscanf(fptr,"%c",&c);
                      for(i=0;c!=')';i++)
                      {
                          name[i]=c;
                          fscanf(fptr,"%c",&c);
                      }
                      name[i]='\0';

                      while(c!='\n')
                        fscanf(fptr,"%c",&c);

                      addLabel(name,bin,symbolList);
                      break;

            default: fprintf(outPtr,"%c",c);
                     newlineFlag=false;
                     break;
        }

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

        else
        {
            fprintf(outPtr,"111");
            cInstruction(fptr,outPtr,c);
        }
}

int main(int argc,char** argv)
{
    FILE *fptr,*outPtr;
    char fname[20];

    if(argc==2)
        strcpy(fname,argv[1]);
    else
    {
        printf("\nUsage: Assembler filename.asm\n");
        return 3;
    }

    fptr=fopen(fname,"r");
    outPtr=fopen("main.asm","w");

    if(!fptr||!outPtr)
        {
            fclose(fptr);
            fclose(outPtr);
            remove("main.asm");
            printf("\nError in opening file\n");
            return 1;
        }

    else
        {
            computeList=createList(compare_compute);
            jmpList=createList(compare_jmp);
            symbolList=createList(compare_symbol);

            init_compute(computeList);
            init_jmp(jmpList);
            init_symbol(symbolList);

            scan1(fptr,outPtr);
        }

    fclose(fptr);
    fclose(outPtr);

    fptr=fopen("main.asm","r");
    modifyName(fname);
    outPtr=fopen(fname,"w");

    if(!fptr||!outPtr)
       {
           fclose(fptr);
           fclose(outPtr);
           remove("main.asm");
           printf("\nError in creating .hack file. You have insufficient memory\n");
           return 2;
       }


    else
        scan2(fptr,outPtr);

    fclose(fptr);
    fclose(outPtr);
    remove("main.asm");

    return 0;
}
