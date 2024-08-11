#include "Mecanico.h"

using namespace std;

Mecanico::Mecanico(const string &nome, const string &senha, vector<OrdemDeServico> *ordens)
    : Funcionario(nome, senha), ordens(ordens) {}

// metodo para visualizar apenas ordens abertas e sem orcamento
void Mecanico::visualizarOrdens() const
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Mecanico  " << endl;
    cout << "Ordens de Servico Pendentes de Orcamento  " << endl;
    cout << "----------------------------------------\n"<< endl;
    // for percorrendo todo o vetor com ordens de servico
    for (size_t i = 0; i < ordens->size(); i++)
    {
        // imprimindo apenas as ordens abertas e sem orcamento
        if (!(*ordens)[i].isOrdemFechada() && !(*ordens)[i].isOrcamentoFeito())
        {
            quantidade++;
            cout << quantidade << ". " << "Pedido: " << (*ordens)[i].getPedido() << endl;
            cout << "Cliente: " << (*ordens)[i].getCliente().getNome() << endl;
            cout << " - Modelo do carro: " << (*ordens)[i].getCliente().getCarro().getModelo() << endl;
            cout << " - Placa: " << (*ordens)[i].getCliente().getCarro().getPlaca() << endl;
            cout << " - Kilometragem: " << (*ordens)[i].getCliente().getCarro().getKilometragem() << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    if (quantidade == 0)
    {
        cout << "No momento, nao existem ordens de servico pendentes de orcamento!\n" << endl;
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
    }
}

void Mecanico::gerarOrcamento()
{
    // visualiza as ordens em aberto
    visualizarOrdens();

    // verifica se ha ordens abertas e sem orcamento
    int quantidade = 0;
    for (size_t i = 0; i < ordens->size(); i++)
    {
        if (!(*ordens)[i].isOrdemFechada() && !(*ordens)[i].isOrcamentoFeito())
        {
            quantidade++;
        }
    }

    // caso nao existam, funcao encerra
    if (quantidade == 0)
    {
        return;
    }

    // selecionar a ordem para gerar o orcamento
    int opcao;
    cout << "Escolha a ordem de servico para gerar o orcamento (digite o numero): ";
    cin >> opcao;

    while (opcao < 1 || opcao > quantidade)
    {
        cout << "Digite uma ordem valida. Tente novamente: ";
        cin >> opcao;
    }

    // achando a posicao no vetor da ordem aberta escolhida
    int posicaoVetor = 0, k = 0;
    for (size_t i = 0; i < ordens->size(); i++)
    {

        if (!(*ordens)[i].isOrdemFechada() && !(*ordens)[i].isOrcamentoFeito())
        {
            k++;
        }
        if (k == opcao)
        {
            posicaoVetor = i;
            break;
        }
    }

    // Inserir pecas necessarias
    string nomePeca;
    float precoPeca;
    char adicionarPeca = 's';
    cout << "\nPecas Necessarias";
    while (adicionarPeca == 's')
    {
        cout << "Informe o nome da peca: ";
        cin.ignore();
        getline(cin, nomePeca);
        cout << "Informe o preco da peca: ";
        cin >> precoPeca;
        (*ordens)[posicaoVetor].getPecas().push_back(Peca(nomePeca, precoPeca));

        cout << "Deseja adicionar outra peca? (s/n): ";
        cin >> adicionarPeca;
    }
    // Inserir servicos necessarios
    string nomeServico;
    float precoServico;
    char adicionarServico = 's';
    cout << "\nServicos Necessarios";
    while (adicionarServico == 's')
    {
        cout << "Informe o nome do servico: ";
        cin.ignore();
        getline(cin, nomeServico);
        cout << "Informe o preco do servico: ";
        cin >> precoServico;
        (*ordens)[posicaoVetor].getServicos().push_back(Servicos(nomeServico, precoServico));
        cout << "Deseja adicionar outro servico? (s/n): ";
        cin >> adicionarServico;
    }
    // Calcular o valor total do orcamento
    double valorTotal = 0.0;
    for (auto &peca : (*ordens)[posicaoVetor].getPecas())
    {
        valorTotal += peca.getPreco();
    }
    for (auto &servico : (*ordens)[posicaoVetor].getServicos())
    {
        valorTotal += servico.getPreco();
    }

    (*ordens)[posicaoVetor].setValorOrcamento(valorTotal);

    cout << "\nOrcamento gerado com sucesso! Valor total: R$ " << fixed << setprecision(2) << (*ordens)[posicaoVetor].getValorOrcamento() << endl;
    (*ordens)[posicaoVetor].setOrcamentoFeito(true);

    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}

void Mecanico::realizarServico()
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Mecanico  " << endl;
    cout << "    Servicos Pendentes de Execucao" << endl;
    cout << "----------------------------------------" << endl;

    for (size_t i = 0; i < ordens->size(); i++)
    {
        // impressao de todas as ordens que ja possuem orcamento
        if (!(*ordens)[i].isOrdemFechada() && (*ordens)[i].isOrcamentoAprovado() && !(*ordens)[i].isServicoConcluido() && (*ordens)[i].isOrcamentoFeito())
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
        cout << "\nNo momento, nao existem servicos pendentes de execucao!" << endl;
        cout << "\nPressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
        return;
    }

    // selecionar a ordem para gerar o orcamento
    int opcao;
    cout << "Selecione o pedido pendente para ser executado: " << endl;
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
        if (!(*ordens)[i].isOrdemFechada() && (*ordens)[i].isOrcamentoAprovado() && (*ordens)[i].isOrcamentoFeito() && !(*ordens)[i].isServicoConcluido())
        {
            k++;
        }
        if (k == opcao)
        {
            posicaoVetor = i;
            break;
        }
    }

    (*ordens)[posicaoVetor].setServicoConcluido(true);
    cout << "\nO servico foi executado com sucesso!\n";
    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    cin.ignore();
    getline(cin, lixo);
}

void Mecanico::menu() 
{
    cout << "----------------------------------------" << endl;
    cout << "              Menu Mecanico  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "1. Visualizar Ordens de servico\n2. Gerar Orcamento\n3. Realizar servicos\n4. Sair\nEscolha: ";
    int opcao;
    cin >> opcao;
    switch (opcao)
    {
    case 1:
        printf("\ec\e[3j");
        visualizarOrdens();
        printf("\ec\e[3j");
        menu();
        break;
    case 2:
        printf("\ec\e[3j");
        gerarOrcamento();
        printf("\ec\e[3j");
        menu();
        break;
    case 3:
        printf("\ec\e[3j");
        realizarServico();
        printf("\ec\e[3j");
        menu();
        break;
    default:
        printf("\ec\e[3j");
        break;
    }
}