#include <stdio.h>
#include <stdlib.h>
#define MAX_DESCRICAO 130
#define MAX_MAIL 100
#define MAX_NOME 200
#include "header.h"
#include <string.h>

void le_quadro(Lfase todo,Lfase doing,Lfase done,Lpessoa lista_de_pessoas)
{
    Lpessoa l = lista_de_pessoas;
    Pes_tar p;
    int conta_todo=0,conta_doing=0,conta_done=0;
    printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |                      |-|\n\t\t|-|   QUADRO DE KANBAM   | |\n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n");

    printf("\n\t\tTO DO\n");
    while (todo)
    {
        printf(" _____________________________________________________________________________________________________________________");
        printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",todo->p_cartao->tarefa.id);
        printf("\n PRIORIDADE -> %d       ",todo->p_cartao->tarefa.prioridade);
        printf("\n DATA CRIACAO(D/M/A)   \n %02d/%02d/%d                 \n",todo->p_cartao->tarefa.criacao.dia,todo->p_cartao->tarefa.criacao.mes,todo->p_cartao->tarefa.criacao.ano);
        if (todo->p_cartao->tarefa.prazo.ano != -1)
            printf("\n DATA DE PRAZO(D/M/A)\n %02d/%02d/%d               \n",todo->p_cartao->tarefa.prazo.dia,todo->p_cartao->tarefa.prazo.mes,todo->p_cartao->tarefa.prazo.ano);
        if (todo->p_cartao->tarefa.conclusao.ano != -1)
            printf("\n DATA CONCLUSAO(D/M/A)\n %02d/%02d/%d               \n",todo->p_cartao->tarefa.conclusao.dia,todo->p_cartao->tarefa.conclusao.mes,todo->p_cartao->tarefa.conclusao.ano);
        if (todo->p_cartao->vai_pessoa)
            printf("\n Pessoa responsavel pela tarefa -> %s\n",todo->p_cartao->vai_pessoa->info.nome);
        printf("\n Descricao: %s",todo->p_cartao->tarefa.descricao);
        printf("\n|_____________________________________________________________________________________________________________________|\n\n");
        todo = todo->next;
        conta_todo++;
    }
    if (conta_todo == 0)
        printf("\n\n\t\t\tNao existem tarefas em TO DO\n\n");
    printf("\t\tDOING\n");
    while(l)
    {
        p = l->tarefas;
        while(p)
        {
            if(p->vai_cartao->fase == 2)
            {
                conta_doing++;
                printf(" _____________________________________________________________________________________________________________________");
                printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",p->vai_cartao->tarefa.id);
                printf("\n PRIORIDADE -> %d       ",p->vai_cartao->tarefa.prioridade);
                printf("\n DATA CRIACAO(D/M/A)   \n %02d/%02d/%d                 \n",p->vai_cartao->tarefa.criacao.dia,p->vai_cartao->tarefa.criacao.mes,p->vai_cartao->tarefa.criacao.ano);
                if (p->vai_cartao->tarefa.prazo.ano != -1)
                    printf("\n DATA DE PRAZO(D/M/A)\n %02d/%02d/%d               \n",p->vai_cartao->tarefa.prazo.dia,p->vai_cartao->tarefa.prazo.mes,p->vai_cartao->tarefa.prazo.ano);
                if (p->vai_cartao->tarefa.conclusao.ano != -1)
                    printf("\n DATA CONCLUSAO(D/M/A)\n %02d/%02d/%d               \n",p->vai_cartao->tarefa.conclusao.dia,p->vai_cartao->tarefa.conclusao.mes,p->vai_cartao->tarefa.conclusao.ano);
                printf("\n Pessoa responsavel pela tarefa -> %s\n",l->info.nome);
                printf("\n Descricao: %s",p->vai_cartao->tarefa.descricao);
                printf("\n|_____________________________________________________________________________________________________________________|\n\n");
            }
            p = p->next;
        }
        l = l->next;
    }
    if (conta_doing == 0)
        printf("\n\n\t\t\tNao existem tarefas em DOING\n\n");
    printf("\t\tDONE\n");
    while (done)
    {
        printf(" _____________________________________________________________________________________________________________________");
        printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",done->p_cartao->tarefa.id);
        printf("\n PRIORIDADE -> %d       ",done->p_cartao->tarefa.prioridade);
        printf("\n DATA CRIACAO(D/M/A)   \n %02d/%02d/%d                 \n",done->p_cartao->tarefa.criacao.dia,done->p_cartao->tarefa.criacao.mes,done->p_cartao->tarefa.criacao.ano);
        if (done->p_cartao->tarefa.prazo.ano != -1)
            printf("\n DATA DE PRAZO(D/M/A)\n %02d/%02d/%d               \n",done->p_cartao->tarefa.prazo.dia,done->p_cartao->tarefa.prazo.mes,done->p_cartao->tarefa.prazo.ano);
        if (done->p_cartao->tarefa.conclusao.ano != -1)
            printf("\n DATA CONCLUSAO(D/M/A)\n %02d/%02d/%d               \n",done->p_cartao->tarefa.conclusao.dia,done->p_cartao->tarefa.conclusao.mes,done->p_cartao->tarefa.conclusao.ano);
        if (done->p_cartao->vai_pessoa)
            printf("\n Pessoa responsavel pela tarefa -> %s\n",done->p_cartao->vai_pessoa->info.nome);
        printf("\n Descricao: %s",done->p_cartao->tarefa.descricao);
        printf("\n|_____________________________________________________________________________________________________________________|\n\n");
        done = done->next;
        conta_done++;
    }
    if (conta_done == 0)
        printf("\n\n\t\t\tNao existem tarefas em DONE\n\n");
    printf("\n\n");
    system("Pause");
}

