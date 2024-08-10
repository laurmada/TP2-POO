#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Pessoa.h"
#include "Carro.h"
#include "Peca.h"
#include "Servicos.h"
#include "Cliente.h"
using namespace std;

// classe para uma ordem de servico
class OrdemDeServico
{
private:
    string pedido;
    double valorOrcamento;
    bool orcamentoFeito;
    bool orcamentoAprovado;
    bool servicoConcluido;
    bool ordemFechada;
    Cliente cliente;
    vector<Peca> pecas;
    vector<Servicos> servicos;

public:
    // construtor
    OrdemDeServico(const string &pedido, Cliente cliente)
        : pedido(pedido), valorOrcamento(0.0), orcamentoFeito(false), orcamentoAprovado(false), servicoConcluido(false), ordemFechada(false), cliente(cliente) {}

    void aprovarOrcamento()
    {
        if (valorOrcamento > 0 && !orcamentoAprovado)
        {
            orcamentoAprovado = true;
            cout << "Orcamento aprovado pelo cliente." << endl;
        }
        else
        {
            cout << "Orcamento nao disponivel ou ja aprovado." << endl;
        }
    }

    void concluirServico()
    {
        if (orcamentoAprovado && !servicoConcluido)
        {
            servicoConcluido = true;
            cout << "Servico concluido." << endl;
        }
        else
        {
            cout << "O servico nao pode ser concluido ainda." << endl;
        }
    }

    void visualizarOrdem() const
    {
    }

    void setOrcamentoFeito(bool orcamentoFeito) { this->orcamentoFeito = orcamentoFeito; }
    void setOrcamentoAprovado(bool orcamentoAprovado) { this->orcamentoAprovado = orcamentoAprovado; }
    void setServicoConcluido(bool servicoConcluido) { this->servicoConcluido = servicoConcluido; }
    void setOrdemFechada(bool ordemFechada) { this->ordemFechada = ordemFechada; }
    string getPedido() const { return pedido; }
    bool isServicoConcluido() const { return servicoConcluido; }
    bool isOrcamentoAprovado() const { return orcamentoAprovado; }
    bool isOrdemFechada() const { return ordemFechada; }
    bool isOrcamentoFeito() const { return orcamentoFeito; }
    double getValorOrcamento() const { return valorOrcamento; }
    Cliente getCliente() const { return cliente; }
    vector<Peca> &getPecas() { return pecas; }
    vector<Servicos> &getServicos() { return servicos; }
    void setValorOrcamento(double valorOrcamento) { this->valorOrcamento = valorOrcamento; }
};

class Funcionario : public Pessoa
{
protected:
    string senha;

public:
    Funcionario(const string &nome, const string &senha) : Pessoa(nome), senha(senha) {}
    void setSenha(const string &novaSenha) { senha = novaSenha; }
    bool verificarSenha(const string &senha) const { return this->senha == senha; }

    virtual void menu() = 0;
};

class Vendedor : public Funcionario
{
private:
    vector<Cliente> *clientes;
    vector<OrdemDeServico> *ordens;

public:
    Vendedor(const string &nome, const string &senha, vector<Cliente> *clientes, vector<OrdemDeServico> *ordens)
        : Funcionario(nome, senha), clientes(clientes), ordens(ordens) {}

