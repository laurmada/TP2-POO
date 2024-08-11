#include "Vendedor.h"
#include <iostream>

using namespace std;

// construtor
Vendedor::Vendedor(const string &nome, const string &senha, vector<Cliente> *clientes, vector<OrdemDeServico> *ordens)
        : Funcionario(nome, senha), clientes(clientes), ordens(ordens) {}

// metodos
void Vendedor::cadastrarCliente()
{
    printf("\ec\e[3j");
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "           Cadastrar Cliente  " << endl;
    cout << "----------------------------------------" << endl;
    string nome, modelo, placa;
    float kilometragem;
    cout << "\nPreencha os campos abaixo com as informacoes do cliente:" << endl;
    cout << "Nome do cliente: ";
    cin >> nome;
    cout << "Modelo do veiculo: ";
    cin >> modelo;
    cout << "Placa do veiculo: ";
    cin >> placa;
    cout << "Kilometragem do veiculo: ";
    cin >> kilometragem;
    Cliente novoCliente(nome, modelo, placa, kilometragem);
    clientes->push_back(novoCliente);
    cout << "Cliente cadastrado: " << novoCliente.getNome() << endl;
}

void Vendedor::gerarOrdemDeServico()
{
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "         Gerar Ordem de Servico  " << endl;
    cout << "----------------------------------------\n"<< endl;
    if (clientes->size()==0){
        cout << "Nao ha clientes cadastrados!" << endl;
        cout << "\nPressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
        return;
    }
    string pedido;
    int cliente;
    cout << "Selecione um cliente dentre os cadastrados:" << endl;
    for (size_t i = 0; i < clientes->size(); i++)
    {
        cout << i + 1 << ". " << (*clientes)[i].getNome() << endl;
    }
    cin >> cliente;
    while (cliente < 1 || cliente > static_cast<int>(clientes->size()))
    {
        cout << "Digite um cliente valido!" << endl;
        cin >> cliente;
    }
    cout << "Preencha os campos abaixo com as informacoes da ordem:" << endl;
    cout << "Pedido: ";
    cin.ignore();         // Ignorar o caractere de nova linha deixado por cin
    getline(cin, pedido); // Lê a linha inteira incluindo espaços
    OrdemDeServico novaOrdem(pedido, (*clientes)[cliente - 1]);
    ordens->push_back(novaOrdem);
    cout << "Ordem Gerada: " << novaOrdem.getPedido() << endl;
}

void Vendedor::aprovarOrcamento() const
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "           Aprovar Orcamentos" << endl;
    cout << "----------------------------------------" << endl;

    for (size_t i = 0; i < ordens->size(); i++)
    {
        // impressao de todas as ordens que ja possuem orcamento
        if (!(*ordens)[i].isOrdemFechada() && !(*ordens)[i].isOrcamentoAprovado() && !(*ordens)[i].isServicoConcluido() && (*ordens)[i].isOrcamentoFeito())
        {
            quantidade++;
            cout << quantidade << "." << " Pedido: " << (*ordens)[i].getPedido() << endl;
            cout << " - Preco do Orcamento: R$ " << fixed << setprecision(2) << (*ordens)[i].getValorOrcamento() << endl;
            cout << "Aprovado: " << ((*ordens)[i].isOrcamentoAprovado() ? "Sim" : "Nao") << endl;
            cout << "Concluido: " << ((*ordens)[i].isServicoConcluido() ? "Sim" : "Nao") << endl;
            cout << "Cliente: " << (*ordens)[i].getCliente().getNome() << endl;
            cout << "Carro: " << (*ordens)[i].getCliente().getCarro().getModelo()
                    << " - Placa: " << (*ordens)[i].getCliente().getCarro().getPlaca()
                    << " - Kilometragem: " << (*ordens)[i].getCliente().getCarro().getKilometragem() << endl;
            cout << "Pecas:" << endl;
            if ((*ordens)[i].getPecas().empty())
            {
                cout << "Nenhuma peca cadastrada." << endl;
            }
            else
            {
                for (auto &peca : (*ordens)[i].getPecas())
                {
                    cout << " - " << peca.getNome() << " - R$ " << fixed << setprecision(2) << peca.getPreco() << endl;
                }
            }
            cout << "Servicos:" << endl;
            if ((*ordens)[i].getServicos().empty())
            {
                cout << "Nenhum servico cadastrado." << endl;
            }
            else
            {
                for (auto &servico : (*ordens)[i].getServicos())
                {
                    cout << " - " << servico.getNome() << " - R$ " << fixed << setprecision(2) << servico.getPreco() << endl;
                }
            }
            cout << "-----------------------------" << endl;
        }
    }

    // caso nao existam, funcao encerra
    if (quantidade == 0)
    {
        cout << "No momento, nao ha ordens de servico orcadas!" << endl;
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
        return;
    }

    // selecionar a ordem para gerar o orcamento
    int opcao;
    cout << "Selecione o pedido para aprovar ou recusar o orcamento: " << endl;
    cin >> opcao;

    while (opcao < 1 || opcao > quantidade)
    {
        cout << "Digite um pedido valida. Tente novamente ";
        cin >> opcao;
    }

    // achando a posicao no vetor da ordem aberta escolhida
    int posicaoVetor = 0, k = 0;
    for (size_t i = 0; i < ordens->size(); i++)
    {
        if (!(*ordens)[i].isOrdemFechada() && !(*ordens)[i].isOrcamentoAprovado() && (*ordens)[i].isOrcamentoFeito() && !(*ordens)[i].isServicoConcluido())
        {
            k++;
        }
        if (k == opcao)
        {
            posicaoVetor = i;
            break;
        }
    }
    // VALIDAR CASO O USUARIO DIGITE UMA STRING
    cout << "Voce deseja aprovar (1) ou recusar (2) o orcamento " << endl;
    cin >> opcao;
    while (opcao < 1 || opcao > 2)
    {
        cout << "Digite uma opcao valida! Tente novamente: ";
        cin >> opcao;
    }

    if (opcao == 1)
    {
        (*ordens)[posicaoVetor].setOrcamentoAprovado(true);
        cout << "O orcamento foi aprovado com sucesso!\n";
    }
    else
    {
        (*ordens)[posicaoVetor].setOrdemFechada(true);
        cout << "O orcamento foi recusado e a ordem fechada.\n";
    }

    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}

