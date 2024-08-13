#include "Servicos.h"

// construtor
Servicos::Servicos(const string &nome, float preco) : nome(nome), preco(preco) {}

// setters
void Servicos::setNome(string nome) { this->nome = nome; }
void Servicos::setPreco(float preco) { this->preco = preco; }

// getters
float Servicos::getPreco() { return preco; }
string Servicos::getNome() { return nome; }
