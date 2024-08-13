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
    // caso nao hajam ordens, imprime uma mensagem de aviso
    if (quantidade == 0)
    {
        cout << "No momento, nao existem ordens de servico pendentes de orcamento!\n" << endl;
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        getline(cin, lixo);
    } else {
    cout << "Pressione 1 para continuar." << endl;
    string lixo;
    getline(cin, lixo);
    }
}

// metodo para gerar o orcamento de uma ordem de servico
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

    // selecionar a ordem para gerar o orcamento e realizar a validacao
    int opcao;
    cout << "Escolha a ordem de servico para gerar o orcamento (digite o numero): ";
    string input;
    while (true) {
        getline(cin, input);

        try {
            opcao = stoi(input); // Tenta converter a string para um inteiro
            if (opcao > 0 && opcao <= quantidade) {
                break; // Se o número for válido, sai do loop
            } else {
                cout << "Numero invalido! Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            // Se a conversão falhar (ou seja, a entrada não é um número válido)
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
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

    // inserir pecas necessarias
    string nomePeca;
    float precoPeca;
    char adicionarPeca = 's';
    cout << "\nPecas Necessarias";
    // loop para realizar a insercao de pecas
    while (adicionarPeca == 's') {
        cout << "\nInforme o nome da peca: ";
        getline(cin, nomePeca);
        
        cout << "Informe o preco da peca: ";
        // validacao do preco como um float
        while (true) {
            string input;
            getline(cin, input);

            try {
                precoPeca = stof(input); 
                break; 
            } catch (invalid_argument &) {
                cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
            }
        }
        // adiciona a peca ao vetor de pecas
        (*ordens)[posicaoVetor].getPecas().push_back(Peca(nomePeca, precoPeca));

        cout << "\nDeseja adicionar outra peca? (s/n): ";
        // validacao da resposta: usuario so pode digitar s ou n
        while (true) {
            string input;
            getline(cin, input);
            if (input.length() == 1 && (input[0] == 'n' || input[0] == 's')) {
                adicionarPeca = input[0];
                break; 
            } else {
                cout << "Entrada invalida. Tente novamente: ";
            }
        }
    }

    // inserir servicos necessarios
    string nomeServico;
    float precoServico;
    char adicionarServico = 's';
    cout << "\nServicos Necessarios";
    // loop para realizar a insercao de servicos
    while (adicionarServico == 's')
    {
        cout << "\nInforme o nome do servico: ";
        getline(cin, nomeServico);

        cout << "Informe o preco do servico: ";
        // validacao do preco como um float
        while (true) {
            string input;
            getline(cin, input);

            try {
                precoServico = stof(input); 
                break; 
            } catch (invalid_argument &) {
                cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
            }
        }
        // adiciona o servico ao vetor de servicos
        (*ordens)[posicaoVetor].getServicos().push_back(Servicos(nomeServico, precoServico));

        cout << "Deseja adicionar outro servico? (s/n): ";
        // validacao da resposta: usuario so pode digitar s ou n
        while (true) {
            string input;
            getline(cin, input);
            if (input.length() == 1 && (input[0] == 'n' || input[0] == 's')) {
                adicionarServico = input[0];
                break; 
            } else {
                cout << "Entrada invalida. Tente novamente: ";
            }
        }
    }

    // calculando o valor total do orcamento
    double valorTotal = 0.0;
    for (auto &peca : (*ordens)[posicaoVetor].getPecas())
    {
        valorTotal += peca.getPreco();
    }
    for (auto &servico : (*ordens)[posicaoVetor].getServicos())
    {
        valorTotal += servico.getPreco();
    }

    // setando o valor do orcamento
    (*ordens)[posicaoVetor].setValorOrcamento(valorTotal);

    cout << "\nOrcamento gerado com sucesso! Valor total: R$ " << fixed << setprecision(2) << (*ordens)[posicaoVetor].getValorOrcamento() << endl;
    // alterando a situacao do orcamento da ordem para feito
    (*ordens)[posicaoVetor].setOrcamentoFeito(true);

    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// metodo para realizar o servico
void Mecanico::realizarServico()
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Mecanico  " << endl;
    cout << "    Servicos Pendentes de Execucao" << endl;
    cout << "----------------------------------------" << endl;

    // iterando sobre o vetor de ordens
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
            if ((*ordens)[i].getPecas().empty()) // se nao houver pecas cadastradas
            {
                cout << "Nenhuma peca cadastrada." << endl;
            }
            else // imprime todas as pecas
            {
                for (auto &peca : (*ordens)[i].getPecas())
                {
                    cout << " - " << peca.getNome() << " - R$ " << fixed << setprecision(2) << peca.getPreco() << endl;
                }
            }
            cout << "Servicos:" << endl;
            if ((*ordens)[i].getServicos().empty()) // se nao houver servicos cadastrados
            {
                cout << "Nenhum servico cadastrado." << endl;
            }
            else // imprime todos os servicos
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
        getline(cin, lixo);
        return;
    }

    // selecionar e validar a ordem para gerar o orcamento
    int opcao;
    cout << "Selecione o pedido pendente para ser executado: " << endl;
    string input;
    while (true) {
        getline(cin, input);

        try {
            opcao = stoi(input); 
            if (opcao > 0 && opcao <= quantidade) {
                break; 
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
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

    // alterando a situacao do servico da ordem para concluido
    (*ordens)[posicaoVetor].setServicoConcluido(true);
    cout << "\nO servico foi executado com sucesso!\n";
    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// metodo do menu do mecanico
void Mecanico::menu() 
{
    printf("\ec\e[3j");
    cout << "----------------------------------------" << endl;
    cout << "              Menu Mecanico  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "1. Visualizar Ordens de servico\n2. Gerar Orcamento\n3. Realizar servicos\n4. Sair\nEscolha: ";

    // validando a escolha do usuario
    int opcao;
    string input;
    while (true) {
        getline(cin, input);

        try {
            opcao = stoi(input); 
            if (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4) {
                break; 
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    switch (opcao)
    {
    case 1: // visualiza as ordens de servico
        printf("\ec\e[3j");
        visualizarOrdens();
        menu();
        break;
    case 2: // visualiza as ordens de servico e gera orcamento
        printf("\ec\e[3j");
        gerarOrcamento();
        menu();
        break;
    case 3: // realiza servicos
        printf("\ec\e[3j");
        realizarServico();
        menu();
        break;
    default: // volta ao menu principal do programa
        printf("\ec\e[3j");
        break;
    }
}