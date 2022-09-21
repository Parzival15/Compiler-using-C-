#include <fstream> // for file-access
#include <string>
#include <iostream>
#include "lex.h"
#include <map>

using namespace std; 

map <string, Token > StringToken = {
    
    {"PROGRAM", PROGRAM}, {"WRITELN", WRITELN},
    {"INTEGER", INTEGER}, {"BEGIN", BEGIN},
    {"END", END}, {"IF", IF},
    {"REAL", REAL}, {"STRING", STRING},
    {"VAR", VAR}, {"ELSE", ELSE},
    {"FOR", FOR}, {"THEN", THEN},
    {"DO", DO}, {"TO", TO}, {"DOWNTO", DOWNTO}, {"IDENT", IDENT},
    {"ICONST", ICONST}, {"RCONST", RCONST},
    {"SCONST", SCONST}, {"PLUS", PLUS},
    {"MINUS", MINUS}, {"MULT", MULT}, {"DIV", DIV}, 
    {"ASSOP", ASSOP}, {"LPAREN", LPAREN}, {"RPAREN", RPAREN}, 
    {"COMMA", COMMA}, {"EQUAL", EQUAL}, {"GTHAN", GTHAN}, 
    {"LTHAN", LTHAN}, {"SEMICOL", SEMICOL}, {"COLON", COLON},
    {"DOT", DOT}, {"ERR", ERR}, {"DONE", DONE}
};

map <Token, string > TokenString = {
    {PROGRAM, "PROGRAM"}, {WRITELN, "WRITELN"},
    {INTEGER, "INTEGER"}, {BEGIN, "BEGIN"},
    {END, "END"}, {IF, "IF"},
    {REAL, "REAL"}, {STRING, "STRING"},
    {VAR, "VAR"}, {ELSE, "ELSE"},
    {FOR, "FOR"}, {THEN, "THEN"},
    {DO, "DO"}, {TO, "TO"}, {DOWNTO, "DOWNTO"}, {IDENT, "IDENT"},
    {ICONST, "ICONST"}, {RCONST, "RCONST"},
    {SCONST, "SCONST"}, {PLUS, "PLUS"},
    {MINUS, "MINUS"}, {MULT, "MULT"}, {DIV, "DIV"}, 
    {ASSOP, "ASSOP"}, {LPAREN, "LPAREN"}, {RPAREN, "RPAREN"}, 
    {COMMA, "COMMA"}, {EQUAL, "EQUAL"}, {GTHAN, "GTHAN"}, 
    {LTHAN, "LTHAN"}, {SEMICOL, "SEMICOL"}, {COLON, "COLON"},
    {DOT, "DOT"}, {ERR, "ERR"}, {DONE, "DONE"}
};
 
string upperCase(string str){
    for(int i = 0; i < str.length(); i++){
        str[i] = toupper(str[i]);
    }
    return str;
}



