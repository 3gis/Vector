#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "testingas.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;
using std::sort;

class zmogus{
protected:
    string vardas;
    string pavarde;
public:
    inline virtual string getVardas() const  {return vardas;}
    inline virtual string getPavarde() const {return pavarde;}
    inline virtual void setVardas(string x) {this-> vardas = x;}
    inline virtual void setPavarde(string x) {this-> pavarde = x;}
};
class studentai : public zmogus {
private:
    double galutinisVid;
    double galutinisMed;
public:
    studentai& operator=(const studentai& gc1);
    inline double getGalutinisVid() const {return galutinisVid;}
    inline double getGalutinisMed() const {return galutinisMed;}
    inline void setGalutinisVid(double x){ this->galutinisVid = x;}
    inline void setGalutinisMed(double x){ this->galutinisMed = x;}

};
ofstream& operator << (ofstream& os, const studentai& gc);
int naujasStudentas(int& studentusk, Vector<studentai>& M, bool& vidurkis);
double mediana(Vector<int>M, int masyvod);
bool lyginimas( studentai& a, studentai& b);
bool testLyginimas( studentai& a,  studentai& b);
void spausdinti(Vector<studentai>& studentas, bool vidurkis, ofstream& ff);
void Generuotifailus(string a, int& b);
void TestNuskaitymas(string pasirinkimas, int& b, Vector <studentai>& M);
void TestRusiavimas(int& k, Vector <studentai>& studentas, Vector<studentai>& kietekai);

#endif // FUNCTIONS_H_INCLUDED
