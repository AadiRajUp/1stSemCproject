#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>

//the path where the datbases and tables are being created/ worked on
const char _defaultPath[]="F:\\aadikofolder\\";
char workingPath[50];


//Tokenizer is a function that seperates the query string into individual words/tokens
char* tokenizer(char* );
//The FUNCTIONS UNDER TOKENIZER WILL BE LISTED BELOW
//
//
//
//The query parser is a function where tokens are parsed i.e. understood and actions occur
int queryParser(char (*p)[30]);
//THE FUNCTIONS UNDER QUERY PARSER WILL BE LISTED BELOW
//
//THE CREATOR FUNCTION HANDELS THE CREATION COMMANDS WHICH CREATE A FILE
    int _creator(char (*p)[30]);
//
//THE DROPPER IS A FUNCTION THAT HANDELS THE DROP COMMANDS
//

    int _dropper(char (*p)[30]);


//_checkDB is a function which checks if a database is included or not
//
    int _checkDB(){
    if(strcmp(workingPath,"F:\\aadikofolder\\")==0) return 0;
    return 1;
    }

//
//_use is a function  which is used to
//

    int _use(char p[30]){
    if (strcmp(workingPath,_defaultPath)>=0){
        strcpy(workingPath,_defaultPath);
        strcat(workingPath,p);
        if(mkdir(workingPath)==0){
            RemoveDirectory(workingPath);
            printf("THE database doesnt exist. Please try again. You are retuned to the server!\n");
            strcpy(workingPath,_defaultPath);
            return -1;
        }
        printf("USING %s\n",p);
        return 0;
    }
    else{
        printf("An unforseen error occured, please contact the developer");
    exit(-1);
    }
    }

//
//THE END FUNCTION IS A FUNCTION WHICH CHECKS IF THE GIVEN query ENDS AFTER A TERM OR NOT
//

    int _end(char (*p)[30],int pos){
    int _endI;
    for(_endI=pos;_endI<30;_endI++){
        if(p[_endI][0]!='\0'){
            printf("Error Unexpected %s\n",p[_endI]);
            return _endI;
        }

    }
    return 0;
    }




int main(){
    strcpy(workingPath,_defaultPath);//cant be done in a global scope so needs to be done here shoild be in line 10
    char str[900];
    while(1){//THIS WHILE LOOP INSURES THAT THE PROGRAM KEEPS FETCHING QUERIES INTIL EOF IS REACHED EOF MEANING PRESSING CTRL+Z
    memset(str, '\0', strlen(str));//THIS FUNCTION SETS EACH AN EVERY VALUE IN STR TO NULL SO THAT PREVIOUS QUERIES DONT INTERFER
                                    //WITH THE NEW BATCH
    str[strcspn(str, "\n")] = '\0';
    printf("Enter your query: \n");
   if (fgets(str, sizeof(str), stdin) == NULL) {//fgets() IS USED AS IT DOESNT TERMINATE UNTILL NEEDED
            break; // Handle EOF
        }
          str[strcspn(str, "\n")] = '\0';
    char *p;
    p= tokenizer(str);
    queryParser(p);
    if(getch()==26){//26 is the ascii value of ^Z
            break;
    }}
    printf("THANKS for using aadi's database");
    return 0;
}
char* tokenizer(char str[]){
//  THE TOKENIZER IS A FUNCTION WHICH BREAKS DOWN A 1 DIMENTIONAL QUERY INTO A 2D ARRAY IN WICH
//  EACH ROW CONTAINS EVERY DIFFERENT WORD
//
    static char breakdown[30][30];//STATIC IS USED AS ONLY STATIC VARIABLES CREATED INSIDE FUNCTION CAN BE PASSED INTO ANOTHER FUNCTION
    // THE main() FUNCTION IS AN EXCEPTION AS OTHER FUNCTIONS ACT AS SUB FUNCTIONS OF IT IDK HOW THO XD
    memset(breakdown, 0, sizeof(breakdown));
    int i,j,k;
    i=0;
    j=0;
    k=0;
    while(str[i]!='\0'){
        if(str[i]==' '){
            j++;
            i++;
            k=0;
            continue;
        }
        breakdown[j][k]=str[i];
        i++;
        k++;
    }

    return breakdown;
}


