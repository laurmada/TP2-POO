#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Pessoa
{
protected:
    string nome;

public:
    Pessoa() {}
    Pessoa(const string &nome) : nome(nome) {}
    string getNome() const { return nome; }
    void setNome(const string &novoNome) { nome = novoNome; }
};

class Carro
{
private:
    string modelo;
    string placa;
    float kilometragem;

public:
    Carro(const string &modelo, const string &placa, float kilometragem)
        : modelo(modelo), placa(placa), kilometragem(kilometragem) {}

    // getters
    string getModelo() const { return modelo; }
    string getPlaca() const { return placa; }
    float getKilometragem() const { return kilometragem; }
    // setters
    void setModelo(string modelo) { this->modelo = modelo; }
    void setPlaca(string placa) { this->placa = placa; }
    void setKilometragem(float kilometragem) { this->kilometragem = kilometragem; }
};

class Peca
{
private:
    string nome;
    float preco;

public:
    Peca(const string &nome, float preco) : nome(nome), preco(preco) {}
    void setNome(string nome)
    {
        this->nome = nome;
    }
    void setPreco(float preco)
    {
        this->preco = preco;
    }
};

class Servicos
{
private:
    string nome;
    float preco;

public:
    Servicos(const string &nome, float preco) : nome(nome), preco(preco) {}
    void setNome(string nome)
    {
        this->nome = nome;
    }
    void setPreco(float preco)
    {
        this->preco = preco;
    }
};

class Cliente : public Pessoa
{
private:
    Carro carro;

public:
    Cliente(const string &nome, const string &modelo, const string &placa, float kilometragem)
        : Pessoa(nome), carro(modelo, placa, kilometragem) {}

