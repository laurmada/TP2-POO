#ifndef PECA_H
#define PECA_H
#include <string>
using namespace std;

// classe para representar uma peca
class Peca
{
private:
    string nome;
    float preco;

public:
    // construtor
    Peca(const string &nome, float preco);

    // setters
    void setNome(string nome);
    void setPreco(float preco);

    // getters
    float getPreco();
    string getNome();
};

#endif 