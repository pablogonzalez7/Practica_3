#ifndef FUNCIONALIDAD_H
#define FUNCIONALIDAD_H

#include <fstream>
using namespace std;

int leerEntero(const char prompt[]);

void escribirArchivoChar(ofstream& archivo, const char* contenido1, const char* contenido2,
                         int tamanio, const char* comprimido);
void metRle();
void metLz78();

#endif // FUNCIONALIDAD_H
