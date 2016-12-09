include_directories("arbitre/")

file(GLOB SRC_FOLDER
    "arbitre/*.cpp"
	"arbitre/main.cpp"
)

add_executable(arbitre ${SRC_FOLDER})
