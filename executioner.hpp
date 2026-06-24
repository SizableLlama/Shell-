#include "parser.hpp"
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
//std::vector<std::string> into a std::vector<char*>

void foo();
// this should all be in a class executioner.

class Executioner {
private:
	std::vector<char*> commandToArgv(const Command& command) {
		std::vector<char*> argv;
		for (const std::string& arg : command.args) {
			argv.push_back(const_cast<char*>(arg.c_str()));
		}
		argv.push_back(nullptr);  // required sentinel — execvp scans until it sees this
		return argv;
	}

	bool builtIn(const Command& command) {
		if (command.args[0] == "cd") {
			if (command.args.size() < 2) {
				char* home = getenv("HOME");
				chdir(home);
				return true;
			}
			else {
				chdir(command.args[1].c_str());
				return true;
			}
		}
		else if (command.args[0] == "exit") {
			std::cout<<std::exit;
			return true;
		}
		return false;
	}










/*
TODO empty string, eg "hi  with no closing indicator results in a crash.
TODO benchmark
TODO figure out the wait function
TODO stop ctrl + c
TODO make a nice main
TODO add functionality to && || | > < >>
*/

public:
	Executioner() = default;
	void run(const Pipeline& pipeline) {
		//TODO make this elif chain a switch. Also, check for built ins before commandToArgv.
		const Command& com = pipeline.commands[0];
		std::vector<char*> argv = commandToArgv(com);
		if (builtIn(com)) return;
		int z = 0;
		size_t x = 0;
		int pointed = 0;
		while (x <= pipeline.commands.size()) {

			if (fork() == 0) {
				execvp(argv[0], argv.data());
				pid_t wait(int *pointed);
				std::cout<<"Forked "<<z<<" times.\n";
				z++;
			}
			else {
				pid_t wait(int *pointed);
				std::cerr<<"There was an error forking. For the "<<z<<"time \n"<<pointed<<"\n";
				z++;
			}
			x++;
		}
		

		/*
		ls -la | grep ".cpp" > output.txt
		turns into:
		ls -la   and   grep ".cpp"
	
		
		need the && and || logic. if both left and right are true, run.
		if left is false but right is true, run.
		
		but how? There must be two arguments. The OS probably checks for us, then I can do accordingly.

		*/









	}
};
//So, i need to build arguments using the commands vector.
//i then loop that to execvp.
//open() is then used to open a file which is also in the commands vector.
