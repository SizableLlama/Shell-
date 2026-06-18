#pragma once

#include "enums.hpp"
#include "shellToken.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <any>


using namespace std;


//Here, we will have a string called command, we will break it up into multiple strings, using whitespace.
//If there is an unrecognised string, we will return an error.
//Next, I will match the smaller strings into the enums.
//I must also define the enums and their functions.


class Scanner final{
		private:
		std::string source;
		//I changed the below from array to vector.
		//called arrayList[]
		vector<Token> tokens;
		int start = 0;
		int current = 0;
		int line = 1;
	public:
		Scanner(string source){
			this->source = source;
		}
	public:
		bool match(char expected);
		char advance();
		bool isAtEnd();
		bool isDigit(char c);
		void number();
		void identifier();
		bool isAlpha(char c);
		char peek();
		bool isAlphaNumeric(char c);
		void addToken(TokenType type, std::any literal);
		void addToken(TokenType type);
		vector<Token> scanTokens();
		void scanToken();
		char peekNext();
		void String();
		bool word();

};
//	private:
//		map<string, TokenType> keywords={
//
//			{"echo", ECHO},
//			{"cd", CD},
//			{"which", WHICH},
//			{"find", FIND},
//			{"touch", TOUCH},
//			{"grep", GREP},
//			{"cat", CAT},
//			{"ls", LS},
//
//		};
//
//
//};



std::vector<Token> Scanner::scanTokens(){
	while(!isAtEnd()){
		//We are at the beggining of the next lexeme.
		start = current;

		scanToken();
	}

	tokens.push_back(Token(END_OF_FILE, "", std::any{}, line));
	return tokens;
};

void Scanner::scanToken(){
	char c = advance();
	switch (c) {
    case '|': addToken(match('|') ? OR_OR : PIPE); break;
    case '>': addToken(match('>') ? APPEND : RIGHT); break;
    case '<': addToken(LEFT); break;
    case '&': addToken(match('&') ? AND_AND : AMP); break;
    case ';': addToken(SEMICOLON); break;
    case '"': String(); break;       // scans to closing quote, calls addToken(STRING) internally
    case ' ': case '\t': break;      // skip whitespace (only when not inside quotes)
    case '\n': line++; break;
    default:
        if (isAlphaNumeric(c)) { //isOperatorChar(c)
		word();
            // shouldn't reach here if all operator chars are cased above
        } else {
            cerr<<"Unknown command.\n";               // consume until whitespace/operator, addToken(WORD) internally
        }
        break;
}
}

//Got rid of Scanner::identifier();

//Got rid of Scanner::NUMBER();

void Scanner::String(){
	while (peek() !='"' && !isAtEnd()){
		if (peek() == '\n') line++;
		advance();
	}

	if (isAtEnd()){
		//Replacing Lox.error()
		std::cerr<<line<< "Unterminated string.";
		return;
	}
	//The closing ".
	advance();

	//Trim the surrounding quotes.
	string value = source.substr(start + 1, current - start - 2);
	addToken(STRING, value);

}



//removed reference to expected.
bool Scanner::match(char expected){
	if (isAtEnd()) return false;
	//Replacing charAt
	if (source.at(current) != expected) return false;

	current++;
	return true;
}

char Scanner::peek(){
	if(isAtEnd()) return '\0';
	return source.at(current);
}

char Scanner::peekNext(){
	if(current + 1 >= source.length()) return '\0';
	return source.at(current + 1);
}

bool Scanner::isAlpha(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isDigit(char c){
	return c>= '0' && c<= '9';
}

bool Scanner::isAlphaNumeric(char c){
	return isAlpha(c) || isDigit(c);
}

bool Scanner::isAtEnd(){
	return current >=source.length();
};

char Scanner::advance(){
	return source.at(current++);
}

void Scanner::addToken(TokenType type){
	std::any literal;
	addToken(type, literal);
}

void Scanner::addToken(TokenType type, std::any literal){
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, literal, line));
}
