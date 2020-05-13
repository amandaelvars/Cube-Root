// Amanda Elvarsdottir
// This program calculates the cuberoot to a second number of places. 

#pragma once
#ifndef _STRINGARITHMETIC_
#define _STRINGARITHMETIC_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv);
void removeleadingzeroes(string& a);
string add(string a, string b);
string sub(string a, string b);
string mult(string a, string b);
bool equals(string a, string b);
bool greaterthan(string a, string b);
bool lessthan(string a, string b);
void cuberoot(string a, string b);
#endif