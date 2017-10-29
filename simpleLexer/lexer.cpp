// Problem#: 20907
// Submission#: 5194653
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const struct { int number; string str[10]; } keywords={3,"int","main","return"} ; //关键词
const struct { int number; string str[10]; } operators ={5,"+","*","=","+=","*="}; //运算符
const struct { int number; string str[10]; } boundaries ={6,"(",")","{","}",",",";"} ; //分界符
struct { int number; string str[100];} identifieres={0}; //标识符
struct { int number; string str[100];} Unsigned_integer={0}; //无符号整数
/*
以上类号分别为1~5，序号从0开始；
标识符是字母开头的字母数字串；
常量为无符号整数；
*/

struct Name 
{
    int type;
    int index;
    Name (int t, int i) {
        type = t;
        index = i;
    }
};

vector<Name> names;

int uintExplore(int index, string& inStream, int inLen) {
    if (inStream[index] < '0' || inStream[index] > '9')
        return -1;
    int pIdx = 1;
    string uintStr = "";
    uintStr += inStream[index];
    while (index + pIdx <= inLen - 1 && inStream[index + pIdx] >= '0' && inStream[index + pIdx] <= '9') {
        uintStr += inStream[index + pIdx];
        pIdx++;
    }
    
    int uintNameIndex = -1;
    for (int i = 0; i < Unsigned_integer.number; i++) {
        if (Unsigned_integer.str[i] == uintStr) {
            uintNameIndex = i;
            break;
        }        
    }

    if (uintNameIndex == -1) {
        Name uintName(5, Unsigned_integer.number);
        names.push_back(uintName);
        Unsigned_integer.str[Unsigned_integer.number] = uintStr;
        Unsigned_integer.number++;        
    } else {
        Name uintName(5, uintNameIndex);
        names.push_back(uintName);
    }

    return pIdx;
}

int opExplore(int index, string& inStream, int inLen) {
    int opIdx = -1;
    switch(inStream[index]) {
        case '+':
            opIdx = 0;
            if (index + 1 <= inLen - 1 && inStream[index + 1] == '=')
                opIdx = 3;
            break;
        case '*':
            opIdx = 1;
            if (index + 1 <= inLen - 1 && inStream[index + 1] == '=')
                opIdx = 4;
            break;
        case '=':
            opIdx = 2;
            break;
    }
    if (opIdx == -1)
        return -1;
    Name opName(2, opIdx);
    names.push_back(opName);
    return opIdx <= 3 ? 1 : 2;
}

int boundaryExplore(int index, string& inStream, int inLen) {
    int bIdx = -1;
    switch(inStream[index]) {
        case '(':
            bIdx = 0;
            break;
        case ')':
            bIdx = 1;
            break;
        case '{':
            bIdx = 2;
            break;
        case '}':
            bIdx = 3;
            break;
        case ',':
            bIdx = 4;
            break;
        case ';':
            bIdx = 5;
            break;
    }
    if (bIdx == -1)
        return -1;
    Name boundaryName(3, bIdx);
    names.push_back(boundaryName);
    return 1;
}

// int, main, return
int keywordExplore(int index, string& inStream, int inLen) {
    if (index + 2 <= inLen - 1 && inStream.substr(index, 3) == "int") {
        Name kwName(1, 0);
        names.push_back(kwName);
        return 3;
    } else if (index + 3 <= inLen - 1 && inStream.substr(index, 4) == "main") {
        Name kwName(1, 1);
        names.push_back(kwName);
        return 4;
    } else if (index + 5 <= inLen - 1 && inStream.substr(index, 6) == "return") {
        Name kwName(1, 2);
        names.push_back(kwName);
        return 6;
    }
    return -1;
}

bool isIdChar(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int idExplore(int index, string& inStream, int inLen) {
    int pIdx = 1;
    string idStr = "";
    idStr += inStream[index];
    while (index + pIdx <= inLen - 1 && isIdChar(inStream[index + pIdx])) {
        idStr += inStream[index + pIdx];
        pIdx++;
    }

    int idNameIndex = -1;
    for (int i = 0; i < identifieres.number; i++) {
        if (identifieres.str[i] == idStr) {
            idNameIndex = i;
            break;
        }
    }

    if (idNameIndex == -1) {
        Name idName(4, identifieres.number);
        names.push_back(idName);
        identifieres.str[identifieres.number] = idStr;
        identifieres.number++;
    } else {
        Name idName(4, idNameIndex);
        names.push_back(idName);
    }
    
    return pIdx;
}

void lexer(string inStream) {
    int index = 0, inLen = inStream.length(), pIdx = -1;
    char curChar;
    while ((curChar = inStream[index]) != '#') {
        string word;
        word.append(1u, curChar);
        if (curChar == '\n' || curChar == ' ') {
            index++;
            continue;
        } else {
            if ((pIdx = uintExplore(index, inStream, inLen)) == -1) {
                if ((pIdx = opExplore(index, inStream, inLen)) == -1) {
                    if ((pIdx = boundaryExplore(index, inStream, inLen)) == -1) {
                        if ((pIdx = keywordExplore(index, inStream, inLen)) == -1) {
                            pIdx = idExplore(index, inStream, inLen);
                        }
                    }
                }
            }
            index += pIdx;
        }
    }
    for (index = 0; index < names.size(); index++) {
        cout << "<" << names[index].type << "," << names[index].index << ">";
    }
    cout << endl;
    cout << "identifieres:";
    for (index = 0; index < identifieres.number - 1; index++)
        cout << identifieres.str[index] << " ";
    cout << identifieres.str[identifieres.number - 1] << endl;

    cout << "Unsigned_integer:";
    for (index = 0; index < Unsigned_integer.number - 1; index++)
        cout << Unsigned_integer.str[index] << " ";
    cout << Unsigned_integer.str[Unsigned_integer.number - 1] << endl;
}

int main(int argc, char const *argv[])
{
    string inStream = "";
    char c;
    FILE *pTestFile;
    pTestFile = fopen("lexerText", "r");
    while ((c = fgetc(pTestFile)) != EOF) {
        inStream += c;
    }    
    lexer(inStream);

    return 0;
}                                 