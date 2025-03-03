cmake_minimum_required(VERSION 3.14)
project(ShootemUp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vérifie si le toolchain file est déjà défini
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Vérifie si la variable d'environnement VCPKG_ROOT est définie
    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
    # Vérifie les emplacements standards sur Windows
    elseif(WIN32)
        # Vérifie d'abord à côté du projet
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
            set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
                CACHE STRING "Vcpkg toolchain file")
        # Vérifie à la racine de C:
        elseif(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
            set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
                CACHE STRING "Vcpkg toolchain file")
        # Vérifie ensuite dans C:/dev/vcpkg (emplacement courant)
        elseif(EXISTS "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
            set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
                CACHE STRING "Vcpkg toolchain file")
        endif()
    endif()
endif()

# Affiche un message concernant le toolchain file
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(WARNING "vcpkg toolchain file not found. SFML and other dependencies might not be found.")
endif()

# Recherche de SFML et ses composants
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED) #changer cette ligne si on veut utiliser la version 3.0(intégrer la 3.0 sur le prochain projet)

# Afficher la version de SFML trouvée
if(SFML_FOUND)
    message(STATUS "Found SFML ${SFML_VERSION_MAJOR}.${SFML_VERSION_MINOR}.${SFML_VERSION_PATCH}")
else()
    message(FATAL_ERROR "Could not find SFML")
endif()

#Project Settings
file(GLOB SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB HEADERS
    "${PROJECT_SOURCE_DIR}/include/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

# Inclure les répertoires d'en-têtes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Lier SFML à l'exécutable
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)

# Options de compilation
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

# Copier les ressources et DLLs dans le répertoire de sortie (pour Windows)
if(WIN32)
    # Copier le dossier des ressources
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )
endif()

# Copier les DLLs de SFML dans le répertoire de sortie
if(WIN32)
    # Copier les DLLs de SFML
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.0/bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()