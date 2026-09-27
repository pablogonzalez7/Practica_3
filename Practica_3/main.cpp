#include <iostream>
#include "doc.h"
#include "rle.h"
#include "bits.h"
#include "lz78.h"
#include "funcionalidad.h"
using namespace std;

int main() {
    int metodo;

    cout << "(1) Compresion y descompresion con RLE.\n"
            "(2) Compresion y descompresion con LZ78 donde se elige la cadena de caracteres.\n"
            "(3) Compresion y descompresion con LZ78 usando cadenas predeterminadas.\n"
            "(4) Encriptacion y desencriptacion con operaciones binarias.\n"
            "(5) Integracion desde archivo con RLE.\n"
            "(6) Integracion desde archivo con LZ78.\n"
            "(0) Salir.\n";

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
            char text1[200] = "";
            char* comprimido = nullptr;
            int tam = 0;

            cout << "Ingrese el texto que desea comprimir con LZ78:" << endl;
            cin.getline(text1, 200);

            char* des = compressLZ78(text1, true, comprimido, tam);

            delete[] des;
            delete[] comprimido;
            break;
        }
        case 3: {
            char texta[] = "ABRACADABRARABARABARA";
            char textb[] = "ABAABABAABBBBBBBBB";
            char sel;
            char* comprimido = nullptr;
            int tam = 0;

            cout << "Escoja el texto que desea comprimir:" << endl;
            cout << "A: ABRACADABRARABARABARA" << endl;
            cout << "B: ABAABABAABBBBBBBBB" << endl;
            cin >> sel;
            cin.ignore();

            if (sel == 'A' || sel == 'a') {
                char* des = compressLZ78(texta, true, comprimido, tam);
                delete[] des;
            } else if (sel == 'B' || sel == 'b') {
                char* des = compressLZ78(textb, true, comprimido, tam);
                delete[] des;
            }

            delete[] comprimido;
            break;
        }
        case 4: {
            char palabra[100] = "";
            int n;

            cout << "Ingrese la cadena que desea encriptar usando operadores binarios:" << endl;
            cin.getline(palabra, 100);

            cout << "Ingrese un numero n para realizar la rotacion entre 1 y 7:" << endl;
            cin >> n;
            cin.ignore();

            if (n > 0 && n < 8) {
                xorCipherPtr(palabra, 'k', n, true);
                cout << "\nEncriptado: " << palabra << endl;

                xorCipherPtr(palabra, 'k', n, false);
                cout << "Desencriptado: " << palabra << endl;
            } else {
                cout << "El valor de n debe estar entre 1 y 7." << endl;
            }

            break;
        }
        case 5: {
            metRle();
            break;
        }
        case 6: {
            metLz78();
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
