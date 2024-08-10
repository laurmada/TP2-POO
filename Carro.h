#ifndef CARRO_H
#define CARRO_H

#include <string>
using namespace std;

// classe para representar um carro
class Carro
{
private:
    string modelo;
    string placa;
    float kilometragem;

public:
    Carro(const string &modelo, const string &placa, float kilometragem);
    string getModelo() const;
    string getPlaca() const;
    float getKilometragem() const;
    void setModelo(string &modelo);
    void setPlaca(string &placa);
    void setKilometragem(float kilometragem);
};

#endif CARRO_H