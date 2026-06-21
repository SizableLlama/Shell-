#pragma once

#include <string>
#include <vector>
#include <memory>

enum class RedirType {
	NONE,   // NOTHING
	INPUT,	// <
	OUTPUT,	// >
	APPEND	// >>
};

struct Command{
	std::vector<std::string> args;
	RedirType redir_type = RedirType::NONE;
	std::string redir_file;
	bool background = false;
};

struct Pipeline{
	std::vector<Command> commands;
};
