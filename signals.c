// #include<stdio.h>
// #include<stdlib.h>
// #include<stdio.h>
// #include<unistd.h>
// #include<sys/types.h>
// #include<string.h>
// #include<wait.h>
// #include<signal.h>
// #include<sys/wait.h>


// void signal_handle1(int signal){
//     printf("PID %d %s\n",getpid(),"ready");}
// void signal_handle2(int signal){
//     printf("PID %d %s\n",getpid(),"caught");}
// void signal_handle3(int signal){
//     printf("PID %d %s\n",getpid(),"dead");}

// int main (){

// pid_t pid;

// // the zombie collector

// pid_t zombies[5];

// // create 4 more processes
// for (int i = 0; i < 4; i++) {
//   pid = fork();
//   if(!pid)
//     break;
// }

//     printf("out the loop\n");

// // signal check
//   if (signal(1, signal_handle1) == SIG_ERR){
//   printf("%s\n","can't catch SIGREADY");
//   }
//   else{
// //   wait(0);
//   sleep(2);
//   kill(getpid(),1); // kill order - and set red
//   }



//   if (signal(1, signal_handle2) == SIG_ERR){
//   printf("%s\n","can't catch SIGREADY");
//   }
//   else{
//   sleep(2);
//   kill(getpid(),1); // kill and catch the signal
//   }



// pid_t temp; // for the zombies catch
// int i=0;
//   if (signal(1, signal_handle3) == SIG_ERR){
//   printf("%s\n","can't catch SIGREADY");
//   }
//   else{
//   sleep(2);
//   temp = getpid();
//   kill(getpid(),1); // kill and catch the signal
//   zombies[i] = getpid(); // father catch all the zombies
//   i++;
//   }


// exit(0);
// }
