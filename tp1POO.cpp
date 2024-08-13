#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Pessoa.h"
#include "Carro.h"
#include "Peca.h"
#include "Servicos.h"
#include "Cliente.h"
#include "OrdemDeServico.h"
#include "Funcionario.h"
#include "Vendedor.h"
#include "Mecanico.h"
#include "Administrador.h"

using namespace std;

int main()
{
    // limpa a tela logo ao iniciar o programa
    printf("\ec\e[3j");

    // inicializacao de vetor para armazenar clientes
    vector<Cliente> clientes;

    // inicializacao de vetor de ordens de servico
    vector<OrdemDeServico> ordens;

    // inicializacao de um administrador
    Administrador admin("admin", "admin123");

    // inicializacao de vetor com tres vendedores
    vector<Vendedor> vendedores;
    Vendedor vendedor1("vendedor1", "vend123", &clientes, &ordens);
    Vendedor vendedor2("vendedor2", "vend123", &clientes, &ordens);
    Vendedor vendedor3("vendedor3", "vend123", &clientes, &ordens);
    vendedores.push_back(vendedor1);
    vendedores.push_back(vendedor2);
    vendedores.push_back(vendedor3);

    // adiciona os vendedores para o controle do administrador
    for (size_t i = 0; i < vendedores.size(); i++)
    {
        admin.adicionarVendedor(&(vendedores[i]));
    }

    // inicializacao de vetor com dois mecanicos
    vector<Mecanico> mecanicos;
    Mecanico mecanico1("mecanico1", "mec123", &ordens);
    Mecanico mecanico2("mecanico2", "mec123", &ordens);
    mecanicos.push_back(mecanico1);
    mecanicos.push_back(mecanico2);

    // adiciona os mecanicos para o controle do administrador
    for (size_t i = 0; i < mecanicos.size(); i++)
    {
        admin.adicionarMecanico(&(mecanicos[i]));
    }

    // laco para o menu de login
    while (true)
    {
        printf("\ec\e[3j");
        cout << "----------------------------------------" << endl;
        cout << "         Bem-vindo a Mecanica" << endl;
        cout << "----------------------------------------\n"
             << endl;

        // variavel que controla o login
        bool verifica = false;

        // pedindo uma opcao e validando
        string input;
        int numero;
        cout << "1. Login\n2. Sair\nEscolha: ";
        while (true) {
            getline(cin, input);
            try {
                numero = stoi(input); // tenta converter o input para inteiro
                if (numero == 1 || numero == 2) {
                    break; // se for valido, sai do loop
                } else {
                    cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
                }
            } catch (invalid_argument &e) {
                cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
            }
        }

        // caso opcao = 2 finaliza o programa
        if (numero == 2) {
            printf("\ec\e[3j");
            cout << "----------------------------------------------" << endl;
            cout << "Obrigado por utilizar os servicos da mecanica!" << endl;
            cout << "----------------------------------------------\n" << endl;
            break;
        }

        // caso seja 1, menu de login
        printf("\ec\e[3j");
        cout << "----------------------------------------" << endl;
        cout << "             Menu de login" << endl;
        cout << "----------------------------------------\n"
             << endl;
        string nome, senha;
        cout << "Nome: ";
        getline(cin, nome);
        cout << "Senha: ";
        getline(cin, senha);
        printf("\ec\e[3j");

        // verificando se o login equivale ao do admin
        if (nome == admin.getNome() && admin.verificarSenha(senha))
        {
            verifica = true;
            admin.menu();
        }

        // verificando se o login equivale a algum dos vendedores
        for (size_t i = 0; i < vendedores.size(); i++)
        {
            if (nome == vendedores[i].getNome() && vendedores[i].verificarSenha(senha))
            {
                vendedores[i].menu();
                verifica = true;
            }
        }

        // verificando se o login equivale a algum dos mecanicos
        for (size_t i = 0; i < mecanicos.size(); i++)
        {
            if (nome == mecanicos[i].getNome() && mecanicos[i].verificarSenha(senha))
            {
                mecanicos[i].menu();
                verifica = true;
            }
        }

        // caso login nao bata com o de ninguem
        if (verifica == false)
        {
            cout << "Login invalido!" << endl;
            cout << "Pressione 1 para voltar ao menu." << endl;
            string lixo;
            getline(cin, lixo);
        }
    }
    return 0;
}