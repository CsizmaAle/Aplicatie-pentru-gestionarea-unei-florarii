#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
using namespace std;


ifstream stoc("flori.in");
ifstream com("comenzi.in");
ofstream offs("flori.out");
ofstream offc("comenzi.out");

struct floare // detalii floare
{
    char cul[15], nume[20];
    int cant, pret;
}fl[100];

struct client // detalii comnda
{
    char nume[15], prenume[15];
};

struct comanda
{
    client c;
    int tip, cat;
}cmd[100];


void meniu();
void a_stoc(floare fl[100], int k);
void a_fl_stoc(floare fl[100], int k);
void a_c_comenzi(comanda cmd[100], int m, floare fl[100], int k);
void salvare_stoc(floare fl[100], int k);
void salvare_comenzi(comanda cmd[100], int m);
void ad_stoc(floare fl[100], int& k);
void ad_comanda(comanda cmd[100], int& m);
void a_comenzi(comanda cmd[100], int m, floare fl[100], int k);
void citire_c(comanda cmd[100], int& m);
void citire_s(floare fl[100], int& k);
void m_stoc(floare fl[100], int k);
void total(floare fl[100], int k);
void verificare(floare fl[100], int k, comanda cmd[100], int m);
void m_comanda(comanda cmd[100], int m);
void stergere(comanda cmd[100], int& m);
void calcul(floare fl[100], int k, comanda cmd[100], int m);

int n, k, m;

int main()
{
    meniu();
    return 0;
}

void meniu()
{
    cout << endl << "   Bine ati venit la NANELE!" << endl;
    do
    {
        system("CLS");
        cout << endl << "           MENIU" << endl;
        cout << endl << "     1.Citire stoc" << endl;
        cout << "     2.Afisare stoc" << endl;
        cout << "     3.Modificare stoc" << endl;
        cout << "     4.Afisare stoc dupa o anumita floare" << endl;
        cout << "     5.Adaugare floare in stoc" << endl;
        cout << "     6.Total stoc" << endl;
        cout << "     7.Copiere si anexare in alt fisier" << endl;
        cout << endl;
        cout << "     8.Citire comenzi" << endl;
        cout << "     9.Verificare comenzi-stoc" << endl;
        cout << "     10.Afisare comenzi" << endl;
        cout << "     11.Modificare comanda" << endl;
        cout << "     12.Stergere comanda" << endl;
        cout << "     13.Calculare pret comenzi" << endl;
        cout << "     14.Adaugare comanda" << endl;
        cout << "     15.Afisare o anumita comanda" << endl;
        cout << "     16.Copiere si anexare in alt fisier" << endl;
        cout << endl << "     17.Iesire meniu" << endl;

        cout << endl << "    Alege o optiune: "; cin >> n;
        cout << endl << endl;
        switch (n)
        {
        case 1: citire_s(fl, k); break;
        case 2: a_stoc(fl, k); break;
        case 3: m_stoc(fl, k); break;
        case 4: a_fl_stoc(fl, k); break;
        case 5: ad_stoc(fl, k); break;
        case 6: total(fl, k); break;
        case 7: salvare_stoc(fl, k); break;
        case 8: citire_c(cmd, m); break;
        case 9: verificare(fl, k, cmd, m); break;
        case 10: a_comenzi(cmd, m, fl, k); break;
        case 11: m_comanda(cmd, m); break;
        case 12: stergere(cmd, m); break;
        case 13: calcul(fl, k, cmd, m); break;
        case 14: ad_comanda(cmd, m); break;
        case 15: a_c_comenzi(cmd, m, fl, k); break;
        case 16: salvare_comenzi(cmd, m); break;
        }
        system("PAUSE");
    } while (n != 17);

}

void a_stoc(floare fl[100], int k)
{
    cout << "     " << setw(3) << "Nr." << setw(13) << "Floare" << setw(12) << "Culoare";
    cout << setw(8) << "Cant." << setw(14) << "Pret/Fir" << endl;
    cout << "    -----------------------------------------------------" << endl;
    for (int i = 1; i <= k; i++)
    {
        cout << "     " << setw(2) << i << setw(15) << fl[i].nume << setw(10) << fl[i].cul;
        cout << setw(7) << fl[i].cant << setw(10) << fl[i].pret << " RON" << endl;
    }
}

