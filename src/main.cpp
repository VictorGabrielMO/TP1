#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "../include/linkedStack.hpp"
#include "../include/algebricExpressionTree.hpp"

#define COMANDO_LER 0
#define COMANDO_INFIXA 1
#define COMANDO_POSFIXA 2
#define COMANDO_RESOLVE 3

#define LER_INFIXA 4
#define LER_POSFIXA 5

std::string GetExpression(std::string line, int readNotation){
    if(readNotation == LER_INFIXA) return line.substr(12, line.size() - 12);
    else if(readNotation == LER_POSFIXA) return line.substr(13, line.size() - 13);
    else throw "ERRO: NOTAÇÃO INDEFINIDA";
}

int GetOperation(std::string line){
    if (line.substr(0,6) == "INFIXA") return COMANDO_INFIXA;
    if (line.substr(0,7) == "POSFIXA") return COMANDO_POSFIXA;
    
    std::string operation;
    std::string::iterator it = line.begin();
    while(1){
        operation += *it;
        it++;
        if(*it == ' ' || *it == '\n'){
            break;
        }
    }

    if (operation == "LER") return COMANDO_LER;
    else if (operation == "RESOLVE") return COMANDO_RESOLVE;
    else throw "ERRO: Operação Inválida";
}

int GetNotation(std::string line){
    std::string notation;
    std::string::iterator it = line.begin();
    int i = 0;

    while(1){
        if(i < 4){
            it++;
            i++;
            continue;
        }
        notation += *it;
        it++;
        i++;
        if(*it == ' ' || *it == '\n'){
            break;
        }
    }

    if (notation == "INFIXA") return LER_INFIXA;
    else if(notation == "POSFIXA") return LER_POSFIXA;
    else{
        throw "ERRO: NOTAÇÃO INDEFINIDA";
    }
}

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool hasOperator(std::string exp){
    return (exp.find('+') != std::string::npos || 
            exp.find('-') != std::string::npos ||
            exp.find('*') != std::string::npos ||
            exp.find('/') != std::string::npos);
}

void ConstructTreeInfix(std::string exp, bool left = true){ //o booleano diz se a expressão passada como parêntese está na esquerda ou direita do operdor
    int i = 0;
    if(!hasOperator(exp)){
        i = 1;
        if(left){
            //adiciona folha a esquerda
        }else{
             //adiciona folha a direita
        }
    }else{
        linkedstack<char> openParentesis;
        int ci = 0;
        std::string expl;
        std::string expr;
        for(char c : exp){
            if(c == '('){
                openParentesis.push('(');
            }else if(c == ')'){
                openParentesis.pop();
            }else if(isOperator(c) && openParentesis.getSize() == 1){
                //criar nó do operador e adicionar a arvore
                expl = exp.substr(2,ci - 3); //retiro o único ( que não foi fechado
                ConstructTreeInfix(expl, true);
                expr = exp.substr(ci+2,exp.size() - (ci + 4)); // retiro o único ) que não foi aberto
                ConstructTreeInfix(expr, false );
            }
            ci++;
        }
    }
}

bool ValidatePostfixNotation(std::string expr) {
    linkedstack<double> st;
    double num = 0;
    bool readingNum = false;
    bool doteWasRead = false;
    int decimalplaces = 0;

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

bool ValidateInfixNotation(std::string exp) {
    linkedstack<char> pilha;
    bool ultimoCaractereOperador = false; // indica se o último caractere foi um operador
    bool ultimoCaractereDigito = false;
    int acumuladordedigitos = 0;
    std::size_t jaexisteponto = std::string::npos; //indica se em um numero em formação já existe um .
    int ci = 0;
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

bool ValidateEXP(std::string line, int readNotation){
    if(readNotation == LER_INFIXA){
        if(ValidateInfixNotation(line)){
            return true;
        }else{
            throw "ERRO: Expressão infixa inválida";
        }
    }
    if(readNotation == LER_POSFIXA){
        if(ValidatePostfixNotation(line)){
            return true;
        }else{
            throw "ERRO: Expressão posfixa inválida";
        }
    }
    throw "ERRO: Notação indefinida";
}

int main () {
  std::string line;
  std::string exp;
  std::ifstream myfile ("../TP1entradas/entdouble.s3.n5.i.in");
  int readNotation = -1;

  algebricExpressionTree t;

  if (myfile.is_open())
  {
    for (int l = 1 ; getline (myfile,line) ; l++ )
    {
      if(line.empty())
        continue;
      //std::cout << line << '\n';
      switch (GetOperation(line))
      {
        case COMANDO_LER: 
            readNotation = GetNotation(line);
            exp = GetExpression(line, readNotation);
            ValidateEXP(exp,readNotation);
            if(readNotation == LER_INFIXA) t.BuildTree(exp);
            std::cout << "E LER\n";
            break;
        case COMANDO_INFIXA:
            std::cout << "E INFIXA\n";
            break;
        case COMANDO_POSFIXA:
            std::cout << "E POSFIXA\n";
            break;
        case COMANDO_RESOLVE:
            std::cout << "E RESOLVE\n";
            break;
      }
    }
    myfile.close();
  }

  else std::cout << "Unable to open file"; 

  return 0;
}