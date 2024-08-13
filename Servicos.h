#ifndef SERVICOS_H
#define SERVICOS_H
#include <string>
using namespace std;

// classe para servicos
class Servicos
{
private:
    string nome;
    float preco;

public:
    // construtor
    Servicos(const string &nome, float preco);

    // setters
    void setNome(string nome);
    void setPreco(float preco);

    // getters
    float getPreco();
    string getNome();
};

#endif 