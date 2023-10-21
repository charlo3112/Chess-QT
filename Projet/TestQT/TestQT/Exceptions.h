#pragma once
#include <stdexcept>

class PieceException : public std::runtime_error {
	public :
		explicit PieceException(const std::string& what_arg) : std::runtime_error(what_arg) {}
};