cmake_minimum_required(VERSION 3.21)
project(Project2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O0 -g -w")

# Aggiungi la directory src ai percorsi di inclusione
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Trova tutti i file sorgente C++ nella directory src (tranne fake_receiver.c)
file(GLOB_RECURSE LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*/fake_receiver.c$")

# Aggiungi il file fake_receiver.c separatamente
set(FAKE_RECEIVER ${CMAKE_CURRENT_SOURCE_DIR}/fake_receiver.cpp)

# Aggiungi tutti i file sorgente alla libreria condivisa
add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES} ${FAKE_RECEIVER})

# Specifica le librerie aggiuntive da collegare (se necessario)
target_link_libraries(${PROJECT_NAME} 
    # Altre librerie
)

# Imposta la directory di output per gli eseguibili
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Aggiungi l'eseguibile e collega la libreria condivisa
add_executable(project_2 ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(project_2 ${PROJECT_NAME})
