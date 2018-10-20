#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_DESCRICAO 130
#define MAX_MAIL 100
#define MAX_NOME 200
#include "header.h"
#include <locale.h>



/*CODE*/
int main()
{
    fflush(stdin);
    menu();
    return 0;
}
void estabelece_limites(int *numero_de_tarefas_em_doing,int *numero_de_tarefas_por_pessoa,Lfase doing,Lpessoa lista_de_pessoas)
{
    char c='a',check='0';
    printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|      ATUALIZACAO     | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
    printf("\tALTERACACAO DE NUMERO MAXIMO DE TAREFAS POR PESSOA --> a\n\tALTERACACAO DE NUMERO MAXIMO DE TAREFAS EM DOING ----> b\n\nSair -> 0\n");
    do{

        printf(">>> ");
            fflush(stdin);
            scanf("%c%c",&c,&check);
        }while(((check!='\n') || (c<'a' || c>'b')) && ((check!='\n') || c != '0'));
    if(c == 'a')
    {
        do{
        printf("NOVO LIMITE MAXIMO PARA NUMERO MAXIMO DE TAREFAS POR PESSOA \n>>> ");
        scan_int_prot(numero_de_tarefas_por_pessoa);
        }while(*numero_de_tarefas_por_pessoa<conta_max_tarefas_pessoas(lista_de_pessoas) || *numero_de_tarefas_por_pessoa < 1 || *numero_de_tarefas_por_pessoa > 1000);
    }
    if(c == 'b')
    {
        do{
            printf("NOVO LIMITE MAXIMO PARA NUMERO MAXIMO DE TAREFAS EM DOING \n>>> ");
            scan_int_prot(numero_de_tarefas_em_doing);
        }while(*numero_de_tarefas_em_doing<conta_elementos_fase(doing) || *numero_de_tarefas_em_doing < 1 || *numero_de_tarefas_em_doing > 1000);
    }
    system("@cls||clear");
}
void menu()
{
    Lcartao lista_de_cartoes=NULL,novo_cartao;
    Lfase todo=NULL,doing=NULL,done=NULL;
    Lpessoa lista_de_pessoas=NULL;
    int numero_de_tarefas_por_pessoa,numero_de_tarefas_em_doing,conf,comp,comp_b;
    float tarefas_terminadas=0.0,tarefas_dentro_prazo=0.0;
    char c='a',check='0';
    lista_de_pessoas=le_pessoas_fich(lista_de_pessoas);
    if (!lista_de_pessoas)
    {
        printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|       ERROR 404      | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
        printf("\tSem pessoas para atribuir tarefas. Por favor adicione primeiro pessoas no ficheiro, e depois utilize o prgrama.\n\n");
        return;
    }
    comp=protege_nomes_fich(lista_de_pessoas);
    if(comp==1){
        printf("\tHa individuos com nomes iguais.Por favor corrija no ficheiro PESSOAS.txt.\nCuidado! Se tiver um 'Enter' a mais no fim do ficheiro tambem estara a corromper os dados!\n");
        return;
    }
    comp_b=protege_nums_fich(lista_de_pessoas);
    if(comp_b==1){
        printf("\tHa individuos com id's iguais.Por favor corrija no ficheiro PESSOAS.txt.\nCuidado! Se tiver um 'Enter' a mais no fim do ficheiro tambem estara a corromper os dados!\n");
        return;
    }
   do{
        printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|       BEM VINDO      | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
        printf("\tDeseja carregar os dados da sessao anterior? (1=SIM;0=NAO)\n>>> ");
        scan_int_prot(&conf);
        if (conf == 1){
            system("@cls||clear");
            le_dados(&lista_de_cartoes,&lista_de_pessoas,&todo,&done,&doing,&numero_de_tarefas_em_doing,&numero_de_tarefas_por_pessoa,&tarefas_terminadas,&tarefas_dentro_prazo);
            if(lista_de_cartoes==NULL){
                printf("\t\tSem dados para carregar...\n");
            }
            else
                printf("\t\tDados Carregados com sucesso!\n");
        }
        else
        {
            numero_de_tarefas_em_doing = 5;
            numero_de_tarefas_por_pessoa = 5;
            system("@cls||clear");
        }


    }while(conf!=0 && conf!=1);
    while(c!='0')
    {
        printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-| WELCOME TO THE MENU! | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
        /*Pessoas*/
        printf("\tListar Pessoas ---------------------------------> a\n\tDefinir maximo de tarefas (pessoa e DOING)  ----> b\n");
        /*Fases*/
        printf("\tInserir nova tarefa em TODO (Criar tarefa) -----> c\n\tPassar tarefa para DOING -----------------------> d\n\tAlterar pessoa responsavel por tafera ----------> e\tMAX TAREFA/PESSOA -> %d\n\tFechar cartao (Passar para DONE) ---------------> f\n\tPassar tarefas para TO DO ----------------------> g\tMAX TAREFA/DOING  -> %d\n",numero_de_tarefas_por_pessoa,numero_de_tarefas_em_doing);
        /*Visualizar*/
        printf("\tVisualizar quadro ------------------------------> h\n\tVisualizar tarefas em TODO ---------------------> i\tNUMERO DE TAREFAS EM TO DO -> %d\n\tVisualizar tarefas em DOING --------------------> j\tNUMERO DE TAREFAS EM DOING -> %d\n\tVisualizar tarefas em DONE ---------------------> k\tNUMERO DE TAREFAS EM DONE  -> %d\n\tVisualizar tarefas de certa pessoa -------------> m\n\tVisualizar todas as tarefas --------------------> n\n",conta_elementos_fase(todo),conta_elementos_fase(doing),conta_elementos_fase(done));
        /*Salvar*/
        printf("\tSalvar -----------------------------------------> o\n");
        if (tarefas_terminadas!=0)
            printf("\n\tPercentagem de tarefas terminadas dentro do prazo : %.2f%\n",(tarefas_dentro_prazo/tarefas_terminadas)*100);
        else
            printf("\n\tPercentagem de tarefas terminadas dentro do prazo : 0%\n");
        printf("\nSair -> 0\n");

        do{

        printf(">>> ");
            fflush(stdin);
            scanf("%c%c",&c,&check);
        }while(((check!='\n') || (c == 'l' || c<'a' || c>'o')) && ((check!='\n') || c != '0'));
        if(c=='a')
        {
            system("@cls||clear");
            listar_pessoas(lista_de_pessoas);
            printf("\n\n");
            system("Pause");
            system("@cls||clear");
        }
        if(c=='b')
        {
            system("@cls||clear");
            estabelece_limites(&numero_de_tarefas_em_doing,&numero_de_tarefas_por_pessoa,doing,lista_de_pessoas);
            printf("\n\t\t\tAtualizacao feita com sucesso!\n\n");
        }
        if(c=='c')
        {
            system("@cls||clear");
            novo_cartao = cria_Lcartaoa(lista_de_cartoes);
            system("@cls||clear");
            if (novo_cartao)
            {
                novo_cartao->vai_pessoa = NULL;
                lista_de_cartoes = insere_Lcartaoa(lista_de_cartoes,novo_cartao);
                todo = passar_para_todo_logo(novo_cartao,todo);
                printf("\n\t\tTarefa criada e inserida em To Do com sucesso!\n\n");
            }

        }

        if(c=='d')
        {
            system("@cls||clear");
            doing=passar_para_doing(lista_de_cartoes,&todo,doing,&done,numero_de_tarefas_em_doing,lista_de_pessoas,numero_de_tarefas_por_pessoa);
            system("@cls||clear");

        }
        if(c=='e')
        {
            system("@cls||clear");
            lista_de_pessoas = altera_pessoa(lista_de_pessoas,lista_de_cartoes,numero_de_tarefas_por_pessoa);
             system("@cls||clear");
        }
        if(c=='f')
        {
            system("@cls||clear");
            done=passar_para_done(lista_de_cartoes,&todo,&doing,done,lista_de_pessoas,&tarefas_terminadas,&tarefas_dentro_prazo);
            system("@cls||clear");
        }
        if(c=='g')
        {
            system("@cls||clear");
            todo = passar_para_todo(lista_de_cartoes,todo,&doing,&done,lista_de_pessoas);
            system("@cls||clear");
        }

        if(c=='h')
        {
            system("@cls||clear");
            le_quadro(todo,doing,done,lista_de_pessoas);
            system("@cls||clear");


        }
        if(c=='i')
        {
            system("@cls||clear");
            printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|        TO DO         | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
            visualiza_fase(todo);
            printf("\n\n");
            system("Pause");
            system("@cls||clear");

        }
        if(c=='j')
        {
            system("@cls||clear");
            printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|        DOING         | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
            visualiza_doing(doing,lista_de_pessoas);
            printf("\n\n");
            system("Pause");
            system("@cls||clear");
        }
        if(c=='k')
        {
            system("@cls||clear");
            printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|         DONE         | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");
            visualiza_fase(done);
            printf("\n\n");
            system("Pause");
            system("@cls||clear");
        }
        if(c=='m')
        {
            system("@cls||clear");
            visualiza_tarefa_de_certa_pessoa(lista_de_pessoas,todo,doing,done);
            system("@cls||clear");
        }
        if(c=='n')
        {
            system("@cls||clear");
            visualiza_todas_tarefas(lista_de_cartoes);
            printf("\n\n");
            system("Pause");
            system("@cls||clear");
        }
        if(c=='o')
        {
            salvar(lista_de_cartoes,&numero_de_tarefas_em_doing,&numero_de_tarefas_por_pessoa,lista_de_pessoas,todo,doing,done,tarefas_terminadas,tarefas_dentro_prazo);
        }
    }
   /* Guarda tarefas e fases*/
    salvar(lista_de_cartoes,&numero_de_tarefas_em_doing,&numero_de_tarefas_por_pessoa,lista_de_pessoas,todo,doing,done,tarefas_terminadas,tarefas_dentro_prazo);
    if (lista_de_pessoas)
        lista_de_pessoas = destroi_pessoas(lista_de_pessoas);
    if (todo)
        todo = destroi_fase(todo);
    if (doing)
        doing = destroi_fase(doing);
    if (done)
        done = destroi_fase(done);
    if (lista_de_cartoes)
        lista_de_cartoes = destroi_tarefas(lista_de_cartoes);
}

void salvar(Lcartao lista_de_cartoes,int *numero_de_tarefas_em_doing,int *numero_de_tarefas_por_pessoa,Lpessoa lista_de_pessoas,Lfase todo,Lfase doing,Lfase done,int tarefas_terminadas,int tarefas_dentro_prazo)
{
    escreve_tarefas_fich(lista_de_cartoes,numero_de_tarefas_em_doing,numero_de_tarefas_por_pessoa);
    escreve_tarefas_de_pessoas(lista_de_pessoas);
    escreve_todo_fich(todo);
    escreve_doing_fich(doing);
    escreve_done_fich(done,tarefas_terminadas,tarefas_dentro_prazo);
    system("@cls||clear");
    printf("\n\tBase de dados atualizada com sucesso, pode verificar no ficheiro TAREFAS.txt\n\n");
}

void scan_int_prot(int * num){
    char o;
    do
        {
            fflush(stdin);
            scanf("%d%c",num,&o);
            if( o!='\n')
                printf("Valor nao aceite\n>>> ");
        }while ( o!='\n');
}
