#ifndef BITS_H
#define BITS_H

unsigned char rotateLeft(unsigned char value, int shift);
unsigned char rotateRight(unsigned char value, int shift);

// Versión para cadenas terminadas en '\0'. Sirve para pruebas manuales.
void xorCipherPtr(char* text, char key, int shift, bool cipher);

// Versión para datos comprimidos. No depende de '\0'.
void xorCipherPtr(char* text, int tamanio, char key, int shift, bool cipher);

#endif // BITS_H