    Carro &getCarro()
    {
        return carro;
    }
};

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
        cout << "Descricao: " << pedido << "\nValor do Orcamento: R$ " << valorOrcamento
             << "\nAprovado: " << (orcamentoAprovado ? "Sim" : "Nao")
             << "\nConcluido: " << (servicoConcluido ? "Sim" : "Nao") << endl;
        //  << "\nCarro: " << carro.getModelo() << " (" << carro.getPlaca() << ")" << endl;
    }

    string getPedido() const { return pedido; }
    bool isServicoConcluido() const { return servicoConcluido; }
    bool isOrcamentoAprovado() const { return orcamentoAprovado; }
    bool isOrdemFechada() const { return ordemFechada; }
    double getValorOrcamento() const { return valorOrcamento; }
    Cliente getCliente() const { return cliente; }
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
        int opcao;
        cout << "----------------------------------------" << endl;
        cout << "         Ordens de Servico" << endl;
        cout << "----------------------------------------" << endl;

        for (size_t i = 0; i < ordens->size(); i++)
        {
            // ADICIONAR isOrcamentoFeito depois
            if (!(*ordens)[i].isOrdemFechada() && !(*ordens)[i].isOrcamentoAprovado() && !(*ordens)[i].isServicoConcluido())
            {
                cout out << i + 1 << ". " << "Pedido: " << (*ordens)[i].getPedido() << endl;
                cout << " - Placa: " << (*ordens)[i].getCliente().getCarro().getPlaca() << endl;
                cout << " - Preco do Orcamento: R$ " << fixed << setprecision(2) << (*ordens)[i].getValorOrcamento() << endl;
                cout << "----------------------------------------" << endl;
            }
        }
        // fecha fecha aberta
        // 0     1     2

        cout << "Selecione o pedido para aprovar o orcamento: " << endl;
        cin >> opcao;

        // IMPLEMENTAR MECANICO PARA TESTAR ORDEM ABERTA
        j = 0;
        for (size_t k = 0; k < ordens->size(); k++)
        {
            // ADICIONAR isOrcamentoFeito depois
            if (!(*ordens)[k].isOrdemFechada() && !(*ordens)[k].isOrcamentoAprovado() && !(*ordens)[k].isServicoConcluido())
            {
                j++;
                OrdemDeServico *OrdemDeServico = ordens[k - 1];
            }
        }
    }

    void alterarSituacaoOrdem()
    {
        cout << "Alterar situacao da ordem de servico..." << endl;
        // Implementacao para alterar a situacao da ordem
    }

    void menu() override
    {
        cout << "Menu Vendedor:\n1. Cadastrar Cliente\n2. Gerar Ordem de Servico\n3. Aprovar orcamentos\n4. Alterar Situacao da Ordem\n5. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            if (clientes->size() == 0)
            {
                cout << "Nao ha clientes cadastrados\n";
                break;
            }
            else
            {
                gerarOrdemDeServico();
            }
            break;
        case 3:
            aprovarOrcamento();
            break;
        case 4:
            alterarSituacaoOrdem();
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

    void visualizarOrdens() const
    {
        cout << "Ordens de Servico em Aberto:" << endl;
        for (const auto &ordem : *ordens)
        {
            if (!ordem.isServicoConcluido())
            {
                ordem.visualizarOrdem();
                cout << endl;
            }
        }
    }

    void gerarOrcamento()
    {
        cout << "Gerar orcamento para uma ordem de servico..." << endl;
        // Implementacao para gerar orcamento
    }

    void fecharOrdem()
    {
        cout << "Fechar ordem de servico..." << endl;
        // Implementacao para fechar ordem de servico
    }

    void menu() override
    {
        cout << "Menu Mecanico:\n1. Visualizar Ordens\n2. Gerar Orcamento\n3. Fechar Ordem\n4. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            visualizarOrdens();
            break;
        case 2:
            gerarOrcamento();
            break;
        case 3:
            fecharOrdem();
            break;
        default:
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

        cin.ignore(); // Limpar o buffer do newline

        if (escolha == 1)
        {
            string novoNome;
            cout << "Novo nome: ";
            getline(cin, novoNome);
            funcionarioSelecionado->setNome(novoNome);
            cout << "Nome alterado com sucesso!" << endl;
        }
        else if (escolha == 2)
        {
            string novaSenha;
            cout << "Nova senha: ";
            getline(cin, novaSenha);
            funcionarioSelecionado->setSenha(novaSenha);
            cout << "Senha alterada com sucesso!" << endl;
        }
        else
        {
            cout << "Opcao invalida." << endl;
        }
    }
    void alterarDadosMecanico()
    {
        cout << "Alterar dados de qual funcionario?\n";
        for (size_t i = 0; i < mecanicos.size(); ++i)
        {
            cout << i + 1 << ". " << mecanicos[i]->getNome() << endl;
        }

        int opcao;
        cout << "Escolha o numero do funcionário: ";
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

        cin.ignore(); // Limpar o buffer do newline

        if (escolha == 1)
        {
            string novoNome;
            cout << "Novo nome: ";
            getline(cin, novoNome);
            funcionarioSelecionado->setNome(novoNome);
            cout << "Nome alterado com sucesso!" << endl;
        }
        else if (escolha == 2)
        {
            string novaSenha;
            cout << "Nova senha: ";
            getline(cin, novaSenha);
            funcionarioSelecionado->setSenha(novaSenha);
            cout << "Senha alterada com sucesso!" << endl;
        }
        else
        {
            cout << "Opcao invalida." << endl;
        }
    }

    void menu() override
    {
        cout << "Menu Administrador:\n1. Editar dados de Vendedores\n2. Editar dados de Mecanicos \n3. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        if (opcao == 1)
        {
            alterarDadosVendedor();
        }
        else if (opcao == 2)
        {
            alterarDadosMecanico();
        }
        else
            return;
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
        // printf("\ec\e[3j");
        // variavel que controla a entrada
        bool verifica = false;
        cout << "1. Login\n2. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        if (opcao == 2)
            break;

        // limpa o menu
        printf("\ec\e[3j");
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
