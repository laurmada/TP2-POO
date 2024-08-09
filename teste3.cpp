#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Pessoa {
protected:
    string nome;
public:
    Pessoa(const string& nome) : nome(nome) {}
    string getNome() const { return nome; }
    void setNome(const string& novoNome) { nome = novoNome; }
};

class Carro {
private:
    string modelo;
    string placa;
public:
    Carro(const string& modelo, const string& placa) : modelo(modelo), placa(placa) {}
    string getModelo() const { return modelo; }
    string getPlaca() const { return placa; }
};

class OrdemDeServico {
private:
    Carro* carro;
    string descricao;
    double valorOrcamento;
    bool orcamentoAprovado;
    bool servicoConcluido;
public:
    OrdemDeServico(Carro* carro, const string& descricao)
        : carro(carro), descricao(descricao), valorOrcamento(0.0), orcamentoAprovado(false), servicoConcluido(false) {}

    void gerarOrcamento(double valor) {
        if (!orcamentoAprovado && !servicoConcluido) {
            valorOrcamento = valor;
            cout << "Orcamento gerado: R$ " << valorOrcamento << endl;
        } else {
            cout << "Orcamento já foi aprovado ou serviço concluído." << endl;
        }
    }

    void aprovarOrcamento() {
        if (valorOrcamento > 0 && !orcamentoAprovado) {
            orcamentoAprovado = true;
            cout << "Orçamento aprovado pelo cliente." << endl;
        } else {
            cout << "Orçamento não disponível ou já aprovado." << endl;
        }
    }

    void concluirServico() {
        if (orcamentoAprovado && !servicoConcluido) {
            servicoConcluido = true;
            cout << "Serviço concluído." << endl;
        } else {
            cout << "O serviço não pode ser concluído ainda." << endl;
        }
    }

    void visualizarOrdem() const {
        cout << "Descrição: " << descricao << "\nValor do Orçamento: R$ " << valorOrcamento 
             << "\nAprovado: " << (orcamentoAprovado ? "Sim" : "Não") 
             << "\nConcluído: " << (servicoConcluido ? "Sim" : "Não") 
             << "\nCarro: " << carro->getModelo() << " (" << carro->getPlaca() << ")" << endl;
    }

    bool isServicoConcluido() const { return servicoConcluido; }
    bool isOrcamentoAprovado() const { return orcamentoAprovado; }
};

class Cliente : public Pessoa {
private:
    vector<Carro> carros;
public:
    Cliente(const string& nome) : Pessoa(nome) {}

    void adicionarCarro(const Carro& carro) {
        carros.push_back(carro);
    }

    vector<Carro>& getCarros() {
        return carros;
    }
};

class Funcionario : public Pessoa {
protected:
    string senha;
public: 
    Funcionario(const string& nome, const string& senha) : Pessoa(nome) , senha(senha) {}
    void setSenha(const string& novaSenha) { senha = novaSenha;}
    bool verificarSenha(const string& senha) const { return this->senha == senha; }
   
    virtual void menu() = 0;
};

class Vendedor : public Funcionario {
private:
    vector<Cliente> clientes;
    vector<OrdemDeServico> ordens;
public:
    Vendedor(const string& nome, const string& senha) : Funcionario(nome, senha) {}

    void cadastrarCliente(const Cliente& cliente) {
        clientes.push_back(cliente);
        cout << "Cliente cadastrado: " << cliente.getNome() << endl;
    }

    void gerarOrdemDeServico(Carro* carro, const string& descricao) {
        ordens.emplace_back(carro, descricao);
        cout << "Ordem de Serviço gerada." << endl;
    }

    void visualizarOrdens() const {
        cout << "Ordens de Serviço:" << endl;
        for (const auto& ordem : ordens) {
            ordem.visualizarOrdem();
            cout << endl;
        }
    }

    void alterarSituacaoOrdem() {
        cout << "Alterar situação da ordem de serviço..." << endl;
        // Implementação para alterar a situação da ordem
    }

    void menu() override {
        cout << "Menu Vendedor:\n1. Cadastrar Cliente\n2. Gerar Ordem de Serviço\n3. Visualizar Ordens\n4. Alterar Situação da Ordem\n5. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        switch (opcao) {
            case 1:
                // Cadastrar Cliente
                break;
            case 2:
                // Gerar Ordem de Serviço
                break;
            case 3:
                visualizarOrdens();
                break;
            case 4:
                alterarSituacaoOrdem();
                break;
            default:
                break;
        }
    }
};

class Mecanico : public Funcionario {
private:
    vector<OrdemDeServico>* ordens;
public:
    Mecanico(const string& nome, const string& senha, vector<OrdemDeServico>* ordens)
        : Funcionario(nome, senha), ordens(ordens) {}

    void visualizarOrdens() const {
        cout << "Ordens de Serviço em Aberto:" << endl;
        for (const auto& ordem : *ordens) {
            if (!ordem.isServicoConcluido()) {
                ordem.visualizarOrdem();
                cout << endl;
            }
        }
    }

