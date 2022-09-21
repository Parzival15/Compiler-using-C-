#include <fstream> // for file-access
#include <string>
#include <iostream>
#include "lex.h"
#include <map>
#include <list>
 

using namespace std;

int main(int argc, char* argv[]){
    
    bool v = false;
    bool iconst = false;
    bool rconst = false;
    bool sconst = false;
    bool ident  = false;  
    int linenum=1;
    int tokenCount =0;
    LexItem tok;
    list<string> vs;
    list<string> iconsts;
    list<string> rconsts;
    list<string> sconsts;
    list<string> idents;
    
    
    
    if (argc == 1){
        cout << "NO SPECIFIED INPUT FILE NAME." <<endl;
        exit(0);
    }
    
    ifstream infile(argv[1]);
    for(int i=1; i<argc; i++){
        string flag(argv[i]);
        
        if(flag == "-v"){
            v= !v;
        }
        else if (flag== "-iconst"){
            iconst = !iconst;
        }
        else if (flag== "-rconst"){
            rconst = !rconst;
        }
        else if(flag =="-sconst"){
            sconst=!sconst;
        }
        else if(flag =="-ident"){
            ident=!ident;
        }
        else if (flag[0] == '-'){
            cerr << "UNRECOGNIZED FLAG " << flag << endl;
            return -1;
        } 
        else if (i== argc-1){
            infile.open(flag);
            if(infile.is_open() == false){
                cerr << "CANNOT OPEN the File " << argv[1] << endl;
                exit(0);
            }
            ifstream infile;
            infile.peek();
            if (infile.eof()){
                 cout << "Lines: 0" << endl;
                exit(0);
            }  
        }
        
    }
    
    if(infile.is_open()==false){
        cerr << "CANNOT OPEN the File " << argv[1] << endl;
        return -1;
        if(infile.is_open() == false){
                cerr << "CANNOT OPEN the File " << argv[1] << endl;
                exit(0);
            }
    }
    else if(argv[2][0] != '-') {
            cout << "ONLY ONE FILE NAME ALLOWED." <<endl;
            exit(0);
        }  
      
    if (infile.is_open() && infile.good()) {
       while((tok = getNextToken(infile, linenum)) != DONE && tok != ERR ){     //reading  lines from file, stores it into variable called line    
        tokenCount++;


            //populating maps
            if(v){
                cout<<tok<<endl; //this will print bc of overloading function
            }
            if(tok.GetToken() == IDENT){
                idents.push_back(tok.GetLexeme());
            }
            if(tok.GetToken() == SCONST){
                sconsts.push_back(tok.GetLexeme());
        
            }
       }
    }
    
    //printing errors, lines, and tokes
    
    //error printing. if theres even i error. end it
    if(tok.GetToken()== ERR){
        cout<< "Error in line " << linenum << " (" <<tok.GetLexeme()<< ")"<<endl; 
        exit(0);
    }
    
    cout << "Lines: " << linenum << endl;

    if (tokenCount != 0){
        cout << "Tokens: " << tokenCount << endl;
    }
    
    //PRINTING, if the flag is true, then then print out their values
  
    if (ident){
        if (idents.empty());
        cout << "IDENTIFIERS: "<<endl;
            for (string n : idents)
                cout << n << " , ";
    }
    if (sconst){
        if (!sconsts.empty())
        sconsts.sort(); //this sorts everything in alpha order
        cout << "STRINGS:" <<endl;
            for (string n : sconsts)
                cout << n<<endl;
    }
    
    if (rconst){
        if (!rconsts.empty())
        cout << "REALS:" <<endl;
            for (string n : rconsts)
                cout << n;
    }
    if (iconst){
        if (!iconsts.empty())
        cout << "INTEGERS:" <<endl;
            for (string n : iconsts)
                cout << n;
    }
    exit(0);
}
