#ifndef MECANICO_H
#define MECANICO_H

#include <iostream>
#include <vector>
#include <string>
#include "Funcionario.h" 
#include "OrdemDeServico.h"
#include "Cliente.h"
#include <iomanip>

// classe para representar um mecanico, que herda de funcionario
class Mecanico : public Funcionario
{
private:
    vector<OrdemDeServico> *ordens; // vetor com ordens de servico
    
public:
    // construtor
    Mecanico(const string &nome, const string &senha, vector<OrdemDeServico> *ordens);

    // metodos
    void visualizarOrdens() const;
    void gerarOrcamento();
    void realizarServico();
    void menu() override;
};

#endif