    void cadastrarCliente()
    {
        string nome, modelo, placa;
        float kilometragem;
        cout << "Preencha os campos abaixo com as informacoes do cliente:" << endl;
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

    void gerarOrdemDeServico()
    {
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

    void aprovarOrcamento() const
    {
        int quantidade = 0;
        cout << "----------------------------------------" << endl;
        cout << "         Ordens de Servico" << endl;
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
            cout << "Nao existem ordens de servico abertas!" << endl;
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

    void fecharOrdens()
    {
        int quantidade = 0;
        cout << "----------------------------------------" << endl;
        cout << "      Ordens de servico abertas" << endl;
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
        int opcao;
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

    void gerarHistoricoVeiculo()
    {

        cout << "----------------------------------------" << endl;
        cout << "            Menu de Historico  " << endl;
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

    void menu() override
    {
        cout << "----------------------------------------" << endl;
        cout << "              Menu Vendedor  " << endl;
        cout << "----------------------------------------\n"
             << endl;
        cout << "\n1. Cadastrar Cliente\n2. Gerar Ordem de Servico\n3. Aprovar ou recusar orcamentos\n4. Fechar ordens de servico\n5. Gerar historico de veiculo\n6. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        printf("\ec\e[3j");
        switch (opcao)
        {
        case 1:
            do
            {
                cadastrarCliente();
                cout << "Digite 1 para cadastrar outro cliente ou 0 para sair: " << endl;
                cin >> opcao;
            } while (opcao == 1);
            printf("\ec\e[3j");
            menu();
            break;
        case 2:
            if (clientes->size() == 0)
            {
                cout << "Nao ha clientes cadastrados\n";
                break;
            }
            else
            {
                do
                {
                    gerarOrdemDeServico();
                    cout << "Digite 1 para gerar outra ordem de servico ou 0 para sair: " << endl;
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
};

class Mecanico : public Funcionario
{
private:
    vector<OrdemDeServico> *ordens;

public:
    Mecanico(const string &nome, const string &senha, vector<OrdemDeServico> *ordens)
        : Funcionario(nome, senha), ordens(ordens) {}

    // metodo para visualizar apenas ordens abertas e sem orcamento
    void visualizarOrdens() const
    {
        int quantidade = 0;
        cout << "----------------------------------------" << endl;
        cout << "Ordens de Servico em Aberto:" << endl;
        cout << "----------------------------------------" << endl;
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
            cout << "Nao existem ordens de servico abertas!" << endl;
        }
    }

    void gerarOrcamento()
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
            cout << "Nao existem ordens de servico abertas!" << endl;
            return;
        }

        // selecionar a ordem para gerar o orcamento
        int opcao;
        cout << "Escolha a ordem de servico para gerar o orcamento (digite o numero): ";
        cin >> opcao;

        while (opcao < 1 || opcao > quantidade)
        {
            cout << "Digite uma ordem valida. Tente novamente ";
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

        cout << "Orcamento gerado com sucesso! Valor total: R$ " << fixed << setprecision(2) << (*ordens)[posicaoVetor].getValorOrcamento() << endl;
        (*ordens)[posicaoVetor].setOrcamentoFeito(true);

        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
    }

    void realizarServico()
    {
        int quantidade = 0;
        cout << "----------------------------------------" << endl;
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
            cout << "Nao existem servicos pendentes!" << endl;
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
        cout << "O servico foi executado com sucesso!\n";
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
    }

    void menu() override
    {
        cout << "Menu Mecanico:\n1. Visualizar Ordens de servico\n2. Gerar Orcamento\n3. Realizar servicos\n4. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            visualizarOrdens();
            printf("\ec\e[3j");
            menu();
            break;
        case 2:
            gerarOrcamento();
            printf("\ec\e[3j");
            menu();
            break;
        case 3:
            realizarServico();
            printf("\ec\e[3j");
            menu();
            break;
        default:
            printf("\ec\e[3j");
            break;
        }
    }
};

class Administrador : public Funcionario
{
private:
    vector<Funcionario *> vendedores;
    vector<Funcionario *> mecanicos;

public:
    Administrador(const string &nome, const string &senha) : Funcionario(nome, senha) {}

    void adicionarVendedor(Funcionario *funcionario)
    {
        vendedores.push_back(funcionario);
    }
    void adicionarMecanico(Funcionario *funcionario)
    {
        mecanicos.push_back(funcionario);
    }

    void alterarDadosVendedor()
    {
        cout << "Alterar dados de qual funcionario?\n";
        for (size_t i = 0; i < vendedores.size(); ++i)
        {
            cout << i + 1 << ". " << vendedores[i]->getNome() << endl;
        }

        int opcao;
        cout << "Escolha o numero do funcionario: ";
        cin >> opcao;

        if (opcao < 1 || opcao > static_cast<int>(vendedores.size()))
        {
            cout << "Opcao invalida." << endl;
            return;
        }

        Funcionario *funcionarioSelecionado = vendedores[opcao - 1];

        cout << "1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
        int escolha;
        cin >> escolha;

        // cin.ignore(); // Limpar o buffer do newline

        if (escolha == 1)
        {
            string novoNome;
            cout << "Novo nome: ";
            cin.ignore();
            getline(cin, novoNome);
            funcionarioSelecionado->setNome(novoNome);
            cout << "Nome alterado com sucesso!" << endl;
        }
        else if (escolha == 2)
        {
            string novaSenha;
            cout << "Nova senha: ";
            cin.ignore();
            getline(cin, novaSenha);
            funcionarioSelecionado->setSenha(novaSenha);
            cout << "Senha alterada com sucesso!" << endl;
        }
        else
        {
            cout << "Opcao invalida." << endl;
        }
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
    }
    void alterarDadosMecanico()
    {
        cout << "Alterar dados de qual funcionario?\n";
        for (size_t i = 0; i < mecanicos.size(); ++i)
        {
            cout << i + 1 << ". " << mecanicos[i]->getNome() << endl;
        }

        int opcao;
        cout << "Escolha o numero do funcionario: ";
        cin >> opcao;

        if (opcao < 1 || opcao > static_cast<int>(mecanicos.size()))
        {
            cout << "Opcao invalida." << endl;
            return;
        }

        Funcionario *funcionarioSelecionado = mecanicos[opcao - 1];

        cout << "1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
        int escolha;
        cin >> escolha;

        // cin.ignore(); // Limpar o buffer do newline

        if (escolha == 1)
        {
            string novoNome;
            cout << "Novo nome: ";
            cin.ignore();
            getline(cin, novoNome);
            funcionarioSelecionado->setNome(novoNome);
            cout << "Nome alterado com sucesso!" << endl;
        }
        else if (escolha == 2)
        {
            string novaSenha;
            cout << "Nova senha: ";
            cin.ignore();
            getline(cin, novaSenha);
            funcionarioSelecionado->setSenha(novaSenha);
            cout << "Senha alterada com sucesso!" << endl;
        }
        else
        {
            cout << "Opcao invalida." << endl;
        }
        cout << "Pressione 1 para voltar ao menu." << endl;
        string lixo;
        cin.ignore();
        getline(cin, lixo);
    }

    void menu() override
    {
        cout << "Menu Administrador:\n1. Editar dados de Vendedores\n2. Editar dados de Mecanicos \n3. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        if (opcao == 1)
        {
            alterarDadosVendedor();
            printf("\ec\e[3j");
            menu();
        }
        else if (opcao == 2)
        {
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
};

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
        if (opcao == 2)
            break;

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