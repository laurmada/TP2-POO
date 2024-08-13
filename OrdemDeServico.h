#ifndef ORDEM_DE_SERVICO_H
#define ORDEM_DE_SERVICO_H

#include <string>
#include <vector>
#include "Cliente.h"  
#include "Peca.h"    
#include "Servicos.h" 

using namespace std;

// classe para representar uma ordem de servico
class OrdemDeServico
{
private:
    string pedido;
    double valorOrcamento;
    bool orcamentoFeito;
    bool orcamentoAprovado;
    bool servicoConcluido;
    bool ordemFechada;
    Cliente cliente;
    vector<Peca> pecas;          // vetor de pecas
    vector<Servicos> servicos;  // vetor de servicos
    
public:
    // construtor
    OrdemDeServico(const string &pedido, Cliente cliente);

    // setters
    void setOrcamentoFeito(bool orcamentoFeito);
    void setOrcamentoAprovado(bool orcamentoAprovado);
    void setServicoConcluido(bool servicoConcluido);
    void setOrdemFechada(bool ordemFechada);
    void setValorOrcamento(double valorOrcamento);

    // getters
    string getPedido() const;
    double getValorOrcamento() const;
    Cliente getCliente() const;
    vector<Peca>& getPecas();
    vector<Servicos>& getServicos();

    // metodos
    bool isServicoConcluido() const;
    bool isOrcamentoAprovado() const;
    bool isOrdemFechada() const;
    bool isOrcamentoFeito() const;
};

#endif