#include "testingas.h"
int main ()
{
    //1 uzduotis: Vector pavyzdines funkcijos
    cout << "Ijungiamos pavyzdines funkcijos..\n";
    std::string a;
    Vector<double> i;
    cout << "Vector i dydis: " << i.size() << "\n";
    cout << "Vector i capacity: " << i.capacity() << "\n";
    cout << "Vector i pradzios adresas: " << i.begin() << "\n";
    cout << "Vector i pabaigos adresas: " << i.end() << "\n";
    cout << "Pridedama reiksmiu i konteineri i: {5,78,21,21.22,6.88}\n";
    i.push_back(5);
    i.push_back(78);
    i.push_back(21);
    i.push_back(21.22);
    i.push_back(6.88);
    cout << "Spausdinamos pridetos reiksmes: ";
    for(auto k : i){
        cout << k << " ";
    }
    cout << "\n";
    cout << "Vector i dydis: " << i.size() << "\n";
    cout << "Vector i capacity: " << i.capacity() << "\n";
    cout << "Vector i pradzios adresas: " << i.begin() << "\n";
    cout << "Vector i pabaigos adresas: " << i.end() << "\n";
    cout << "Kuriamas naujas Vector h, kuris turi 20 ketvertu..\n";
    Vector<double> h(20,4);
    cout << "Sukurta. Tikrinama..\n";
    for(auto k : h){
        cout << k << " ";
    }
    cout << "\n";
    cout << "Vector h prilyginamas Vector'iui i..\n";
    h = i;
    cout << "Tikrinama..\n";
    for(auto k : h){
        cout << k << " ";
    }
    cout << "\n";
    cout << "Vector h dydis: " << h.size() << "\n";
    cout << "Vector h capacity: " << h.capacity() << "\n";
    cout << "Vector h pradzios adresas: " << h.begin() << "\n";
    cout << "Vector h pabaigos adresas: " << h.end() << "\n";
    cout << "Antroji uzduotis: std::vector ir Vector lyginimas..\n";
    // 2 uzduotis: efektyvumo analize - std::vector ir Vector
    unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
    clock_t start, end;
    cout << "Dydis: " << sz << ".. Pildoma (std::vector)..\n";
    int countt = 0;
    start = clock();
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i){
        v1.push_back(i);
        if(v1.capacity()==v1.size())
            countt++;
    }
    end = clock();
    double diff = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Uzpildyta per: " << diff << ", atminties perskirtymas padarytas "<< countt <<" kartu\n";

    // Pradėti v2 užpildymo laiko matavimą
    start = clock();
    Vector<int> v2;
    countt = 0;
    cout << "Dydis: " << sz << ".. Pildoma (Vector)..\n";
    for (int i = 1; i <= sz; ++i){
        v2.push_back(i);
        if(v2.capacity()==v2.size())
            countt++;
    }
        // Baigti v2 užpildymo laiko matavimą
    end = clock();
    diff = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Uzpildyta per: " << diff << ", atminties perskirtymas padarytas "<< countt <<" kartu\n";

    return 0;
}
