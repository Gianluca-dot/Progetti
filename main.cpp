#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

class Interazione {
public:
    string tipo;
    string data;
    string descrizione;
};

class Cliente {
public:
    string nome;
    string cognome;
    string telefono;
    vector<Interazione> interazioni;
};

vector<Cliente> clienti;
const string FILE_DATI = "clienti.csv";

void pulisciInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int cercaCliente(const string& nome, const string& cognome) {
    for (int i = 0; i < (int)clienti.size(); i++) {
        if (clienti[i].nome == nome && clienti[i].cognome == cognome)
            return i;
    }
    return -1;
}

void salvaDati() {
    ofstream file(FILE_DATI);
    if (!file) {
        cout << "Errore nel salvataggio dei dati.\n";
        return;
    }

    for (const Cliente& c : clienti) {
        file << "CLIENTE;" << c.nome << ';' << c.cognome << ';' << c.telefono << '\n';
        for (const Interazione& i : c.interazioni)
            file << "INTERAZIONE;" << i.tipo << ';' << i.data << ';' << i.descrizione << '\n';
    }
}

void caricaDati() {
    ifstream file(FILE_DATI);
    if (!file) return;

    clienti.clear();
    string riga;

    while (getline(file, riga)) {
        stringstream ss(riga);
        vector<string> campi;
        string campo;
        while (getline(ss, campo, ';')) campi.push_back(campo);

        if (campi.empty()) continue;

        if (campi[0] == "CLIENTE" && campi.size() >= 4) {
            Cliente c;
            c.nome = campi[1];
            c.cognome = campi[2];
            c.telefono = campi[3];
            clienti.push_back(c);
        } else if (campi[0] == "INTERAZIONE" && campi.size() >= 4 && !clienti.empty()) {
            Interazione i;
            i.tipo = campi[1];
            i.data = campi[2];
            i.descrizione = campi[3];
            clienti.back().interazioni.push_back(i);
        }
    }
}

void mostraInterazioni(const Cliente& c) {
    cout << "\n--- Gestione clienti ---\n";

    bool appuntamenti = false;
    bool contratti = false;

    for (const Interazione& i : c.interazioni) {
        if (i.tipo == "Appuntamento") {
            if (!appuntamenti) cout << "\nAppuntamenti:\n";
            appuntamenti = true;
            cout << "Data: " << i.data << " - " << i.descrizione << '\n';
        }
    }

    for (const Interazione& i : c.interazioni) {
        if (i.tipo == "Contratto") {
            if (!contratti) cout << "\nContratti:\n";
            contratti = true;
            cout << "Data: " << i.data << " - " << i.descrizione << '\n';
        }
    }

    if (!appuntamenti) cout << "\nAppuntamenti: nessuno\n";
    if (!contratti) cout << "Contratti: nessuno\n";
}

void aggiungiInterazione(Cliente& c, const string& tipo) {
    Interazione i;
    i.tipo = tipo;

    cout << "Data: ";
    getline(cin, i.data);
    cout << "Descrizione: ";
    getline(cin, i.descrizione);

    c.interazioni.push_back(i);
    cout << "Operazione completata.\n";
}

void gestioneCommerciale(Cliente& c) {
    while (true) {
        mostraInterazioni(c);
        cout << "\n1. Aggiungi appuntamento\n";
        cout << "2. Aggiungi contratto\n";
        cout << "3. Elimina cliente\n";
        cout << "4. Salva ed esci\n";
        cout << "Scelta: ";

        int scelta;
        if (!(cin >> scelta)) {
            cin.clear();
            pulisciInput();
            continue;
        }
        pulisciInput();

        if (scelta == 1) {
            aggiungiInterazione(c, "Appuntamento");
        } else if (scelta == 2) {
            aggiungiInterazione(c, "Contratto");
        } else if (scelta == 3) {
            char conferma;
            cout << "Confermi eliminazione del cliente? (s/n): ";
            cin >> conferma;
            pulisciInput();
            if (conferma == 's' || conferma == 'S') {
                int indice = cercaCliente(c.nome, c.cognome);
                if (indice != -1) clienti.erase(clienti.begin() + indice);
                salvaDati();
                cout << "Cliente eliminato.\n";
                return;
            }
        } else if (scelta == 4) {
            salvaDati();
            return;
        }
    }
}

void modificaAnagrafica(Cliente& c) {
    cout << "Nuovo nome: ";
    getline(cin, c.nome);
    cout << "Nuovo cognome: ";
    getline(cin, c.cognome);
    cout << "Nuovo telefono: ";
    getline(cin, c.telefono);
    cout << "Dati anagrafici modificati.\n";
}

void schedaCliente(int indice) {
    while (indice >= 0 && indice < (int)clienti.size()) {
        Cliente& c = clienti[indice];

        cout << "\n========== SCHEDA CLIENTE ==========\n";
        cout << "Dati anagrafici\n";
        cout << "Nome: " << c.nome << '\n';
        cout << "Cognome: " << c.cognome << '\n';
        cout << "Telefono: " << c.telefono << '\n';
        mostraInterazioni(c);

        cout << "\n1. Modifica dati anagrafici\n";
        cout << "2. Modifica dati commerciali\n";
        cout << "3. Elimina cliente\n";
        cout << "4. Salva ed esci\n";
        cout << "Scelta: ";

        int scelta;
        if (!(cin >> scelta)) {
            cin.clear();
            pulisciInput();
            continue;
        }
        pulisciInput();

        if (scelta == 1) {
            modificaAnagrafica(c);
            salvaDati();
        } else if (scelta == 2) {
            gestioneCommerciale(c);
        } else if (scelta == 3) {
            char conferma;
            cout << "Confermi eliminazione del cliente? (s/n): ";
            cin >> conferma;
            pulisciInput();
            if (conferma == 's' || conferma == 'S') {
                clienti.erase(clienti.begin() + indice);
                salvaDati();
                cout << "Cliente eliminato.\n";
                return;
            }
        } else if (scelta == 4) {
            salvaDati();
            return;
        }
    }
}

void cercaClienteMenu() {
    string nome, cognome;
    cout << "Nome: ";
    getline(cin, nome);
    cout << "Cognome: ";
    getline(cin, cognome);

    int indice = cercaCliente(nome, cognome);
    if (indice == -1) {
        cout << "Cliente non trovato.\n";
        return;
    }

    schedaCliente(indice);
}

void aggiungiCliente() {
    Cliente c;

    cout << "\n========== NUOVO CLIENTE ==========\n";
    cout << "Nome: ";
    getline(cin, c.nome);
    cout << "Cognome: ";
    getline(cin, c.cognome);
    cout << "Telefono: ";
    getline(cin, c.telefono);

    clienti.push_back(c);
    salvaDati();
    cout << "Cliente salvato.\n";
}

int main() {
    caricaDati();

    while (true) {
        cout << "\n========== INSURAPRO CRM ==========\n";
        cout << "1. Cerca Cliente\n";
        cout << "2. Aggiungi Cliente\n";
        cout << "3. Esci\n";
        cout << "Scelta: ";

        int scelta;
        if (!(cin >> scelta)) {
            cin.clear();
            pulisciInput();
            continue;
        }
        pulisciInput();

        if (scelta == 1) {
            cercaClienteMenu();
        } else if (scelta == 2) {
            aggiungiCliente();
        } else if (scelta == 3) {
            salvaDati();
            cout << "Dati salvati. Arrivederci.\n";
            break;
        }
    }

    return 0;
}
