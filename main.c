#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void login();
void add();                       ///-- User defined functions--///
void startMenu();
void questions();
void q10();
void renderLatex(char *line);
void shuffleOptions(char options[4][100], char *correctAns);
void authenticity_check(char username[],char password[]);

int qCount=0;   
int score=0;                    ///--Global Variable--///

int main() {
    srand(time(NULL));        //Use current time as the starting seed.
    char choice[20];
/////////////////////////////-- Main Menu--/////////////////////////////
    printf("\t\t\t\tWelcome to BCA Entrance preparation\n");
    printf("Main menu:\n");
    printf("a) Login\n");
    printf("b) Register\n");
    printf("c) Exit\n");


/////////////-- User's choice-////////////
    printf("Enter your choice: ");
    scanf("%s", choice);

    if (strcmp(choice, "a") == 0 || strcmp(choice, "Login") == 0) {
        login();
    }
    else if (strcmp(choice, "b") == 0 || strcmp(choice, "Register") == 0) {
        add();
    }
    else if (strcmp(choice, "c") == 0 || strcmp(choice, "Exit") == 0) {
        printf("Hope you return soon\n");
        exit(0);
    }
    else {
        printf("Invalid choice\n");
    }

    return 0;
}

void login() {
    char username[50], password[50];
    printf("\t\t\t\t\tEnter the details \n");

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    printf("Login attempted with Username: %s\n", username);
    authenticity_check(username,password);
}

void add() {         //////////--register-////////
    FILE *ptr,*ptr2;
    char username[50], password[50];

    printf("\t\t\t\t\tRegister new user\n");

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);




/////////--- Writing user's username in the file-----//////////////
    ptr=fopen("user.txt","a");
    if(ptr==NULL){
        printf("Username cannot be saved");
    }
    fprintf(ptr,"%s\n",username);
    fclose(ptr);

/////////--- Writing user's password in the file-----//////////////
    ptr2=fopen("pass.txt","a");
    if(ptr2==NULL){
        printf("Password cannot be saved");
    }
    fprintf(ptr2,"%s\n",password);

    fclose(ptr2);
    printf("User %s registered successfully!\n", username);
    startMenu();





}

void startMenu() {
    char choice[50];

     #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif       //  clear the console screen and reset the cursor to the top-left corner
    printf("\t\t\t\t\t START MENU\n");
    printf("a) Start preparation\n");
    printf("b) Exit\n");  
    printf("Enter your choice : ");
    scanf("%s",choice);


    if(strcmp(choice,"a")==0 || strcmp(choice,"Start preparation")==0){
        questions();


    }
    else if(strcmp(choice,"Exit")==0 || strcmp(choice,"b")==0){
        printf("Exiting...\n");
        exit(0);
    }
}
void shuffleOptions(char options[4][100], char *correctAns) {

    int correctIndex = *correctAns - 'a';

    for (int i = 3; i > 0; i--) {      // swapping with respect to character
                                      // let i=3 and j=1 then after swap i=1 and j=3
        int j = rand() % (i + 1);    // Fisher-Yates shuffle concept

        // swap options
        char temp[100];
        strcpy(temp, options[i]);
        strcpy(options[i], options[j]);
        strcpy(options[j], temp);

        // track correct answer movement
        if (i == correctIndex)  // k hamro corect index ko value pahila i sama same thyo if yes bhane aba swap paxi j ma hola
            correctIndex = j;

        else if (j == correctIndex)
            correctIndex = i;
    }

    *correctAns = 'a' + correctIndex;
}
void renderLatex(char *line) {           // change latex equation into rendered math form as parser does

    char lower[50], upper[50], body[200];

    // INTEGRATION
     char *intPtr = strstr(line, "\\int");   // finds position from when parsing to be done
    if (strstr(line, "\\int")) {
            char before[300];

         int posBefore = intPtr - line;

         strncpy(before, line, posBefore);

         before[posBefore] = '\0';

         printf("%s", before);


        char lower[50], upper[50], body[500];

        sscanf(intPtr,
           "\\int_{%[^}]}^{%[^}]} %[^\n]",
           lower,
           upper,
           body);

    // Separate options
    char equation[300];
    char options[300];

    char *optPtr = strstr(body, "Options:");

    if (optPtr != NULL) {

        int pos = optPtr - body;

        strncpy(equation, body, pos);

        equation[pos] = '\0';

        strcpy(options, optPtr);
    }
    else {

        strcpy(equation, body);
        options[0] = '\0';
    }

    // Convert ^2
    char *ptr;

    if ((ptr = strstr(equation, "^2"))) {

        char temp[300];

        int pos = ptr - equation;

        strncpy(temp, equation, pos);

        temp[pos] = '\0';

        strcat(temp, "²");

        strcat(temp, ptr + 2);

        strcpy(equation, temp);
    }

    // Convert ^3
    if ((ptr = strstr(equation, "^3"))) {

        char temp[300];

        int pos = ptr - equation;

        strncpy(temp, equation, pos);

        temp[pos] = '\0';

        strcat(temp, "³");

        strcat(temp, ptr + 2);

        strcpy(equation, temp);
    }

    // PRINT
    printf("\n");

    printf(" %s\n", upper);

    printf(" ⌠\n");

    printf(" ⎮ %s\n", equation);

    printf(" ⌡\n");

    printf(" %s\n", lower);

    // Print options separately
    if (strlen(options) > 0) {

        printf("\n%s\n", options);
    }
}

    // SUMMATION
    else if (strstr(line, "\\sum")) {

        char start[50], end[50], expr[100];
        char *sumPtr = strstr(line, "\\sum");
        char before[300];

        int posBefore = sumPtr - line;

         strncpy(before, line, posBefore);

         before[posBefore] = '\0';

         printf("%s", before);

        sscanf(sumPtr,
               "\\sum_{n=%[^}]}^{%[^}]} %[^\n]",
               start,
               end,
               expr);

        printf("\n");
        printf("  %s\n", end);
        printf("  Σ %s\n", expr);
        printf(" n=%s\n", start);
    }

// DYNAMIC SQUARE ROOT PARSER
else if (strstr(line, "\\sqrt")) {

    char result[1000] = "";
    char *ptr = line;

    while (*ptr) {

        // Found \sqrt
        if (strstr(ptr, "\\sqrt{") == ptr) {

            ptr += 6; // skip \sqrt{

            strcat(result, "√");

            // copy everything until }
            while (*ptr && *ptr != '}') {

                strncat(result, ptr, 1);
                ptr++;
            }

            // skip }
            if (*ptr == '}') {
                ptr++;
            }
        }

        else {

            strncat(result, ptr, 1);
            ptr++;
        }
    }

    printf("%s\n", result);
}

    // DEFAULT
    else {
        printf("%s", line);
    }
}

