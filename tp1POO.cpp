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

    // inicializacao de vetor para armazenar clientes
    vector<Cliente> clientes;
    // inicializacao de vetor de ordens de servico
    vector<OrdemDeServico> ordens;

    printf("\ec\e[3j");
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

    // Adiciona os vendedores para o controle do administrador
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

    // Adiciona os mecanicos para o controle do administrador
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

        // variavel que controla a entrada
        bool verifica = false;
        cout << "1. Login\n2. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        if (opcao == 2) {
            printf("\ec\e[3j");
            cout << "----------------------------------------------" << endl;
            cout << "Obrigado por utilizar os servicos da mecanica!" << endl;
            cout << "----------------------------------------------\n" << endl;
            break;
        }

        // limpa o menu
        printf("\ec\e[3j");
        cout << "----------------------------------------" << endl;
        cout << "             Menu de login" << endl;
        cout << "----------------------------------------\n"
             << endl;
        string nome, senha;
        cout << "Nome: ";
        cin >> nome;
        cout << "Senha: ";
        cin >> senha;
        printf("\ec\e[3j");

        for (size_t i = 0; i < clientes.size(); i++)
        {
            cout << "Cliente: " << clientes[i].getNome() << endl;
            cout << "Carro: " << clientes[i].getCarro().getModelo()
                 << " - Placa: " << clientes[i].getCarro().getPlaca()
                 << " - Kilometragem: " << clientes[i].getCarro().getKilometragem() << endl;
            cout << "-----------------------------" << endl;
        }

        for (size_t i = 0; i < ordens.size(); i++)
        {
            cout << "Pedido: " << ordens[i].getPedido() << endl;
            cout << "Valor do Orcamento: R$ " << ordens[i].getValorOrcamento() << endl;
            cout << "Aprovado: " << (ordens[i].isOrcamentoAprovado() ? "Sim" : "Nao") << endl;
            cout << "Concluido: " << (ordens[i].isServicoConcluido() ? "Sim" : "Nao") << endl;
            cout << "Cliente: " << ordens[i].getCliente().getNome() << endl;
            cout << "Carro: " << ordens[i].getCliente().getCarro().getModelo()
                 << " - Placa: " << ordens[i].getCliente().getCarro().getPlaca()
                 << " - Kilometragem: " << ordens[i].getCliente().getCarro().getKilometragem() << endl;
            cout << "Pecas:" << endl;
            if (ordens[i].getPecas().empty())
            {
                cout << "Nenhuma peca cadastrada." << endl;
            }
            else
            {
                for (auto &peca : ordens[i].getPecas())
                {
                    cout << " - " << peca.getNome() << " - R$ " << fixed << setprecision(2) << peca.getPreco() << endl;
                }
            }

            cout << "Servicos:" << endl;
            if (ordens[i].getServicos().empty())
            {
                cout << "Nenhum servico cadastrado." << endl;
            }
            else
            {
                for (auto &servico : ordens[i].getServicos())
                {
                    cout << " - " << servico.getNome() << " - R$ " << fixed << setprecision(2) << servico.getPreco() << endl;
                }
            }
            cout << "-----------------------------" << endl;
        }

        // verificando se o login equivale ao do admin
        if (nome == admin.getNome() && admin.verificarSenha(senha))
        {
            verifica = true;
            admin.menu();
        }

        // verificando se o login equivale ao dos vendedores
        for (size_t i = 0; i < vendedores.size(); i++)
        {
            if (nome == vendedores[i].getNome() && vendedores[i].verificarSenha(senha))
            {
                vendedores[i].menu();
                verifica = true;
            }
        }

        // verificando se o login equivale ao dos mecanicos
        for (size_t i = 0; i < mecanicos.size(); i++)
        {
            if (nome == mecanicos[i].getNome() && mecanicos[i].verificarSenha(senha))
            {
                mecanicos[i].menu();
                verifica = true;
            }
        }

        if (verifica == false)
        {
            cout << "Login invalido!" << endl;
        }
    }


    return 0;
}