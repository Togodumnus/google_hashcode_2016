#pragma once

#include <iostream>
#include <string>

/**
 * real modulo
 * @see http://stackoverflow.com/a/12089637/2058840
 */
inline int modulo(int a, int b) {
	const int result = a % b;
	return result >= 0 ? result : result + b;
}
