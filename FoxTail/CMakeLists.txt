# CMakeList.txt : CMake project for FoxTail, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (FoxTail SHARED "FoxTail.hpp" 
	"Container.hpp" 
	"Container.cpp" 
	"Services/ServiceInterface.hpp" 
	"Services/UseServices.hpp"
	)

target_compile_features(FoxTail PUBLIC cxx_std_17)

include(GenerateExportHeader)
generate_export_header(FoxTail)

target_include_directories(FoxTail PRIVATE ${CMAKE_CURRENT_BINARY_DIR})


# TODO: Add tests and install targets if needed.

install(TARGETS FoxTail DESTINATION lib)
install(FILES 
	Container.hpp 
	${CMAKE_CURRENT_BINARY_DIR}/foxtail_export.h 
	FoxTail.hpp
	Services/ServiceInterface.hpp
	Services/UseServices.hpp
	DESTINATION 
	include
)