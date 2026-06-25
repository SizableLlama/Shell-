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

struct Command {
		std::vector<std::string> args;
		RedirType redir_type = RedirType::NONE;
		std::string redir_file;
		bool background = false;
};

struct Pipeline {
		std::vector<Command> commands;
};
/*
struct Sequence {
        enum class Op { NONE, AND, OR, SEMI };
        Op op = Op::NONE;
        std::shared_ptr<Sequence> left;
		std::shared_ptr<Pipeline> Pipeline;
};
This struct was needed for the logical opperators. I cannot yet implement them.
they are too complex for I.
*/
