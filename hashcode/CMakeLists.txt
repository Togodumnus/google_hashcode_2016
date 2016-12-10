include_directories("hashcode/")

file(GLOB SRC_FOLDER
    "hashcode/*.cpp"
	"hashcode/main.cpp"
)

add_executable(hashcode ${SRC_FOLDER})
