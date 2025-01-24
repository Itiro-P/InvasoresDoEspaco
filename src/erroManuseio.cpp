#include <erroManuseio.hpp>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>

void erroArquivo(const std::string &mensagem) {
    throw std::runtime_error("Erro ao carregar " + mensagem + ".\nVerifique se o arquivo ou diretorio existem.");
    std::cin.get();
}
