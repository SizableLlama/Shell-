#pragma once

#include "enums.hpp"
#include "lexer.hpp"
#include "structs.hpp"
#include "shellToken.hpp"
#include <cstdio>
#include <vector>
//no clue what i'm doing, just know i need structs and something else.


//TODO change all the else if s to a switch

//If source is a string, maybe the tokens should be a "source" ?



//The parser filters the Tokens into either Command, or Pipeline.
//it can do this by adding rules to the structs. Think about it.
//what is the criteria for a command versus a pipeline?

//It all makes sense, at long last. The parser takes tokens, and stores them in the args vector.
//When it finds a | it saves the command and starts a new one!!!



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


                // The parser filters the Tokens into either Command, or Pipeline.
                Pipeline parseExample() {
                        Pipeline pipeline;
                        Command currentCommand;
                        while (!isAtEnd()) {


                                if (match(WORD) || match(STRING)) {
                                        currentCommand.args.push_back(tokens[current].lexeme);
                                }
                                else if(match(PIPE)) {
                                        pipeline.commands.push_back(currentCommand);
                                }
                                else if (match(RIGHT)) {
                                        currentCommand.redir_type = RedirType::OUTPUT;
                                        //Here i expect a string, aka, a file name.
                                        //And so, I must append the next token, which should happend anyway, 
                                        if (match(WORD) || match(STRING)) {
                                                //No idea if this is right. Also don't know what is the OS's job
                                                currentCommand.redir_file = tokens[current].lexeme;
                                                currentCommand.args.push_back(tokens[current].lexeme);
                                        }
                                        else{
                                                std::cerr<<"expected file name following '>'\n";
                                        }
                                }
                                else if (match(LEFT)) {
                                        currentCommand.redir_type = RedirType::INPUT;

                                }
                                else if (match(APPEND)) {
                                        currentCommand.redir_type = RedirType::APPEND;
                                }
                                else if (match(AMP)) {
                                        currentCommand.background = true;
                                }
                                else if (match(SEMICOLON)) {
                                        pipeline.commands.push_back(currentCommand);
                                }
                                else if (match(AND_AND)) {
                                        pipeline.commands.push_back(currentCommand);
                                }
                                else if (match(OR_OR)) {
                                        pipeline.commands.push_back(currentCommand);
                                }
                                else if (match(END_OF_FILE)) {
                                        break;
                                }



                                advance();
                        }

                        return pipeline;
                }
};