void visualiza_todas_tarefas(Lcartao l)
{
    int conta =0;
    printf("\t\t VISUALIZACAO DE TODAS AS TAREFAS\n");
    while (l)
    {
        /*Coisitas estéticas*/
        printf(" _____________________________________________________________________________________________________________________");
        printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",l->tarefa.id);
        printf("\n PRIORIDADE -> %d       ",l->tarefa.prioridade);
        printf("\n DATA CRIACAO(D/M/A)   \n %02d/%02d/%d                 \n",l->tarefa.criacao.dia,l->tarefa.criacao.mes,l->tarefa.criacao.ano);
        if (l->tarefa.prazo.ano != -1)
            printf("\n DATA DE PRAZO(D/M/A)\n %02d/%02d/%d               \n",l->tarefa.prazo.dia,l->tarefa.prazo.mes,l->tarefa.prazo.ano);
        if (l->tarefa.conclusao.ano != -1)
            printf("\n DATA CONCLUSAO(D/M/A)\n %02d/%02d/%d               \n",l->tarefa.conclusao.dia,l->tarefa.conclusao.mes,l->tarefa.conclusao.ano);
        if (l->vai_pessoa)
            printf("\n Pessoa responsavel pela tarefa -> %s\n",l->vai_pessoa->info.nome);
        printf("\n Descricao: %s",l->tarefa.descricao);
        printf("\n|_____________________________________________________________________________________________________________________|\n\n");
        l = l->next;
        conta++;
    }
    if (conta == 0)
    /*pequena alteraçao--Paulo*/
        printf("\n\n\t\t\tNao existem tarefas");
}

Lcartao procura_tarefa(Lcartao l,int n)
{
    Lcartao fim = NULL;
    while (l)
    {
        if (l->tarefa.id==n)
        {
            fim = l;
            break;
        }
        l=l->next;
    }
    return fim;
}


