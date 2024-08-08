cmake_minimum_required(VERSION 3.10)

# Nome del progetto
project(MageWorkflow)

# Versione del C++
set(CMAKE_CXX_STANDARD 17)

# Aggiungi le directory include
include_directories(${CMAKE_SOURCE_DIR})

# Trova i pacchetti richiesti
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)
find_package(log4cpp REQUIRED)

# Aggiungi le sorgenti del progetto
add_executable(MageWorkflow
    main.cpp
    ConversionWorker.cpp
    GUI.cpp
    Utils.cpp
)

# Linka le librerie
target_link_libraries(MageWorkflow
    Qt5::Widgets
    ${OpenCV_LIBS}
    log4cpp::log4cpp
)
