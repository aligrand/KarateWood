cmake_minimum_required(VERSION 3.24)

project(KarateWood)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

add_executable(KarateWood src/karatewood.c
				src/inputmanager.c
				src/executeaction.c
				src/menu.c
				src/run.c)