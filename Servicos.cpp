#include "Servicos.h"

Servicos::Servicos(const string &nome, float preco) : nome(nome), preco(preco) {}
void Servicos::setNome(string nome) { this->nome = nome; }
void Servicos::setPreco(float preco) { this->preco = preco; }
float Servicos::getPreco() { return preco; }
string Servicos::getNome() { return nome; }