int queryParser(char (*p)[30]){
    int i,j,k;//WHILE THE WORD QUERYPARSER MAY SOUND COOL IT'S JUST A BUNCH OF IFS AND ELSES
    i=0;

    while(p[i][0]!='\0'){
        i++;
    }
    int noOfTokens=i+1;
    if (strcmp(strupr(p[0]),"CREATE")==0) {

            _creator(p);
            return 0;

    }
    if (strcmp(strupr(p[0]),"USE")==0){
        if(!_end(p,2)){
        _use(&p[1]);
        return 0;
    }
    return -1;
    }


    if (strcmp(strupr(p[0]),"DROP")==0){
        _dropper(p);
        return 0;
    }

    printf("UNEXPECTED %s\n",p[0]);
    return -1;

}
int _creator(char (*p)[30]){
//CREATOR JUST HANDLES CREATE COMMANDS
//1) DATABASE
//2) TABLE
//
//

    if(strcmp(strupr(p[1]),"DATABASE")==0){
        if(_checkDB()){
            printf("YOU ARE ALREADY ON A DATABASE THE DATABASE %s\n",&workingPath[16]);
            return;
        }
        int check;
        char *dirname;
        char runningPath[50]="";
        strcat(runningPath,workingPath);
        strcat(runningPath,p[2]);
        check = mkdir(runningPath);

        if (!check){
            printf("Database created\n");
            strcat(workingPath,p[2]);
            return 0;
            }
        else {
            printf("Unable to create Database\n");
            return;
        }

    }
    else if(strcmp(strupr(p[1]),"TABLE")==0)
    {
        if(!_checkDB()){
            printf("PLEASE SELECT A DATABASE TO CREATE A TABLE IN\n");
            return;
        }

        FILE *_creator_f;
        char runningPath[50];
        strcpy(runningPath,workingPath);
        strcat(runningPath,"\\");
        strcat(runningPath,p[2]);
        strcat(runningPath,".txt");
        if(fopen(runningPath,"r")){
            printf("ERROR! TABLE ALREADY EXISTS!\n");
            return;
        }

        _creator_f = fopen(runningPath,"w");
        if(_creator_f){
           printf("TABLE %s successfully Created\n", p[2]);
           }
        else{
            printf("An error Occurred! TABLE could not be created\n");
           }
            fclose(_creator_f);
                }
    else{
        printf("ERROR! EXPECTED DATABASE OR TABLE INSTED OF: \"%s\" \n",p[1]);
        }

}



int _dropper(char (*p)[30]){
    int _droppertemp=_end(p,3);
    strupr(p[1]);
//    printf("%d\n",_droppertemp);
//
//printf("%s\t%s\t%s\t%s\t%s\t%d\t%s\n",p[0],p[1],p[2],p[3],p[4],strcmp(p[1],"DATABASE"),workingPath);
 if(strcmp(p[1],"DATABASE")==0){
        if (strcmp(workingPath,_defaultPath)>=0){
        strcpy(workingPath,_defaultPath);
        if(mkdir(workingPath)==0){
            RemoveDirectory(workingPath);
            printf("THE database doesnt exist. Please try again. \n");
            strcpy(workingPath,_defaultPath);
            return -1;
        }
        else{
            if(_droppertemp){
        printf("Error! Unexpected %s after %s\n",p[_droppertemp],p[2]);
           return -1;
        }
        strcat(workingPath,p[2]);

        if(RemoveDirectory(workingPath)!=0)
        {
            printf("Server sucessfully Dropped!\n");
            return 0;
        }
        else{
            printf("Error the server could not be dropped!\n");
            if(GetLastError()==145){
                    printf("Please delete all the tables inside the database!\n");
                    return -1;
                }
            printf("ERROR code : %lu\n",GetLastError());
            return -1;
        }
        }

    }
    }


    else if(strcmp(strupr(p[1]),"TABLE")==0)
    {
        if(!_checkDB()){
            printf("PLEASE SELECT A DATABASE TO DROP A TABLE IN\n");
            return -1;
        }

        FILE *_creator_f;
        char runningPath[50];
        strcpy(runningPath,workingPath);
        strcat(runningPath,"\\");
        strcat(runningPath,p[2]);
        strcat(runningPath,".txt");
        _creator_f=fopen(runningPath,"r");
        if(_creator_f){
            fclose(_creator_f);
            if(remove(runningPath)==0){
                printf("TABLE SUCESSFULLY DROPPED\n");
                return 0;
            }
            else{
                    printf("%s\n",runningPath);

                printf("ERROR! Table couldn't be dropped : %lu\n",GetLastError());
            }
        }
        else{
            printf("The TABLE %s NOT FOUND\n",p[2]);
        }
            fclose(_creator_f);
                }
    else{
        printf("ERROR! EXPECTED DATABASE OR TABLE INSTED OF: \"%s\" \n",p[1]);
        }


}


//FILE *_creator_f;
//if(fopen("HELLO.txt","r")){
//    printf("ERROR! FILE ALREADY EXISTS!");
//    return;
//}
//_creator_f = fopen("HELLO.txt","w");
//if(_creator_f){
//   printf("File successfully Created");
//   }
//   else{
//    printf("An error Occurred! File could not be created");
//   }
//fclose(_creator_f);
//}
