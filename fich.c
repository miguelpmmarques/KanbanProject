#include <stdio.h>
#include <stdlib.h>
#define MAX_DESCRICAO 130
#define MAX_MAIL 100
#define MAX_NOME 200
#define MAX_ERRO 5000
#include "header.h"
#include <string.h>


/*Lpessoa le_pessoas*/
void escreve_tarefas_de_pessoas(Lpessoa l)
{
    Lpessoa lista_pessoas = l;
    Pes_tar aux;
    FILE * fp;
    fp= fopen("TAREFA_PESSOAS.txt","w");
    fprintf(fp,"%d\n",conta_total_tarefas_pessoas(lista_pessoas));
    while (lista_pessoas)
    {
        aux = lista_pessoas->tarefas;
        while (aux)
        {
            fprintf(fp,"%d %d\n",lista_pessoas->info.id,aux->vai_cartao->tarefa.id);
            aux = aux->next;
        }
        lista_pessoas = lista_pessoas->next;
    }
    fclose(fp);

}
void escreve_tarefas_fich(Lcartao l,int *numero_de_tarefas_em_doing, int *numero_de_tarefas_por_pessoa)
{
    FILE * fp;
    fp= fopen("TAREFAS.txt","w");
    fprintf(fp,"%d\n",*numero_de_tarefas_por_pessoa);
    fprintf(fp,"%d\n",*numero_de_tarefas_em_doing);
    fprintf(fp,"%d\n",conta_tarefas(l));
    while (l)
    {
        /*Coisitas estéticas*/
        fprintf(fp,"%d\n",l->tarefa.id);
        fprintf(fp,"%d\n",l->tarefa.prioridade);
        fprintf(fp,"%d/%d/%d \n",l->tarefa.criacao.dia,l->tarefa.criacao.mes,l->tarefa.criacao.ano);
        fprintf(fp,"%d/%d/%d \n",l->tarefa.prazo.dia,l->tarefa.prazo.mes,l->tarefa.prazo.ano);
        fprintf(fp,"%d/%d/%d \n",l->tarefa.conclusao.dia,l->tarefa.conclusao.mes,l->tarefa.conclusao.ano);
        fprintf(fp,"%d\n",l->fase);
        fprintf(fp,"%d\n",l->tarefa.dono);
        fprintf(fp,"%s\n",l->tarefa.descricao);
        l = l->next;
    }
    fclose(fp);

}

void escreve_todo_fich(Lfase l)
{
    int conta,total;
    FILE * fp;
    fp = fopen("TODO.txt","w");
    total=conta_elementos_fase(l);
    fprintf(fp,"%d\n",total);
    conta=0;
    while (l)
    {
        fprintf(fp,"%d",l->p_cartao->tarefa.id);
        conta++;
        if(conta!=total)
            fprintf(fp,"\n");
        l = l->next;
    }
    fclose(fp);
}


void escreve_doing_fich(Lfase l)
{
    int conta,total;
    FILE * fp;
    fp = fopen("DOING.txt","w");
    total=conta_elementos_fase(l);
    conta=0;
    fprintf(fp,"%d\n",total);
    while (l)
    {
        fprintf(fp,"%d",l->p_cartao->tarefa.id);
        conta++;
        if(conta!=total)
            fprintf(fp,"\n");
        l = l->next;
    }
    fclose(fp);
}

void escreve_done_fich(Lfase l,float tarefas_terminadas,float tarefas_dentro_prazo)
{
    int conta,total;
    FILE * fp;
    fp = fopen("DONE.txt","w");
    total=conta_elementos_fase(l);
    conta=0;
    fprintf(fp,"%f\n",tarefas_terminadas);
    fprintf(fp,"%f\n",tarefas_dentro_prazo);
    fprintf(fp,"%d\n",total);
    while (l)
    {
        fprintf(fp,"%d",l->p_cartao->tarefa.id);
        conta++;
        if(conta!=total)
            fprintf(fp,"\n");
        l = l->next;
    }
    fclose(fp);
}



Lpessoa le_tarefas_de_pessoas(Lpessoa lista_pessoas,Lcartao cartoes,int * numero_de_tarefas_por_pessoa,int erro[],int * j)
{
    int n,i,id_pessoa,id_tarefa;
    Lpessoa l = lista_pessoas;
    Lcartao tarefa;
    FILE * fp;
    fp= fopen("TAREFA_PESSOAS.txt","r");
    (*j)=0;
    erro[0]=0;
    fscanf(fp,"%d",&n);
    for (i=0;i<n;i++)
    {
        fscanf(fp,"%d %d",&id_pessoa,&id_tarefa);
        lista_pessoas = procura_id_pessoa(l,id_pessoa);
        tarefa = procura_tarefa(cartoes,id_tarefa);
        tarefa->vai_pessoa = lista_pessoas;
        if (lista_pessoas){
        lista_pessoas->tarefas = faz_lista_tarefas_pessoas(lista_pessoas->tarefas);
        lista_pessoas->tarefas->vai_cartao = tarefa;
        }
        if(lista_pessoas==NULL){

            erro[(*j)]=id_tarefa;
            (*j)++;
        }
    }
    fclose(fp);
    return l;
}

