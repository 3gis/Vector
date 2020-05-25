#include "functions.h"

int main() {
    int studentusk = -1;
    string pasirinkimas;
    bool vidurkis = false;
    while (true) {
        cout << " Ar norite testuoti greicius? (Y/N) \n";
        cin >> pasirinkimas;
        if (pasirinkimas == "n" || pasirinkimas == "N") {
            while (true) {
                cout << "Skaiciuoti vidurki? (jei ne, bus skaiciuojama mediana) (Y/N)";
                cin >> pasirinkimas;
                if (pasirinkimas == "y" || pasirinkimas == "Y") {
                    vidurkis = true;
                    cout << "Bus skaiciuojamas vidurkis..\n";
                    break;
                }
                else if (pasirinkimas == "n" || pasirinkimas == "N") {
                    cout << "Bus skaiciuojama mediana..\n";
                    break;
                }
            }
            Vector<studentai> studentas;
            naujasStudentas(studentusk, studentas, vidurkis);
            std::sort(studentas.begin(), studentas.end(), lyginimas);
            ofstream ff("kursiokai.txt");
            spausdinti(studentas, vidurkis, ff);
        }
        else if (pasirinkimas == "y" || pasirinkimas == "Y") {
            int k;
            Vector <studentai> kietekai;
            Vector <studentai> studentas;
            cout << "Kuriami failai..\n ";
            ofstream fk("kietekai.txt");
            ofstream fv("vargsiukai.txt");
            string failuPavadinimai[5] = { "Pirmas.txt","Antras.txt","Trecias.txt","Ketvirtas.txt","Penktas.txt" };
            for (k = 0; k < 5; k++) {

                Generuotifailus(failuPavadinimai[k], k);
                TestNuskaitymas(failuPavadinimai[k], k, studentas);
                cout << "Sarasas rikiuojamas su funkcija sort.. \n";
                sort(studentas.begin(), studentas.end(), testLyginimas);
                cout << "Sarasas rusiuojamas i vargsiukus ir kietekus \n";
                TestRusiavimas(k, studentas, kietekai);
                cout << "Spausdinami sarasai i atskirus failus.. \n";
                spausdinti(kietekai, true, fv);
                spausdinti(studentas, true, fk);
                studentas.clear();
                kietekai.clear();
                cout << "----------------------------\n";
            }
            fk.close();
            fv.close();
        }
    }
    return 0;
}
