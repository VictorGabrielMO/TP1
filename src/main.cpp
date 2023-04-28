#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "../include/linkedstack.hpp"

#define LER 0
#define INFIXA 1
#define POSFIXA 2
#define RESOLVE 3

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool ValidatePostfixNotation(std::string line) {
    linkedstack<double> st;
    double num = 0;
    bool readingNum = false;
    bool doteWasRead = false;
    int decimalplaces = 0;
    std::string expr = line.substr(4,line.size() - 4);

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (c == ' ') {
            // ignora espaços pois o caso já foi tratado em quando é dígito e o sucessor é espaço
            continue;
        }
        else if (isOperator(c)) {
            // se o caractere atual for um operador, remova dois valores da pilha
            // e aplique a operação correspondente, empilhe o resultado na pilha
            if (st.getSize() < 2) {
                return false;
            }
            double op1 = st.getTop();
            st.pop();
            double op2 = st.getTop();
            st.pop();

            switch (c) {
                case '+': st.push(op2 + op1); break;
                case '-': st.push(op2 - op1); break;
                case '*': st.push(op2 * op1); break;
                case '/': st.push(op2 / op1); break;
            }
            readingNum = false;
            doteWasRead = false;
        }
        else if (c == '.') { 
            if(doteWasRead){
                return false; //certifica que não podem existir dois pontos em um mesmo número
            }else if (!readingNum){
                return false; //certifica que não existem pontos que não são antecedidos por dígitos
            }
            doteWasRead = true;
            decimalplaces = 0;
        }
        else if (isdigit(c)){
            // se o caractere atual for um dígito, adiciona o dígito ao número atual
            if (!readingNum) {
                // inicia a leitura de um novo número
                num = 0;
                readingNum = true;
            }

            if(doteWasRead){
                decimalplaces ++;
                num = num + ((c - '0') * pow(10,-decimalplaces));// usando o fato de que os algorismos são dispostos de forma crescente em ASCII
            }else{
                num = num * 10 + (c - '0'); 
            }

            if (i == expr.length() - 1 || expr[i+1] == ' ') {
                // se o próximo caractere for um espaço ou se o caractere atual for o último,
                // empilha o número lido
                st.push(num);
                readingNum = false;
                doteWasRead = false;
            }
        }else{
            return false;
        }
    }

    // se houver apenas um elemento na pilha após processar toda a expressão, ela é válida
    return (st.getSize() == 1);
}


bool ValidateInfixNotation(std::string line) {
    linkedstack<char> pilha;
    bool ultimoCaractereOperador = false; // indica se o último caractere foi um operador
    bool ultimoCaractereDigito = false;
    int acumuladordedigitos = 0;
    std::size_t jaexisteponto = std::string::npos; //indica se em um numero em formação já existe um .
    int ci = 0;
    std::string exp = line.substr(4,line.size() - 4);
    if (exp.size() > 1000)
        throw "Expressão com mais caracteres que o limite máximo (1000)"; 
    for (char c : exp) {
        if (isdigit(c)) { // verifica se é um operando válido
            ultimoCaractereOperador = false;
            ultimoCaractereDigito = true;
            acumuladordedigitos++;
        } else if (c == '.'){
            if(!ultimoCaractereDigito){
                return false;
            }
            std::string numero = exp.substr(ci - acumuladordedigitos,acumuladordedigitos);
            jaexisteponto = numero.find('.');
            if(jaexisteponto != std::string::npos){
                return false;
            }
            ultimoCaractereDigito = false;
            acumuladordedigitos++; 
        } else if (c == '(') { // empilha parêntese aberto
            pilha.push(c);
            ultimoCaractereOperador = true; // = true pois caso houver ( + deve-se retornar false
            ultimoCaractereDigito = false;
            acumuladordedigitos = 0;
        } else if (c == ')') { // desempilha parêntese aberto correspondente
            if (pilha.empty() || pilha.getTop() != '(') {
                return false;
            }
            if(ultimoCaractereOperador){
                return false;
            }
            pilha.pop();
            ultimoCaractereOperador = false;
            ultimoCaractereDigito = false;
            acumuladordedigitos = 0;
        } else if (isOperator(c)) { // verifica se é um operador válido
            if (ultimoCaractereOperador) {
                return false;
            }
            ultimoCaractereOperador = true;
            ultimoCaractereDigito = false;
            acumuladordedigitos = 0;
        } else if(c == ' '){
            ultimoCaractereDigito = false;
            acumuladordedigitos = 0;
        } else {
            return false; // se encontrar qualquer outro caractere, a expressão é inválida
        }
        ci++;
    }
    return pilha.empty() && !ultimoCaractereOperador; // verifica se todos os parênteses foram fechados corretamente e se o último caractere não foi um operador
}

bool ValidateEXP(std::string line){
    if(ValidatePostfixNotation(line)) return true;
    else if(ValidateInfixNotation(line)) return false;
    else throw "ERRO: Expressão inválida";
}

std::string GetExpression(std::string line, bool isInvPolish){
    
    return "TESTE";
}

int GetOperation(std::string line){
    if (line == "INFIXA") return INFIXA;
    if (line == "POSFIXA") return POSFIXA;
    
    std::string operation;
    std::string::iterator it = line.begin();
    while(1){
        operation += *it;
        it++;
        if(*it == ' ' || *it == '\n'){
            break;
        }
    }

    if (operation == "LER") return LER;
    else if (operation == "RESOLVE") return RESOLVE;
    else throw "ERRO: Operação Inválida";
}

int main () {
  std::string line;
  std::ifstream myfile ("../TP1entrada/entdouble.s8.n5.p.in");
  bool isInvPolish = false;

  if (myfile.is_open())
  {
    for (int l = 1 ; getline (myfile,line) ; l++ )
    {
      if(line.empty())
        continue;
      //std::cout << line << '\n';
      switch (GetOperation(line))
      {
        case LER: 
            isInvPolish = ValidateEXP(line);
            //GetExpression(line,isInvPolish);
            std::cout << "E LER\n";
            break;
        case INFIXA:
            std::cout << "E INFIXA\n";
            break;
        case POSFIXA:
            std::cout << "E POSFIXA\n";
            break;
        case RESOLVE:
            std::cout << "E RESOLVE\n";
            break;
      }
    }
    myfile.close();
  }

  else std::cout << "Unable to open file"; 

  return 0;
}