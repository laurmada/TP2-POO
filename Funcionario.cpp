#include "Funcionario.h"  
#include <iostream>

using namespace std;

// construtor
Funcionario::Funcionario(const string &nome, const string &senha) : Pessoa(nome), senha(senha) {}

// metodos
void Funcionario::setSenha(const string &novaSenha) { senha = novaSenha; }
bool Funcionario::verificarSenha(const string &senha) const { return this->senha == senha; }