int conta_tarefas_uma_pessoa(Pes_tar l)
{
    int conta=0;
    Pes_tar move = l;
    while (move)
    {
        conta++;
        move = move->next;
    }
    return conta;
}
void visualiza_tarefa_de_certa_pessoa(Lpessoa lista_de_pessoas,Lfase todo,Lfase doing,Lfase done)
{
    int conta,i;
    Lpessoa check;
    char nome_pessoa[MAX_NOME];
    Lfase corre;
    listar_pessoas(lista_de_pessoas);
    do{
        printf("\tIndique o nome da pessoa:\t\n>>> ");
        gets(nome_pessoa);
        fflush(stdin);
        check = procura_nome_pessoa(nome_pessoa,lista_de_pessoas);
    }while(!check);
    system("@cls||clear");
    printf("\t\t(@)\n\t\t|-|______________________(@)\n\t\t| |      TAREFAS DE      |-|\n\t\t|-| %s                      \n\t\t|_|______________________|-|\n\t\t(@)                      |_|\n\t\t                         (@)\n\n",nome_pessoa);
    for (i=1;i<4;i++)
    {
        conta = 0;
        switch (i){
            case 1:
                    printf("\n\t\tTO DO\n");
                    corre = todo;
                    break;
            case 2:
                    printf("\n\t\tDOING\n");
                    corre = doing;
                    break;
            default:
                    printf("\n\t\tDONE\n");
                    corre = done;
                    break;

        }
        while (corre)
        {
            if(corre->p_cartao->vai_pessoa == check)
            {
                /*Coisitas estéticas*/
                printf(" _____________________________________________________________________________________________________________________");
                printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",corre->p_cartao->tarefa.id);
                printf("\n PRIORIDADE -> %d       ",corre->p_cartao->tarefa.prioridade);
                printf("\n DATA CRIACAO(D/M/A)   \n %d/%d/%d                 \n",corre->p_cartao->tarefa.criacao.dia,corre->p_cartao->tarefa.criacao.mes,corre->p_cartao->tarefa.criacao.ano);
                if (corre->p_cartao->tarefa.prazo.ano != -1)
                    printf("\n DATA DE PRAZO(D/M/A)\n %d/%d/%d               \n",corre->p_cartao->tarefa.prazo.dia,corre->p_cartao->tarefa.prazo.mes,corre->p_cartao->tarefa.prazo.ano);
                if (corre->p_cartao->tarefa.conclusao.ano != -1){
                    printf("\n DATA CONCLUSAO(D/M/A)\n %d/%d/%d               \n",corre->p_cartao->tarefa.conclusao.dia,corre->p_cartao->tarefa.conclusao.mes,corre->p_cartao->tarefa.conclusao.ano);
                }
                if (corre->p_cartao->vai_pessoa->info.nome)
                    printf("\n Pessoa responsavel pela tarefa -> %s\n",corre->p_cartao->vai_pessoa->info.nome);
                printf("\n Descricao: %s",corre->p_cartao->tarefa.descricao);
                printf("\n|_____________________________________________________________________________________________________________________|\n\n");
                conta++;
                }

            corre = corre->next;
            }

    if (conta == 0)
        printf("\n\t\t\tNao existem tarefas\n\n");
    }
    system("Pause");
    system("@cls||clear");

}

