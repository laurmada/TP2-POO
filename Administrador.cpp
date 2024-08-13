#include "Administrador.h"

using namespace std;

Administrador::Administrador(const string &nome, const string &senha) : Funcionario(nome, senha) {}

// metodo para inserir um vendedor ao controle do funcionario
void Administrador::adicionarVendedor(Funcionario *funcionario)
{
    vendedores.push_back(funcionario);
}

// metodo para inserir um mecanico ao controle do funcionario
void Administrador::adicionarMecanico(Funcionario *funcionario)
{
    mecanicos.push_back(funcionario);
}

// metodo que altera os dados de um vendedor
void Administrador::alterarDadosVendedor()
{
    cout << "----------------------------------------" << endl;
    cout << "           Menu Administrador  " << endl;
    cout << "        Alterar Dados Vendedor  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "Alterar dados de qual funcionario?\n";
    // imprime todos os vendedores
    for (size_t i = 0; i < vendedores.size(); ++i)
    {
        cout << i + 1 << ". " << vendedores[i]->getNome() << endl;
    }

    // validacao da escolha do vendedor
    int opcao;
    cout << "\nEscolha o numero do funcionario: ";
    string input;
    while (true) {
        getline(cin, input);

        try {
            opcao = stoi(input); // tenta converter para um inteiro
            if (opcao > 0 && opcao <= static_cast<int>(vendedores.size())) {
                break; // se valido, sai do loop
            } else {
                cout << "Numero invalido! Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    Funcionario *funcionarioSelecionado = vendedores[opcao - 1];

    // validacao da escolha do que fazer
    cout << "\n1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
    int escolha;
    while (true) {
        getline(cin, input);

        try {
            escolha = stoi(input); // Tenta converter a string para um inteiro
            if (escolha == 1 || escolha == 2) {
                break; // Se o número for válido, sai do loop
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }

    if (escolha == 1) // troca o nome
    {
        string novoNome;
        cout << "\nNovo nome: ";
        getline(cin, novoNome);
        funcionarioSelecionado->setNome(novoNome);
        cout << "\nNome alterado com sucesso!" << endl;
    }
    else if (escolha == 2) // troca a senha
    {
        string novaSenha;
        cout << "\nNova senha: ";
        getline(cin, novaSenha);
        funcionarioSelecionado->setSenha(novaSenha);
        cout << "Senha alterada com sucesso!" << endl;
    }
    cout << "\nPressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// metodo que altera os dados de um mecanico, identico ao vendedor
void Administrador::alterarDadosMecanico()
{
    cout << "----------------------------------------" << endl;
    cout << "           Menu Administrador  " << endl;
    cout << "        Alterar Dados Mecanico  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "Alterar dados de qual funcionario?\n";

    // imprime todos os mecanicos
    for (size_t i = 0; i < mecanicos.size(); ++i)
    {
        cout << i + 1 << ". " << mecanicos[i]->getNome() << endl;
    }

    // validacao da escolha do vendedor
    int opcao;
    cout << "\nEscolha o numero do funcionario: ";
    string input;
    while (true) {
        getline(cin, input);
        try {
            opcao = stoi(input); 
            if (opcao > 0 && opcao <= static_cast<int>(mecanicos.size())) {
                break; 
            } else {
                cout << "Numero invalido! Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    Funcionario *funcionarioSelecionado = mecanicos[opcao - 1];

    // validacao da escolha do que fazer
    cout << "\n1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
    int escolha;
    while (true) {
        getline(cin, input);

        try {
            escolha = stoi(input); 
            if (escolha == 1 || escolha == 2) {
                break;
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }

    if (escolha == 1) // troca o nome
    {
        string novoNome;
        cout << "\nNovo nome: ";
        getline(cin, novoNome);
        funcionarioSelecionado->setNome(novoNome);
        cout << "\nNome alterado com sucesso!" << endl;
    }
    else if (escolha == 2) // troca a senha
    {
        string novaSenha;
        cout << "\nNova senha: ";
        getline(cin, novaSenha);
        funcionarioSelecionado->setSenha(novaSenha);
        cout << "\nSenha alterada com sucesso!" << endl;
    }
    cout << "\nPressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// menu do administrador
void Administrador::menu() 
{
    cout << "----------------------------------------" << endl;
    cout << "           Menu Administrador  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "1. Editar dados de Vendedores\n2. Editar dados de Mecanicos \n3. Sair\nEscolha: ";
    int opcao;
    string input;
    while (true) {
        getline(cin, input);
        try {
            opcao = stoi(input); // tenta converter string para inteiro
            if (opcao == 1 || opcao == 2 || opcao == 3) {
                break; // se opcao valida, sai do loop
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1, 2 ou 3. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    if (opcao == 1) // chama metodo para editar dados de vendedores
    {
        printf("\ec\e[3j");
        alterarDadosVendedor();
        printf("\ec\e[3j");
        menu();
    }
    else if (opcao == 2) // chama metodo para editar dados de mecanicos
    {
        printf("\ec\e[3j");
        alterarDadosMecanico();
        printf("\ec\e[3j");
        menu();
    }
    else // sai da conta de administrador
    {
        printf("\ec\e[3j");
        return;
    }
}
