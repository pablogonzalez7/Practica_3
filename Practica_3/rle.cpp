#include "rle.h"
#include <string>
#include <cctype>
using namespace std;

string rleCompress(const string& input) {
    string result = "";

    if (input.empty()) {
        return result;
    }

    int count = 1;

    for (int i = 1; i <= (int)input.length(); i++) {
        if (i < (int)input.length() && input[i] == input[i - 1]) {
            count++;
        } else {
            result += to_string(count);
            result += ':';
            result += input[i - 1];
            count = 1;
        }
    }

    return result;
}

string rleDecompress(const string& input) {
    string result = "";
    int i = 0;

    while (i < (int)input.length()) {
        string numero = "";

        while (i < (int)input.length() && isdigit((unsigned char)input[i])) {
            numero += input[i];
            i++;
        }

        if (numero.empty() || i >= (int)input.length() || input[i] != ':') {
            return result;
        }

        i++; // saltar ':'

        if (i >= (int)input.length()) {
            return result;
        }

        char caracter = input[i];
        i++;

        int count = stoi(numero);
        for (int j = 0; j < count; j++) {
            result += caracter;
        }
    }

    return result;
}