Lcartao le_tarefas_fich(Lcartao l, int *numero_de_tarefas_em_doing, int *numero_de_tarefas_por_pessoa){
    FILE * fp;
    int i,num,ide,pri,dono,fas;
    Data cria,pra,conc;
    char des[MAX_DESCRICAO];
    fp = fopen("TAREFAS.txt","r");
    fscanf(fp,"%d",numero_de_tarefas_por_pessoa);
    fscanf(fp,"%d",numero_de_tarefas_em_doing);
    fscanf(fp,"%d",&num);
        if(num==0){
            fclose(fp);
            return NULL;
        }
    for(i=0;i<num;i++)
    {
        fscanf(fp,"%d",&ide);
        fscanf(fp,"%d",&pri);
        fscanf(fp,"%d/%d/%d",&cria.dia,&cria.mes,&cria.ano);
        fscanf(fp,"%d/%d/%d",&pra.dia,&pra.mes,&pra.ano);
        fscanf(fp,"%d/%d/%d",&conc.dia,&conc.mes,&conc.ano);
        fscanf(fp,"%d",&fas);
        fscanf(fp,"%d",&dono);
        fscanf(fp," %[^\n]s",des);
        l=faz_lista_cart(l,ide,pri,cria,pra,conc,fas,dono,des);
    }
    fclose(fp);
    return l;
}

Lpessoa le_pessoas_fich(Lpessoa l){
    FILE * fp;
    char mail[MAX_MAIL],nome[MAX_NOME];
    int id,tamanho;
    fp=fopen("PESSOAS.txt","r");
    do{
        fflush(stdin);
        fscanf(fp,"%d\n",&id);
        fscanf(fp,"%[0-9a-zA-Z ]",nome);
        fscanf(fp,"%s",mail);
        l = faz_lista_pessoas(l,id,nome,mail);
    }while(fgetc(fp)!=EOF);
    if (NULL != fp) {
    fseek(fp, 0, SEEK_END);
    tamanho = ftell(fp);
    if (0 == tamanho) {
        return NULL;
    }
}
    fclose(fp);
    return l;
}



Lfase le_todo_fich(Lcartao l,Lfase todo){
    FILE * fp;
    Lfase nova_fase;
    int ide,nr;
    Lcartao novo=NULL;
    fp = fopen("TODO.txt","r");
    fscanf(fp,"%d",&nr);
    if(nr == 0)
    {
        fclose(fp);
        return NULL;
    }

    do{
        fscanf(fp,"%d",&ide);
        novo=procura_tarefa(l,ide);
        nova_fase=cria_no_fase(novo);
        todo=insere_em_todo(todo,nova_fase);
    }while(fgetc(fp)!=EOF);
    fclose(fp);
    return todo;
}

Lfase le_doing_fich(Lcartao l,Lfase doing){
    FILE * fp;
    Lfase nova_fase;
    int ide,nr;
    Lcartao novo=NULL;
    fp = fopen("DOING.txt","r");
    fscanf(fp,"%d",&nr);
    if(nr == 0)
    {
        fclose(fp);
        return NULL;
    }

    do{
        fscanf(fp,"%d",&ide);
        novo=procura_tarefa(l,ide);
        nova_fase=cria_no_fase(novo);
        doing=insere_em_doing(doing,nova_fase);
    }while(fgetc(fp)!=EOF);
    fclose(fp);
    return doing;
}

Lfase le_done_fich(Lcartao l,Lfase done,float *tarefas_terminadas,float *tarefas_dentro_prazo){
    FILE * fp;
    Lfase nova_fase;
    int ide,nr;
    Lcartao novo=NULL;
    fp = fopen("DONE.txt","r");
    fscanf(fp,"%f",tarefas_terminadas);
    fscanf(fp,"%f",tarefas_dentro_prazo);
    fscanf(fp,"%d",&nr);
    if(nr == 0)
    {
        fclose(fp);
        return NULL;
    }

    do{
        fscanf(fp,"%d",&ide);
        novo=procura_tarefa(l,ide);
        nova_fase=cria_no_fase(novo);
        done=insere_em_done(done,nova_fase);
    }while(fgetc(fp)!=EOF);
    fclose(fp);
    return done;
}


Lcartao protege_pess_fich(Lcartao lista_de_cartoes,Lpessoa lista_de_pessoas){
    Lcartao act=lista_de_cartoes;
    Lpessoa pess=NULL,confirma=NULL;
    while(act){
        if(act->vai_pessoa!=NULL){
            pess=act->vai_pessoa;
            confirma=procura_id_pessoa(lista_de_pessoas,pess->info.id);
            if (!confirma)
                return act;
        }
        act=act->next;
    }
    return act;
}


