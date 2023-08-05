
cmake_minimum_required (VERSION 3.27.1)

project (e2spd)

    find_library(SPEECHD_LIB speechd)
find_path(SPEECHD_PATH "libspeechd.h")



add_subdirectory (src)


add_executable (e2spd
			   src/main.cpp
			   			   src/TTS.cpp
						   src/State.cpp)
target_include_directories(e2spd
	PUBLIC
	"${SPEECHD_PATH}"
		PRIVATE
		src)
  target_link_libraries(e2spd PUBLIC "${SPEECHD_LIB}")
#target_include_directories(e2spd PUBLIC "${SPEECHD_PATH}")

target_compile_features(e2spd PRIVATE cxx_std_17)
