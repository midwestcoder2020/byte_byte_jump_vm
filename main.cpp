#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

#define JLE '1'
#define SUB '2'
#define MOV '3'
#define JE  '4'

#define MEM_START 0x00
#define MEM_END 0x7f
#define MEM_LEN 0x100
#define OUT 65535

using namespace std;

int main(int argc, char** argv){
    
    std::cout << "running byte byte jump VM" << std::endl;


    //create memory
    unsigned char mem[MEM_LEN];
    memset(mem,0x00,MEM_LEN);

    //create pc 
    char pc,byte_a_addy,byte_b_addy,opp = 0x00;
    
    //load programs instructions
    FILE* f = fopen("program.bbj","rb");

    if(!f){
        printf("Unable to open file!");
        return -1;
    }

    //seek to end
    fseek(f,0,SEEK_END);

    //get size
    long size = ftell(f);

    //seek back to beginning
    fseek(f,0,SEEK_SET);


    //create program instruction array
    //from read size
    char buffer[size];

    int res = fread(buffer,size,1,f);

    if(res !=1){
        printf("unable to read file. closing!");
        fclose(f);
        return -1;
    }

    while(pc < size){
        opp = buffer[pc];
        byte_a_addy = buffer[pc+1];
        byte_b_addy = buffer[pc+2];
        pc+=3;

        printf("opp %c\n",opp);
        printf("byte a %c\n",byte_a_addy);
        printf("byte b %c\n",byte_b_addy);

        switch(opp){

            case JLE:{
            printf("jle opp\n\n");

            //check if a i less thtn zero and jump then address b

            if(mem[byte_a_addy] < 0){
                pc = byte_b_addy;
            }

            }
            break;

            case SUB:{
                printf("sub opp\n\n");

                //sub a from b
                mem[byte_b_addy] = mem[byte_a_addy] - mem[byte_a_addy];
            }
            break;

            case MOV:{
                printf("mov opp\n\n");

                if(byte_b_addy == OUT){
                    cout << byte_a_addy << endl;
                }
                else{
                //move a into be
                mem[byte_b_addy] = mem[byte_a_addy];
                }
            }
            break;

            case JE: {
                printf("je opp\n\n");

                //check if a a == 0 then goto b
                if(mem[byte_a_addy] == 0){
                    pc = byte_b_addy;
                }
            }
            break;

            default:
            printf("unable to parse %c\n\n",opp);
        }
    }

    

    return 0;
}
