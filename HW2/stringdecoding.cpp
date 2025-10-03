#include <string>
#include <iostream>
#include "QueType.h"
#include "StackType.h"

std::string decode(std::string exp, std::string code);

bool in(char ch, std::string code);

bool in(char ch, std::string code){
    for(int i=0; i < static_cast<int>(code.length()); i++){
        if(code[i] == ch) return true;
    }
    return false;
}

std::string decode(std::string exp, std::string code){
    StackType<char> firststr;
    QueType<char> secondstr;
    std::string result;
    for (int i = 0; i < static_cast<int>(exp.length()); i++){
        if (in(exp[i], code)){
            firststr.Push(exp[i]);
        }
        else{
            secondstr.Enqueue(exp[i]);
        }
    }
    while (!secondstr.IsEmpty()){
        char item;
        secondstr.Dequeue(item);
        result += item;
    }
    while (!firststr.IsEmpty()){
        result += firststr.Pop();
    }
    return result;
}

