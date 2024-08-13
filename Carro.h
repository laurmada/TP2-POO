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
    // construtor
    Carro(const string &modelo, const string &placa, float kilometragem);

    // getters
    string getModelo() const;
    string getPlaca() const;
    float getKilometragem() const;

    // setters
    void setModelo(string &modelo);
    void setPlaca(string &placa);
    void setKilometragem(float kilometragem);
};

#endif 