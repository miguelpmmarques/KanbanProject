#include <stdio.h>
#include <stdlib.h>
#define MAX_DESCRICAO 130
#define MAX_MAIL 100
#define MAX_NOME 200
#include <locale.h>
#include <string.h>

typedef struct card *Lcartao;
typedef struct pessoa *Lpessoa;
typedef struct fase *Lfase;
typedef struct tarefa_pessoa *Pes_tar;

/*DATAS*/
typedef struct{
    int dia,mes,ano;
}Data;


/*TAREFAS*/
typedef struct{
    int id;
    int dono;
    int prioridade;
    Data criacao;
    Data prazo;
    Data conclusao;
    char descricao[MAX_DESCRICAO];
}Cartao;

typedef struct card{
    Cartao tarefa;
    Lcartao next;
    Lpessoa vai_pessoa;
    int fase;
}Card;


/*PESSOAS*/
typedef struct{
    int id;
    char email[MAX_MAIL];
    char nome[MAX_NOME];
}Info_Pessoa;

typedef struct pessoa{
    Lpessoa next;
    Pes_tar tarefas;
    Info_Pessoa info;
}Pessoa;


/*FASES*/
typedef struct fase{
    Lfase next;
    Lcartao p_cartao;
}Fase;


/*TAREFA_POR_PESSOA*/

typedef struct tarefa_pessoa{
    Lcartao vai_cartao;
    Pes_tar next;
}Tarefa_pessoa;




/*MISCELLANEOUS*/
void menu(void);
void estabelece_limites(int *numero_de_tarefas_em_doing,int *numero_de_tarefas_por_pessoa,Lfase doing,Lpessoa lista_de_pessoas);
void scan_int_prot(int * num);

/*DATAS*/
int calcula_diferenca_datas(Data um, Data dois);
int calcula_numero_dias(int anos,int meses,int dias);
void protege_datas(int * dia,int * mes,int * ano);
int deteta_problema_data(int dia, int mes, int ano);

/*TAREFAS*/
Lcartao faz_lista_cart(Lcartao l,int ide,int pri,Data cria,Data pra,Data conc,int fas,int dono,char des[]);
Lcartao insere_Lcartaoa (Lcartao l,Lcartao novo);
Lcartao cria_Lcartaoa (Lcartao l);
Lcartao procura_tarefa(Lcartao l,int n);/*Tinhas-te esquecido de declarar a funcao aqui*/
void visualiza_todas_tarefas(Lcartao l);
Lcartao destroi_tarefas(Lcartao l);
Pes_tar destroi_tarefas_de_pessoas(Pes_tar l);
void escreve_tarefas_fich(Lcartao l,int *numero_de_tarefas_em_doing, int *numero_de_tarefas_por_pessoa);
int conta_tarefas(Lcartao l);
Lcartao le_tarefas_fich(Lcartao l, int *numero_de_tarefas_em_doing, int *numero_de_tarefas_por_pessoa);

/*FASES*/
Lfase destroi_fase(Lfase l);
Lfase passar_para_doing(Lcartao l,Lfase *todo,Lfase doing,Lfase *done,int numero_de_tarefas_em_doing,Lpessoa lista_de_pessoas,int numero_de_tarefas_por_pessoa);
Lfase passar_para_done(Lcartao l,Lfase *todo,Lfase *doing,Lfase done,Lpessoa lista_de_pessoas,float *tarefas_terminadas,float *tarefas_dentro_prazo);
Lfase passar_para_todo(Lcartao l,Lfase todo,Lfase* doing,Lfase* done,Lpessoa lista_de_pessoas);
Lcartao altera_id_fase(Lcartao l,int fase);/*minha - um bocado desnecessaria mas e mais organizado assim*/
void visualiza_fase(Lfase f);/*nova tambem*/
void visualiza_doing(Lfase doing,Lpessoa lista_de_pessoas);
void le_quadro(Lfase todo,Lfase doing,Lfase done,Lpessoa lista_de_pessoas);
Lfase cria_no_fase(Lcartao l);
Lfase procura_tarefa_em_fase(Lfase l,int n); /*Confirma se uma tarefa se encontra na fase*/
Lfase insere_em_done(Lfase done,Lfase novo);
Lfase insere_em_todo(Lfase todo, Lfase nova_fase);
Lfase elimina_no_fase(Lfase f, int aux);
Lfase insere_em_doing(Lfase f,Lfase new_);
Lfase passar_para_todo_logo(Lcartao novo,Lfase todo);
int conta_elementos_fase(Lfase f);

