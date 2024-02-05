#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Student {
    string nume, spec;
    int an;
    float media;

public:
    Student(string nume, string spec, int an, float media)
            : nume(nume), spec(spec), an(an), media(media) {}

    static bool compNume(Student *s1, Student *s2) {
        return s1->nume > s2->nume;
    }

    static bool compMedia(Student *s1, Student *s2) {
        return s1->media < s2->media;
    }

    friend class ListaStudenti;
};

class ListaStudenti {
private:
    int n;
    Student **studenti;

    int partitie(int s, int d, bool (*comparator)(Student*, Student*)) {
        Student *pivot = studenti[s], *t;
        int i = s + 1, j = d;

        while (i <= j) {
            while (!comparator(studenti[i], pivot) && i <= n - 1)
                i++;
            while (comparator(studenti[j], pivot) && j > 0)
                j--;

            if (i <= j) {
                t = studenti[i];
                studenti[i] = studenti[j];
                studenti[j] = t;
                i++;
                j--;
            }
        }

        t = studenti[s];
        studenti[s] = studenti[j];
        studenti[j] = t;

        return j;
    }

    void quicksort(int s, int d, bool (*comparator)(Student*, Student*)) {
        if (s < d) {
            int poz = partitie(s, d, comparator);
            quicksort(s, poz, comparator);
            quicksort(poz + 1, d, comparator);
        }
    }

public:
    ListaStudenti(string nume) {
        ifstream intrare(nume);
        if (intrare.fail()) {
            cout << "Eroare deschidere fisier";
            exit(1);
        }

        int i = 0;
        n = 0;
        string temp;

        while (intrare >> temp) {
            n++;
        }

        cout << "\n nr studenti: " << n;

        studenti = new Student*[n];

        intrare.clear();
        intrare.seekg(0, ios::beg);

        i = 0; // Reset i
        while (intrare >> temp) {
            stringstream linie(temp);
            string nume, spec;
            int an;
            float media;

            getline(linie, nume, ',');
            getline(linie, temp, ',');
            nume = nume + " " + temp;

            getline(linie, spec, ',');
            getline(linie, temp, ',');
            an = stoi(temp);

            getline(linie, temp, ',');
            media = stof(temp);

            studenti[i] = new Student(nume, spec, an, media);
            i++;
        }

        intrare.close();
    }

    int getN() {
        return n;
    }

    void afiseaza() {
        for (int i = 0; i < n; i++)
            cout << '\t' << studenti[i]->nume << "," << studenti[i]->spec << ","
                 << studenti[i]->an << "," << studenti[i]->media << '\n';
    }

    void sorteaza(bool (*comparator)(Student*, Student*)) {
        Student *t;
        bool modificat;

        do {
            modificat = false;

            for (int i = 0; i < n - 1; i++) {
                if (comparator(studenti[i], studenti[i + 1])) {
                    t = studenti[i];
                    studenti[i] = studenti[i + 1];
                    studenti[i + 1] = t;
                    modificat = true;
                }
            }
        } while (modificat);
    }

    void sorteazaQ(bool (*comparator)(Student*, Student*)) {
        quicksort(0, n - 1, comparator);
    }
};

int main() {
    ListaStudenti ls("elevi.txt");
    cout << "\n Am citit " << ls.getN() << " studenti:" << '\n';
    ls.afiseaza();

    cout << "Studenti sortati alfabetic:" << '\n';
    ls.sorteazaQ(Student::compNume);
    ls.afiseaza();

    cout << "Studenti sortati dupa medii:" << '\n';
    ls.sorteazaQ(Student::compMedia);
    ls.afiseaza();

    return 0;
}
