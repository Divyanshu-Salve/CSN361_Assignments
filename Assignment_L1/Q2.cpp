#include <stdio.h> 
#include <dirent.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
  
int main(void)
{ 
    char S[1000] = "/sys/class/net/";
    char S1[1000] = "/address";
    strcat(S,"enp2s0");
    strcat(S,S1);
    FILE* ptr = fopen(S,"r"); 
    if (ptr==NULL) 
    { 
        printf("no such file."); 
        return 0; 
    } 
    char Arr[100];
    while (fscanf(ptr,"%s",Arr)==1) 
        printf("MAC address is : %s\n", Arr); 
     
    return 0; 
}