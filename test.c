#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#define LENGTH 30
#define WIDTH 50
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
int queryParser(char (*p)[WIDTH]);
//THE FUNCTIONS UNDER QUERY PARSER WILL BE LISTED BELOW
//
//THE CREATOR FUNCTION HANDELS THE CREATION COMMANDS WHICH CREATE A FILE
    int _creator(char (*p)[WIDTH]);
//
        int handleTable(char (*p)[WIDTH]);
//
//THE columnNormalizer is a function that removes all the unnecesary parts from a program
//
//
            char* _columnNormalizer(char p[],int);
//THE DROPPER IS A FUNCTION THAT HANDELS THE DROP COMMANDS
//

    int _dropper(char (*p)[WIDTH]);


//_checkDB is a function which checks if a database is included or not
//
    int _checkDB(){
    if(strcmp(workingPath,"F:\\aadikofolder\\")==0) return 0;
    return 1;
    }

//
//_use is a function  which is used to
//

    int _use(char p[WIDTH]){
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

    int _end(char (*p)[WIDTH],int pos){
    int _endI,i;
    for(_endI=pos;_endI<LENGTH;_endI++){
        if(p[_endI][0]!='\0'){
            printf("Error Unexpected %s\n",p[_endI]);
            return _endI;
        }

    }
    return 0;
    }
//ALERT GOD LEVEL CODE INCOMMING, MAKING A TABLE YAYYYYYYYYYYYYY!
//
//
//
// AABA HUNXA LOW LEVEL PROGRAMMING OOH SHIIIII
//

//int char string
struct aboutColumns{
char name[30];
char dataType[10];
void *value;
};
struct aboutTable{
char name[30];
int fieldCount;
struct aboutColumns *pColumns;//pColums[feidCOunt];
};



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
    static char breakdown[LENGTH][WIDTH];//STATIC IS USED AS ONLY STATIC VARIABLES CREATED INSIDE FUNCTION CAN BE PASSED INTO ANOTHER FUNCTION
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


int queryParser(char (*p)[WIDTH]){
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
int _creator(char (*p)[WIDTH]){
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
            fclose(_creator_f);
            return;
        }

        _creator_f = fopen(runningPath,"w");
        if(_creator_f){
           printf("TABLE %s successfully Created\n", p[2]);
                       fclose(_creator_f);//THIS LINE NEEDS TO BE REMOVED

           handleTable(p);
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



int _dropper(char (*p)[WIDTH]){
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

int handleTable(char (*p)[WIDTH]){
char tableStructure[100];
int handleTable_temp = 0 , handleTable_i = 3,handleTable_j = 0,handleTable_k = 0,handleTable_switch=0;//Switch flips ensuring everything between '(' and ')' is read
int handleTable_countColumns=1;
memset(tableStructure,'\0',100);
while(p[handleTable_i][0]!='\0'){
if(p[handleTable_i][handleTable_j]=='\0'){
        handleTable_i++;
        handleTable_j=0;
    }

    if (p[handleTable_i][handleTable_j]=='(' || p[handleTable_i][handleTable_j]==';'){
        handleTable_switch=!handleTable_switch;
    }//This here flips the switch on the condition that either ( or ; is detected and the switch is on whilst reading between the columns ; was used for uniformity as closing braces also needed to be implimented
    if(p[handleTable_i][handleTable_j]==','){
        handleTable_countColumns++;
    }
//printf("%d  \n",handleTable_switch);
    if(handleTable_switch){
        tableStructure[handleTable_k]=p[handleTable_i][handleTable_j];
//        printf("%c",tableStructure[handleTable_k]);
    handleTable_k++;
    }

    handleTable_j++;
    }
printf("\nThe inside string is %s  %d\n",tableStructure,handleTable_countColumns);
char (*p1)[30]= _columnNormalizer(tableStructure,handleTable_countColumns);
int i;
for(i=0;i<handleTable_countColumns*2;i++){
    printf("%s\n",p1[i]);
}

}

char* _columnNormalizer(char p[], int columnCount){

    //  THE TOKENIZER IS A FUNCTION WHICH BREAKS DOWN A 1 DIMENTIONAL QUERY INTO A 2D ARRAY IN WICH
//  EACH ROW CONTAINS EVERY DIFFERENT WORD
//
printf("%s",p);
    static char breakdown1[30][30];//STATIC IS USED AS ONLY STATIC VARIABLES CREATED INSIDE FUNCTION CAN BE PASSED INTO ANOTHER FUNCTION
    // THE main() FUNCTION IS AN EXCEPTION AS OTHER FUNCTIONS ACT AS SUB FUNCTIONS OF IT IDK HOW THO XD
    memset(breakdown1, 0, sizeof(breakdown1));
    int i=0,j=-1,k=0;//as in 1st iteration j will increment


while(p[i]!='\0'){
        if(p[i]=='('||p[i]==':'||p[i]==','){
                i++;
        j++;
        k=0;
            continue;
        }
        if(p[i]==')'){
            break;
        }
        breakdown1[j][k]=p[i];
        i++;
        k++;
}
        return breakdown1;
    }






////int _columnNormalizer_i,_columnNormalizer_k=0,_columnNormalizer_switch=0;
////aboutTable.fieldCount=columnCount;
////aboutTable.pColumns = (struct aboutColumns*) calloc(aboutTable.fieldCount,sizeof(struct aboutColumns));
////for(_columnNormalizer_i=0;_columnNormalizer_i<strlen(p);i++){
////    if(p[_columnNormalizer_i]=='('||p[_columnNormalizer_i]==')'){
////        continue;
////    }
////    if(p[_columnNormalizer_i]==':'){
////        _columnNormalizer_switch+=1;
////        continue;
////    }
////    if(p[_columnNormalizer_i]==','){
////        _columnNormalizer_switch-=1;
////        continue;
////    }
////    aboutTable.pColumns[k]
////}
////




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