void citire_s(floare fl[100], int& k)
{
    stoc >> k;
    for (int i = 1; i <= k; i++)
        stoc >> fl[i].nume >> fl[i].cul >> fl[i].cant >> fl[i].pret;
}

void citire_c(comanda cmd[100], int& m)
{
    com >> m;
    for (int i = 1; i <= m; i++)
        com >> cmd[i].c.nume >> cmd[i].c.prenume >> cmd[i].tip >> cmd[i].cat;
}

void m_stoc(floare fl[100], int k)
{
    int gasit = 0;
    char flmod[12] = "";
    cout << "     Introduceti floarea a carei cantitati doriti sa o modificati: ";
    cin >> flmod;
    for (int i = 1; i <= k && !gasit; i++)
        if (strcmp(fl[i].nume, flmod) == 0)
        {
            gasit = 1;
            cout << "     Introduceti cantitatea:"; cin >> fl[i].cant;
        }
    if (!gasit)cout << "   Nu s-a putut gasi floarea" << endl;
}

void total(floare fl[100], int k)
{
    cout << "     Total flori in magazin: ";
    int sum = 0;
    for (int i = 1; i <= k; i++)
        sum += fl[i].cant;
    cout << sum << endl;
}

void verificare(floare fl[100], int k, comanda cmd[100], int m)
{
    for (int i = 1; i <= m; i++)
        if (fl[cmd[i].tip].cant < cmd[i].cat)
            cout << "     Mai trebuie " << cmd[i].cat - fl[cmd[i].tip].cant << " " << fl[cmd[i].tip].nume << endl;
}

void m_comanda(comanda cmd[100], int m)
{
    int gasit = 0;
    char num[15] = "";
    cout << "     Introduceti numele clientului care modifica comanda:";
    cin >> num;
    for (int i = 1; i <= m && !gasit; i++)
        if (strcmp(num, cmd[i].c.nume) == 0)
        {
            cout << "     Modificarile sunt:" << endl;
            cout << "     Tip floare:"; cin >> cmd[i].tip;
            cout << "     Numar fire:"; cin >> cmd[i].cat;
            gasit = 1;
        }
    if (!gasit)cout << "       Clientul nu a fost gasit" << endl;
}

void stergere(comanda cmd[100], int& m)
{
    int gasit = 0;
    cout << "     Numele clientului a carui comanda se sterge:";
    char num[15] = "";
    cin >> num;
    for (int i = 1; i <= m && !gasit; i++)
        if (strcmp(num, cmd[i].c.nume) == 0)
        {
            gasit = 1;
            for (int j = i; j < m; j++) cmd[j] = cmd[j + 1];
            m--;
        }
    if (!gasit)cout << "       Clientul nu a fost gasit" << endl;
}

void calcul(floare fl[100], int k, comanda cmd[100], int m)
{
    int sume[100] = { 0 };
    for (int i = 1; i <= m; i++)
    {
        sume[i] = fl[cmd[i].tip].pret * cmd[i].cat;
    }


    cout << "     " << setw(3) << "Nr." << setw(13) << "Nume" << setw(13) << "Prenume";
    cout << setw(14) << "Flori" << setw(14) << "Cantitate" << setw(6) << "Pret" << endl;
    cout << "    ------------------------------------------------------------------" << endl;
    for (int i = 1; i <= m; i++)
    {
        cout << "     " << setw(3) << i << setw(13) << cmd[i].c.nume;
        cout << setw(13) << cmd[i].c.prenume << setw(14) << fl[cmd[i].tip].nume;
        cout << setw(10) << cmd[i].cat << setw(9) << sume[i] << endl;

    }
}

void a_comenzi(comanda cmd[100], int m, floare fl[100], int k)
{
    cout << "     " << setw(3) << "Nr." << setw(13) << "Nume" << setw(13) << "Prenume";
    cout << setw(11) << "Flori" << setw(14) << "Cantitate" << endl;
    cout << "    --------------------------------------------------------" << endl;
    for (int i = 1; i <= m; i++)
    {
        cout << "     " << setw(3) << i << setw(13) << cmd[i].c.nume;
        cout << setw(13) << cmd[i].c.prenume << setw(11) << fl[cmd[i].tip].nume;
        cout << setw(8) << cmd[i].cat << endl;
    }
}