Lcartao cria_Lcartaoa (Lcartao l)
{
    Lcartao novo = NULL;
    int i;
    printf("\n\t  CRIACAO DE CARTAO\n\n\nVoltar-->0\nProsseguir-->Qualquer outro valor\n>>>");
    scan_int_prot(&i);
    if(i==0)
    {
        return novo;
    }
    novo = (Lcartao)malloc(sizeof(Card));
    printf("\n\tIdentificador (Unico)\n>>> ");
    do{
        fflush(stdin);
        scan_int_prot(&novo->tarefa.id);
        if(novo->tarefa.id<1 || novo->tarefa.id > 9999999)
            printf("Valor nao aceite\n>>> ");
        if(procura_tarefa(l,novo->tarefa.id))
            printf("Ja existe uma tarefa com esse id\n>>> ");
        fflush(stdin);
    }while (novo->tarefa.id<1 || novo->tarefa.id > 9999999 || procura_tarefa(l,novo->tarefa.id));
    printf("\tPrioridade: (Escala de 1 a 10)\n>>> ");
    do{
        scan_int_prot(&novo->tarefa.prioridade);
        fflush(stdin);
        if (novo->tarefa.prioridade>10 || novo->tarefa.prioridade<1)
        {
            printf("Valor nao aceite\n>>> ");
        }
        fflush(stdin);
    }while(novo->tarefa.prioridade>10 || novo->tarefa.prioridade<1);
    printf("\tData de criacao:\nAno:\n>>> ");
    scan_int_prot(&novo->tarefa.criacao.ano);
    fflush(stdin);
        printf("\tData de criacao:\nMes:\n>>> ");
    scan_int_prot(&novo->tarefa.criacao.mes);
    fflush(stdin);
    printf("\tData de criacao:\nDia:\n>>> ");
    scan_int_prot(&novo->tarefa.criacao.dia);
    fflush(stdin);
    protege_datas(&novo->tarefa.criacao.dia, &novo->tarefa.criacao.mes, &novo->tarefa.criacao.ano); /*Ve e altera se achares que e preciso, mas parece estar a funcionar*/
    do{
        printf("\tData de Prazo:\nAno:\n>>> ");
        scan_int_prot(&novo->tarefa.prazo.ano);
        fflush(stdin);
        printf("\tData de Prazo:\nMes:\n>>> ");
        scan_int_prot(&novo->tarefa.prazo.mes);
        fflush(stdin);
        printf("\tData de Prazo:\nDia:\n>>> ");
        scan_int_prot(&novo->tarefa.prazo.dia);
        fflush(stdin);
        protege_datas(&novo->tarefa.prazo.dia, &novo->tarefa.prazo.mes, &novo->tarefa.prazo.ano);
        if(calcula_diferenca_datas(novo->tarefa.prazo,novo->tarefa.criacao)>0)
            printf("A data de prazo tem de ser posterior a data de criacao\n");
    }while(calcula_diferenca_datas(novo->tarefa.prazo,novo->tarefa.criacao)>0);
    printf("\tDescricao:\n>>> ");
    fflush(stdin);
    gets(novo->tarefa.descricao);
    novo->next=NULL;
    novo->vai_pessoa=NULL;
    novo->tarefa.conclusao.ano = -1;
    novo->fase=1;
    novo->tarefa.dono = -1;
    novo->vai_pessoa = NULL;
    printf("\n\n");
    system("Pause");
    return novo;
}

Lcartao insere_Lcartaoa (Lcartao l,Lcartao novo)
{
    Data default_;
    Lcartao act = l,ant=NULL;
    default_.ano=0;
    default_.mes=0;
    default_.dia=0;
    while (act && calcula_diferenca_datas(default_,act->tarefa.criacao) < calcula_diferenca_datas(default_,novo->tarefa.criacao))
    {
        ant = act;
        act = act->next;
    }
    novo->next = act;
    if (ant==NULL)
        l = novo;
    else
        ant->next=novo;
    return l;
}



Lcartao destroi_tarefas(Lcartao l){
    Lcartao aux;
    aux=l;
    if(aux==NULL)
    {
        l=NULL;
        return l;
    }
    l=l->next;
    if(aux && l==NULL)
    {
        free(aux);
        return l;
    }
    while(l)
    {
        free(aux);
        aux=l;
        l=l->next;
    }
    free(l);
    return l;
}


Lcartao faz_lista_cart(Lcartao l,int ide,int pri,Data cria,Data pra,Data conc,int fas,int dono,char des[]){
    Lcartao novo;
    novo=(Lcartao)malloc(sizeof(Card));
    novo->tarefa.id=ide;
    novo->tarefa.prioridade=pri;
    novo->tarefa.criacao.dia=cria.dia;
    novo->tarefa.criacao.mes=cria.mes;
    novo->tarefa.criacao.ano=cria.ano;
    novo->tarefa.prazo.dia=pra.dia;
    novo->tarefa.prazo.mes=pra.mes;
    novo->tarefa.prazo.ano=pra.ano;
    novo->tarefa.conclusao.dia=conc.dia;
    novo->tarefa.conclusao.mes=conc.mes;
    novo->tarefa.conclusao.ano=conc.ano;
    novo->fase = fas;
    novo->tarefa.dono = dono;
    strcpy(novo->tarefa.descricao,des);
    l=insere_Lcartaoa(l,novo);
    return l;
}
Lpessoa faz_lista_pessoas(Lpessoa l,int ide,char nom[],char em[]){
    Lpessoa nova;
    nova=(Lpessoa)malloc(sizeof(Pessoa));
    strcpy(nova->info.nome,nom);
    strcpy(nova->info.email,em);
    nova->info.id=ide;
    nova->next=NULL;
    nova->tarefas=NULL;
    l=insere_Lpessoa(l,nova);
    return l;
}

