#include "doc.h"
#include <iostream>
#include <fstream>
using namespace std;

string leerArchivo(const string& nombre) {
    ifstream archivo(nombre);
    string contenido = "", linea;

    while (getline(archivo, linea)) {
        contenido += linea;
    }

    archivo.close();
    return contenido;
}

void escribirArchivo(const string& nombre, const string& contenido) {
    ofstream archivo(nombre, ios::app);
    if (!archivo) {
        cout << "Error al crear el archivo: " << nombre << endl;
        return;
    }

    archivo << contenido;
    archivo.close();
}

void limpiarArchivo(const string& nombre) {
    ofstream archivo(nombre, ios::trunc);
    archivo.close();
}

bool compararString(string a, string b) {
    return a == b;
}

char* lecturachar(ifstream& instancia) {
    int capacidad = 16;
    int longitud = 0;
    char* linea = new char[capacidad];

    char c;
    while (instancia.get(c)) {
        if (c == '\n') {
            break;
        }

        if (longitud >= capacidad - 1) {
            capacidad *= 2;
            char* nuevaLinea = new char[capacidad];

            for (int i = 0; i < longitud; i++) {
                nuevaLinea[i] = linea[i];
            }

            delete[] linea;
            linea = nuevaLinea;
        }

        linea[longitud] = c;
        longitud++;
    }

    if (longitud == 0 && instancia.eof()) {
        delete[] linea;
        return nullptr;
    }

    linea[longitud] = '\0';
    return linea;
}