void questions() {
    FILE *fq, *fa;
    char qline[256], aline[256];
    int currentLine = 0;
    int qNo;
    char ans;

    printf("From which question number do you want to continue: ");
    scanf("%d", &qNo);
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    fq = fopen("question.txt", "r");
    fa = fopen("ans.txt", "r");

    if (fq == NULL || fa == NULL) {
        printf("Error opening files.\n");
        return;
    }

    // Skip lines before qNo
    while (currentLine < qNo - 1 &&
           fgets(qline, sizeof(qline), fq) &&
           fgets(aline, sizeof(aline), fa)) {
        currentLine++;
    }

    // MAIN LOOP (continuous questions)
    while (fgets(qline, sizeof(qline), fq) &&       // while (there is another question AND another answer)
           fgets(aline, sizeof(aline), fa)) {

        currentLine++;
        qCount++;

        printf("\nQuestion %d:\n", currentLine);

        if (strstr(qline,"\\") )    {    //qline conatins 1 question and it contains whether it is in latex form or not
           renderLatex(qline);
        }
        else {
        char *optPtr = strstr(qline, "Options:");

if (optPtr != NULL) {

    int pos = optPtr - qline;

    char questionPart[500];

    strncpy(questionPart, qline, pos);

    questionPart[pos] = '\0';

    printf("%s\n", questionPart);

    // extract options
    char options[4][100];

    sscanf(optPtr,
           "Options: a) %[^b] b) %[^c] c) %[^d] d) %[^\n]",
           options[0],
           options[1],
           options[2],
           options[3]);

    // original correct answer
    char correctAns = aline[0];

    // shuffle
    shuffleOptions(options, &correctAns);

    // print shuffled options
    printf("Options:\n");

    printf("a) %s\n", options[0]);
    printf("b) %s\n", options[1]);
    printf("c) %s\n", options[2]);
    printf("d) %s\n", options[3]);

    // replace aline answer temporarily
    aline[0] = correctAns;
}

    }
        printf("Enter your answer: ");
        scanf(" %c", &ans);

        if (ans == aline[0]) {        // ans is single character datatype so comparing with first character of aline which is correct answer
            printf("Correct answer!\n");
            score++;
        } else {
            printf("Wrong answer. Correct answer: %c\n", aline[0]);
        }

        // Check for 10-question limit
        if (qCount >= 10) {
            q10();   // ask user continue or exit
        }
    }

    printf("\nNo more questions in file.\n");

    fclose(fq);
    fclose(fa);
}


void q10() {
    char choice[20];

    printf("\n--- 10 Questions Completed ---\n");
    printf("a) Continue the game\n");
    printf("b) Exit\n");
    printf("Enter your choice: ");
    scanf("%s", choice);

    if (strcmp(choice, "a") == 0 || strcmp(choice, "Continue the game") == 0) {
        qCount = 0; // reset counter
        #ifdef _WIN32
        system("cls");
       #else
        system("clear");
        #endif
       
        return;       // continue quiz
    }
    else if (strcmp(choice, "b") == 0 || strcmp(choice, "Exit") == 0) {
        printf("Exiting...\n");
        exit(0);
    }
    else {
        printf("Invalid choice. Continuing by default.\n");
        qCount = 0;
    }
}

void authenticity_check(char username[],char password[]){
    FILE *fu,*fp;

    char storedUser[50];
    char storedPass[50];

    int found =0;

    fu = fopen("user.txt","r");
    fp = fopen("pass.txt","r");

    if(fu == NULL || fp==NULL){
        printf("Error opening file ");
        return;
    }
             // Read both files line by line together
    while(fscanf(fu,"%s",storedUser)!=EOF && fscanf(fp,"%s",storedPass)!=EOF){
        if(strcmp(username,storedUser)==0 && strcmp(password,storedPass)==0){
            found=1;
            break;

        }
    }
    fclose(fu);
    fclose(fp);

    if(found){
        printf("Login successful !\n");
        startMenu();

    }
    else{
        printf("Credentials not found . Either retry or create a new account");
        
    }


}




