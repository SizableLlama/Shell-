#pragma once

#include "enums.hpp"
#include "lexer.hpp"
#include "structs.hpp"
#include "shellToken.hpp"
#include <vector>
#include <fstream>
#include <iostream>

class Parser final {
        private:
                std::vector<Token> tokens;
                int current = 0;

        public:
                Parser(std::vector<Token> tokens) {
                        this->tokens = tokens;
                }



                bool isAtEnd() {
                        return current >= tokens.size() || tokens.at(current).type == END_OF_FILE;
                }


                Token peek() {
                        if (isAtEnd()) return Token(END_OF_FILE, "", std::any{}, 0);
                        return tokens.at(current);
                }


                Token advance() {
                        if (!isAtEnd()) current++;
                        return tokens.at(current - 1);
                }


                bool match(TokenType expected) {
                        if (isAtEnd()) return false;


                        if (peek().type != expected) return false;

                        current++;
                        return true;
                }

                void foo(){
                        std::cout<<"foo\n";
                }


                Pipeline parse() {
                        Pipeline pipeline;
                        Command currentCommand;

                        while (!isAtEnd()) {

                                if (match(WORD) || match(STRING)) {
                                        currentCommand.args.push_back(tokens[current - 1].lexeme);
					continue;
                                }
                                else if(match(PIPE)) {
                                        if (!match(END_OF_FILE)) {
						pipeline.commands.push_back(currentCommand);
						currentCommand = Command();
						continue;
					}
					else {
						std::cerr<<"Expected expression following '|'\n";
						continue;
					}
                                }
                                else if (match(RIGHT)) {
                                        currentCommand.redir_type = RedirType::OUTPUT;
                                        if (match(WORD) || match(STRING)) {
                                                currentCommand.redir_file = tokens[current - 1].lexeme;
						continue;
                                        }
					else if (match(END_OF_FILE)) {
						std::cerr<<"Expected expression following '>'\n";
						continue;
					}
                                        else{
                                                std::cerr<<"Expected file name following '>'\n";
						continue;
                                        }
                                }
                                else if (match(LEFT)) {
                                        currentCommand.redir_type = RedirType::INPUT;
					if (match(WORD) || match(STRING)) {
						currentCommand.redir_file = tokens[current - 1].lexeme;
						currentCommand.args.push_back(tokens[current - 1].lexeme);
						continue;
					}
					else if (match(END_OF_FILE)) {
						std::cerr<<"Expected expression following '<'\n";
					}
					else {
						std::cerr<<"Expected file name following '<'\n";
					}
                                }
                                else if (match(APPEND)) {
                                        currentCommand.redir_type = RedirType::APPEND;
					if (match(WORD) || match(STRING)) {
						currentCommand.redir_file = tokens[current - 1].lexeme;
						continue;
					}
					else if (match(END_OF_FILE)) {
						std::cerr<<"Expected expression following '>>'\n";
					}
					else{
						std::cerr<<"Expected file name following '>>'\n";
					}
                                }
                                else if (match(AMP)) {
                                        pipeline.background = true;
					pipeline.commands.push_back(currentCommand);
					currentCommand = Command();
					continue;
                                }
                                else if (match(SEMICOLON)) {
                                        pipeline.commands.push_back(currentCommand);
					currentCommand = Command();
					continue;
                                }
                                else if (match(AND_AND)) {
                                        if (!match(END_OF_FILE)) {
						pipeline.commands.push_back(currentCommand);
						currentCommand = Command();
						continue;
					}
					else {
						std::cerr<<"Expected expression following '&&'\n";
					}
                                }
                                else if (match(OR_OR)) {
					if (!match(END_OF_FILE)) {
                                        	pipeline.commands.push_back(currentCommand);
						currentCommand = Command();
						continue;
					}
					else {
						std::cerr<<"Expected expression following '||'\n";
					}
                                }

                                advance();
                        }
			if(!currentCommand.args.empty()) {
				pipeline.commands.push_back(currentCommand);
			}

                        return pipeline;
                }
};
