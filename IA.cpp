#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <limits>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

map<string, string> conocimiento;

void cargar_conocimiento(const string& archivo) {
    ifstream fin(archivo);
    if (!fin.is_open()) return;
    string pregunta, respuesta;
    while (getline(fin, pregunta) && getline(fin, respuesta)) {
        conocimiento[pregunta] = respuesta;
    }
    fin.close();
}

void guardar_conocimiento(const string& archivo) {
    ofstream fout(archivo);
    for (const auto& par : conocimiento) {
        fout << par.first << endl << par.second << endl;
    }
    fout.close();
}

// Calcula la distancia de Levenshtein entre dos cadenas
int distancia_levenshtein(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (tolower(a[i - 1]) == tolower(b[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
        }
    }
    return dp[n][m];
}

string quitar_tildes(const string& texto) {
    string resultado = texto;
    string acentuadas = "áéíóúÁÉÍÓÚ";
    string sin_acentos = "aeiouAEIOU";
    for (size_t i = 0; i < resultado.size(); ++i) {
        size_t pos = acentuadas.find(resultado[i]);
        if (pos != string::npos) {
            resultado[i] = sin_acentos[pos];
        }
    }
    return resultado;
}

string normalizar(const string& texto) {
    string tmp = quitar_tildes(texto);
    string resultado;
    for (char c : tmp) {
        if (isalnum((unsigned char)c) || isspace((unsigned char)c)) {
            resultado += tolower((unsigned char)c);
        }
        // Ignora signos de puntuación
    }
    return resultado;
}

string responder(const string& entrada) {
    string entrada_norm = normalizar(entrada);
    // Buscar coincidencia exacta normalizada
    for (const auto& par : conocimiento) {
        if (normalizar(par.first) == entrada_norm) {
            return par.second;
        }
    }
    // Buscar la pregunta más parecida (normalizando)
    int mejor_dist = 3; // Permite hasta 3 errores
    string mejor_respuesta = "";
    string mejor_pregunta = "";
    for (const auto& par : conocimiento) {
        int dist = distancia_levenshtein(entrada_norm, normalizar(par.first));
        if (dist < mejor_dist) {
            mejor_dist = dist;
            mejor_respuesta = par.second;
            mejor_pregunta = par.first;
        }
    }
    if (!mejor_respuesta.empty()) {
        return mejor_respuesta + " (Forma correcta: \"" + mejor_pregunta + "\")";
    }
    cout << "No entiendo tu mensaje. ¿Cómo debería responder?" << endl;
    string nueva_respuesta;
    getline(cin, nueva_respuesta);
    conocimiento[entrada] = nueva_respuesta;
    guardar_conocimiento("conocimiento.txt");
    return "¡Gracias por enseñarme!";
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // Habilita UTF-8 en la consola de Windows
    cargar_conocimiento("conocimiento.txt");
    string mensaje;
    while (true) {
        cout << "Escribe un mensaje (o escribe 'salir' para terminar): ";
        getline(cin, mensaje);
        if (mensaje == "salir") break;
        cout << responder(mensaje) << endl;
    }
    guardar_conocimiento("conocimiento.txt");
    return 0;
}

#pragma execution_character_set("utf-8")