void le_dados(Lcartao * lista_de_cartoes,Lpessoa * lista_de_pessoas,Lfase * todo,Lfase * done,Lfase * doing,int * numero_de_tarefas_em_doing,int * numero_de_tarefas_por_pessoa,float * tarefas_terminadas,float * tarefas_dentro_prazo){
    int i,erro[MAX_ERRO],j;
    *lista_de_cartoes=le_tarefas_fich(*lista_de_cartoes,numero_de_tarefas_em_doing,numero_de_tarefas_por_pessoa);
    *lista_de_pessoas = le_tarefas_de_pessoas(*lista_de_pessoas,*lista_de_cartoes,numero_de_tarefas_por_pessoa,erro,&j);
    *todo=le_todo_fich(*lista_de_cartoes,*todo);
    *doing=le_doing_fich(*lista_de_cartoes,*doing);
    *done=le_done_fich(*lista_de_cartoes,*done,tarefas_terminadas,tarefas_dentro_prazo);

    for(i=0;i<j;i++){
        printf("Erro: Pessoa com tarefa(de id %d) atribuida apagada\nAltere o responsavel!\n",erro[i]);
        *lista_de_pessoas=da_pessoa(*lista_de_pessoas,*lista_de_cartoes,*numero_de_tarefas_por_pessoa,erro[i]);
        system("@cls||clear");
    }
}

Lpessoa da_pessoa(Lpessoa lista_de_pessoas,Lcartao l,int numero_de_tarefas_por_pessoa,int id_tar){
    Lpessoa responsavel=NULL;
    Lcartao o_cartao;
    Pes_tar apont=NULL;
    int id_pess;
    o_cartao = procura_tarefa(l,id_tar);
    listar_pessoas(lista_de_pessoas);
    do{
        printf("Introduza o id do novo responsavel para a tarefa. Lembre-se do numero maximo de tarefas por pessoa(%d)!\n>>> ",numero_de_tarefas_por_pessoa);
        fflush(stdin);
        scan_int_prot(&id_pess);
        responsavel = procura_id_pessoa(lista_de_pessoas,id_pess);
        if(responsavel){
            if (conta_tarefas_uma_pessoa(responsavel->tarefas) >= numero_de_tarefas_por_pessoa)
                printf("\n\t\tEsta pessoa tem o maximo de tarefas possiveis\n");
            if (verifica_se_pessoa_tem_tarefas_nessa_semana(responsavel,o_cartao)){
                printf("\n\t\tEsta pessoa ja tem um prazo no espaco dessa semana\nAltere o prazo para coincidir com o prazo ja definido, ou para nao calhar na mesma semana.\n");
                do{
                    printf("\tData de Prazo:\nAno:\n>>> ");
                    scan_int_prot(&o_cartao->tarefa.prazo.ano);
                    fflush(stdin);
                    printf("\tData de Prazo:\nMes:\n>>> ");
                    scan_int_prot(&o_cartao->tarefa.prazo.mes);
                    fflush(stdin);
                    printf("\tData de Prazo:\nDia:\n>>> ");
                    scan_int_prot(&o_cartao->tarefa.prazo.dia);
                    fflush(stdin);
                    protege_datas(&o_cartao->tarefa.prazo.dia, &o_cartao->tarefa.prazo.mes, &o_cartao->tarefa.prazo.ano);
                    if(calcula_diferenca_datas(o_cartao->tarefa.prazo,o_cartao->tarefa.criacao)>0)
                    printf("A data de prazo tem de ser posterior a data de criacao\n");
                }while(calcula_diferenca_datas(o_cartao->tarefa.prazo,o_cartao->tarefa.criacao)>0);
            }
        }
    }while(responsavel==NULL || conta_tarefas_uma_pessoa(responsavel->tarefas) >= numero_de_tarefas_por_pessoa || verifica_se_pessoa_tem_tarefas_nessa_semana(responsavel,o_cartao));
    apont=faz_lista_tarefas_pessoas(apont);
    responsavel->tarefas= insere_Pes_tar(responsavel->tarefas,apont);
    responsavel->tarefas->vai_cartao = o_cartao;
    o_cartao->vai_pessoa = responsavel;
    o_cartao->tarefa.dono=responsavel->info.id;
    system("Pause");
    return lista_de_pessoas;
}

int protege_nomes_fich(Lpessoa lista_de_pessoas){
    Lpessoa ant,act;
    int comp;
    char nome_a[MAX_NOME],nome_b[MAX_NOME];
    ant=lista_de_pessoas;
    act=ant->next;
    while(act){
        strcpy(nome_a,ant->info.nome);
        while(act){
            strcpy(nome_b,act->info.nome);
            comp=strcmp(nome_a,nome_b);
            if (comp==0)
                return 1;
            act=act->next;
        }
        ant=ant->next;
        act=ant->next;
    }
    return 0;
}

int protege_nums_fich(Lpessoa lista_de_pessoas){
    Lpessoa ant,act;
    int num_a,num_b;
    ant=lista_de_pessoas;
    act=ant->next;
    while(act){
        num_a=ant->info.id;
        while(act){
            num_b=act->info.id;
            if (num_a==num_b)
                return 1;
            act=act->next;
        }
        ant=ant->next;
        act=ant->next;
    }
    return 0;
}
