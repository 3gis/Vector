#include "functions.h"

int naujasStudentas(int& studentusk, vector<studentai>& M, bool& vidurkis) {
    string pasirinkimas;
    string p;
    float suma = 0;
    int masyvod = 0;
    vector<int> namudarbai;
    while (true) {
        cout << "Ar norite skaityti is failo? (Y/N)";
        cin >> pasirinkimas;
        if (pasirinkimas == "y" || pasirinkimas == "Y") {
            ifstream fd;
            cout << "**Ikelkite txt faila i programos aplankala!** \n Iveskite txt failo pavadinima: <pavadinimas>.txt \n";
            cin >> pasirinkimas;
            cout << "\n";
            if (pasirinkimas[pasirinkimas.length() - 4] == '.')
                fd.open(pasirinkimas);
            else
                fd.open(pasirinkimas + ".txt");
            try {
                if (fd.is_open()) {
                    std::stringstream ss;
                    ss << fd.rdbuf();
                    fd.close();
                    int stulpeliai = 0;
                    while (ss >> pasirinkimas) {
                        if (pasirinkimas == "Egz." || pasirinkimas == "Egzaminas") {
                            stulpeliai++;
                            break;
                        }
                        else
                            stulpeliai++;
                    }
                    while (!ss.eof()) {
                        studentai k;
                        studentusk++;
                        string vardas, pavarde;
                        ss >> vardas >> pavarde;
                        k.setVardas(vardas);
                        k.setPavarde(pavarde);
                        for (int i = 0; i < stulpeliai - 3; i++) {
                            ss >> pasirinkimas;
                            suma += atof(pasirinkimas.c_str());
                            namudarbai.push_back(atof(pasirinkimas.c_str()));
                        }
                        ss >> p;
                        namudarbai.push_back(atof(p.c_str()));
                        if (vidurkis == true)
                            k.setGalutinisVid(((double)(suma / (stulpeliai - 3)) * 0.40 + 0.60 * atof(p.c_str())));
                        else {
                            sort(namudarbai.begin(), namudarbai.end());
                            k.setGalutinisMed(mediana(namudarbai, stulpeliai - 2));
                        }
                        M.push_back(k);
                        suma = 0;
                        namudarbai.clear();
                    }
                    cout << "Nuskaityta: " << studentusk + 1 << " rezultatu \n";
                    naujasStudentas(studentusk, M, vidurkis);
                    return 0;
                }
                else {
                    throw(1);
                }
            }
            catch (int) {
                cout << "Failas nerastas!!! \n";
            }
        }
        else {
            cout << "Rankinis studentu irasymas... \n";
            break;
        }
    }
    while (true) {
        cout << "Ar norite prideti studenta? (Y/N)";
        cin >> pasirinkimas;
        if (pasirinkimas == "y" || pasirinkimas == "Y") {
            studentusk++;
            M.push_back(studentai());
            string t;
            cout << "Iveskite studento varda: ";
            cin >> t;
            M[studentusk].setVardas(t);
            cout << endl << "Iveskite studento pavarde: ";
            cin >> t;
            M[studentusk].setPavarde(t);
            cout << endl << "Ar norite atsitiktinai sugeneruoti rezultatus? (Y/N): ";
            cin >> pasirinkimas;
            if (pasirinkimas == "Y" || pasirinkimas == "y") {
                int limitas = rand() % 100 + 1;
                for (int i = 0; i < limitas; i++) {
                    masyvod++;
                    namudarbai.push_back(rand() % 10 + 1);
                    namudarbai.push_back(rand() % 10 + 1); // egzamino balas
                }
            }
            else {
                while (true) {
                    cout << endl << "Iveskite studento namu darbu pazymius (Iveskite ne skaiciu arba 0, kad baigtumete irasyma): " << endl;
                    cin >> p;
                    for (auto i = p.begin(); i < p.end(); i++)
                        if (*i == ',')
                            *i = '.';
                    double x = atof(p.c_str());
                    cout << "Priimtas kaip: " << x << endl;
                    if (x != 0) {
                        if (x - floor(x) == 0) {
                            masyvod++;
                            namudarbai.push_back(x);
                        }
                        else cout << "Tik sveikieji skaiciai!" << endl;
                    }
                    else {
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << endl << "Namu darbu rezultatu irasymas baigtas.." << endl;
                        while (true) {
                            cout << "Iveskite egzamino rezultata: ";
                            cin >> p;
                            for (auto i = p.begin(); i < p.end(); i++)
                                if (*i == ',')
                                    *i = '.';
                            x = atof(p.c_str());
                            cout << "Priimtas kaip: " << x << endl;
                            if (x != 0) {
                                if (x - floor(x) == 0) {
                                    masyvod++;
                                    namudarbai.push_back(x);
                                    break;
                                }
                                else cout << "Tik sveikieji skaiciai!" << endl;
                            }
                            else {
                                cin.clear();
                                cin.ignore(100, '\n');
                            }
                        }
                        break;
                    }
                }
            }
        }
        else {
            cout << "Rezultatu irasymas baigtas.." << endl;
            return 0;
        }
        break;
    }
    for (int i = 0; i < masyvod - 1; i++)
        suma += namudarbai[i];
    M[studentusk].setGalutinisVid((double)suma / (masyvod - 1) * 0.4 + 0.6 * namudarbai.back());
    sort(namudarbai.begin(), namudarbai.end());
    M[studentusk].setGalutinisMed(mediana(namudarbai, masyvod));
    cout << "-----------------------------------------" << endl;
    namudarbai.clear();
    naujasStudentas(studentusk, M, vidurkis);
    return 0;
}
ofstream& operator << (ofstream& os, const studentai& gc){
    char buffer[80];
    sprintf(buffer, "%-20s %-20s %-20.2lf \n", gc.getPavarde().c_str(), gc.getVardas().c_str(), gc.getGalutinisVid());
    os << buffer;
    return os;
}
studentai& studentai::operator=(const studentai& gc1){
    if(this == &gc1)
        return *this;
    this->vardas = gc1.vardas;
    this->pavarde = gc1.pavarde;
    this->galutinisMed = gc1.galutinisMed;
    this->galutinisVid = gc1.galutinisVid;
    return *this;
}
double mediana(vector<int>M, int masyvod) {
    return masyvod % 2 == 0 ? (double)(((M[(masyvod / 2) - 1]) + (M[(masyvod / 2)])) / 2.0) : M[(masyvod / 2)];
}
bool lyginimas(studentai& a, studentai& b) {
    return a.getPavarde() < b.getPavarde();
}
bool testLyginimas(studentai& a,studentai& b) {
    return a.getGalutinisVid() > b.getGalutinisVid();
}
void spausdinti(vector<studentai>& studentas, bool vidurkis, ofstream& ff) {
    char buffer[80];
    if (vidurkis == true)
        sprintf(buffer, "%-20s %-20s %-20s \n", "Pavarde", "Vardas", "Galutinis (Vid.)");
    else
        sprintf(buffer, "%-20s %-20s %-20s \n", "Pavarde", "Vardas", "Galutinis (Med.)");
    ff << buffer;
    for (int i = 0; i < 80; i++, ff << "-");
    ff << "\n";
    if (vidurkis == true) {
        for (auto i : studentas) {
            //sprintf(buffer, "%-20s %-20s %-20.2lf \n", i.getPavarde().c_str(), i.getVardas().c_str(), i.getGalutinisVid());
            ff << i;
        }
    }
    else {
        for (auto i : studentas) {
            //sprintf(buffer, "%-20s %-20s %-20.2lf \n", i.getPavarde().c_str(), i.getVardas().c_str(), i.getGalutinisMed());
            ff << i;
        }
    }
}
void Generuotifailus(string a, int& b) {
    auto start = std::chrono::high_resolution_clock::now();
    ofstream ff(a);
    srand(time(NULL));
    long int limitai[5] = { 1000,10000,100000,1000000,10000000 };
    //long int limitas = limitai[rand() % 5];
    cout << "Kuriamas " << limitai[b] << " dydzio sarasas faile " << a << "\n";
    ff << "Vardas Pavarde Egz. \n";
    for (long int i = 0; i < limitai[b]; i++) {
        ff << "Vardas" << i << " Pavarde" << i << " ";
        ff << rand() % 10 + 1;
        ff << "\n";

    }
    ff.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "=== Irasymas uztruko: " << diff.count() << "\n";
}
void TestNuskaitymas(string pasirinkimas, int& b, vector <studentai>& M) {
    cout << "Skaitomi vardai is failo " << pasirinkimas << "\n";
    auto start = std::chrono::high_resolution_clock::now();
    ifstream fd;
    fd.open(pasirinkimas);
    string p;
    if (fd.is_open()) {
        std::stringstream ss;
        ss << fd.rdbuf();
        fd.close();
        while (ss >> pasirinkimas) {
            if (pasirinkimas == "Egz." || pasirinkimas == "Egzaminas")
                break;
        }
        string t1,t2;
        while (!ss.eof()) {
            studentai k;

            ss >> t1 >> t2 >> p;
            k.setVardas(t1);
            k.setPavarde(t2);
            k.setGalutinisVid(atof(p.c_str()));
            M.push_back(k);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "=== Skaitymas uztruko: " << diff.count() << "\n";
}
void TestRusiavimas(int& k, vector <studentai>& studentas, vector<studentai>& kietekai) { //kietekai yra vargsiukai
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i : studentas) {
        if (i.getGalutinisVid() < 5)
            kietekai.push_back(i);
    }
    studentas.resize(studentas.size() - kietekai.size());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "=== Rusiavimas uztruko: " << diff.count() << "\n";
}
