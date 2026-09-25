#include <iostream>
#include "doc.h"
#include "rle.h"

using namespace std;

int main() {
    int metodo;

    cout << "(1) Compresion y descompresion con RLE.\n"


    cout << "Ingrese un numero para seleccionar el metodo a utilizar:" << endl;
    cin >> metodo;
    cin.ignore();

    while (metodo > 0) {
        switch (metodo) {
        case 1: {
            string texto;
            cout << "Ingrese texto: ";
            getline(cin, texto);

            string nombreArchivo = "resultado.txt";
            limpiarArchivo(nombreArchivo);

            escribirArchivo(nombreArchivo, "--- ORIGINAL ---\n");
            escribirArchivo(nombreArchivo, texto + "\n\n");

            string comprimido = rleCompress(texto);
            escribirArchivo(nombreArchivo, "###### COMPRIMIDO ######\n");
            escribirArchivo(nombreArchivo, comprimido + "\n\n");

            string descomprimido = rleDecompress(comprimido);
            escribirArchivo(nombreArchivo, "###### DESCOMPRIMIDO #####\n");
            escribirArchivo(nombreArchivo, descomprimido + "\n\n");

            if (compararString(texto, descomprimido)) {
                cout << "La descompresion produjo exitosamente el texto inicial." << endl;
            } else {
                cout << "La descompresion no es igual al texto original." << endl;
            }

            cout << "Proceso completado. Revise resultado.txt" << endl;
            break;
        }
        case 2: {

            break;
        }

        default:
            cout << "Opcion no valida." << endl;
            break;
        }

        cout << "\nIngrese un numero para seleccionar el metodo a utilizar:" << endl;
        cin >> metodo;
        cin.ignore();
    }

    return 0;
}