void Vendedor::fecharOrdens()
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "        Fechar ordens de servico" << endl;
    cout << "----------------------------------------" << endl;

    for (size_t i = 0; i < ordens->size(); i++)
    {
        // impressao de todas as ordens que estao abertas
        if (!(*ordens)[i].isOrdemFechada())
        {
            quantidade++;
            cout << quantidade << "." << " Pedido: " << (*ordens)[i].getPedido() << endl;
            cout << " - Preco do Orcamento: R$ " << fixed << setprecision(2) << (*ordens)[i].getValorOrcamento() << endl;
            cout << "Cliente: " << (*ordens)[i].getCliente().getNome() << endl;
            cout << "Carro: " << (*ordens)[i].getCliente().getCarro().getModelo()
                    << " - Placa: " << (*ordens)[i].getCliente().getCarro().getPlaca()
                    << " - Kilometragem: " << (*ordens)[i].getCliente().getCarro().getKilometragem() << endl;
            cout << "Pecas Necessarias:" << endl;
            if ((*ordens)[i].getPecas().empty())
            {
                cout << "Nenhuma peca cadastrada." << endl;
            }
            else
            {
                for (auto &peca : (*ordens)[i].getPecas())
                {
                    cout << " - " << peca.getNome() << " - R$ " << fixed << setprecision(2) << peca.getPreco() << endl;
                }
            }
            cout << "Servicos:" << endl;
            if ((*ordens)[i].getServicos().empty())
            {
                cout << "Nenhum servico cadastrado." << endl;
            }
            else
            {
                for (auto &servico : (*ordens)[i].getServicos())
                {
                    cout << " - " << servico.getNome() << " - R$ " << fixed << setprecision(2) << servico.getPreco() << endl;
                }
            }
            cout << "-----------------------------" << endl;
        }
    }
    // caso nao existam, funcao encerra
    if (quantidade == 0)
    {
        cout << "Nao existem ordens abertas!" << endl;
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
        return;
    }
    int opcao;
    // selecionar a ordem para fechar
    cout << "Selecione o pedido para fecha-lo: " << endl;
    cin >> opcao;

    while (opcao < 1 || opcao > quantidade)
    {
        cout << "Digite um pedido valido. Tente novamente: ";
        cin >> opcao;
    }

    // achando a posicao no vetor da ordem aberta escolhida
    int posicaoVetor = 0, k = 0;
    for (size_t i = 0; i < ordens->size(); i++)
    {
        if (!(*ordens)[i].isOrdemFechada())
        {
            k++;
        }
        if (k == opcao)
        {
            posicaoVetor = i;
            break;
        }
    }

    (*ordens)[posicaoVetor].setOrdemFechada(true);
    cout << "A ordem foi fechada com sucesso!\n";
    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}

