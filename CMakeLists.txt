cmake_minimum_required(VERSION 3.22)
project(prova01 C)

set(CMAKE_C_STANDARD 99)

add_executable(prova01-aeds2 main.c data/Funcionarios.c data/Funcionarios.h ordenacao/keySort.c ordenacao/insertionSort.c ordenacao/arvoreBinariaVenc.c busca/buscaBinaria.c busca/buscaSequencial.c selecao/selecaoNatural.c ordenacao/arvoreBinariaVenc.c selecao/Selecao.h ordenacao/Ordenacao.h busca/Busca.h hash/Hash.h hash/tabelaHash.c)
