#include "OrdemDeServico.h"

#include <iostream>

using namespace std;

// construtor
OrdemDeServico::OrdemDeServico(const string &pedido, Cliente cliente)
    : pedido(pedido), valorOrcamento(0.0), orcamentoFeito(false), orcamentoAprovado(false),
      servicoConcluido(false), ordemFechada(false), cliente(cliente) {}

// setters
void OrdemDeServico::setOrcamentoFeito(bool orcamentoFeito) { this->orcamentoFeito = orcamentoFeito; }
void OrdemDeServico::setOrcamentoAprovado(bool orcamentoAprovado) { this->orcamentoAprovado = orcamentoAprovado; }
void OrdemDeServico::setServicoConcluido(bool servicoConcluido) { this->servicoConcluido = servicoConcluido; }
void OrdemDeServico::setOrdemFechada(bool ordemFechada) { this->ordemFechada = ordemFechada; }
void OrdemDeServico::setValorOrcamento(double valorOrcamento) { this->valorOrcamento = valorOrcamento; }

// getters
string OrdemDeServico::getPedido() const { return pedido; }
double OrdemDeServico::getValorOrcamento() const { return valorOrcamento; }
Cliente OrdemDeServico::getCliente() const { return cliente; }
vector<Peca>&OrdemDeServico::getPecas() { return pecas; }
vector<Servicos>&OrdemDeServico::getServicos() { return servicos; }

// metodos
bool OrdemDeServico::isServicoConcluido() const { return servicoConcluido; }
bool OrdemDeServico::isOrcamentoAprovado() const { return orcamentoAprovado; }
bool OrdemDeServico::isOrdemFechada() const { return ordemFechada; }
bool OrdemDeServico::isOrcamentoFeito() const { return orcamentoFeito; }