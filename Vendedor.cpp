#include "Vendedor.h"
#include <iostream>

using namespace std;

// construtor
Vendedor::Vendedor(const string &nome, const string &senha, vector<Cliente> *clientes, vector<OrdemDeServico> *ordens)
        : Funcionario(nome, senha), clientes(clientes), ordens(ordens) {}

// metodo para cadastrar um cliente
void Vendedor::cadastrarCliente()
{
    printf("\ec\e[3j");
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "           Cadastrar Cliente  " << endl;
    cout << "----------------------------------------" << endl;
    // pedindo informacoes do cliente
    string nome, modelo, placa;
    float kilometragem;
    cout << "\nPreencha os campos abaixo com as informacoes do cliente:" << endl;
    cout << "Nome do cliente: ";
    getline(cin, nome);
    cout << "Modelo do veiculo: ";
    getline(cin, modelo);
    cout << "Placa do veiculo: ";
    getline(cin, placa);
    cout << "Kilometragem do veiculo: ";
    // validacao da kilometragem como um float
    string input;
    while (true) {
        getline(cin, input);
        try {
            kilometragem = stof(input); 
            break;
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    Cliente novoCliente(nome, modelo, placa, kilometragem);
    // adiciona o cliente ao vetor de clientes
    clientes->push_back(novoCliente);
    cout << "Cliente cadastrado: " << novoCliente.getNome() << endl;
}

// metodo para gerar uma ordem de servico
void Vendedor::gerarOrdemDeServico()
{
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "         Gerar Ordem de Servico  " << endl;
    cout << "----------------------------------------\n"<< endl;
    // caso nao hajam clientes cadastrados, volta ao menu
    if (clientes->size()==0){
        cout << "Nao ha clientes cadastrados!" << endl;
        cout << "\nPressione 1 para voltar ao menu." << endl;
        string lixo;
        getline(cin, lixo);
        return;
    }
    string pedido;
    int cliente;
    // impressao dos clientes cadastrados
    cout << "Clientes cadastrados:" << endl;
    for (size_t i = 0; i < clientes->size(); i++)
    {
        cout << i + 1 << ". " << (*clientes)[i].getNome() << endl;
    }
    // validacao da selecao de cliente do usuario
    cout << "\nSelecione um cliente: ";
    string input;
    while (true) {
        getline(cin, input);

        try {
            cliente = stoi(input);
            if (cliente > 0 && cliente <= static_cast<int>(clientes->size())) {
                break; 
            } else {
                cout << "Numero invalido! Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    // le a ordem de servico, associa ao cliente e adiciona ao vetor de ordens
    cout << "\nPreencha os campos abaixo com as informacoes da ordem:" << endl;
    cout << "Pedido: ";
    getline(cin, pedido); 
    OrdemDeServico novaOrdem(pedido, (*clientes)[cliente - 1]);
    ordens->push_back(novaOrdem);
    cout << "Ordem Gerada: " << novaOrdem.getPedido() << endl;
}

// metodo para aprovar um orcamento gerado
void Vendedor::aprovarOrcamento() const
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "           Aprovar Orcamentos" << endl;
    cout << "----------------------------------------" << endl;

    // iteracao sobre todos os elementos do vetor de ordens
    for (size_t i = 0; i < ordens->size(); i++)
    {
        // impressao de todas as ordens abertas e que ja possuem orcamento
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

    // caso nao existam ordens com orcamento, funcao encerra
    if (quantidade == 0)
    {
        cout << "No momento, nao ha ordens de servico orcadas!" << endl;
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        getline(cin, lixo);
        return;
    }

    // selecionar a ordem para gerar o orcamento
    int opcao;
    cout << "Selecione o pedido para aprovar ou recusar o orcamento: " << endl;
    // validacao da ordem escolhida pelo usuario
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

    // validando a escolha do usuario, ele so pode digitar 1 ou 2
    cout << "Voce deseja aprovar (1) ou recusar (2) o orcamento? ";
    while (true) {
        getline(cin, input);

        try {
            opcao = stoi(input); 
            if (opcao == 1 || opcao == 2) {
                break; 
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }

    if (opcao == 1) // aprova o orcamento, alterando o atributo
    {
        (*ordens)[posicaoVetor].setOrcamentoAprovado(true);
        cout << "O orcamento foi aprovado com sucesso!\n";
    }
    else // reprova o orcamento, alterando o atributo
    {
        (*ordens)[posicaoVetor].setOrdemFechada(true);
        cout << "O orcamento foi recusado e a ordem fechada.\n";
    }

    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// metodo para fechar uma ordem
void Vendedor::fecharOrdens()
{
    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "        Fechar ordens de servico" << endl;
    cout << "----------------------------------------" << endl;

    // iteracao sobre todas as ordens
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

    // caso nao existam ordens abertas, funcao encerra
    if (quantidade == 0)
    {
        cout << "Nao existem ordens abertas!" << endl;
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        getline(cin, lixo);
        return;
    }

    // selecionando uma ordem para ser fechada e realizando a validacao
    int opcao;
    cout << "Selecione o pedido para fecha-lo: " << endl;
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

    // alterando o atributo da ordem para indicar que foi fechada
    (*ordens)[posicaoVetor].setOrdemFechada(true);
    cout << "A ordem foi fechada com sucesso!\n";
    cout << "Pressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// metodo que gera o historico de ordens de um veiculo
void Vendedor::gerarHistoricoVeiculo()
{
    // menus e solicitacao dos dados do veiculo escolhido ao usuario
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "        Gerar Historico de Veiculo  " << endl;
    cout << "----------------------------------------" << endl;
    string nome, placa;
    cout << "Digite o nome do cliente: ";
    getline(cin, nome);
    cout << "Digite a placa do veiculo que deseja gerar o historico: ";
    getline(cin, placa);

    int quantidade = 0;
    cout << "----------------------------------------" << endl;
    cout << "         Historico do veiculo " << endl;
    cout << "Placa: " << placa << endl;
    cout << "Cliente: " << nome << endl;
    cout << "----------------------------------------" << endl;

    // percorrendo todo o vetor de ordens
    for (size_t i = 0; i < ordens->size(); i++)
    {
        // impressao de todas as ordens que possuem o cliente e placa iguais ao solicitado
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

    // caso nao tenham sido encontradas ordens, o veiculo nao possui historico
    if (quantidade == 0)
    {
        cout << "O veiculo nao possui historico." << endl;
        cout << "----------------------------------------";

    }

    cout << "\nPressione 1 para voltar ao menu." << endl;
    string lixo;
    getline(cin, lixo);
}

// metodo do menu do vendedor
void Vendedor::menu()
{
    printf("\ec\e[3j");
    cout << "----------------------------------------" << endl;
    cout << "              Menu Vendedor  " << endl;
    cout << "----------------------------------------\n"<< endl;
    cout << "1. Cadastrar Cliente\n2. Gerar Ordem de Servico\n3. Aprovar ou recusar orcamentos\n4. Fechar ordens de servico\n5. Gerar historico de veiculo\n6. Sair\nEscolha: ";
    
    // validando a escolha do usuario
    int opcao;
    string input;
    while (true) {
        getline(cin, input);

        try {
            opcao = stoi(input); 
            if (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6) {
                break; 
            } else {
                cout << "Numero invalido! Escolha entre as opcoes 1 ou 2. Tente novamente: ";
            }
        } catch (invalid_argument &e) {
            cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
        }
    }
    printf("\ec\e[3j");
    switch (opcao)
    {
    case 1: // cadastra um cliente quantas vezes necessario ate que um 0 seja digitado
        do
        {
            cadastrarCliente();
            cout << "\nDigite 1 para cadastrar outro cliente ou 0 para sair: " << endl;
            // validacao do que foi digitado pelo usuario
            string input;
            while (true) {
                getline(cin, input);
                try {
                    opcao = stoi(input); 
                    if (opcao == 1 || opcao == 0) {
                        break; 
                    } else {
                        cout << "Numero invalido! Escolha entre as opcoes 1 ou 0. Tente novamente: ";
                    }
                } catch (invalid_argument &e) {
                    cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
                }
            }
        } while (opcao == 1);
        printf("\ec\e[3j");
        menu();
        break;
    case 2: // gera uma ordem de servico quantas vezes for necessario ate que um 0 seja digitado
        printf("\ec\e[3j");
        if (clientes->size() == 0)
        {
            gerarOrdemDeServico();
            menu();
            break;
        }
        else
        {
            do
            {
                gerarOrdemDeServico();
                cout << "\nDigite 1 para gerar outra ordem de servico ou 0 para sair: ";
                // validacao da opcao digitada pelo usuario
                string input;
                while (true) {
                    getline(cin, input);
                    try {
                        opcao = stoi(input); 
                        if (opcao == 1 || opcao == 0) {
                            break; 
                        } else {
                            cout << "Numero invalido! Escolha entre as opcoes 1 ou 0. Tente novamente: ";
                        }
                    } catch (invalid_argument &e) {
                        cout << "Entrada invalida, apenas numeros sao permitidos! Tente novamente: ";
                    }
                }
                printf("\ec\e[3j");
            } while (opcao == 1);
        }
        printf("\ec\e[3j");
        menu();
        break;
    case 3: // aprova um orcamento
        aprovarOrcamento(); 
        printf("\ec\e[3j");
        menu();
        break;
    case 4: // fecha uma ordem
        fecharOrdens();
        printf("\ec\e[3j");
        menu();
        break;
    case 5: // gera um historico de veiculo
        gerarHistoricoVeiculo();
        printf("\ec\e[3j");
        menu();
        break;
    default: // volta ao menu principal do programa
        break;
    }
}

