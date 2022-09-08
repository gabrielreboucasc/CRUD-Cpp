#ifndef _FUNCOES_H_INCLUDED_
#define _FUNCOES_H_INCLUDED_

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;
using std::getline;

#include <ios>
#include <limits>
using std::numeric_limits;
using std::streamsize;

#include <stdbool.h>

struct alunos{
    char nome_aluno[50], curso_aluno[50], email_aluno[50];
    int matricula_aluno;
}alunos;

struct avaliador{
    char nome_avaliador[50], email_avaliador[50], instituicao[50];
    int ordem_avaliador;
}avaliador[10];

typedef struct Dados_Banca{
    char orientador[50], titulo_banca[50], resumo[50];
}dados_banca;

typedef struct Cadastro_banca {
    // Referente as informações dos alunos, avaliadores e banca
    struct avaliador *avaliadores;
    struct alunos *alunos;
    dados_banca *banca_info;

    // Informações para ordenar
    int id_banca;
    int qtde_avaliadores;

    // Mecanismo para unir as bancas
    struct Cadastro_banca *prox;
    struct Cadastro_banca *ant;
}cadastro_banca;

// Referências para a lista
cadastro_banca *inicio = NULL;
cadastro_banca *fim = NULL;
int qtde_bancas = 0;

void adicionar_banca();
void imprimir_bancas();
void remover_banca();
void atualizar_banca();

void adicionar_banca(){
    cadastro_banca *banca = (cadastro_banca *) malloc(sizeof(cadastro_banca));

    // Área Aluno
    // Aloca memória para alunos
    banca->alunos = (struct alunos *) malloc(sizeof(struct alunos));

    // Recebe as informações de aluno
    cout << "\nAluno" << endl;
    cout << "Nome........: ";
    cin.getline(banca->alunos->nome_aluno, 50);
    cout << "Curso.......: ";
    cin.getline(banca->alunos->curso_aluno, 50);
    cout << "Matrícula...: ";
    cin >> banca->alunos->matricula_aluno;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "email.......: ";
    cin.getline(banca->alunos->email_aluno, 50);

    // Área de informações da banca
    banca->banca_info = (dados_banca *) malloc(sizeof(dados_banca));

    cout << "\nDados da banca" << endl;
    cout << "Título......: ";
    cin.getline(banca->banca_info->titulo_banca, 50);
    cout << "Resumo......: ";
    cin.getline(banca->banca_info->resumo, 50);
    cout << "Orientador..: ";
    cin.getline(banca->banca_info->orientador, 50);

    // Área Avaliadores
    cout << "\nAcrescentará quantos avaliadores? ";
    cin >> banca->qtde_avaliadores;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Aloca memória para avaliadores
    banca->avaliadores = (struct avaliador *) malloc(banca->qtde_avaliadores*sizeof(struct avaliador));

    for(int i=0; i<banca->qtde_avaliadores; i++){
        int i_mais_um = i+1;
        cout << "\nAvaliador " << i_mais_um << endl;
        cout << "Nome..........: ";
        cin.getline(banca->avaliadores[i].nome_avaliador, 50);
        cout << "Instituição...: ";
        cin.getline(banca->avaliadores[i].instituicao, 50);
        cout << "Email.........: ";
        cin.getline(banca->avaliadores[i].email_avaliador, 50);
        banca->avaliadores[i].ordem_avaliador = i_mais_um;
    }

    banca->ant = NULL;
    banca->prox = NULL;

    // Aloca os elementos na lista
    if(inicio == NULL){ //lista vazia
        inicio = banca;
        fim = banca;
    }else{ // "no fim"
        banca->ant = fim;
        fim->prox = banca;
        fim = banca;
    }
    qtde_bancas++;
    banca->id_banca = qtde_bancas;
}

void imprimir_bancas(){
    if(inicio == NULL){ // Lista vazia!
        printf("\nNão há bancas cadastradas!\n");
    }else{
        // Inicia um ponteiro auxiliar no início
        cadastro_banca *aux = inicio;

        // loop printando as bancas
        for(int i=0; i < qtde_bancas; i++){
            cout << endl << "\t<------ Banca " << aux->id_banca << " ------>" << endl << endl;

            cout << "\t\tAluno" << endl;
            cout << "Aluno.......: " << aux->alunos->nome_aluno;
            cout << " | " << aux->alunos->matricula_aluno;
            cout << " | " << aux->alunos->curso_aluno;
            cout << " | " << aux->alunos->email_aluno << endl;

            cout << endl << "\t\tAvaliadores" << endl;
            
            for (int i = 0; i < aux->qtde_avaliadores; i++){
                cout << "Avaliador " << aux->avaliadores[i].ordem_avaliador << " : " << aux->avaliadores[i].nome_avaliador;
                cout << " | " << aux->avaliadores[i].email_avaliador;
                cout << " | " << aux->avaliadores[i].instituicao << endl;
            }

            cout << "\n\t\tTCC" << endl;
            cout << "Orientador..: " << aux->banca_info->orientador << endl;
            cout << "Título......: " << aux->banca_info->titulo_banca << endl;
            cout << "Resumo......: " << aux->banca_info->resumo << endl;

            cout << endl << "\t------- Banca " << aux->id_banca << " -------" << endl;

            // Encaminha o aux para o próximo
            aux = aux->prox;
        }
    }
}

