INSURAPRO CRM - PROGETTO WINDOWS + VISUAL STUDIO CODE

File principali:
- main.cpp             Codice sorgente C++
- clienti.csv          File dati del CRM
- compila_windows.bat  Compila il programma su Windows con g++
- .vscode/             Configurazione consigliata per VS Code

IMPORTANTE:
L'eseguibile Windows (.exe) deve essere generato su Windows con un compilatore
C++ Windows (MinGW-w64/MinGW). Il file Linux presente nella versione precedente
non e' un eseguibile Windows.

Per compilare:
1. Installa MinGW-w64/MinGW e Visual Studio Code con l'estensione C/C++.
2. Apri questa cartella in VS Code.
3. Esegui compila_windows.bat oppure usa il terminale:
   g++ -std=c++17 -O2 -o InsuraPro_CRM.exe main.cpp
4. Avvia InsuraPro_CRM.exe.

Il programma salva i dati in clienti.csv nella stessa cartella dell'eseguibile.
