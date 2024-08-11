#ifndef MECANICO_H
#define MECANICO_H

#include <iostream>
#include <vector>
#include <string>
#include "Funcionario.h" 
#include "OrdemDeServico.h"
#include "Cliente.h"
#include <iomanip>

class Mecanico : public Funcionario
{
private:
    vector<OrdemDeServico> *ordens;
public:
    Mecanico(const string &nome, const string &senha, vector<OrdemDeServico> *ordens);

    void visualizarOrdens() const;
    void gerarOrcamento();
    void realizarServico();
    void menu() override;
};

#endif