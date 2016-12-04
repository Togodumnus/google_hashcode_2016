#pragma once

#include <iostream>
#include <string>

class LogMachine {

	private:
		bool m_flag = false;
		std::string m_prefix = "";

		void out_prefix() {
			if (m_flag) {
				if (m_prefix != "") {
					std::cout << "[" << m_prefix << "]	";
				}
			}
		}

	public:
		LogMachine(std::string prefix = "", bool flag = true) {
			m_flag = flag;
			m_prefix = prefix;
		}

		void operator()(std::string what) {
			if (m_flag) {
				out_prefix();
				std::cout << what << std::endl;
			}
		}

		template<class O>
		void operator()(O& o) {
			if (m_flag) {
				out_prefix();
				std::cout << o << std::endl;
			}
		}
		template<class O>
		void operator()(std::string what, O& o) {
			if (m_flag) {
				out_prefix();
				std::cout << what;
				std::cout << " " << o << std::endl;
			}
		}
};

