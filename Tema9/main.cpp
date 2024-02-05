#include "ListaStudenti.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ListaStudenti ls;

    ls.afiseaza();

    ls.sorteaza(Student::compNume);

    ls.afiseaza();

    ls.sorteaza(Student::compMedia);

    ls.afiseaza();

    ls.sorteazaQ(Student::compNume);

    ls.afiseaza();

    ls.sorteazaQ(Student::compMedia);

    ls.afiseaza();

    return 0;
}

// ListaStudenti.h

#ifndef LABORATOR1_LISTASTUDENTI_H
#define LABORATOR1_LISTASTUDENTI_H

#include "Nod.h"

class ListaStudenti {
private:
    Nod *varf;
    int nrNoduri;

    void eliminaVarf();

    int partitie(int, int, bool (*)(Student*, Student*));

    void quicksort(int, int, bool (*)(Student*, Student*));

public:
    ListaStudenti();
    ~ListaStudenti();

    void adauga(Student *);
    void afiseaza();
    void sterge(string);
    Student*& operator[](int);

    void sorteaza(bool (*)(Student*, Student*));
    void sorteazaQ(bool (*)(Student*, Student*));
};

#endif // LABORATOR1_LISTASTUDENTI_H

// ListaStudenti.cpp

#include "ListaStudenti.h"
#include <iostream>
#include <fstream>
#include <sstream>

ListaStudenti::ListaStudenti() : varf(nullptr), nrNoduri(0) {
    ifstream intrare("studenti.txt");

    if (intrare.fail()) {
        cout << "Eroare deschidere fisier";
        exit(1);
    }

    string temp;

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

        adauga(new Student(nume, spec, an, media));
    }

    intrare.close();
}

ListaStudenti::~ListaStudenti() {
    while (varf != nullptr) {
        eliminaVarf();
    }
}

void ListaStudenti::adauga(Student *s) {
    Nod *nou = new Nod(s);
    nou->urmator = varf;
    varf = nou;
    nrNoduri++;
}

void ListaStudenti::eliminaVarf() {
    if (varf != nullptr) {
        Nod *temp = varf;
        varf = varf->urmator;
        delete temp;
        nrNoduri--;
    }
}

void ListaStudenti::afiseaza() {
    cout << "Nr noduri: " << nrNoduri << '\n';

    for (Nod *a = varf; a; a = a->urmator) {
        a->afiseaza();
    }
}

void ListaStudenti::sterge(string nume) {
    Nod *prec = nullptr;

    for (Nod *a = varf; a; a = a->urmator) {
        if (a->ps->getNume() == nume) {
            if (prec == nullptr) {
                varf = a->urmator;
            } else {
                prec->urmator = a->urmator;
            }

            delete a;
            nrNoduri--;

            return;
        }

        prec = a;
    }

    cout << "Numele nu a fost gasit.\n";
}

Student*& ListaStudenti::operator[](int index) {
    Nod *current = varf;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->urmator;
    }

    if (current != nullptr) {
        return current->ps;
    } else {
        // Tratează cazul în care indexul este mai mare decât numărul de noduri
        // sau lista este goală. Poți arunca o excepție sau trata altfel.
        cerr << "Index invalid.\n";
        exit(1);
    }
}

void ListaStudenti::sorteaza(bool (*comparator)(Student*, Student*)) {
    Student *t;
    bool modificat;

    do {
        modificat = false;

        for (int i = 0; i < nrNoduri - 1; i++) {
            if (comparator((*this)[i], (*this)[i + 1])) {
                t = (*this)[i];
                (*this)[i] = (*this)[i + 1];
                (*this)[i + 1] = t;
                modificat = true;
            }
        }
    } while (modificat);
}

int ListaStudenti::partitie(int s, int d, bool (*comparator)(Student*, Student*)) {
    Student *pivot = (*this)[s];
    Student *t;
    int i = s + 1, j = d;

    while (i < j) {
        while (!comparator((*this)[i], pivot) && i < nrNoduri - 1)
            i++;
        while (comparator((*this)[j], pivot) && j > 0)
            j--;
        if (i < j) {
            t = (*this)[i];
            (*this)[i] = (*this)[j];
            (*this)[j] = t;
            i++;
