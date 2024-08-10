#include "Peca.h"

Peca::Peca(const string &nome, float preco) : nome(nome), preco(preco) {}
void Peca::setNome(string nome) { this->nome = nome; }
void Peca::setPreco(float preco) { this->preco = preco; }
float Peca::getPreco() { return preco; }
string Peca::getNome() { return nome; }