Lpessoa insere_Lpessoa(Lpessoa l,Lpessoa nova){
    Lpessoa act = l,ant=NULL;
    while (act && strcmp(act->info.nome,nova->info.nome)<0)
    {
        ant = act;
        act = act->next;
    }
    nova->next = act;
    if (ant==NULL)
        l = nova;
    else
        ant->next=nova;
    return l;
}

void listar_pessoas(Lpessoa l){
    int conta=0;
    printf("\t\t VISUALIZACAO DE TODAS AS PESSOAS\n");
    while (l)
    {
        /*Coisitas estéticas*/
        printf(" _____________________________________________________________________________________________________________________");
        printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",l->info.id);
        printf("\n Nome:%s",l->info.nome);
        printf("\n email: %s",l->info.email);
        printf("\n|_____________________________________________________________________________________________________________________|\n\n");
        l = l->next;
        conta++;
    }
    if (conta==0){
        printf("Nao existem pessoas...\n");
    }
    printf("\n\n");
}
Lpessoa procura_id_pessoa(Lpessoa lista_de_pessoas,int id)
{
    Lpessoa check = NULL;
    Lpessoa move = lista_de_pessoas;
    while (move)
    {
        if (move->info.id == id)
        {
            check = move;
            return check;
        }
        move=move->next;
    }
    return check;
}

Lpessoa procura_nome_pessoa(char nome_pessoa[MAX_NOME],Lpessoa lista_de_pessoas)
{
    Lpessoa check = NULL;
    Lpessoa move = lista_de_pessoas;
    while (move)
    {
        if (!strcmp(move->info.nome,nome_pessoa))
        {
            check = move;
            break;
        }
        move=move->next;
    }
    return check;
}


