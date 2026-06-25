#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <csignal>
#include <signal.h>
#include "parser.hpp"
#include "parser.hpp"
#include "executioner.hpp"
#include <filesystem>

int main() {
	std::string input;
	Executioner executor;

	while (true) {
		std::cout<<std::filesystem::current_path()<< "Bell >";
		if (!std::getline(std::cin, input)) {
			std::cout<<"\nExiting shell...\n";
			break;
		}
		if (input == "exit") {
			break;
		}
		if (input.empty()) {
			continue;
		}

		Scanner scanner(input);
		std::vector<Token> token = scanner.scanTokens();

		Parser parser(token);
		Pipeline pipeline = parser.parse();

		executor.run(pipeline);
	}
	return 0;
}
