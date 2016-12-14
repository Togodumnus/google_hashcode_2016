

class ReadException : std::exception {
std::string file;
public:
	inline ReadException(std::string f) {
		file = f;
	}
	inline const char* what() const noexcept {
		std::string m = "Can't read file ";
		m += file;
		return m.c_str();
	};
};