/*PESSOAS*/
int verifica_se_pessoa_tem_tarefas_nessa_semana(Lpessoa l,Lcartao taref);
Lpessoa da_pessoa(Lpessoa lista_de_pessoas,Lcartao l,int numero_de_tarefas_por_pessoa,int id_tar);
Lpessoa destroi_pessoas(Lpessoa l);
Lpessoa procura_id_pessoa(Lpessoa lista_de_pessoas,int id);
Lpessoa le_tarefas_de_pessoas(Lpessoa l,Lcartao cartoes,int * numero_de_tarefas_por_pessoa,int erro[],int * j);
Lpessoa le_pessoas_fich(Lpessoa l);
int conta_total_tarefas_pessoas(Lpessoa l);
Lpessoa faz_lista_pessoas(Lpessoa l,int ide,char nom[],char em[]);
Lpessoa insere_Lpessoa(Lpessoa l,Lpessoa nova);
void listar_pessoas(Lpessoa l);
Lpessoa procura_nome_pessoa(char nome_pessoa[MAX_NOME],Lpessoa lista_de_pessoas);

Pes_tar faz_lista_tarefas_pessoas(Pes_tar l);
Pes_tar insere_Pes_tar(Pes_tar l,Pes_tar nova);
void visualiza_tarefa_de_certa_pessoa(Lpessoa lista_de_pessoas,Lfase todo,Lfase doing,Lfase done);
Lpessoa altera_pessoa(Lpessoa lista_de_pessoas,Lcartao l,int numero_de_tarefas_por_pessoa);
Pes_tar procura_tarefa_na_pessoa(Lpessoa *check,int id);
int conta_max_tarefas_pessoas(Lpessoa l);
int conta_tarefas_uma_pessoa(Pes_tar l);


/*FICHEIROS*/

void salvar(Lcartao lista_de_cartoes,int *numero_de_tarefas_em_doing,int *numero_de_tarefas_por_pessoa,Lpessoa lista_de_pessoas,Lfase todo,Lfase doing,Lfase done,int tarefas_terminadas,int tarefas_dentro_prazo);
void escreve_done_fich(Lfase l,float tarefas_terminadas,float tarefas_dentro_prazo);
void escreve_todo_fich(Lfase l);
void escreve_doing_fich(Lfase l);
void escreve_tarefas_de_pessoas(Lpessoa lista_pessoas);
Lfase le_todo_fich(Lcartao l,Lfase todo);
Lfase le_doing_fich(Lcartao l,Lfase doing);
Lfase le_done_fich(Lcartao l,Lfase done,float *tarefas_terminadas,float *tarefas_dentro_prazo);
Lfase faz_todo_fich(Lcartao novo,Lfase todo);
Lcartao protege_pess_fich(Lcartao lista_de_cartoes,Lpessoa lista_de_pessoas);
void le_dados(Lcartao * lista_de_cartoes,Lpessoa * lista_de_pessoas,Lfase * todo,Lfase * done,Lfase * doing,int * numero_de_tarefas_em_doing,int * numero_de_tarefas_por_pessoa,float * tarefas_terminadas,float * tarefas_dentro_prazo);
int protege_nomes_fich(Lpessoa lista_de_pessoas);
int protege_nums_fich(Lpessoa lista_de_pessoas);
