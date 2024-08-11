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
    Servicos(const string &nome, float preco);
    void setNome(string nome);
    void setPreco(float preco);
    float getPreco();
    string getNome();
};

#endif 