void Vendedor::gerarHistoricoVeiculo()
{
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "        Gerar Historico de Veiculo  " << endl;
    cout << "----------------------------------------" << endl;
    string nome, placa;
    cout << "Digite o nome do cliente: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Digite a placa do veiculo que deseja gerar o historico: ";
    cin >> placa;

    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "         Historico do veiculo " << endl;
    cout << "Placa: " << placa << endl;
    cout << "Cliente: " << nome << endl;
    cout << "----------------------------------------" << endl;
    for (size_t i = 0; i < ordens->size(); i++)
    {
        // impressao de todas as ordens que estao abertas
        if ((*ordens)[i].getCliente().getNome() == nome && (*ordens)[i].getCliente().getCarro().getPlaca() == placa)
        {
            quantidade++;
            cout << quantidade << "." << " Pedido: " << (*ordens)[i].getPedido() << endl;
            cout << " - Preco do Orcamento: R$ " << fixed << setprecision(2) << (*ordens)[i].getValorOrcamento() << endl;
            cout << "Orcamento aprovado: " << ((*ordens)[i].isOrcamentoAprovado() ? "Sim" : "Nao") << endl;
            cout << "Concluido: " << ((*ordens)[i].isServicoConcluido() ? "Sim" : "Nao") << endl;
            cout << "Situacao do pedido: " << ((*ordens)[i].isOrdemFechada() ? "Fechada" : "Aberta") << endl;
            cout << "Cliente: " << (*ordens)[i].getCliente().getNome() << endl;
            cout << "Carro: " << (*ordens)[i].getCliente().getCarro().getModelo()
                    << " - Placa: " << (*ordens)[i].getCliente().getCarro().getPlaca()
                    << " - Kilometragem: " << (*ordens)[i].getCliente().getCarro().getKilometragem() << endl;
            cout << "Pecas Necessarias:" << endl;
            if ((*ordens)[i].getPecas().empty())
            {
                cout << "Nenhuma peca cadastrada." << endl;
            }
            else
            {
                for (auto &peca : (*ordens)[i].getPecas())
                {
                    cout << " - " << peca.getNome() << " - R$ " << fixed << setprecision(2) << peca.getPreco() << endl;
                }
            }
            cout << "Servicos:" << endl;
            if ((*ordens)[i].getServicos().empty())
            {
                cout << "Nenhum servico cadastrado." << endl;
            }
            else
            {
                for (auto &servico : (*ordens)[i].getServicos())
                {
                    cout << " - " << servico.getNome() << " - R$ " << fixed << setprecision(2) << servico.getPreco() << endl;
                }
            }
            cout << "-----------------------------" << endl;
        }
    }

    if (quantidade == 0)
    {
        cout << "O veiculo nao possui historico." << endl;
    }
    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}

void Vendedor::menu()
{
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "1. Cadastrar Cliente\n2. Gerar Ordem de Servico\n3. Aprovar ou recusar orcamentos\n4. Fechar ordens de servico\n5. Gerar historico de veiculo\n6. Sair\nEscolha: ";
    int opcao;
    cin >> opcao;
    printf("\ec\e[3j");
    switch (opcao)
    {
    case 1:
        do
        {
            cadastrarCliente();
            cout << "\nDigite 1 para cadastrar outro cliente ou 0 para sair: " << endl;
            cin >> opcao;
        } while (opcao == 1);
        printf("\ec\e[3j");
        menu();
        break;
    case 2:
        printf("\ec\e[3j");
        if (clientes->size() == 0)
        {
            gerarOrdemDeServico();
            break;
        }
        else
        {
            do
            {
                gerarOrdemDeServico();
                cout << "\nDigite 1 para gerar outra ordem de servico ou 0 para sair: " << endl;
                cin >> opcao;
            } while (opcao == 1);
        }
        printf("\ec\e[3j");
        menu();
        break;
    case 3:
        aprovarOrcamento();
        printf("\ec\e[3j");
        menu();
        break;
    case 4:
        fecharOrdens();
        printf("\ec\e[3j");
        menu();
        break;
    case 5:
        gerarHistoricoVeiculo();
        printf("\ec\e[3j");
        menu();
        break;
    default:
        break;
    }
}

