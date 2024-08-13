#include "Peca.h"

// construtor
Peca::Peca(const string &nome, float preco) : nome(nome), preco(preco) {}

// setters
void Peca::setNome(string nome) { this->nome = nome; }
void Peca::setPreco(float preco) { this->preco = preco; }

// getters
float Peca::getPreco() { return preco; }
string Peca::getNome() { return nome; }