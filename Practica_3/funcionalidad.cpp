#include "funcionalidad.h"

#include "doc.h"
#include "lz78.h"
#include "rle.h"
#include "bits.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int pedirRotacion() {
    int n;
    cout << "Ingrese un valor de rotacion n entre 1 y 7: ";
    cin >> n;
    cin.ignore();

    while (n <= 0 || n >= 8) {
        cout << "Valor invalido. Ingrese n entre 1 y 7: ";
        cin >> n;
        cin.ignore();
    }

    return n;
}

void escribirBytes(ofstream& archivo, const char* datos, int tamanio) {
    for (int i = 0; i < tamanio; i++) {
        archivo << (int)(unsigned char)datos[i] << " ";
    }
    archivo << "\n";
}

void escribirArchivoChar(ofstream& archivo, const char* contenido1, const char* contenido2,
                         int tamanio, const char* comprimido) {
    if (!archivo) {
        cout << "Error al escribir en el archivo." << endl;
        return;
    }

    archivo << "-----COMPRESION-----\n";
    for (int i = 0; i < tamanio; i += 2) {
        int indice = (unsigned char)comprimido[i];
        char caracter = comprimido[i + 1];

        if (caracter == '\0') {
            archivo << "(" << indice << ", '\\0')\n";
        } else {
            archivo << "(" << indice << ", '" << caracter << "')\n";
        }
    }

    archivo << "-----DESCOMPRESION-----\n" << contenido2 << "\n";
    archivo << "-----ORIGINAL-----\n" << contenido1 << "\n";
}

void compresionrle(ifstream& archivo, int n) {
    try {
        ofstream resultados("compresionrle.txt");

        if (!archivo) throw 1;
        if (!resultados) throw 2;

        string texto;
        int numeroLinea = 0;
        char clave = 'k';

        while (getline(archivo, texto)) {
            numeroLinea++;
            resultados << "\n========== LINEA " << numeroLinea << " ==========" << "\n";
            resultados << "--- ORIGINAL ---\n" << texto << "\n\n";

            string comprimido = rleCompress(texto);
            resultados << "--- COMPRIMIDO ---\n" << comprimido << "\n\n";

            int tam = (int)comprimido.length();
            char* datos = new char[tam + 1];
            for (int i = 0; i < tam; i++) datos[i] = comprimido[i];
            datos[tam] = '\0';

            xorCipherPtr(datos, tam, clave, n, true);
            resultados << "--- ENCRIPTADO (bytes) ---\n";
            escribirBytes(resultados, datos, tam);

            xorCipherPtr(datos, tam, clave, n, false);
            string desencriptado(datos, tam);
            resultados << "--- DESENCRIPTADO ---\n" << desencriptado << "\n\n";

            string descomprimido = rleDecompress(desencriptado);
            resultados << "--- DESCOMPRIMIDO ---\n" << descomprimido << "\n\n";

            if (compararString(texto, descomprimido)) {
                resultados << "--- COMPARACION ---\nSon iguales\n";
            } else {
                resultados << "--- COMPARACION ---\nNO son iguales\n";
            }

            delete[] datos;
        }

        resultados.close();
    }
    catch (int excp) {
        switch (excp) {
        case 1:
            cout << "Error: No se pudo abrir integrar.txt\n";
            break;
        case 2:
            cout << "Error: No se pudo crear compresionrle.txt\n";
            break;
        default:
            cout << "Error desconocido\n";
        }
    }
    catch (...) {
        cout << "Excepcion por defecto\n";
    }
}

void compresionLz78(ifstream& archivo, int n) {
    try {
        ofstream resultados("compresionlz78.txt");

        if (!archivo) throw 1;
        if (!resultados) throw 2;

        int numeroLinea = 0;
        char clave = 'k';

        while (true) {
            char* linea = lecturachar(archivo);

            if (linea == nullptr) {
                break;
            }

            numeroLinea++;
            resultados << "\n========== LINEA " << numeroLinea << " ==========" << "\n";

            char* comprimido = nullptr;
            int tamanio = 0;
            char* pruebaDes = compressLZ78(linea, false, comprimido, tamanio);

            resultados << "-----ORIGINAL-----\n" << linea << "\n";
            resultados << "-----COMPRESION-----\n";
            for (int i = 0; i < tamanio; i += 2) {
                int indice = (unsigned char)comprimido[i];
                char caracter = comprimido[i + 1];

                if (caracter == '\0') {
                    resultados << "(" << indice << ", '\\0')\n";
                } else {
                    resultados << "(" << indice << ", '" << caracter << "')\n";
                }
            }

            xorCipherPtr(comprimido, tamanio, clave, n, true);
            resultados << "-----ENCRIPTADO (bytes)-----\n";
            escribirBytes(resultados, comprimido, tamanio);

            xorCipherPtr(comprimido, tamanio, clave, n, false);
            resultados << "-----DESENCRIPTADO COMO PARES-----\n";
            for (int i = 0; i < tamanio; i += 2) {
                int indice = (unsigned char)comprimido[i];
                char caracter = comprimido[i + 1];

                if (caracter == '\0') {
                    resultados << "(" << indice << ", '\\0')\n";
                } else {
                    resultados << "(" << indice << ", '" << caracter << "')\n";
                }
            }

            char* lineaDes = decompressLZ78(comprimido, tamanio);
            resultados << "-----DESCOMPRESION-----\n" << lineaDes << "\n";

            if (comparacion(lineaDes, linea, false)) {
                resultados << "-----COMPARACION-----\nSon iguales\n";
            } else {
                resultados << "-----COMPARACION-----\nNO son iguales\n";
            }

            delete[] pruebaDes;
            delete[] lineaDes;
            delete[] comprimido;
            delete[] linea;
        }

        resultados.close();
    }
    catch (int excp) {
        switch (excp) {
        case 1:
            cout << "Error: No se pudo abrir integrar.txt\n";
            break;
        case 2:
            cout << "Error: No se pudo crear compresionlz78.txt\n";
            break;
        default:
            cout << "Error desconocido\n";
        }
    }
    catch (...) {
        cout << "Excepcion por defecto\n";
    }
}

void metRle() {
    int n = pedirRotacion();
    ifstream archivoCompresion("integrar.txt");
    compresionrle(archivoCompresion, n);
    cout << "Proceso RLE completado. Revise compresionrle.txt\n";
}

void metLz78() {
    int n = pedirRotacion();
    ifstream archivoCompresion("integrar.txt");
    compresionLz78(archivoCompresion, n);
    cout << "Proceso LZ78 completado. Revise compresionlz78.txt\n";
}