Lpessoa altera_pessoa(Lpessoa lista_de_pessoas,Lcartao l,int numero_de_tarefas_por_pessoa)
{
    int id;
    Lpessoa nova_pessoa,pessoa_antiga;
    Lcartao encontra;
    char nome_pessoa[MAX_NOME];
    Pes_tar encontra_na_pessoa;
    visualiza_todas_tarefas(l);
    printf("Indique o ID da tarefa para o qual quer mudar a pessoa responsavel:\nVoltar -> 0\n>>> ");
    scan_int_prot(&id);
    if(id == 0)
        return lista_de_pessoas;
    do{
        encontra = procura_tarefa(l,id);
        if(!encontra || !(encontra->vai_pessoa))
        {
            printf("A tarefa de indicou ou nao existe ou nao tem ninguem responsavel por ela, tente outra vez\nPara voltar -> 0\n>>> ");
            scan_int_prot(&id);
        }
        if (id == 0)
            return lista_de_pessoas;

    }while(!encontra || !encontra->vai_pessoa);
    listar_pessoas(lista_de_pessoas);
    do{
        printf("\tIndique o nome da pessoa que quer tornar resposavel por esta tarefa:\t\nVoltar -> 0\n>>> ");
        gets(nome_pessoa);
        nova_pessoa = procura_nome_pessoa(nome_pessoa,lista_de_pessoas);
        if (!strcmp(nome_pessoa,"0"))
            return lista_de_pessoas;
        if (nova_pessoa)
        {
            if ((nova_pessoa == encontra->vai_pessoa))
                return lista_de_pessoas;
            if (conta_tarefas_uma_pessoa(nova_pessoa->tarefas) >= numero_de_tarefas_por_pessoa)
                printf("\n\t\tEsta pessoa tem o maximo de tarefas possiveis\n");
            if (verifica_se_pessoa_tem_tarefas_nessa_semana(nova_pessoa,encontra))
                printf("\n\t\tEsta pessoa ja tem um prazo no espaco dessa semana\n");
        }
    }while(!nova_pessoa || conta_tarefas_uma_pessoa(nova_pessoa->tarefas) >= numero_de_tarefas_por_pessoa || verifica_se_pessoa_tem_tarefas_nessa_semana(nova_pessoa,encontra));
    /*Alteracao proprimente dita*/
    pessoa_antiga = encontra->vai_pessoa;
    encontra_na_pessoa = procura_tarefa_na_pessoa(&pessoa_antiga,id);
    encontra_na_pessoa->next = NULL;
    nova_pessoa->tarefas= insere_Pes_tar(nova_pessoa->tarefas,encontra_na_pessoa);
    encontra->vai_pessoa = nova_pessoa;
    encontra->tarefa.dono=nova_pessoa->info.id;
    return lista_de_pessoas;
}
Pes_tar faz_lista_tarefas_pessoas(Pes_tar l){
    Pes_tar nova;
    nova=(Pes_tar)malloc(sizeof(Pes_tar));
    nova->next=NULL;
    nova->vai_cartao=NULL;
    l=insere_Pes_tar(l,nova);
    return l;
}
Pes_tar insere_Pes_tar(Pes_tar l,Pes_tar nova){
    if (l)
        nova->next = l;
    l = nova;
    return l;
}
Pes_tar procura_tarefa_na_pessoa(Lpessoa *check,int id)
{
    Pes_tar fim = NULL,move = (*check)->tarefas,ant=NULL;
    while (move)
    {
        if (move->vai_cartao->tarefa.id==id)
        {
            fim = move;
            if (ant)
                ant->next = move->next;
            else
                (*check)->tarefas = move->next;
            break;
        }
        ant = move;
        move=move->next;
    }

    return fim;
}
int conta_max_tarefas_pessoas(Lpessoa l)
{
    int max=0,conta;
    Lpessoa move = l;
    Pes_tar aux;
    while (move)
    {
        conta = 0;
        aux = move->tarefas;
        while(aux)
        {
            conta++;
            aux = aux->next;
        }
        move = move->next;
        if (conta>max)
            max = conta;
    }
    return max;
}

int verifica_se_pessoa_tem_tarefas_nessa_semana(Lpessoa l,Lcartao taref)
{
    int veredito = 0;
    Lpessoa move = l;
    Pes_tar aux;
    aux = move->tarefas;
    while(aux)
    {
        if (abs(calcula_diferenca_datas(aux->vai_cartao->tarefa.prazo,taref->tarefa.prazo))<=7)
        {
            veredito += 1;

        }
        aux = aux->next;
    }
    return veredito;
}

int conta_total_tarefas_pessoas(Lpessoa l){
    int conta=0;
    Lpessoa move = l;
    Pes_tar aux;
    while (move)
    {
        aux = move->tarefas;
        while(aux)
        {
            conta++;
            aux = aux->next;
        }
        move = move->next;
    }
    return conta;
}
Lpessoa destroi_pessoas(Lpessoa l){
    Lpessoa aux;
    aux=l;
    if(aux==NULL)
    {
        return l;
    }
    l=l->next;
    if(aux && l==NULL)
    {
        aux->tarefas = destroi_tarefas_de_pessoas(aux->tarefas);
        free(aux);
        return l;
    }
    while(l)
    {
        aux->tarefas = destroi_tarefas_de_pessoas(aux->tarefas);
        free(aux);
        aux=l;
        l=l->next;
    }
    free(l);

return l;
}
Pes_tar destroi_tarefas_de_pessoas(Pes_tar l){
    Pes_tar aux;
    aux=l;
    if(aux==NULL)
    {
        return l;
    }
    l=l->next;
    if(aux && l==NULL)
    {
        free(aux);
        return l;
    }
    while(l)
    {
        free(aux);
        aux=l;
        l=l->next;
    }
    free(l);
return l;
}