    void gerarOrcamento() {
        cout << "Gerar orçamento para uma ordem de serviço..." << endl;
        // Implementação para gerar orçamento
    }

    void fecharOrdem() {
        cout << "Fechar ordem de serviço..." << endl;
        // Implementação para fechar ordem de serviço
    }

    void menu() override {
        cout << "Menu Mecânico:\n1. Visualizar Ordens\n2. Gerar Orçamento\n3. Fechar Ordem\n4. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        switch (opcao) {
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

class Administrador : public Funcionario {
private:
    vector<Funcionario*> funcionarios;
public:
    Administrador(const string& nome, const string& senha) : Funcionario(nome, senha) {}

    void adicionarFuncionario(Funcionario* funcionario) {
        funcionarios.push_back(funcionario);
    }

    void alterarDadosFuncionario() {
        cout << "Alterar dados de qual funcionário?\n";
        for (size_t i = 0; i < funcionarios.size(); ++i) {
            cout << i + 1 << ". " << funcionarios[i]->getNome() << endl;
        }

        int opcao;
        cout << "Escolha o número do funcionário: ";
        cin >> opcao;

        if (opcao < 1 || opcao > static_cast<int>(funcionarios.size())) {
            cout << "Opção inválida." << endl;
            return;
        }

        Funcionario* funcionarioSelecionado = funcionarios[opcao - 1];

        cout << "1. Alterar Nome\n2. Alterar Senha\nEscolha: ";
        int escolha;
        cin >> escolha;

        cin.ignore();  // Limpar o buffer do newline

        if (escolha == 1) {
            string novoNome;
            cout << "Novo nome: ";
            getline(cin, novoNome);
            funcionarioSelecionado->setNome(novoNome);
            cout << "Nome alterado com sucesso!" << endl;
        } else if (escolha == 2) {
            string novaSenha;
            cout << "Nova senha: ";
            getline(cin, novaSenha);
            funcionarioSelecionado->setSenha(novaSenha);
            cout << "Senha alterada com sucesso!" << endl;
        } else {
            cout << "Opção invalida." << endl;
        }
    }

    void menu() override {
        cout << "Menu Administrador:\n1. Alterar Dados de Funcionario\n2. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        if (opcao == 1) {
            alterarDadosFuncionario();
        }
    }
};

int main() {
    // inicializacao de um administrador
    Administrador admin("admin", "admin123");

    // inicializacao de vetor com tres vendedores
    vector<Vendedor> vendedores;
    Vendedor vendedor1("vendedor1", "vend123");
    Vendedor vendedor2("vendedor2", "vend123");
    Vendedor vendedor3("vendedor3", "vend123");
    vendedores.push_back(vendedor1);
    vendedores.push_back(vendedor2);
    vendedores.push_back(vendedor3);

    // Adiciona os vendedores para o controle do administrador
    for (size_t i = 0; i < vendedores.size(); i++) {
        admin.adicionarFuncionario(&(vendedores[i]));
    }

    // inicializacao de vetor de ordens de servico
    vector<OrdemDeServico> ordens;

    // inicializacao de vetor com dois mecanicos
    vector<Mecanico> mecanicos;
    Mecanico mecanico1("mecanico1", "mec123", &ordens);
    Mecanico mecanico2("mecanico2", "mec123", &ordens);
    mecanicos.push_back(mecanico1);
    mecanicos.push_back(mecanico2);

    // Adiciona os mecanicos para o controle do administrador
    for (size_t i = 0; i < mecanicos.size(); i++) {
        admin.adicionarFuncionario(&(mecanicos[i]));
    }
    
    //laco para o menu de login
    while (true) {
        //variavel que controla a entrada
        bool verifica = false;
        cout << "1. Login\n2. Sair\nEscolha: ";
        int opcao;
        cin >> opcao;
        if (opcao == 2) break;
        
        //limpa o menu
        printf("\ec\e[3j");
        string nome, senha;
        cout << "Nome: ";
        cin >> nome;
        cout << "Senha: ";
        cin >> senha;
        printf("\ec\e[3j");
        
        
        //verificando se o login equivale ao do admin
        if (nome == admin.getNome() && admin.verificarSenha(senha)) {
            verifica = true;
            admin.menu();
        }

        //verificando se o login equivale ao dos vendedores
        for (size_t i = 0; i < vendedores.size(); i++){
            if (nome == vendedores[i].getNome() && vendedores[i].verificarSenha(senha)) {
                vendedores[i].menu();
                verifica = true;

            } 
        } 
        
        //verificando se o login equivale ao dos mecanicos
        for (size_t i = 0; i < mecanicos.size(); i++){
            if (nome == mecanicos[i].getNome() && mecanicos[i].verificarSenha(senha)) {
                mecanicos[i].menu();
                verifica = true;
            } 
        } 

        if(verifica == false) {
            cout << "Login invalido!" << endl;
        }
    }
    

    return 0;
}
