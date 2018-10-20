#include <stdio.h>
#include <stdlib.h>
#define MAX_DESCRICAO 130
#define MAX_MAIL 100
#define MAX_NOME 200
#include "header.h"
#include <string.h>




void visualiza_doing(Lfase doing,Lpessoa lista_de_pessoas)
{
    int conta=0;
    Lpessoa l=lista_de_pessoas;
    Pes_tar p;
    if (l == NULL)
        printf("no");
    while(l)
    {
        p = l->tarefas;
        while(p)
        {
            if(p->vai_cartao->fase == 2)
            {
                conta++;
                printf(" _____________________________________________________________________________________________________________________");
                printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",p->vai_cartao->tarefa.id);
                printf("\n PRIORIDADE -> %d       ",p->vai_cartao->tarefa.prioridade);
                printf("\n DATA CRIACAO(D/M/A)   \n %d/%d/%d                 \n",p->vai_cartao->tarefa.criacao.dia,p->vai_cartao->tarefa.criacao.mes,p->vai_cartao->tarefa.criacao.ano);
                if (p->vai_cartao->tarefa.prazo.ano != -1)
                    printf("\nDATA DE PRAZO(D/M/A)\n %d/%d/%d               \n",p->vai_cartao->tarefa.prazo.dia,p->vai_cartao->tarefa.prazo.mes,p->vai_cartao->tarefa.prazo.ano);
                if (p->vai_cartao->tarefa.conclusao.ano != -1)
                    printf("\nDATA CONCLUSAO(D/M/A)\n %d/%d/%d               \n",p->vai_cartao->tarefa.conclusao.dia,p->vai_cartao->tarefa.conclusao.mes,p->vai_cartao->tarefa.conclusao.ano);
                if (doing->p_cartao->vai_pessoa)
                    printf("\n Pessoa responsavel pela tarefa -> %s\n",l->info.nome);
                printf("\n Descricao: %s",p->vai_cartao->tarefa.descricao);
                printf("\n|_____________________________________________________________________________________________________________________|\n\n");
            }
            p = p->next;
        }
        l = l->next;
    }
    if (conta == 0)
    {
        printf("\n\n\t\t\tNao existem tarefas\n");
    }
}


Lfase insere_em_doing(Lfase f,Lfase new_) /*AINDA NAO TEM ORDENAÇAO INCUTIDA*/
{
    new_->next = f;
    f = new_;
    return f;
}
Lfase elimina_no_fase(Lfase f, int aux)
{
    Lfase ant = NULL,act=f;
    while(act && act->p_cartao->tarefa.id != aux)
    {
        ant = act;
        act = act->next;
    }
    if (act)
    {
        if (ant)
        {
            ant->next = act->next;
        }
        else
        {
            f = act->next;
        }
    }
    return f;
}

Lfase cria_no_fase(Lcartao l){
    Lfase no_novo;
    no_novo = (Lfase)malloc(sizeof(Fase));
    no_novo->next=NULL;
    no_novo->p_cartao=l;
    return no_novo;
}

void visualiza_fase(Lfase f){    /*NAO SE APLICA PARA O DOING!!!!!*/
    int conta =0;
    while (f)
    {
        /*Coisitas estéticas*/
        printf(" _____________________________________________________________________________________________________________________");
        printf("\n|ID -> %d\t\t\t\t\t\t\t\t\t\t\t\t\t      |",f->p_cartao->tarefa.id);
        printf("\n PRIORIDADE -> %d       ",f->p_cartao->tarefa.prioridade);
        printf("\n DATA CRIACAO(D/M/A)   \n %d/%d/%d                 \n",f->p_cartao->tarefa.criacao.dia,f->p_cartao->tarefa.criacao.mes,f->p_cartao->tarefa.criacao.ano);
        if (f->p_cartao->tarefa.prazo.ano != -1)
            printf("\nDATA DE PRAZO(D/M/A)\n %d/%d/%d               \n",f->p_cartao->tarefa.prazo.dia,f->p_cartao->tarefa.prazo.mes,f->p_cartao->tarefa.prazo.ano);
        if (f->p_cartao->tarefa.conclusao.ano != -1)
            printf("\nDATA CONCLUSAO(D/M/A)\n %d/%d/%d               \n",f->p_cartao->tarefa.conclusao.dia,f->p_cartao->tarefa.conclusao.mes,f->p_cartao->tarefa.conclusao.ano);
        if (f->p_cartao->vai_pessoa)
            printf("\n Pessoa responsavel pela tarefa -> %s\n",f->p_cartao->vai_pessoa->info.nome);
        printf("\n Descricao: %s",f->p_cartao->tarefa.descricao);
        printf("\n|_____________________________________________________________________________________________________________________|\n\n");
        f = f->next;
        conta++;
    }
    if (conta == 0)
    /*pequena alteraçao--Paulo*/
        printf("\n\n\t\t\tNao existem tarefas\n");
}

