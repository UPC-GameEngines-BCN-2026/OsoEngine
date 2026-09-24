# CMakeList.txt: proyecto de CMake para OsoEngine, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glm CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Agregue un origen al ejecutable de este proyecto.
add_executable (OsoEngine "OsoEngine.cpp" "OsoEngine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OsoEngine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(OsoEngine PRIVATE
    glm::glm
    SDL3::SDL3
    glad::glad
    imgui::imgui
)

target_compile_options(OsoEngine PRIVATE
    /GR-   
    /EHs-c-
)
# TODO: Agregue pruebas y destinos de instalación si es necesario.
