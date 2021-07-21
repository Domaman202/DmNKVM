# CMakeList.txt: проект CMake для DmNKVM; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (DmNKVM "DmNKVM.cpp" "DmNKVM.hpp" "main.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