int conta_elementos_fase(Lfase f)
{
    int conta = 0;
    while(f)
    {
        conta++;
        f=f->next;
    }
    return conta;
}
Lfase destroi_fase(Lfase l){
    Lfase aux;
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


Lfase passar_para_done(Lcartao l,Lfase *todo,Lfase *doing,Lfase done,Lpessoa lista_de_pessoas,float *tarefas_terminadas,float *tarefas_dentro_prazo){
    Lfase repetido,find_doing,find_todo;
    int aux=1,confirma;
    printf("\t\tDOING\n");
    visualiza_doing(*doing,lista_de_pessoas);
    printf("\n\n\t\t\tINDIQUE QUE TAREFA QUER POR EM DONE\n**Lembre-se que nao pode ter mais tarefas em Doing do que aquelas por si definidas(mudar depois pelo n)**\n");
    printf("\t\n\tIndique o id da respetiva tarefa / 0 para voltar\n>>> ");
    scan_int_prot(&aux);
        while (aux != 0)
        {
            find_todo=procura_tarefa_em_fase(*todo,aux);
            find_doing=procura_tarefa_em_fase(*doing,aux);
            repetido = procura_tarefa_em_fase(done,aux);
            while(find_todo || !find_doing || repetido)
            {
                if (!find_todo && !find_doing && !repetido)
                    printf("\tEssa tarefa nao existe\n\n>>> ");
                if (find_todo)
                    printf("\tNao se pode passar tarefas de todo para done\n\n>>> ");
                if (repetido)
                    printf("\tJa existe essa tarefa em DONE\n\n>>> ");
                scan_int_prot(&aux);
                if (aux==0)
                    return done;
                find_todo=procura_tarefa_em_fase(*todo,aux);
                find_doing=procura_tarefa_em_fase(*doing,aux);
                repetido = procura_tarefa_em_fase(done,aux);
            }
            printf("\t\t**Esta tarefa esta em DOING**\n\t--Vai agora passar uma tarefa de DOING para DONE--\n**Isto significa que a tarefa ganhara a sua data de conclusao!**\n--Escreva 0 para abortar ou outro numero qualquer para confirmar--\n>>>");
            scan_int_prot(&confirma);
            if (confirma==0)
                return done;
            printf("\t\tID aceite!");
            do{
                printf("\n\tData de Conclusao:\nAno:\n>>> ");
                fflush(stdin);
                scan_int_prot(&find_doing->p_cartao->tarefa.conclusao.ano);
                printf("\tData de Conclusao:\nMes:\n>>> ");
                fflush(stdin);
                scan_int_prot(&find_doing->p_cartao->tarefa.conclusao.mes);
                printf("\tData de Conclusao:\nDia:\n>>> ");
                fflush(stdin);
                scan_int_prot(&find_doing->p_cartao->tarefa.conclusao.dia);
                protege_datas(&find_doing->p_cartao->tarefa.conclusao.dia, &find_doing->p_cartao->tarefa.conclusao.mes, &find_doing->p_cartao->tarefa.conclusao.ano);

                if(calcula_diferenca_datas(find_doing->p_cartao->tarefa.conclusao,find_doing->p_cartao->tarefa.criacao)>0)
                    printf("A data de conclusao tem de ser posterior ou coincidente a de criacao!\n");
            }while(calcula_diferenca_datas(find_doing->p_cartao->tarefa.conclusao,find_doing->p_cartao->tarefa.criacao)>0);
            *tarefas_terminadas += 1;
            if(calcula_diferenca_datas(find_doing->p_cartao->tarefa.conclusao,find_doing->p_cartao->tarefa.prazo)>=0)
                *tarefas_dentro_prazo += 1;
            *doing = elimina_no_fase(*doing,find_doing->p_cartao->tarefa.id);
            done = insere_em_done(done,find_doing);
            find_doing->p_cartao->fase=3;
            system("@cls||clear");
            printf("\t\tDOING\n");
            visualiza_doing(*doing,lista_de_pessoas);
            printf("\n\t\t TAREFA INSERIDA EM DONE COM SUCESSO!\n");
            printf("\nPara voltar -> 0\nOu entao indique o id da respetiva tarefa\n>>> ");
            scan_int_prot(&aux);
        }
    system("@cls||clear");
    return done;
}
Lfase insere_em_done(Lfase done,Lfase novo)
{
    Data default_;
    Lfase act = done,ant=NULL;
    default_.ano=0;
    default_.mes=0;
    default_.dia=0;
    while (act && calcula_diferenca_datas(default_,act->p_cartao->tarefa.criacao) < calcula_diferenca_datas(default_,novo->p_cartao->tarefa.criacao))
    {
        ant = act;
        act = act->next;
    }
    novo->next = act;
    if (ant==NULL)
        done = novo;
    else
        ant->next=novo;
    return done;
}
Lfase passar_para_doing(Lcartao l,Lfase *todo,Lfase doing,Lfase *done,int numero_de_tarefas_em_doing,Lpessoa lista_de_pessoas,int numero_de_tarefas_por_pessoa)
{
    Lpessoa check;
    Lfase repetido,find_done,find_todo;
    char nome_pessoa[MAX_NOME];
    int aux=1,confirma;
    if (numero_de_tarefas_em_doing == conta_elementos_fase(doing))
    {
        do{
            system("@cls||clear");
            printf("\n\n\tO NUMERO DE TAREFAS EM DOING ESTA NO SEU LIMITE\n\t  RETIRE ALGUMA TAREFA OU AUMENTE O SEU LIMITE\n\t\t  PARA PODER ADICIONAR MAIS!\n\nVoltar -> 0\n>>> ");
            scan_int_prot(&aux);
        }while(aux !=0);
        return doing;
    }
    printf("\t\tTO DO\n");
    visualiza_fase(*todo);
    printf("\t\tDONE\n");
    visualiza_fase(*done);
    printf("\n\n\t\tINDIQUE QUE TAREFA QUER POR EM DOING\nlembre-se que nao pode ter mais tarefas em Doing do que aquelas por si definidas(mudar depois pelo n)\n");
    printf("\t\n\tIndique o id da respetiva tarefa OU 0 para voltar\n>>> ");
    scan_int_prot(&aux);
    fflush(stdin);
        while (aux != 0)
        {
            find_todo=procura_tarefa_em_fase(*todo,aux);
            find_done=procura_tarefa_em_fase(*done,aux);
            repetido = procura_tarefa_em_fase(doing,aux);
            while((!find_todo && !find_done) || repetido)
            {
                if (!find_done && !find_todo && !repetido)
                    printf("\tNao existe nenhuma tarefa com esse nome\n\n>>> ");
                if (repetido)
                    printf("\tJa existe essa tarefa em DOING\n\n>>> ");
                scan_int_prot(&aux);
                fflush(stdin);
                if (aux==0)
                    return doing;
                find_todo=procura_tarefa_em_fase(*todo,aux);
                find_done=procura_tarefa_em_fase(*done,aux);
                repetido = procura_tarefa_em_fase(doing,aux);
            }
            if (numero_de_tarefas_em_doing == conta_elementos_fase(doing))
            {
                do{
                    system("@cls||clear");
                    printf("\n\n\tO NUMERO DE TAREFAS EM DOING ESTA NO SEU LIMITE\n\t  RETIRE ALGUMA TAREFA OU AUMENTE O SEU LIMITE\n\t\t  PARA PODER ADICIONAR MAIS!\n\nVoltar -> 0\n>>> ");
                    scan_int_prot(&aux);
                }while(aux !=0);
                return doing;
            }

            if(find_done)
            {
                printf("||Esta tarefa esta em DONE||\n!!Vai agora passar uma tarefa de done para DOING!!\n(Isto significa que a tarefa perdera a sua data de conclusao!)\n--Escreva 0 para abortar ou outro numero qualquer para confirmar--\n>>>");
                scan_int_prot(&confirma);
                fflush(stdin);
                if (confirma==0)
                    return doing;
                find_done->p_cartao->tarefa.conclusao.ano=-1;
                find_done->p_cartao->tarefa.conclusao.mes=-1;
                find_done->p_cartao->tarefa.conclusao.dia=-1;
                *done = elimina_no_fase(*done,find_done->p_cartao->tarefa.id);
                doing = insere_em_doing(doing,find_done);
                find_done->p_cartao->fase=2;
            }
            if(find_todo)
            {
                printf("||Esta tarefa esta em TODO||\n!!Vai agora passar uma tarefa de TODO para DOING!!\n(Nao se esqueça dos limites que definiu para tarefas abertas!)\n--Escreva 1 se quer mudar a data de prazo--\n--Escreva 0 para abortar ou outro numero qualquer para confirmar--\n>>>");
                scan_int_prot(&confirma);
                fflush(stdin);
                if (confirma==0)
                    return doing;
                if (confirma==1)
                {
                   do{
                        printf("\tData de Prazo:\nAno:\n>>> ");
                        scan_int_prot(&find_todo->p_cartao->tarefa.prazo.ano);
                        fflush(stdin);
                        printf("\tData de Prazo:\nMes:\n>>> ");
                        scan_int_prot(&find_todo->p_cartao->tarefa.prazo.mes);
                        fflush(stdin);
                        printf("\tData de Prazo:\nDia:\n>>> ");
                        scan_int_prot(&find_todo->p_cartao->tarefa.prazo.dia);
                        fflush(stdin);
                        protege_datas(&find_todo->p_cartao->tarefa.prazo.dia, &find_todo->p_cartao->tarefa.prazo.mes, &find_todo->p_cartao->tarefa.prazo.ano);
                        if(calcula_diferenca_datas(find_todo->p_cartao->tarefa.prazo,find_todo->p_cartao->tarefa.criacao)>0)
                            printf("A data de prazo tem de ser posterior a data de criacao!\n");
                    }while(calcula_diferenca_datas(find_todo->p_cartao->tarefa.prazo,find_todo->p_cartao->tarefa.criacao)>0);
                }


                    if (find_todo->p_cartao->vai_pessoa == NULL)
                    {
                        listar_pessoas(lista_de_pessoas);
                        do{
                            printf("\n\tIndique o nome do responsavel:\t\n>>> ");
                            gets(nome_pessoa);
                            fflush(stdin);
                            check = procura_nome_pessoa(nome_pessoa,lista_de_pessoas);
                            if (!check)
                                printf("\n\t\tNao existe uma pessoa com esse nome");
                            if (check && conta_tarefas_uma_pessoa(check->tarefas) >= numero_de_tarefas_por_pessoa)
                                printf("\n\t\tEsta pessoa tem o maximo de tarefas possiveis");
                            if (check && verifica_se_pessoa_tem_tarefas_nessa_semana(check,find_todo->p_cartao))
                                printf("\n\t\tEsta pessoa ja tem um prazo no espaco dessa semana\n");
                        }while(!check || conta_tarefas_uma_pessoa(check->tarefas) >= numero_de_tarefas_por_pessoa || verifica_se_pessoa_tem_tarefas_nessa_semana(check,find_todo->p_cartao));
                        find_todo->p_cartao->vai_pessoa = check;
                        check->tarefas = faz_lista_tarefas_pessoas(check->tarefas); /*Criar lista*/
                        check->tarefas->vai_cartao = find_todo->p_cartao;           /*Inserir na nova lista ligada*/
                        find_todo->p_cartao->tarefa.dono = check->info.id;
                    }
                    *todo = elimina_no_fase(*todo,find_todo->p_cartao->tarefa.id);
                    doing = insere_em_doing(doing,find_todo);
                    find_todo->p_cartao->fase=2;
            }
            system("@cls||clear");
             printf("\t\tTO DO\n");
            visualiza_fase(*todo);
            printf("\t\tDONE\n");
            visualiza_fase(*done);
            printf("\n\n\t\t TAREFA INSERIDA EM DOING COM SUCESSO!\n");
            printf("\nIndique o id da respetiva tarefa OU 0 para voltar\n>>> ");
            scan_int_prot(&aux);
        }
        fflush(stdin);
        system("@cls||clear");
        return doing;
}



Lfase procura_tarefa_em_fase(Lfase l,int n)
{

    Lfase fim = NULL,move = l;
    while (move)
    {
        if (move->p_cartao->tarefa.id==n)
        {
            fim = move;
            break;
        }
        move=move->next;
    }
    return fim;
}

int conta_tarefas(Lcartao l)
{
    int conta = 0;
    while(l)
    {
        conta++;
        l=l->next;
    }
    return conta;
}



Lfase passar_para_todo(Lcartao l,Lfase todo,Lfase* doing,Lfase* done,Lpessoa lista_de_pessoas)
{
    Lfase repetido,find_done,find_doing;
    int aux,confirma;
    printf("\t\tDOING\n");
    visualiza_doing(*doing,lista_de_pessoas);
    printf("\t\tDONE\n");
    visualiza_fase(*done);
    printf("\n\n\t\tINDIQUE QUE TAREFA QUER POR EM TO DO\nlembre-se que tarefas em DONE nao podem ser inseridas em TO DO\n");
    printf("\t\n\tIndique o id da respetiva tarefa / 0 para voltar\n>>> ");
    scan_int_prot(&aux);
        while (aux != 0)
        {
            find_done=procura_tarefa_em_fase(*done,aux);
            find_doing=procura_tarefa_em_fase(*doing,aux);
            repetido = procura_tarefa_em_fase(todo,aux);
            while((!find_done && !find_doing) || repetido)
            {
                if (!find_done && !find_doing && !repetido)
                    printf("\tNao existe nenhuma tarefa com esse id\n\n>>> ");
                if (repetido)
                    printf("\tJa existe essa tarefa em TO DO\n\n>>> ");
                scan_int_prot(&aux);
                if (aux==0)
                    return todo;
                find_done=procura_tarefa_em_fase(*done,aux);
                find_doing=procura_tarefa_em_fase(*doing,aux);
                repetido = procura_tarefa_em_fase(todo,aux);
            }
            if (find_done)
            {
                printf("||Esta tarefa esta em DONE||\n!!Vai agora passar uma tarefa de DONE para TODO (REABRIR CARTAO)!!\n--Escreva 0 para abortar ou outro numero qualquer para confirmar--\n>>>");
                scan_int_prot(&confirma);
                if (confirma==0)
                    return todo;
                *done = elimina_no_fase(*done,find_done->p_cartao->tarefa.id);
                todo = insere_em_todo(todo,find_done);
                find_done->p_cartao->fase=1;
                find_done->p_cartao->tarefa.conclusao.ano=-1;
                printf("\t\tDeseja alterar a data de criacao e de prazo?\n\tEscreva 0 para nao alterar ou outro numero qualquer para confirmar\n>>>");
                scan_int_prot(&confirma);
                if (confirma != 0)
                {

                    printf("\tData de criacao:\nAno:\n>>> ");
                    scan_int_prot(&find_done->p_cartao->tarefa.criacao.ano);
                    fflush(stdin);
                        printf("\tData de criacao:\nMes:\n>>> ");
                    scan_int_prot(&find_done->p_cartao->tarefa.criacao.mes);
                    fflush(stdin);
                    printf("\tData de criacao:\nDia:\n>>> ");
                    scan_int_prot(&find_done->p_cartao->tarefa.criacao.dia);
                    fflush(stdin);
                    protege_datas(&find_done->p_cartao->tarefa.criacao.dia, &find_done->p_cartao->tarefa.criacao.mes, &find_done->p_cartao->tarefa.criacao.ano); /*Ve e altera se achares que e preciso, mas parece estar a funcionar*/
                    do{
                        printf("\tData de Prazo:\nAno:\n>>> ");
                        scan_int_prot(&find_done->p_cartao->tarefa.prazo.ano);
                        fflush(stdin);
                        printf("\tData de Prazo:\nMes:\n>>> ");
                        scan_int_prot(&find_done->p_cartao->tarefa.prazo.mes);
                        fflush(stdin);
                        printf("\tData de Prazo:\nDia:\n>>> ");
                        scan_int_prot(&find_done->p_cartao->tarefa.prazo.dia);
                        fflush(stdin);
                        protege_datas(&find_done->p_cartao->tarefa.prazo.dia, &find_done->p_cartao->tarefa.prazo.mes, &find_done->p_cartao->tarefa.prazo.ano);
                        if (verifica_se_pessoa_tem_tarefas_nessa_semana(find_done->p_cartao->vai_pessoa,find_done->p_cartao)>1)
                            printf("Esta pessoa ja tem um prazo no espaco dessa semana\n");
                        if(calcula_diferenca_datas(find_done->p_cartao->tarefa.prazo,find_done->p_cartao->tarefa.criacao)>0)
                            printf("A data de prazo tem de ser posterior a data de criacao\n");
                    }while(calcula_diferenca_datas(find_done->p_cartao->tarefa.prazo,find_done->p_cartao->tarefa.criacao)>0 || verifica_se_pessoa_tem_tarefas_nessa_semana(find_done->p_cartao->vai_pessoa,find_done->p_cartao)>1);
                }
                system("@cls||clear");
                printf("\t\tDOING\n");
                visualiza_doing(*doing,lista_de_pessoas);
                printf("\t\tDONE\n");
                visualiza_fase(*done);
                printf("\n\t\t TAREFA INSERIDA EM TO DO COM SUCESSO!\n");
                printf("\t\n\n\n\tIndique o id da respetiva tarefa que quer colocar em To Do / 0 para voltar\n>>> ");
                scan_int_prot(&aux);
            }
            if (find_doing)
            {
                printf("||Esta tarefa esta em DOING||\n!!Vai agora passar uma tarefa de DOING para TODO!!\n--Escreva 0 para abortar ou outro numero qualquer para confirmar--\n>>>");
                scan_int_prot(&confirma);
                if (confirma==0)
                    return todo;

                *doing = elimina_no_fase(*doing,find_doing->p_cartao->tarefa.id);
                todo = insere_em_todo(todo,find_doing);
                find_doing->p_cartao->fase=1;
                printf("\t\tDOING\n");
                visualiza_doing(*doing,lista_de_pessoas);
                printf("\t\tDONE\n");
                visualiza_fase(*done);
                printf("\n\t\tTarefa inserida em TO DO com sucesso!\n\n");
                printf("\t\n\n\n\tIndique o id da respetiva tarefa que quer colocar em To Do / 0 para voltar\n>>> ");
                scan_int_prot(&aux);
            }
        }
    system("@cls||clear");
    return todo;
}
Lfase insere_em_todo(Lfase todo, Lfase nova_fase)
{
    Data default_;
    Lfase ant=NULL,act=todo;
    default_.ano=0;
    default_.mes=0;
    default_.dia=0;
    while (act && (act->p_cartao->tarefa.prioridade > nova_fase->p_cartao->tarefa.prioridade))
    {
        ant = act;
        act = act->next;
    }
    while (act && (act->p_cartao->tarefa.prioridade == nova_fase->p_cartao->tarefa.prioridade) && (calcula_diferenca_datas(default_,act->p_cartao->tarefa.prazo) < calcula_diferenca_datas(default_,nova_fase->p_cartao->tarefa.prazo)))
    {
        ant = act;
        act = act->next;
    }
    nova_fase->next = act;
    if (!ant)
        todo = nova_fase;
    else
        ant->next=nova_fase;
    return todo;
}
Lfase passar_para_todo_logo(Lcartao novo,Lfase todo)
{
    Data default_;
    Lfase ant=NULL,act=todo;
    Lfase nova_fase;
    nova_fase = cria_no_fase(novo);
    default_.ano=0;
    default_.mes=0;
    default_.dia=0;
    while (act && (act->p_cartao->tarefa.prioridade > nova_fase->p_cartao->tarefa.prioridade))
    {
        ant = act;
        act = act->next;
    }
    while (act && (act->p_cartao->tarefa.prioridade == nova_fase->p_cartao->tarefa.prioridade) && (calcula_diferenca_datas(default_,act->p_cartao->tarefa.prazo) < calcula_diferenca_datas(default_,nova_fase->p_cartao->tarefa.prazo)))
    {
        ant = act;
        act = act->next;
    }
    nova_fase->next = act;
    if (!ant)
        todo = nova_fase;
    else
        ant->next=nova_fase;
    return todo;
}
