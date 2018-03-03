#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct task{
    char *identifier;
    int runtime;
    int totalRunTime;
    int startTime;
    struct task * next;
    struct task * previous;
}List;
typedef struct stack{
    char *identifier;
    int startTime;
    int totalRunTime;
    struct stack * next;
    struct stack * previous;
    int completionTime;
}Stack;
void printCompletedTasks(char * filename);
void printCommands();
void readCommand();
void createTask(char *task_name, int runtime);
void pushToCompletedStack(Stack * task);
int deleteBottomFromStack();
void displayMostRecentCompletedTasks(int k);
void addToWaitingList(List * list);
void removeFromWaitingList(List * list);
void simulate(int k);

List* waitingTasks;
Stack * completedTasks;

int quit=0;
int systemTime=0;
int idleTime=0;
int idle=0;
int main() {
    printf("Welcome to the least slack time scheduler implementation.\n");


    do{
        printCommands();
        readCommand();
    }
    while(quit==0);
    return 0;
}
void printCompletedTasks(char * filename){
    Stack * current=completedTasks;
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while(current!=NULL){
        fprintf(f, "CompletedTask: %s, startTime: %d, finishTime: %d, totalRunTime: %d\n",current->identifier,current->startTime,current->completionTime,current->totalRunTime);
        current=current->next;
    }
    fclose(f);
    printf("Dumped the completed tasks stack into the text file '%s'",filename);


}
void printCommands(){
    printf("\n\nThe avaible commands are:\n");
    printf("\t> MRCT k\t'Display the information of most recently completed k tasks'\n");
    printf("\t> ECTS\t'Empty completed tasks stack'\n");
    printf("\t> DFCTS file_name\t'Dump completed tasks stack content into a text file named file_name in same directory with the program'\n");
    printf("\t> DECTCTS k\t'Delete k earliest completed tasks from the stack'\n");
    printf("\t> DST\t'Display system time'\n");
    printf("\t> DIT\t'Display total (idle) time'\n");
    printf("\t> SNT task_name runtime\t'Start a new task'\n");
    printf("\t> S k\t'Simulate k units'\n");
    printf("\t> QUIT\t'Quit the program'\n");
    //printTasks();

    printf("Please enter a command:\n");
    printf("\t> ");
}
void readCommand(){
    int maxLength=50;
    char str[maxLength];
    fgets(str,maxLength,stdin);
    char * pch;
    pch = strtok (str," \n");
    int commandIndex=0;
    char *command[3];
    command[0]=NULL;
    command[1]=NULL;
    command[2]=NULL;
    while (pch != NULL)     //Parse the input with splitting with spaces into the command array
    {
        command[commandIndex]=pch;
        pch = strtok (NULL, " \n");
        commandIndex++;
    }
    if(command[0]==NULL){
        printf("Error: You need to enter a command.\n");
    }
    else{
        if(strncmp("MRCT",command[0],4)==0){
            if(command[1]!=NULL){
                //display most recent k tasks
                displayMostRecentCompletedTasks(atoi(command[1]));
            }
            else{
                printf("Wrong syntax, expected a value of k, ending program.\n");
                exit(1);
            }

        }
        else if(strncmp("ECTS",command[0],4)==0){
            //Empty completed tasks stack
            while(deleteBottomFromStack()==1);
            printf("Emptied the tasks stack\n");
        }
        else if(strncmp("DFCTS",command[0],5)==0){
            //Dump completed tasks stack content into a text file
            if(command[1]!=NULL){
                printCompletedTasks(command[1]);
            }
            else{
                printf("Error: You need to specify the file name, like this: DFCTS test.txt\n");
            }
        }
        else if(strncmp("DECTCTS",command[0],7)==0){
            //Delete k earliest completed tasks from the stack
            if(command[1]!=NULL){
                int i;
                for(i=0;i<atoi(command[1]);i++){
                    if(deleteBottomFromStack()==0)
                        printf("There arent any task to delete in completed tasks stack\n");
                }
            }
            else{
                printf("Error: You need to specify the how many earliest completed tasks to be deleted.\n");
            }
        }
        else if(strncmp("DST",command[0],3)==0){
            //display system time
            printf("System time: %d\n",systemTime);
        }
        else if(strncmp("DIT",command[0],3)==0){
            //display total idle time
            printf("Total idle time: %d\n",idleTime);
        }
        else if(strncmp("SNT",command[0],3)==0){
            if(command[1]!=NULL){
                if(command[2]!=NULL){
                    //start a new task
                    createTask(command[1],atoi(command[2]));
                    printf("Created the task: %s, %d\n\n",command[1], atoi(command[2]));
                }
                else{
                    printf("Error: You need to specify the task runtime length.\n");
                }
            }
            else{
                printf("Error: You need to specify the task name.\n");
            }
        }
        else if(strncmp("S",command[0],1)==0){
            if(command[1]!=NULL){
                //simulate k units
                simulate(atoi(command[1]));
                printf("Simulated %d units.\n",atoi(command[1]));
            }else{
                printf("Error: You need to specify the simulation duration.\n");
            }
        }

        else if(strncmp("QUIT",command[0],4)==0){
            quit=1;
            printf("Quitting...");
        }
        else{
            printf("Error: Unknown command, please try again.\n");
        }
    }
}
void createTask(char *task_name, int runtime){
    List *newList=malloc(sizeof(List));
    char * taskn=strdup(task_name);
    int runtimen=runtime;
    newList->identifier=taskn;
    newList->runtime=runtimen;
    newList->next=waitingTasks;
    newList->previous=NULL;
    newList->totalRunTime=runtime;
    newList->startTime=systemTime;
    if(waitingTasks==NULL)
        waitingTasks=newList;
    else{
        waitingTasks->previous=newList;
        waitingTasks=waitingTasks->previous;
    }
}
void pushToCompletedStack(Stack * task){
    //Stack * stack=malloc(sizeof(Stack));
    task->previous=NULL;
    task->next=completedTasks;
    if(completedTasks!=NULL){
        completedTasks->previous=task;

    }
    completedTasks=task;

}
int deleteBottomFromStack(){
    Stack *current=completedTasks;
    if(current!=NULL){
        while(current->next!=NULL){
            current=current->next;
        }

        if(current->previous!=NULL){
            current->previous->next=NULL;
        }
        else{
            completedTasks=NULL;
        }
        printf("Deleted task: %s\n",current->identifier);
        free(current);
        return 1;
    }
    else return 0;
}
void displayMostRecentCompletedTasks(int k){
    int i;
    Stack *tmpStack=completedTasks;
    for(i=0;i<k;i++){
        if(tmpStack!=NULL){
            printf("Completed task, Name: %s, Total Run Time: %d, Completion Time: %d\n",tmpStack->identifier,tmpStack->totalRunTime,tmpStack->completionTime);
            tmpStack=tmpStack->next;
        }
    }

}
void addToWaitingList(List * list){
    list->next=waitingTasks;
    list->previous=NULL;
    if(waitingTasks!=NULL){
        waitingTasks->previous=list;
        waitingTasks=waitingTasks->previous;
    }
    else
        waitingTasks=list;
}
void removeFromWaitingList(List * list){
    if(list->previous!=NULL)
        list->previous->next=list->next;
    else
        waitingTasks=list->next;
    if(list->next!=NULL)
        list->next->previous=list->previous;

}
void simulate(int k){
    int i;
    for(i=0;i<k;i++){
        idleTime++;
        List * current=waitingTasks;
        List * minimum=current;
        while(current!=NULL){           //iterates all the tasks and finds the lowest runtime task.
            if(current->runtime < minimum->runtime)
                minimum=current;
            current=current->next;
        }
        if(minimum!=NULL){
            systemTime++;
            idle=0;
            removeFromWaitingList(minimum);
            minimum->runtime--;
            if(minimum->runtime==0){
                Stack * tmp=malloc(sizeof(Stack));
                tmp->identifier=minimum->identifier;
                tmp->totalRunTime=minimum->totalRunTime;
                tmp->completionTime=systemTime-minimum->startTime;
                tmp->startTime=minimum->startTime;

                pushToCompletedStack(tmp);
            }
            else
                addToWaitingList(minimum);
        }
        else{
            if(idle==0){
                systemTime++;
                idle=1;
            }
        }

    }
}
