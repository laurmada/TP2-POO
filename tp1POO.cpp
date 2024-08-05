#include <string.h>
#include <string>
#include <iostream>
using namespace std;

class Pessoa {
    string nome;
    int idade;
    public:
    Pessoa(string nome = "", int idade = 0): nome(nome), idade(idade){}
    void setPessoa(string nome, int idade) {
        this->nome = nome;
        this->idade = idade;
    }
    string const getNome() {
        return nome;
    }
    int const getIdade(){
        return idade;
    } 
    Pessoa() {};
   
};

class Veiculo{
    string placa;
    string modelo;
    public:
    Veiculo(string modelo = "", string placa = ""): modelo(modelo), placa(placa){}
    void setVeiculo(string placa, string modelo){
        placa = placa;
        modelo = modelo;
    }
    Veiculo() {};
};

class Cadastro : virtual public Veiculo, public Pessoa{
    private:
    string usuario;
    string senha;
    public:
    Cadastro(string usuario = "", string senha = "", string nome = "", int idade = 0, string modelo = "", string placa = ""): usuario(usuario), senha(senha), Pessoa(nome, idade), Veiculo(modelo, placa){}

    ~Cadastro() {};

    void setCadastro(string usuario, string senha) {
        this->usuario = usuario;
        this->senha = senha;
    }
    string getUsuario (){
        return usuario;
    }
    string getSenha(){
        return senha;
    }
};


class Vendedor: virtual public Cadastro{
    Cadastro C;    
    public: 
    void set() {
        
    }
    ~Vendedor() {};
    


};

class Administrador : public Cadastro{ // herda vendedor e mecanico
    public:
    string editaVendedor() {

    }
    ~Administrador() {};
};

void menu(){
    
}

int main() {

    Cadastro C;


    int idade = 1;

    string nome = "laura";


    C.setPessoa(nome, idade);

    C.getNome();

    cout << "nome: " << C.getNome();

    int opcao;



    cout << "1: Login\n2: Sair do sistema\n";

    cin >> opcao;


    
    if(opcao == 1){
        opcao = 0;
        cout << "1: Administrador\n2: Vendedor\n3: Mecânico\n";
    } else{
       exit(0);
    }

    return 0;
}
