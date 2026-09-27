#include "bits.h"

unsigned char rotateLeft(unsigned char value, int shift) {
    return (unsigned char)((value << shift) | (value >> (8 - shift)));
}

unsigned char rotateRight(unsigned char value, int shift) {
    return (unsigned char)((value >> shift) | (value << (8 - shift)));
}

void xorCipherPtr(char* text, char key, int shift, bool cipher) {
    if (text == nullptr) return;

    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char dato = (unsigned char)text[i];

        if (cipher) {
            dato = rotateLeft(dato, shift);
            dato = dato ^ (unsigned char)key;
        } else {
            dato = dato ^ (unsigned char)key;
            dato = rotateRight(dato, shift);
        }

        text[i] = (char)dato;
    }
}

void xorCipherPtr(char* text, int tamanio, char key, int shift, bool cipher) {
    if (text == nullptr) return;

    for (int i = 0; i < tamanio; i++) {
        unsigned char dato = (unsigned char)text[i];

        if (cipher) {
            dato = rotateLeft(dato, shift);
            dato = dato ^ (unsigned char)key;
        } else {
            dato = dato ^ (unsigned char)key;
            dato = rotateRight(dato, shift);
        }

        text[i] = (char)dato;
    }
}
