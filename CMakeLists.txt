cmake_minimum_required(VERSION 3.20)
project(Sah_Test)

set(CMAKE_CXX_STANDARD 17)

# Căutăm SFML - obligatoriu pentru a găsi header-ele (.hpp)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Sah_Test main.cpp
        Piesa.h
        mutari_piese.h
        mutari_piese.cpp
        initializare_tabla.h
        initializare_tabla.cpp)

# Forțăm linkarea manuală cu bibliotecile de sistem
# Aceasta este metoda cea mai sigură pe Ubuntu/Debian
target_link_libraries(Sah_Test sfml-graphics sfml-window sfml-system)