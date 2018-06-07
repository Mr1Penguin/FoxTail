cmake_minimum_required (VERSION 3.8)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(foxtail_tests Container.cpp)
target_compile_features(foxtail_tests PUBLIC cxx_std_17)
target_link_libraries(foxtail_tests
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	FoxTail
)

target_include_directories(foxtail_tests PRIVATE ${Boost_INCLUDE_DIRS} "${CMAKE_CURRENT_BINARY_DIR}/../FoxTail" "../FoxTail")