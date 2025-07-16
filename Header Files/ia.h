#pragma once
#include <map>
#include <string>

extern std::map<std::string, std::string> conocimiento;

void cargar_conocimiento(const std::string& archivo);
void guardar_conocimiento(const std::string& archivo);
std::string responder(const std::string& entrada);