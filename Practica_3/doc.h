#ifndef DOC_H
#define DOC_H

#include <string>
#include <fstream>
using namespace std;

string leerArchivo(const string& nombre);
void escribirArchivo(const string& nombre, const string& contenido);
void limpiarArchivo(const string& nombre);
bool compararString(string a, string b);
char* lecturachar(ifstream& instancia);

#endif // DOC_H
