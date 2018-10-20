#include <stdio.h>
#include <stdlib.h>
#define MAX_DESCRICAO 130
#define MAX_MAIL 100
#define MAX_NOME 200
#define ESCOLHA 3
#include "header.h"
#include <string.h>



int calcula_diferenca_datas(Data um, Data dois){
    int n_um,n_dois;
    n_um = calcula_numero_dias(um.ano,um.mes,um.dia);
    n_dois = calcula_numero_dias(dois.ano,dois.mes,dois.dia);
    return (n_dois-n_um);
}
int calcula_numero_dias(int anos,int meses,int dias)
{
    int a=0,m,i;
    meses--;
    m=0;
    for(i=0;i<anos;i++)
    {
        if (i%4==0)
            a++;
        if (i%100==0 && i%400!=0)
            a--;
    }
    a = a*366+(anos-a-1)*365;
    switch (meses){
            case 12:    m+=31;
            case 11:    m+=30;
            case 10:    m+=31;
            case  9:    m+=30;
            case  8:    m+=31;
            case  7:    m+=31;
            case  6:    m+=30;
            case  5:    m+=31;
            case  4:    m+=30;
            case  3:    m+=31;
            case  2:    if (anos%4 == 0 && anos%100!=0 && anos%400==0)
                            m+=29;
                        else
                            m+=28;
                        /*(anos%4 == 0 ? m+=29 : m+=28);*/
            case  1:    m+=31;
            default:    break;
    }
    return a+m+dias;
}

void protege_datas(int * dia,int * mes,int * ano){
    int deteta;
    deteta = deteta_problema_data(*dia,*mes,*ano);
    if(deteta!=0)
        printf("Valor invalido!\n");
    while(deteta!=0)
    {

        if(deteta==1)
        {
            printf("Por favor insira outra vez o ano:");
            scan_int_prot(ano);
            fflush(stdin);
        }
        if(deteta==2)
        {
            printf("Por favor insira outra vez o mes:");
            scan_int_prot(mes);
            fflush(stdin);
        }
        if(deteta==3)
        {
            printf("Por favor insira outra vez o dia:");
            scan_int_prot(dia);
            fflush(stdin);
        }
        deteta=deteta_problema_data(*dia,*mes,*ano);
    }
}

int deteta_problema_data(int dia,int mes,int ano){
    if (ano<0)
        return 1; /*primeiro tipo de erro:ano negativo */
    if((mes<1 || mes>12))
        return 2; /*segundo tipo de erro:mes fora do limite */
    if(dia>0 && dia<32)
    {
        if(mes==2)
        {
            if ((dia>29 && ano%4 == 0 && ano%100!=0 && ano%400==0) || ((dia>28 && ano%4 != 0) || (dia>28 && (ano%100==0 && ano%400!=0))))
                    return 3; /*terceiro tipo de erro: dia fora do limite */
        }
        if(mes==4)
        {
            if (dia>30)
                return 3;
        }
       if(mes==6)
        {
            if (dia>30)
                return 3;
        }
        if(mes==9)
        {
            if (dia>30)
                return 3;
        }
        if(mes==11)
        {
            if (dia>30)
                return 3;
        }


    }
    if (dia<1 || dia>31)
        return 3;
    return 0; /*sem erros*/
}
