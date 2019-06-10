
// #include<stdio.h>
// #include<stdlib.h>
// #include<stdio.h>
// #include<unistd.h>
// #include<sys/types.h>
// #include<string.h>
// #include<wait.h>
// #include<signal.h>
// #include<sys/wait.h>
// #include "md5.h"


// int isMD5=3;
// char md[100];

// void isMd5 (int mysignal){
//     int j=0;
//     int count=0;
//    while(md[j]!='\0'){
//        count++;
//        j++;

//    }

//     if (count==32) isMD5= 1;
//     else isMD5= 0;
    
// }
    


// int main() 
// { 
//     // We use two pipes 
//     // First pipe to send input string from parent 
//     // Second pipe to send concatenated string from child 
  
//     int fd1[2];  // Used to store two ends of first pipe 
//     int fd2[2];  // Used to store two ends of second pipe 
  
//     char input_str[100]; 
//     pid_t p; 
  
//     if (pipe(fd1)==-1) 
//     { 
//         fprintf(stderr, "Pipe Failed" ); 
//         return 1; 
//     } 
//     if (pipe(fd2)==-1) 
//     { 
//         fprintf(stderr, "Pipe Failed" ); 
//         return 1; 
//     } 
  
//     p = fork(); 
  
//     if (p < 0) 
//     { 
//          fprintf(stderr, "fork Failed" ); 
//         return 1; 
//     } 
  
//     // Parent process 
//     else if (p > 0) 
//     { 
//         printf("please enter your string:");
//         scanf("%s", input_str); 

//         char _str[100]; 

//         close(fd1[0]);  // Close reading end of first pipe 
  
//         // Write input string and close writing end of first 
//         // pipe. 
//         write(fd1[1], input_str, strlen(input_str)+1); 
//         close(fd1[1]); 
  
//         // Wait for child to send a string 
//         wait(NULL); 
  
//         close(fd2[1]); // Close writing end of second pipe 
  
//         // Read string from child, print it and close 
//         // reading end. 
//         read(fd2[0], _str, 100); 

//         printf(",d5 %s\n",md);

//         if(isMD5==1){
//         printf("after md5 string: %s\n", _str);

//         }
//         else{
//             printf("Md5 is not good");
//         }

//         //printf("%zu\n",strlen(_str)); 
//         //kill(0,SIGKILL);
      
//         close(fd2[0]); 
//     } 
  
//     // child process 
//     else
//     { 
//         close(fd1[1]);  // Close writing end of first pipe 
  
//         // Read a string using first pipe 
//         char _str[100]; 
//         read(fd1[0], _str, 100); 
  
//         // Concatenate a fixed string with it 
        
//         // Close both reading ends 
//         close(fd1[0]); 
//         close(fd2[0]); 

//         std::string str;
//         str=md5(_str);
//        // char ans[str.length() + 1];
//         int i;

//         for( i=0;i<str.length();i++){
//             md[i]=str.at(i);

//         }
//         md[i]='\0';

       

//         strcpy(md, str.c_str());
//         signal(SIGTERM,isMd5);
//         kill(getpid(),SIGTERM);

  
//         // Write concatenated string and close writing end 
//         write(fd2[1], md, strlen(md)+1); 
//         close(fd2[1]); 
  
//         exit(0); 
//     } 
// } 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include "md5.h"
#include <sys/wait.h>



pid_t pid;
char buff[20];
bool Checksize = 0;
int chlidpid = 0;
 std::string msgrevered;
char* ans;

void catchSigT(int sig_num)
{
if(strlen(msgrevered.c_str()) == 32){
    Checksize = 1;
}
};


int main(int argc,char *argv[])
{

int mypipefd[2];
int ret = pipe(mypipefd);
int i =0;
char str1[20]="";

    signal(SIGTERM, catchSigT);

    if(ret == -1){
        perror("pipes fail");
        exit(1);
    }

pid = fork();

if (pid == 0){
        /* Chlid Process */

    read(mypipefd[0], buff, 20);
    sleep(1);    

    // using md5
    msgrevered = md5(buff);
    char answer[msgrevered.length() + 1];
    strcpy(answer, msgrevered.c_str());
    write(mypipefd[1],answer,strlen(answer) + 1);
    kill(pid,SIGTERM);
    sleep(3);


}else{

        /* Parent Process */

    for(i=1;i<argc;i++){  

    char temp[20]="";
    strncpy(temp, argv[i], 20);
    strcat(temp," ");
    strcat(str1,temp);
    }
    if(strlen(str1) >20){
        perror("size fail");
         kill(0,SIGKILL);
        exit(1);
    }else {
    printf("plain text: %s\n",str1);   
    write(mypipefd[1], str1,20);
    sleep(5);
}
    read(mypipefd[0], buff, 32);
    sleep(5);
    if(Checksize == 1){
        printf("encrypted by process: %d : %s\n ",getpid(),buff);
        sleep(1);

        // kill(0,SIGKILL);
    }

}
}
