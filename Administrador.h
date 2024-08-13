#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <vector>
#include <string>
#include "Funcionario.h" 
#include <iomanip>

// classe para representar um administrador 
class Administrador : public Funcionario
{
private:
    vector<Funcionario *> vendedores;
    vector<Funcionario *> mecanicos;
    
public:
    // construtor
    Administrador(const string &nome, const string &senha);

    // metodos
    void adicionarVendedor(Funcionario *funcionario);
    void adicionarMecanico(Funcionario *funcionario);
    void alterarDadosVendedor();
    void alterarDadosMecanico();
    void menu() override;
};

#endif