void ad_comanda(comanda cmd[100], int& m)
{
    m++;
    cout << "     Introduceti datele comenzii:" << endl;
    cout << "     Nume client:"; cin >> cmd[m].c.nume;
    cout << "     Prenume client:"; cin >> cmd[m].c.prenume;
    cout << "     Tip(nr nat):"; cin >> cmd[m].tip;
    cout << "     Cantitate:"; cin >> cmd[m].cat;
    cout << endl;
}

void a_c_comenzi(comanda cmd[100], int m, floare fl[100], int k)
{
    char nu[15] = "";
    int gasit = 0;
    cout << "     Intoduceti numele clientului:"; cin >> nu;
    for (int i = 1; i <= m && !gasit; i++)
        if (strcmp(nu, cmd[i].c.nume) == 0)
        {
            gasit = 1;
            cout << "     Datele sunt" << endl;
            cout << "     " << setw(3) << "Nr." << setw(13) << "Nume" << setw(13) << "Prenume";
            cout << setw(11) << "Flori" << setw(14) << "Cantitate" << endl;
            cout << "    --------------------------------------------------------" << endl;
            cout << "     " << setw(3) << i << setw(13) << cmd[i].c.nume << setw(13) << cmd[i].c.prenume;
            cout << setw(11) << fl[cmd[i].tip].nume << setw(8) << cmd[i].cat << endl;
        }

}

void salvare_comenzi(comanda cmd[100], int m)
{

    offc << "     " << setw(3) << "Nr." << setw(13) << "Nume" << setw(13) << "Prenume";
    offc << setw(14) << "Flori" << setw(14) << "Cantitate" << endl;
    offc << "    -----------------------------------------------------------" << endl;
    for (int i = 1; i <= m; i++)
    {
        offc << "     " << setw(3) << i << setw(13) << cmd[i].c.nume;
        offc << setw(13) << cmd[i].c.prenume << setw(14) << fl[cmd[i].tip].nume;
        offc << setw(8) << cmd[i].cat << endl;
    }
}

void salvare_stoc(floare fl[100], int k)
{
    offs << "     " << setw(3) << "Nr." << setw(13) << "Floare" << setw(12) << "Culoare";
    offs << setw(8) << "Cant." << setw(14) << "Pret/Fir" << endl;
    offs << "    -----------------------------------------------------" << endl;
    for (int i = 1; i <= k; i++)
    {
        offs << "     " << setw(2) << i << setw(15) << fl[i].nume;
        offs << setw(10) << fl[i].cul << setw(7) << fl[i].cant;
        offs << setw(10) << fl[i].pret << " RON" << endl;
    }

}

void a_fl_stoc(floare fl[100], int k)
{
    char flo[12] = "";
    int gasit = 0;
    cout << "     Introduceti floarea ale carei date doriti afisate:"; cin >> flo;
    cout << endl;
    for (int i = 1; i <= k && !gasit; i++)
        if (strcmp(fl[i].nume, flo) == 0)
        {
            gasit = 1;
            cout << "     " << setw(3) << "Nr." << setw(13) << "Floare" << setw(12) << "Culoare";
            cout << setw(8) << "Cant." << setw(14) << "Pret/Fir" << endl;
            cout << "    -----------------------------------------------------" << endl;
            cout << "     " << setw(2) << i << setw(15) << fl[i].nume << setw(10) << fl[i].cul;
            cout << setw(7) << fl[i].cant << setw(10) << fl[i].pret << " RON" << endl;
        }
    if (!gasit)cout << "   Nu s-a putut gasi floarea" << endl;
}

void ad_stoc(floare fl[100], int& k)
{
    k++;
    cout << "     Introduceti datele florii care se adauga: " << endl;
    cout << "     Floare: "; cin >> fl[k].nume;
    cout << "     Culoare: "; cin >> fl[k].cul;
    cout << "     Cantitate: "; cin >> fl[k].cant;
    cout << "     Pret/fir: "; cin >> fl[k].pret;
}
