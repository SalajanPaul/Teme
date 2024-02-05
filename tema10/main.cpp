#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

class Persoana
{
public:
    string nume;
    string prenume;

    Persoana(const string& n, const string& p)
        : nume(n), prenume(p) {}

    bool operator<(const Persoana& other) const
    {
        return nume < other.nume;
    }
};

class Elev : public Persoana
{
public:
    int anStudiu;

    Elev(const string& n, const string& p, int an)
        : Persoana(n, p), anStudiu(an) {}
};

class Disciplina
{
public:
    int codD;
    string denumire;

    Disciplina(int cod, const string& den)
        : codD(cod), denumire(den) {}
};

class Nota
{
public:
    int codD;
    int codE;
    string data;
    int nota;

    Nota(int codDisciplina, int codElev, const string& d, int n)
        : codD(codDisciplina), codE(codElev), data(d), nota(n) {}
};

class ManagerNote
{
private:
    vector<Elev> elevi;
    vector<Disciplina> discipline;
    vector<Nota> note;

public:
    void citesteDate(const string& numeFisierElevi, const string& numeFisierDiscipline, const string& numeFisierNote)
    {
        citesteElevi(numeFisierElevi);
        citesteDiscipline(numeFisierDiscipline);
        citesteNote(numeFisierNote);
    }

    void afiseazaMediile()
    {
        map<int, map<int, vector<int>>> mediiElevi;

        for (const auto& nota : note)
        {
            mediiElevi[nota.codE][nota.codD].push_back(nota.nota);
        }

        for (auto& [codElev, mediiDiscipline] : mediiElevi)
        {
            float mediaElev = 0.0;
            int nrDiscipline = 0;

            for (auto& [codDisciplina, noteDisciplina] : mediiDiscipline)
            {
                float mediaDisciplina = 0.0;

                for (int nota : noteDisciplina)
                {
                    mediaDisciplina += nota;
                }

                mediaDisciplina /= noteDisciplina.size();
                cout << "Elev: " << elevi[codElev].nume << " " << elevi[codElev].prenume
                     << ", Disciplina:" << discipline[codDisciplina].denumire
                     << ", Medie: " << mediaDisciplina << endl;

                mediaElev += mediaDisciplina;
                nrDiscipline++;
            }

            if (nrDiscipline > 0)
            {
                mediaElev /= nrDiscipline;
                cout << "Media generala pentru elevul " << elevi[codElev].nume << " " << elevi[codElev].prenume
                     << ":" << mediaElev << endl;
            }
        }
    }

private:
    void citesteElevi(const string& numeFisier)
    {
        ifstream file(numeFisier);
        if (!file.is_open())
        {
            cerr << "Nu s-a putut deschide fisierul" << numeFisier << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        while (getline(file, line))
        {
            int cod;
            string nume, prenume;
            int an;

            stringstream ss(line);
            ss >> cod;
            ss.ignore();
            getline(ss, nume, ',');
            getline(ss, prenume, ',');
            ss >> an;

            elevi.emplace_back(nume, prenume, an);
        }

        file.close();
        sort(elevi.begin(), elevi.end());
    }

    void citesteDiscipline(const string& numeFisier)
    {
        ifstream file(numeFisier);
        if (!file.is_open())
        {
            cerr << "Nu s-a putut deschide fisierul" << numeFisier << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        while (getline(file, line))
        {
            int cod;
            string denumire;

            stringstream ss(line);
            ss >> cod;
            ss.ignore();
            getline(ss, denumire, ',');
            discipline.emplace_back(cod, denumire);
        }

        file.close();
    }

    void citesteNote(const string& numeFisier)
    {
        ifstream file(numeFisier);
        if (!file.is_open())
        {
            cerr << "Nu s-a putut deschide fisierul " << numeFisier << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        while (getline(file, line))
        {
            int codD, codE, nota;
            string data;

            stringstream ss(line);
            ss >> codD;
            ss.ignore();
            ss >> codE;
            ss.ignore();
            ss >> data;
            ss.ignore();
            note.emplace_back(codD, codE, data, nota);
        }

        file.close();
    }
};

int main()
{
    ManagerNote managerNote;
    managerNote.citesteDate("elevi.txt", "discipline.txt", "note.txt");
    managerNote.afiseazaMediile();

    return 0;
}
