//
// Created by yirat on 24/05/2020.
//

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int fd[2];
int val=0;
int toFinish=1;
int x;
pid_t pid,ppid,id;

//fd[0]= to read
//fd[1]= to write


void sig_handle(int sig){
        if(val==5){
            printf("%d\n", val);
            printf("Son in term\n");
            printf("father is term\n");
            toFinish = 0;
            return;
        }
        printf("%d",val);
        if(pid==getpid()){    //son process
            x = 0;
            read(fd[0], &x, sizeof(int));
            val = ++x;
            write(fd[1], &val, sizeof(int));
            usleep(1000000);
            kill(ppid, SIGUSR1);

        }
        else if(ppid==getpid()){
            x=0;
            read(fd[0], &x, sizeof(int));
            val = ++x;
            write(fd[1], &val, sizeof(int));
            usleep(1000000);
            kill(pid, SIGUSR1); // send the signal.

        }
//    if (val == 5) {
//
//    }
//    else{
//        printf("%d\n", val);
//    }
}


int main(){
    int start=0;
    if(pipe(fd)<0){
        printf("pipe is failed");
        return -1;
    }
    pid = fork();
    if(pid<0){
        printf("fork failed");
        return -1;
    }

        if(pid) { //father process.
            signal(SIGUSR1, sig_handle);

        }
        else {
             signal(SIGUSR1, sig_handle);
             ppid = getppid();
             printf("son is here");
             write(fd[1], &val, sizeof(int));
             kill(ppid, SIGUSR1);

        }
        printf("aabout to go to loop");
        while(toFinish){}


    close(fd[0]);
    close(fd[1]);
    return 0;
}












//    while(toFinish) {
//        if (pid) { //father process
//
//                if(turn ==0) {
//                    read(fd[0], &x, sizeof(int));
//                    val=++x;
//                    write(fd[1], &val, sizeof(int));
//                    usleep(1000000);
//                    turn =1;
//                    kill(pid, 10); // send the signal.
//                }
//
//        } else {  //son process
//            pid_t fPID= getppid();
//            if(start==0 && turn ==2){
//                write(fd[1],&val, sizeof(int));
//                usleep(1000000);
//                start++;
//                turn =0;
//                kill(fPID,10);
//            }
//            else{
//                    if(turn ==1) {
//                        read(fd[0], &x, sizeof(int));
//                        val=++x;
//                        write(fd[1], &val, sizeof(int));
//                        usleep(1000000);
//                        turn =0;
//                        kill(fPID, 10);
//                    }
//
//            }
//        }
//    }
