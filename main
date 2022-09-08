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

#include "funcoes.cpp"

int main()
{
    // Loop para rodar o sistema
    while(1){
        char escolha;
        printf("\n[C] Cadastrar\n[E] Exibir\n[A] Atualizar\n[R] Remover\n");
        printf("Escolha uma operação: ");
        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (escolha){
            case ('c'):
                adicionar_banca();
                break;

            case ('C'):
                adicionar_banca();
                break;

            case ('e'):
                imprimir_bancas();
                break;

            case ('E'):
                imprimir_bancas();
                break;

            case ('r'):
                remover_banca();
                break;

            case ('R'):
                remover_banca();
                break;

            case ('a'):
                atualizar_banca();
                break;

            case ('A'):
                atualizar_banca();
                break;

            default:
                cout << "\nOperação Inválida!\n";
                break;
        }
    }
}
