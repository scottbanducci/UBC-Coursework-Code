#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// YOU: Allocate these global variables, using these names
char str1[31] = "Welcome! Please enter a name: ";
char str2[12] = "Good luck, ";



void print(char str[]){
    write(1,str,strlen(str));
} 

int main()
{
    char buf[128];
    print(str1);
    
    int size = read(0,buf, 256);

    print(str2);

    write(1,buf,size);
    
}