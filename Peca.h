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
    Peca(const string &nome, float preco);
    void setNome(string nome);
    void setPreco(float preco);
    float getPreco();
    string getNome();
};

#endif PECA_H