LexItem getNextToken(istream& in, int& linenum){
    enum TokenState {START, INID, INSTRING, ININT, INREAL, INCOMMENT} lexstate = START;
    char character;
    char nCharacter;
    string lex="";
    //int strtype=0;


    while (in.get(character)) {
        switch (lexstate) {

            case START:
                if (in.peek() == -1 || in.eof()){
                    return LexItem(DONE, "DONE", linenum);
                }
                if (character == '\n'){
                    linenum++;
                    continue;
                }
                if (isspace(character)){
                    continue;
                }
               //lex = character;
                if (isalpha(character)){
                    lex=toupper(character);
                    lexstate = INID;
                }
                if( character == '"' ){
                    lexstate = INSTRING;
                    continue;	
                }
                if( character == '\'' ) {
                    lexstate = INSTRING;

                }
                if(isdigit(character) ) {
                    lexstate = ININT;
                }
                if (character == '/' && char(in.peek()) == '/') {
                    lexstate = INCOMMENT;
                }
                if( character == '+' ) {
                    lex += character;
                    return LexItem(PLUS,lex,linenum);
                }              
                if(character == '-'){
                    lex += character;
                    return LexItem(MINUS,lex,linenum);
                } 
                if(character == '*'){
                    lex += character;
                    return LexItem(MULT,lex,linenum);
                } 
                    //comment 
                if(character == '/'){
                    lex += character;
                    return LexItem(DIV,lex,linenum);
                } 
                if(character == ';'){
                    lex+=character;
                    return LexItem(SEMICOL,lex,linenum);  
                }
                    
                if(character == '='){
                    lex += character;
                    return LexItem(EQUAL,lex,linenum);
                    
                }  
                if(character == '('){
                    lex += character;
                    nCharacter = in.peek();
                    if(nCharacter == '*'){
                        lexstate= INCOMMENT;
                    }
                    else{
                        return LexItem(LPAREN,lex,linenum);
                    }
                }
                if(character == ')'){
                    lex += character;
                    return LexItem(RPAREN,lex,linenum);
                }
                if(character == ':'){
                    lex += character;
                    nCharacter = in.peek();
                    if(nCharacter == '='){
                        in.get(character);
                        return LexItem(ASSOP,lex,linenum); 
                    }
                    else{
                        return LexItem(COLON,lex,linenum);
                    }
                }
                if(character == ','){
                    lex += character;
                    return LexItem(COMMA,lex,linenum);
                }
                if(character == '<'){
                    lex += character;
                    return LexItem(LTHAN,lex,linenum);
                }
                if(character == '>'){
                    lex += character;
                    return LexItem(GTHAN,lex,linenum);
                    }
                if(character == '.'){
                    lex += character;
                    return LexItem(DOT,lex,linenum);
                    /*nCharacter = in.peek();
                    if(isdigit(nCharacter)){
                        lexstate = INREAL; 
                    }*/
                }
                if(character == '\'' || character =='"'){
                        lexstate = INSTRING;
                    }
                    break;
        
                               
            case INID:
                if( isalpha(character) || isdigit(character) ) {
                    //character = toupper(character);
                    lex += character;
                    if(!isalnum(in.peek())) {
                        }
                }
                else{
                     if(character == '!' || character == '.'  || character == '#'){
                            lex += character;
                            return LexItem(ERR,lex,linenum); 
                        }  
                 
                        in.putback(character);
                        string keyword = upperCase(lex);
                        
                        
                        if(keyword == "PROGRAM"){
                            return LexItem(PROGRAM,keyword,linenum);
                        } 
                        else if(keyword == "WRITELN"){
                            return LexItem(WRITELN,keyword,linenum);
                        }
                        else if(keyword == "INTEGER"){
                            return LexItem(INTEGER,keyword,linenum);
                        }
                        else if(keyword == "BEGIN"){
                            return LexItem(BEGIN,keyword,linenum);
                        }
                        else if(keyword == "END"){
                            return LexItem(END,keyword,linenum);
                        }
                        else if(keyword == "IF"){
                            return LexItem(IF,keyword,linenum);
                        }
                        else if(keyword == "REAL"){
                            return LexItem(REAL,keyword,linenum);
                        }
                        else if(keyword == "STRING"){
                            return LexItem(STRING,keyword,linenum);
                        }
                        else if(keyword == "VAR"){
                            return LexItem(VAR,keyword,linenum);
                        }
                        else if(keyword == "ELSE"){
                            return LexItem(ELSE,keyword,linenum);
                        }
                        else if(keyword == "FOR"){
                            return LexItem(FOR,keyword,linenum);
                        }
                        else if(keyword == "THEN"){
                            return LexItem(THEN,keyword,linenum);
                        }
                        else if(keyword == "DO"){
                            return LexItem(DO,keyword,linenum);
                        }
                        else if(keyword == "TO"){
                            return LexItem(TO,keyword,linenum);
                        }
                        else if(keyword == "DOWNTO"){
                            return LexItem(DOWNTO,keyword,linenum);
                        }
                        else{ 
                            return LexItem(IDENT,lex,linenum);
                        }
                    }

                    break;
                

            case INSTRING:

                if(character == '\'') {
                    lex+=character;
                    return LexItem(SCONST, '\''+ lex, linenum);
                }
                //lex += character;
                else if(character == '\n'){
                    lex.insert(0, 1, '\'');
                    return LexItem(ERR, lex, linenum);
                }
                else {
                    lex+=character;
                }
                

                break;

            case ININT:
                if( isdigit(character) ) {
                    lex += character;
                }
                else if(character == '.') {
                    lexstate = INREAL;
                    lex+= character; 
                }
                else if (isalpha(character)){
                    lex+= character; 
                    lexstate = INID;
                }
                else {
                    in.putback(character);
                    return LexItem(ICONST, lex, linenum);
                }
                break;

            case INREAL:
                if (isdigit(character)){
                    lex+= character;
                }
                else if(isalpha(character)){
                    lex += character;
                    lexstate = INID ;
                }
                else if(character == '.'){
                    lex+=character;
                    return LexItem(ERR,lex,linenum);
                }
                else {
                    in.putback(character);
                    return LexItem(RCONST, lex, linenum);
                }
                
                break;


            case INCOMMENT:
                if( character == '\n' ) {
                    linenum++;
                    //lexstate = START;
                }
                if(in.peek()==1){
                    cout << "Missing a comment end delimiters '*)'at line " << linenum <<endl;
                    return LexItem(ERR, lex, linenum);
                }
                else if (character== '(' && lex.back()== '*'){
                    lexstate= START;
                    break;
                }
                break;
          
             if (in.peek() == -1 || in.eof()){
                         return LexItem(DONE,"",0); 
                }
           /*
           case DONE:
                    return LexItem(DONE, lex, linenum);
                    break;
           
           case ERR:
                    return LexItem(ERR, lex, linenum);
                    break;
            */
                }
        }
    return LexItem();
    }


ostream& operator<<(ostream& out, const LexItem& tok) {
    Token get = tok.GetToken();
    out<<TokenString[get];
    if((get == SCONST) || (get == RCONST) || (get == ICONST) || (get == IDENT) || (get == ERR)){
        out << "(" << upperCase(tok.GetLexeme()) << ")";
    }
    return out;
}

    


