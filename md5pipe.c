
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<wait.h>
#include<signal.h>
#include<sys/wait.h>
#include "md5.h"


int isMD5=3;
char md[100];

void isMd5 (int mysignal){
    int j=0;
    int count=0;
   while(md[j]!='\0'){
       count++;
       j++;

   }

    if (count==32) isMD5= 1;
    else isMD5= 0;
    
}
    


int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        printf("please enter your string:");
        scanf("%s", input_str); 

        char _str[100]; 

        close(fd1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first 
        // pipe. 
        write(fd1[1], input_str, strlen(input_str)+1); 
        close(fd1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        close(fd2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close 
        // reading end. 
        read(fd2[0], _str, 100); 

        printf(",d5 %s\n",md);

        if(isMD5==1){
        printf("after md5 string: %s\n", _str);

        }
        else{
            printf("Md5 is not good");
        }

        //printf("%zu\n",strlen(_str)); 
        //kill(0,SIGKILL);
      
        close(fd2[0]); 
    } 
  
    // child process 
    else
    { 
        close(fd1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        char _str[100]; 
        read(fd1[0], _str, 100); 
  
        // Concatenate a fixed string with it 
        
        // Close both reading ends 
        close(fd1[0]); 
        close(fd2[0]); 

        std::string str;
        str=md5(_str);
       // char ans[str.length() + 1];
        int i;

        for( i=0;i<str.length();i++){
            md[i]=str.at(i);

        }
        md[i]='\0';

       

        strcpy(md, str.c_str());
        signal(SIGTERM,isMd5);
        kill(getpid(),SIGTERM);

  
        // Write concatenated string and close writing end 
        write(fd2[1], md, strlen(md)+1); 
        close(fd2[1]); 
  
        exit(0); 
    } 
} 