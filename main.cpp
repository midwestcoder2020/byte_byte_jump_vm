#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#define JLE 0x1
#define SUB 0x2
#define MOV 0x3
#define JE  0x4

#define OUT 65535
#define HALT -1

using namespace std;

int main(int argc, char** argv){

    std::cout << "hello byte byte loading file..." << std::endl;
    
    //instruction pointer
    int ip=0;

    //int for registers
    char op,addy_a,addy_b;

    //load file into memory
    std::ifstream infile("./file.raw");

    infile.seekg(0,std::ios::end);
    size_t length = infile.tellg();

    infile.seekg(0,std::ios::beg);

    char *mem = new char[length+1];

    infile.read(mem,length);

    while(ip > 0){

        //example
        // 0, 1, 2

        //get op
        op = mem[ip];

        //get var a from mem
        addy_a=mem[ip+1];

        //get var b from mem
        addy_b=mem[ip+2];    

        //inc ip
        ip+=3;

        //process op
        switch(op){

            case MOV:
            {

                if(addy_b == OUT){
                    cout << mem[addy_a] << endl;
                }
                else{
                mem[addy_b] = mem[addy_a];
                }
            }

            break;

            case JLE:{
                if(mem[addy_a] < 0){
                    ip = addy_b;
                }
            }

            break;

            case SUB:{
                mem[addy_b] -= mem[addy_a];
            }

            case JE:{
                if(mem[addy_a] == 0){
                    ip = mem[addy_b];
                }
            }
            break;

            case HALT:{
                exit(0);
            }
            break;

        }

        
        for(int x = 0; x < length+1;x++){
            cout << mem[x];
            if(x % 5 == 0){
                cout << endl;
            }

        }


    }

    return 0;
}
