#include "Administrador.h"

using namespace std;

Administrador::Administrador(const string &nome, const string &senha) : Funcionario(nome, senha) {}

void Administrador::adicionarVendedor(Funcionario *funcionario)
{
    vendedores.push_back(funcionario);
}

void Administrador::adicionarMecanico(Funcionario *funcionario)
{
    mecanicos.push_back(funcionario);
}

void Administrador::alterarDadosVendedor()
{
    cout << "----------------------------------------" << endl;
    cout << "           Menu Administrador  " << endl;
    cout << "        Alterar Dados Vendedor  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "Alterar dados de qual funcionario?\n";
    for (size_t i = 0; i < vendedores.size(); ++i)
    {
        cout << i + 1 << ". " << vendedores[i]->getNome() << endl;
    }

    int opcao;
    cout << "\nEscolha o numero do funcionario: ";
    cin >> opcao;

    if (opcao < 1 || opcao > static_cast<int>(vendedores.size()))
    {
        cout << "Opcao invalida." << endl;
        return;
    }

    Funcionario *funcionarioSelecionado = vendedores[opcao - 1];

    cout << "\n1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
    int escolha;
    cin >> escolha;

    // cin.ignore(); // Limpar o buffer do newline

    if (escolha == 1)
    {
        string novoNome;
        cout << "\nNovo nome: ";
        cin.ignore();
        getline(cin, novoNome);
        funcionarioSelecionado->setNome(novoNome);
        cout << "\nNome alterado com sucesso!" << endl;
    }
    else if (escolha == 2)
    {
        string novaSenha;
        cout << "\nNova senha: ";
        cin.ignore();
        getline(cin, novaSenha);
        funcionarioSelecionado->setSenha(novaSenha);
        cout << "Senha alterada com sucesso!" << endl;
    }
    else
    {
        cout << "Opcao invalida." << endl;
    }
    cout << "\nPressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}
void Administrador::alterarDadosMecanico()
{
    cout << "----------------------------------------" << endl;
    cout << "           Menu Administrador  " << endl;
    cout << "        Alterar Dados Mecanico  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "Alterar dados de qual funcionario?\n";
    for (size_t i = 0; i < mecanicos.size(); ++i)
    {
        cout << i + 1 << ". " << mecanicos[i]->getNome() << endl;
    }

    int opcao;
    cout << "\nEscolha o numero do funcionario: ";
    cin >> opcao;

    if (opcao < 1 || opcao > static_cast<int>(mecanicos.size()))
    {
        cout << "Opcao invalida." << endl;
        return;
    }

    Funcionario *funcionarioSelecionado = mecanicos[opcao - 1];

    cout << "\n1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
    int escolha;
    cin >> escolha;

    // cin.ignore(); // Limpar o buffer do newline

    if (escolha == 1)
    {
        string novoNome;
        cout << "\nNovo nome: ";
        cin.ignore();
        getline(cin, novoNome);
        funcionarioSelecionado->setNome(novoNome);
        cout << "\nNome alterado com sucesso!" << endl;
    }
    else if (escolha == 2)
    {
        string novaSenha;
        cout << "\nNova senha: ";
        cin.ignore();
        getline(cin, novaSenha);
        funcionarioSelecionado->setSenha(novaSenha);
        cout << "\nSenha alterada com sucesso!" << endl;
    }
    else
    {
        cout << "Opcao invalida." << endl;
    }
    cout << "\nPressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}

void Administrador::menu() 
{
    cout << "----------------------------------------" << endl;
    cout << "           Menu Administrador  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "1. Editar dados de Vendedores\n2. Editar dados de Mecanicos \n3. Sair\nEscolha: ";
    int opcao;
    cin >> opcao;
    if (opcao == 1)
    {
        printf("\ec\e[3j");
        alterarDadosVendedor();
        printf("\ec\e[3j");
        menu();
    }
    else if (opcao == 2)
    {
        printf("\ec\e[3j");
        alterarDadosMecanico();
        printf("\ec\e[3j");
        menu();
    }
    else
    {
        printf("\ec\e[3j");
        return;
    }
}