void remover_banca(){
    if(inicio!=NULL){
        int banca_escolhida;
        cout << endl << "Qual banca será removida? ";
        cin >> banca_escolhida;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(banca_escolhida <= qtde_bancas && banca_escolhida > 0){
            cadastro_banca *lixo = inicio;
            if(inicio->id_banca == fim->id_banca){
                inicio = NULL;
                fim = NULL;
            }else{
                if(banca_escolhida == inicio->id_banca){
                    inicio->prox->ant = NULL;
                    inicio = inicio->prox;
                }else{
                    for(int i=0; i < (banca_escolhida-1); i++){
                        lixo = lixo->prox;
                    }
                    if(lixo->id_banca == fim->id_banca){
                        fim->ant->prox = NULL;
                        fim = fim->ant;
                    }else{
                        lixo->prox->ant = lixo->ant;
                        lixo->ant->prox = lixo->prox;
                        lixo->ant = NULL;
                        lixo->prox = NULL;
                    }
                }
            }
            // Libera a memória
            free(lixo);
            qtde_bancas--;

            // Diminui os id de cada banca
            cadastro_banca *aux = inicio;
            if(aux != NULL){
                if(banca_escolhida != (qtde_bancas+1)){
                    int atual = 1;
                    for(int i=0; i<qtde_bancas; i++){
                        aux->id_banca = atual;
                        atual++;
                        aux = aux->prox;
                    }
                }
            }
            cout << endl << banca_escolhida << "° banca removida!!\n" << endl; 
        }else{ // Banca com id errado
            cout << "\nNão há banca com esse número!\n";
        }
    }else{ // Lista vazia!
        cout << "\nNão há bancas cadastradas!\n";
    }
}

void atualizar_banca(){
    if(inicio != NULL){
        int atualizar, alternativa_escolhida;
        cout << "\nQual banca atualizar? ";
        cin >> atualizar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(atualizar <= qtde_bancas && atualizar > 0){
            cadastro_banca *aux = inicio;

            int contador = 0;
            for(int i=0; i<(atualizar-1);i++){
                contador++;
                aux = aux->prox;
            }

            int plano_fuga = 0;
            while (plano_fuga == 0){
                cout << "\n[1] Alunos\n[2] Avaliadores\n[3] Infos da banca\n[4] Finalizar\nDigite sua escolha: ";
                cin >> alternativa_escolhida;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (alternativa_escolhida){
                    // Atualiza os dados sobre alunos
                    case (1):
                        // Numera quantos alunos serão adicionados

                        // Aloca memória para alunos
                        aux->alunos = (struct alunos *) malloc(sizeof(struct alunos));

                        cout << "\t\tAluno" << endl;
                        cout << "Nome..........: ";
                        cin.getline(aux->alunos->nome_aluno, 50);
                        cout << "Matrícula.....: ";
                        cin >> aux->alunos->matricula_aluno;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Curso.........: ";
                        cin.getline(aux->alunos->curso_aluno, 50);
                        cout << "Email.........: ";
                        cin.getline(aux->alunos->email_aluno, 50);
                        break;

                    // Atualiza os dados sobre avaliadores
                    case (2):
                        // Numera quantos avaliadores serão adiocnados
                        cout << "\nAcrescentará quantos avaliadores? ";
                        cin >> aux->qtde_avaliadores;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        // Aloca memória para avaliadores
                        aux->avaliadores = (struct avaliador *) malloc(aux->qtde_avaliadores*sizeof(struct avaliador));

                        for(int i=0; i < aux->qtde_avaliadores; i++){
                            int i_mais_um = i+1;
                            cout << "\nAvaliador " << i_mais_um << endl;
                            cout << "Nome..........: ";
                            cin.getline(aux->avaliadores[i].nome_avaliador, 50);
                            cout << "Instituição...: ";
                            cin.getline(aux->avaliadores[i].instituicao, 50);
                            cout << "Email.........: ";
                            cin.getline(aux->avaliadores[i].email_avaliador, 50);
                            aux->avaliadores[i].ordem_avaliador = i_mais_um;
                        }
                        break;

                    // Atualiza os dados sobre a banca
                    case (3):
                        aux->banca_info = (dados_banca *) malloc(sizeof(dados_banca));

                        cout << "\nDados da banca" << endl;
                        cout << "Título......: ";
                        cin.getline(aux->banca_info->titulo_banca, 50);
                        cout << "Resumo......: ";
                        cin.getline(aux->banca_info->resumo, 50);
                        cout << "Orientador..: ";
                        cin.getline(aux->banca_info->orientador, 50);


                        break;

                    case (4):
                        cout << "\nConcluído!\n";
                        plano_fuga++;
                        break;
                    
                    default:
                        cout << "\nOperação de atualização inválida!\n";
                        break;
                }
            }
        }else{ // Caso a banca escolhida não exista
            cout << "\nNão há banca com esse número!\n";
        }
    }else{ // Lista vazia!
        cout << "\nNão há bancas cadastradas!\n";
    }
}

#endif // FUNCOES_H_INCLUDED
