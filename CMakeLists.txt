cmake_minimum_required(VERSION 3.30)
project(InvasoresDoEspaco LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main 
    src/main.cpp
    src/ator.cpp
    src/interface.cpp
    src/projetil.cpp
    src/erroManuseio.cpp
    src/gerenciadorAliens.cpp
    src/recursoManager.cpp
    src/gerenciadorProjeteis.cpp
)

# Diretório com os arquivos de recursos
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/misc)

# Copiar recursos para o diretório de saída
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/misc
)

target_compile_features(main PRIVATE cxx_std_17)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE SFML::Graphics SFML::System SFML::Audio)