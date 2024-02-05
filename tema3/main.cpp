#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define MAX 100

using namespace std;

class Student {
public:
    string nume, spec;
    int an;
    float media;

    // Constructors
    Student() : nume(""), spec(""), an(0), media(0.0) {}
    Student(const string& n, const string& s, int a, float m)
            : nume(n), spec(s), an(a), media(m) {}
};

bool compNume(Student s1, Student s2) { return s1.nume > s2.nume; }

bool compMedia(Student s1, Student s2) { return s1.media < s2.media; }

class TabStudenti {
public:
    void sorteaza(Student tab[], int n, bool (*comparator)(Student, Student)) {
        Student t;
        bool modificat;

        do {
            modificat = false;
            for (int i = 0; i < n - 1; i++)
                if (comparator(tab[i], tab[i + 1])) {
                    t = tab[i];
                    tab[i] = tab[i + 1];
                    tab[i + 1] = t;
                    modificat = true;
                }
        } while (modificat);
    }
};

void afiseaza(Student studenti[], int n) {
    for (int i = 0; i < n; i++)
        cout << '\t' << studenti[i].nume << ", " << studenti[i].spec << ", " <<
             studenti[i].an << ", " << studenti[i].media << '\n';
}

int main() {
    Student* studenti = new Student[MAX];

    // Citirea datelor din fișier
    ifstream intrare("studenti.txt");
    if (intrare.fail()) {
        cout << "Eroare deschidere fisier";
        return 1;
    }

    int contor = 0;
    string line;
    while (getline(intrare, line)) {
        stringstream ss(line);
        string nume, spec;
        int an;
        float media;

        getline(ss, nume, ',');
        getline(ss, spec, ',');
        ss >> an;
        ss.ignore(); // Ignorăm virgula
        ss >> media;

        studenti[contor] = Student(nume, spec, an, media);
        contor++;
    }

    intrare.close();

    // Sortare după nume și afișare
    TabStudenti tabStudenti;
    tabStudenti.sorteaza(studenti, contor, compNume);
    cout << "Sortare dupa nume:\n";
    afiseaza(studenti, contor);

    // Sortare după medie și afișare
    tabStudenti.sorteaza(studenti, contor, compMedia);
    cout << "\nSortare dupa medie:\n";
    afiseaza(studenti, contor);

    // Eliberare memorie alocată dinamic
    delete[] studenti;

    return 0;
}
