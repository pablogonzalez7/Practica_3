#include "lz78.h"
#include <iostream>
using namespace std;

struct Entry {
    int prefijo;
    char c;
};

int longitudChar(const char* texto) {
    int n = 0;
    while (texto != nullptr && texto[n] != '\0') {
        n++;
    }
    return n;
}

int findEntry(Entry* dict, int size, int prefijo, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefijo == prefijo && dict[i].c == c) {
            return i;
        }
    }
    return -1;
}

void copiarFrase(Entry* dict, int index, char* temp, int& pos) {
    if (index == 0) return;

    copiarFrase(dict, dict[index].prefijo, temp, pos);
    temp[pos++] = dict[index].c;
}

char* decompressLZ78(const char* compressed, int tam) {
    int capacidadResultado = tam * 20 + 50;
    char* resultado = new char[capacidadResultado];
    int r = 0;

    Entry* dict = new Entry[tam / 2 + 2];
    int dictSize = 1;
    dict[0].prefijo = 0;
    dict[0].c = '\0';

    for (int i = 0; i < tam; i += 2) {
        int prefijo = (unsigned char)compressed[i];
        char c = compressed[i + 1];

        char temp[1000];
        int pos = 0;

        copiarFrase(dict, prefijo, temp, pos);

        for (int j = 0; j < pos; j++) {
            resultado[r++] = temp[j];
        }

        if (c != '\0') {
            resultado[r++] = c;
        }

        dict[dictSize].prefijo = prefijo;
        dict[dictSize].c = c;
        dictSize++;
    }

    resultado[r] = '\0';
    delete[] dict;
    return resultado;
}

bool comparacion(const char* descomprimido, const char* input, bool des) {
    bool iguales = true;

    for (int i = 0; ; i++) {
        if (input[i] != descomprimido[i]) {
            iguales = false;
            break;
        }
        if (input[i] == '\0') break;
    }

    if (des) {
        cout << "Texto: " << descomprimido << endl;
        if (iguales) {
            cout << "Son iguales\n" << endl;
        } else {
            cout << "Son diferentes\n" << endl;
        }
    }

    return iguales;
}

char* compressLZ78(const char* input, bool des, char* &compressed, int &tam) {
    int longitud = longitudChar(input);
    int capacidad = longitud * 2 + 2;

    Entry* dict = new Entry[longitud + 2];
    int dictSize = 1;
    dict[0].prefijo = 0;
    dict[0].c = '\0';

    if (compressed == nullptr) {
        compressed = new char[capacidad];
    }

    tam = 0;
    int currentprefijo = 0;

    if (des) {
        cout << "Salida (indice, caracter):\n";
    }

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int index = findEntry(dict, dictSize, currentprefijo, c);

        if (index != -1) {
            currentprefijo = index;
        } else {
            compressed[tam] = (char)currentprefijo;
            compressed[tam + 1] = c;
            tam += 2;

            if (des) {
                cout << "(" << currentprefijo << ", " << c << ")\n";
            }

            dict[dictSize].prefijo = currentprefijo;
            dict[dictSize].c = c;
            dictSize++;
            currentprefijo = 0;
        }
    }

    if (currentprefijo != 0) {
        compressed[tam] = (char)currentprefijo;
        compressed[tam + 1] = '\0';
        tam += 2;

        if (des) {
            cout << "(" << currentprefijo << ", \\0)\n";
        }
    }

    char* descomprimido = decompressLZ78(compressed, tam);

    if (des) {
        comparacion(descomprimido, input, true);
    }

    delete[] dict;
    return descomprimido;
}
