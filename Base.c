#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#include <direct.h>
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

//_insert is a function which insert the data into any given table
//
//

    int _inserter(char (*p)[WIDTH]);
//

int _selector(char (*p)[WIDTH]);
//_use is a function  which is used to
//

int _deleter(char (*p)[WIDTH]);

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



//_checkDB is a function which checks if a database is included or not
//
    int _checkDB(){
    if(strcmp(workingPath,"F:\\aadikofolder\\")==0) return 0;
    return 1;
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
    if (strcmp(strupr(p[0]),"INSERT")==0){
        _inserter(p);
        return 0;
    }
    if (strcmp(strupr(p[0]),"SELECT")==0){
        _selector(p);
        return 0;
    }
    if (strcmp(strupr(p[0]), "DELETE") == 0) {
    _deleter(p);
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
        char runningPath[50]; //for txt table
        char runningPath2[50]; //for metadata
        strcpy(runningPath,workingPath);
        strcat(runningPath,"\\");
        strcat(runningPath,p[2]);
        strcat(runningPath,".txt");
        _creator_f=fopen(runningPath,"r");
        if(_creator_f){
            fclose(_creator_f);
            strcpy(runningPath2,workingPath);
            strcat(runningPath2,"\\");
            strcat(runningPath2,p[2]);
            strcat(runningPath2,".meta");
            if(remove(runningPath)==0&&remove(runningPath2)==0){
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
//printf("\nThe inside string is %s  %d\n",tableStructure,handleTable_countColumns);
char (*p1)[30]= _columnNormalizer(tableStructure,handleTable_countColumns);
int i;

struct aboutTable _workingTable;
strcpy(_workingTable.name, p[2]);
_workingTable.fieldCount=handleTable_countColumns;
_workingTable.pColumns=(struct aboutColumns *)calloc(sizeof(struct aboutColumns),_workingTable.fieldCount);
for(i=0;i<handleTable_countColumns*2;i++){
    if(i%2==0){
        strcpy(_workingTable.pColumns[i/2].name,p1[i]);
    }
    else {
        strcpy(_workingTable.pColumns[(i-1)/2].dataType,p1[i]);
    }
}
printf("\n\n\nThe Defined table is as follows:\n\n\n");
for(i=0;i<handleTable_countColumns;i++){
    printf("|\t%s\t|",_workingTable.pColumns[i].name);
}
printf("\n\n");
for(i=0;i<handleTable_countColumns;i++){
    printf("|\t%s\t|",_workingTable.pColumns[i].dataType);
}
printf("\n");
char runningPath[50];
strcpy(runningPath,workingPath);
strcat(runningPath,"\\");
strcat(runningPath,p[2]);
strcat(runningPath,".meta");
FILE *metaFileForTable;
metaFileForTable=fopen(runningPath,"w");
fprintf(metaFileForTable,"fieldCount=%d\n",_workingTable.fieldCount);
fprintf(metaFileForTable,"rowCount=%d\n",0);
for(i=0;i<handleTable_countColumns*2;i+=2){
    fprintf(metaFileForTable,"%s:%s\n",p1[i],p1[i+1]);
}
fclose(metaFileForTable);
}

char* _columnNormalizer(char p[], int columnCount){

    //  THE TOKENIZER IS A FUNCTION WHICH BREAKS DOWN A 1 DIMENTIONAL QUERY INTO A 2D ARRAY IN WICH
//  EACH ROW CONTAINS EVERY DIFFERENT WORD
//
    static char breakdown1[30][30];//STATIC IS USED AS ONLY STATIC VARIABLES CREATED INSIDE FUNCTION CAN BE PASSED INTO ANOTHER FUNCTION
    // THE main() FUNCTION IS AN EXCEPTION AS OTHER FUNCTIONS ACT AS SUB FUNCTIONS OF IT IDK HOW THO XD
    memset(breakdown1, 0, sizeof(breakdown1));
    int i=0,j=-1,k=0;//as in 1st iteration j will increment

//(name:str,address:str,roll:int);
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
        if(j/2!=columnCount){
        return breakdown1;}
        else{
            printf("Error bhayo hai :(\n");
            return NULL;
        }
    }

int _inserter(char (*p)[WIDTH]) {
    if (!_checkDB()) {
        printf("Please open a database first!\n");
        return -1;
    }

    // Extract table name
    char tableName[30];
    strcpy(tableName, p[1]);

    // Extract values from query
    char values[100] = {0};
    int i = 2;
    while (p[i][0] != '\0') {
        strcat(values, p[i]);
        strcat(values, " ");
        i++;
    }

    // Clean values string
    char* start = strchr(values, '(');
    char* end = strchr(values, ')');
    if (start && end) {
        *end = '\0';
        strcpy(values, start + 1);
    } else {
        strcpy(values, p[2]);
    }

    // Read metadata
    char metaPath[50];
    snprintf(metaPath, sizeof(metaPath), "%s\\%s.meta", workingPath, tableName);

    FILE* metaFile = fopen(metaPath, "r");
    if (!metaFile) {
        printf("Error: Table '%s' does not exist.\n", tableName);
        return -1;
    }

    int fieldCount = 0, rowCount = 0, columnIndex = 0;
    char columnNames[30][30], columnTypes[30][10];
    char line[100];

    while (fgets(line, sizeof(line), metaFile)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline

        if (strstr(line, "fieldCount=")) {
            sscanf(line, "fieldCount=%d", &fieldCount);
        }
        else if (strstr(line, "rowCount=")) {
            sscanf(line, "rowCount=%d", &rowCount);
        }
        else if (strchr(line, ':')) {
            char* colon = strchr(line, ':');
            *colon = '\0';

            // Trim whitespace from column name and type
            char* nameEnd = line + strlen(line) - 1;
            while (isspace(*nameEnd)) nameEnd--;
            *(nameEnd + 1) = '\0';
            strcpy(columnNames[columnIndex], line);

            char* typeStart = colon + 1;
            while (isspace(*typeStart)) typeStart++;
            char* typeEnd = typeStart + strlen(typeStart) - 1;
            while (isspace(*typeEnd)) typeEnd--;
            *(typeEnd + 1) = '\0';
            strcpy(columnTypes[columnIndex], typeStart);

            columnIndex++;
        }
    }
    fclose(metaFile);

    // Validate metadata consistency
    if (columnIndex != fieldCount) {
        printf("Error: Metadata mismatch in '%s' (expected %d fields, found %d)\n",
              tableName, fieldCount, columnIndex);
        return -1;
    }

    // Parse input values
    char* tokens[30] = {0};
    int valueCount = 0;
    char* token = strtok(values, ",");

    while (token && valueCount < 30) {
        // Trim whitespace
        while (isspace(*token)) token++;
        char* end = token + strlen(token) - 1;
        while (end >= token && isspace(*end)) end--;
        *(end + 1) = '\0';

        tokens[valueCount++] = token;
        token = strtok(NULL, ",");
    }

    // Validate value count
    if (valueCount != fieldCount) {
        printf("Error: Expected %d values, got %d\n", fieldCount, valueCount);
        return -1;
    }

    // Type validation
    for (int i = 0; i < valueCount; i++) {
        char* value = tokens[i];
        char* expectedType = columnTypes[i];
        char* endPtr;

        if (strcmp(expectedType, "int") == 0) {
            long num = strtol(value, &endPtr, 10);
            if (*endPtr != '\0' || strlen(value) == 0) {
                printf("Error: Column '%s' requires integer, got '%s'\n",
                      columnNames[i], value);
                return -1;
            }
        }
        else if (strcmp(expectedType, "str") == 0) {
            if (strlen(value) == 0) {
                printf("Error: Column '%s' requires non-empty string\n",
                      columnNames[i]);
                return -1;
            }
        }
        else {
            printf("Error: Unknown type '%s' for column '%s'\n",
                  expectedType, columnNames[i]);
            return -1;
        }
    }

    // Write to data file
    char dataPath[50];
    snprintf(dataPath, sizeof(dataPath), "%s\\%s.txt", workingPath, tableName);

    FILE* dataFile = fopen(dataPath, "a");
    if (!dataFile) {
        printf("Error: Couldn't open data file for '%s'\n", tableName);
        return -1;
    }

    for (int i = 0; i < valueCount; i++) {
        fprintf(dataFile, "%s%c", tokens[i], (i == valueCount-1) ? '\n' : ',');
    }
    fclose(dataFile);

    // Update metadata row count
    metaFile = fopen(metaPath, "r+");
    if (!metaFile) {
        printf("Error: Couldn't update metadata for '%s'\n", tableName);
        return -1;
    }

    char metaContent[1024] = {0};
    rewind(metaFile);
    while (fgets(line, sizeof(line), metaFile)) {
        if (strstr(line, "rowCount=")) {
            sprintf(line, "rowCount=%d\n", rowCount + 1);
        }
        strcat(metaContent, line);
    }

    fclose(metaFile);
    metaFile = fopen(metaPath, "w");
    fprintf(metaFile, "%s", metaContent);
    fclose(metaFile);

    printf("Successfully inserted 1 row into '%s'\n", tableName);
    return 0;
}
int _selector(char (*p)[WIDTH]) {
    if (!_checkDB()) {
        printf("Error: No database selected.\n");
        return -1;
    }

    // Step 1: Parse the SELECT query
    char tableName[30];
    strcpy(tableName, p[3]); // Assuming query is "SELECT * FROM table;"

    // Step 2: Read metadata to get columns
    char metaPath[50];
    snprintf(metaPath, sizeof(metaPath), "%s\\%s.meta", workingPath, tableName);

    FILE* metaFile = fopen(metaPath, "r");
    if (!metaFile) {
        printf("Error: Table '%s' does not exist.\n", tableName);
        return -1;
    }

    // Read column names and types
    char columns[30][30];
    char types[30][10];
    int fieldCount = 0;
    char line[100];

    while (fgets(line, sizeof(line), metaFile)) {
        if (strchr(line, ':')) {
            char* colon = strchr(line, ':');
            *colon = '\0';
            strcpy(columns[fieldCount], line);
            strcpy(types[fieldCount], colon + 1);
            fieldCount++;
        }
    }

    fclose(metaFile);

    // Step 3: Determine columns to display
    int displayAll = 0;
    int displayColumns[30] = {0}; // 1 = display, 0 = skip

    if (strcmp(p[1], "*") == 0) {
        // Select all columns
        displayAll = 1;
        for (int i = 0; i < fieldCount; i++) displayColumns[i] = 1;
    } else {
        // Select specific columns (e.g., "SELECT name, age")
        for (int i = 1; p[i][0] != '\0' && strcmp(p[i], "FROM") != 0; i++) {
            for (int j = 0; j < fieldCount; j++) {
                if (strcmp(p[i], columns[j]) == 0) {
                    displayColumns[j] = 1;
                    break;
                }
            }
        }
    }

    // Step 4: Read data from the .txt file
    char dataPath[50];
    snprintf(dataPath, sizeof(dataPath), "%s\\%s.txt", workingPath, tableName);

    FILE* dataFile = fopen(dataPath, "r");
    if (!dataFile) {
        printf("Error: Table '%s' has no data.\n", tableName);
        return -1;
    }

    // Step 5: Print formatted output
    printf("\n");
    // Print header
    for (int i = 0; i < fieldCount; i++) {
        if (displayAll || displayColumns[i]) {
            printf("| %-15s ", columns[i]);
        }
    }
    printf("|\n");

    // Print separator
    for (int i = 0; i < fieldCount; i++) {
        if (displayAll || displayColumns[i]) {
            printf("|-----------------");
        }
    }
    printf("|\n");

    // Print rows
    char row[500];
    while (fgets(row, sizeof(row), dataFile)) {
        char* token = strtok(row, ",");
        int colIdx = 0;

        while (token) {
            // Trim whitespace/newline
            char* end = token + strlen(token) - 1;
            while (*end == ' ' || *end == '\n') end--;
            *(end + 1) = '\0';

            if (displayAll || displayColumns[colIdx]) {
                printf("| %-15s ", token);
            }
            token = strtok(NULL, ",");
            colIdx++;
        }
        printf("|\n");
    }

    fclose(dataFile);
    return 0;
}
int _deleter(char (*p)[WIDTH]) {
    if (!_checkDB()) {
        printf("Please open a database first!\n");
        return -1;
    }

    // Step 1: Extract table name
    char tableName[30];
    strcpy(tableName, p[1]); // Table name is in p[1]

    // Step 2: Check if table exists
    char dataPath[50], metaPath[50];
    snprintf(dataPath, sizeof(dataPath), "%s\\%s.txt", workingPath, tableName);
    snprintf(metaPath, sizeof(metaPath), "%s\\%s.meta", workingPath, tableName);

    FILE* dataFile = fopen(dataPath, "r");
    if (!dataFile) {
        printf("Error: Table '%s' does not exist.\n", tableName);
        return -1;
    }

    // Step 3: Read the condition (DELETE tableName WHERE column=value)
    if (strcmp(strupr(p[2]), "WHERE") != 0) {
        printf("Error: Expected 'WHERE' clause.\n");
        fclose(dataFile);
        return -1;
    }

    char columnToMatch[30], valueToMatch[30];
    strcpy(columnToMatch, p[3]); // Column name
    strcpy(valueToMatch, p[5]);  // Value (assuming simple format column=value)

    // Step 4: Read table metadata to find column index
    FILE* metaFile = fopen(metaPath, "r");
    if (!metaFile) {
        printf("Error: Could not read metadata for '%s'.\n", tableName);
        fclose(dataFile);
        return -1;
    }

    int fieldCount = 0, rowCount = 0, columnIndex = -1;
    char columnNames[30][30], columnTypes[30][10];
    char line[100];

    while (fgets(line, sizeof(line), metaFile)) {
        if (strstr(line, "rowCount=")) {
            sscanf(line, "rowCount=%d", &rowCount);
        } else if (strchr(line, ':')) {
            char* colon = strchr(line, ':');
            *colon = '\0';
            strcpy(columnNames[fieldCount], line);
            strcpy(columnTypes[fieldCount], colon + 1);
            if (strcmp(columnNames[fieldCount], columnToMatch) == 0) {
                columnIndex = fieldCount;
            }
            fieldCount++;
        }
    }
    fclose(metaFile);

    if (columnIndex == -1) {
        printf("Error: Column '%s' not found in table '%s'.\n", columnToMatch, tableName);
        fclose(dataFile);
        return -1;
    }

    // Step 5: Read all rows and filter out the ones matching the condition

    FILE* tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error: Could not create temp file.\n");
        fclose(dataFile);
        return -1;
    }

    int deletedRows = 0;
    while (fgets(line, sizeof(line), dataFile)) {
        char* tokens[30] = {0};
        int tokenIndex = 0;
        char* token = strtok(line, ",");
        while (token) {
            tokens[tokenIndex++] = token;
            token = strtok(NULL, ",");
        }
        // Compare value in the specified column
        if (strcmp(tokens[columnIndex], valueToMatch) == 0) {
            deletedRows++;
            continue; // Skip this row (delete it)
        }
        // Write back rows that are not deleted
        for (int i = 0; i < tokenIndex; i++){
        if(((i+1)%(fieldCount+1))==0){
            fprintf(tempFile,"\n");
            continue;//VVIMP LINE
        }
            fprintf(tempFile, "%s,", tokens[i]);
        }
    }

    fclose(dataFile);
    fclose(tempFile);

    // Replace original file with temp file
    remove(dataPath);
    rename("temp.txt", dataPath);
    // Step 6: Update row count in metadata
    if (deletedRows > 0) {
        rowCount -= deletedRows;
        metaFile = fopen(metaPath, "r+");
        if (!metaFile) {
            printf("Error: Could not update metadata.\n");
            return -1;
        }

        char metaContent[1000] = {0};
        while (fgets(line, sizeof(line), metaFile)) {
            if (strstr(line, "rowCount=")) {
                sprintf(line, "rowCount=%d\n", rowCount);
            }
            strcat(metaContent, line);
        }

        fclose(metaFile);
        metaFile = fopen(metaPath, "w");
        fprintf(metaFile, "%s", metaContent);
        fclose(metaFile);
    }
    printf("Deleted %d row(s) from table '%s'.\n", deletedRows, tableName);
    return 0;
}
