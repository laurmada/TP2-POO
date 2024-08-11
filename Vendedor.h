#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <vector>
#include <string>
#include "Funcionario.h" 
#include "OrdemDeServico.h"
#include "Cliente.h"
#include <iomanip>

using namespace std;

class Vendedor : public Funcionario {
private:
    vector<Cliente> *clientes;
    vector<OrdemDeServico> *ordens;
public:
    // construtor
    Vendedor(const string &nome, const string &senha, vector<Cliente> *clientes, vector<OrdemDeServico> *ordens);

    // metodos
    void cadastrarCliente();
    void gerarOrdemDeServico();
    void aprovarOrcamento() const;
    void fecharOrdens();
    void gerarHistoricoVeiculo();
    void menu() override;
};

#endif