#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//Normal keys value :
#define TAB 9
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SAVE 19 //ctrl+s




#define EXTENDED -32
// Extended keys(value of 2nd Byte):
#define HOME 71
#define UP 72
#define LEFT 75
#define RIGHT 77
#define END 79
#define DOWN 80
#define DELETEKEY 83




void gotoxy( int, int);
void textattr(int);

void getSize(int* size);
void cleanConsole();
void color_space(int,int);
void resetColorat(int,int);
void resetColor();
void getCursorToStart(int,int);
void moveCursor(int,int);
void print_finaltxt(char*,int,int,int,int,int);
void handleEXETENDEDkeys(char*,char**,int*,int);
int calculateExtraSpaces(char*,char*,int);

int main()
{

    FILE *file;
    char filename[] = "doc.txt";
    long fileSize;

    file = fopen(filename, "r");
    if (file == NULL) {
        // If the file doesn't exist, create it with default content
        printf("File '%s' does not exist. Creating a new file...\n", filename);


        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error creating file");
            return 1;
        }
        fclose(file);

        // Re-open the file in read mode to proceed
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening newly created file");
            return 1;
        }
    }


    //determine file's size
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);


    long size =500;
    int line_size = 50;


    getSize(&size);

    int lines_num =(size%line_size)?size/line_size+1:size/line_size;

    size +=fileSize;
    char* string;
    string = malloc(size * sizeof(char));
    if (string == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }
    // Read the file content into the allocated memory
    fread(string, sizeof(char), fileSize, file);
    string[fileSize] = '\0';

    int chars_count= fileSize;
    char ch;
    char* currPos;
    currPos = string +fileSize;

    //positioning variables
    int start_x =30,start_y=3;
    int extraSpaces = 0; //appears as result of Enter keys

    do{
        extraSpaces = calculateExtraSpaces(string, currPos, line_size);
        int curX = ((currPos - string + extraSpaces) % line_size) + start_x;
        int curline = ((currPos - string + extraSpaces) / line_size) + start_y;

        print_finaltxt(string,chars_count,line_size,start_x,start_y,lines_num);
        moveCursor(curX, curline);

        ch = getch();
        cleanConsole();

        if(ch == SAVE ){
            file = fopen(filename, "w");
            if (file == NULL) {
                perror("Error opening file for writing");
                free(string);
                return 1;
            }
            fwrite(string, sizeof(char), strlen(string), file);
            fclose(file);
            printf("File updated successfully!\n");
        }else if(ch == EXTENDED){
            handleEXETENDEDkeys(string, &currPos, &chars_count, line_size);
        }else if(ch == BACKSPACE){
            if (currPos > string) {
                for (int i = currPos - string; i < chars_count; i++) {
                    string[i - 1] = string[i];
                }
                chars_count--;
                currPos--;
            } else {
                printf("No characters to delete before the cursor!");
            }
        }else if(ch!= ESC && chars_count<size - 2){
            for (int i = chars_count; i > currPos - string; i--) {
                string[i] = string[i - 1];
            }
            *currPos = ch;
            currPos++;
            chars_count++;
        }else if (chars_count>= size - 2){
            printf("You reached to maximum allowed number of chars \n");
        }
    }while(ch!= ESC);
    cleanConsole();
    printf("your final message is : ");
    print_finaltxt(string, chars_count, line_size, start_x, start_y, lines_num);
    extraSpaces = calculateExtraSpaces(string, currPos, line_size);
    resetColorat(0 ,start_y + (size / line_size) + (extraSpaces / line_size)+3);


    free(string);
    return 0;
}

/**
 * gotoxy - moves the cursor to a specified position in the console.
 * @column: the X-coordinate (horizontal position).
 * @line: the Y-coordinate (vertical position).
 */
void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}


/**
 * textattr - sets the text and background color in the console.
 * @i: attribute value representing the desired colors.
 */
void textattr(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

/**
 * getSize - prompts the user to specify the size of the message.
 * @size: pointer to an integer to store the entered size.
 */
void getSize(int* size){
    printf("Please enter the legth of your message : ");
    scanf("%d",size);
    printf("\n");
}


/**
 * cleanConsole - clears the console screen.
 */
void cleanConsole(){
    system("cls");
}


/**
 * color_space - applies a specific background color to the console at a position.
 * @pos_x: X-coordinate of the position.
 * @pos_y: Y-coordinate of the position.
 */
void color_space(int pos_x,int pos_y){
    gotoxy(pos_x,pos_y);
    textattr(0x70);
}

/**
 * resetColorat - resets the text color at a specific position to the default.
 * @x: X-coordinate.
 * @y: Y-coordinate.
 */
void resetColorat(int x, int y){
    gotoxy(x,y);
    textattr(0x07);
}

/**
 * resetColor - resets the console text color to the default.
 */
void resetColor(){
    textattr(0x07);
}

/**
 * getCursorToStart - moves the cursor to the starting position.
 * @x: X-coordinate of the starting position.
 * @y: Y-coordinate of the starting position.
 */
void getCursorToStart(int x,int y){
    gotoxy(x,y);
}


/**
 * moveCursor - moves the cursor to a specified position.
 * @x: X-coordinate.
 * @y: Y-coordinate.
 */
void moveCursor(int x,int y){
    gotoxy(x,y);
}

/**
 * print_finaltxt - displays the text with formatting (e.g., background color).
 * @string: pointer to the text to display.
 * @charsCount: number of characters in the text.
 * @line_size: maximum number of characters allowed in one line.
 * @start_x: X-coordinate of the starting point.
 * @start_y: Y-coordinate of the starting point.
 * @lines: number of lines for the colored area.
 * =
 */
void print_finaltxt(char* string,int charsCount,int line_size,int start_x,int start_y,int lines){
    color_space(start_x,start_y);
    int curLine = 0;
    int BreaksHandler = 0;
    for(int i=0;i<charsCount;i++,BreaksHandler++){
        if(i == 0 && *string == ENTER){
            moveCursor(start_x,start_y+curLine);
            for(int j = 0;j<line_size;j++,BreaksHandler++){
                printf(" ");
            }
            BreaksHandler--;
        }

        if(BreaksHandler%line_size == 0 && BreaksHandler>0){
            curLine++;
            color_space(start_x,start_y+curLine);
        }
        printf("%c",*(string+ i));

        int temp =BreaksHandler+1;
        while(*(string+i+1) == ENTER){
            while(temp % line_size != 0){
                if(temp == 1){
                    printf("d");
                    BreaksHandler++;
                }
                printf("d");
                BreaksHandler++;
                temp++;
            }
            if(*(string+i+2) == ENTER){ //ensure there is Enter -> otherwise,it will goto newline already
            curLine++;
            color_space(start_x,start_y+curLine);
            }
            i++;
            temp = 1;
        }
    }
    for(;BreaksHandler%line_size !=0 ||(BreaksHandler%line_size ==0  && BreaksHandler < line_size*lines);BreaksHandler++){
        if(BreaksHandler%(line_size) == 0 && BreaksHandler>0){
            curLine++;
            color_space(start_x,start_y+curLine);
        }
        printf(" ");
    }
    //printing empty line
    curLine++;
    moveCursor(start_x,start_y+curLine);
    for(int i = 0;i<line_size;i++){
        printf(" ");
        if(i%line_size == 0 && i>0){
            curLine++;
            color_space(start_x,start_y+curLine);
        }
    }

    resetColor();
}
/**
 * handleEXETENDEDkeys - handles extended keyboard keys (e.g., arrow keys).
 * @str: pointer to the text buffer.
 * @curPOs: pointer to the current cursor position pointer.
 * @charsCount: pointer to the total number of characters.
 * @size: maximum number of characters per line.
 */
void handleEXETENDEDkeys(char* str,char** curPOs,int* charsCount,int size){
    char ch = getch();
    switch(ch){
        case RIGHT:
            if(*curPOs == str+*charsCount){
                printf("Your cursor is already at the end of the text!");
                break;
            }
            (*curPOs)++;
            break;
        case LEFT:
             if(*curPOs == str){
                printf("Your cursor is already at the start of the text!");
                break;
            }
            (*curPOs)--;
            printf(" The cursor point to : %c",**curPOs);
            break;
        case DELETEKEY:
            if(*charsCount == 0 || (*(curPOs)-str)==*charsCount){
                printf("No chars after cursor to delete !!!");
                break;
            }
            for(int i=(*curPOs-str); i<*charsCount-1;i++){
                str[i]=str[i+1];
            }
            (*charsCount)--;
            break;
        case END:
            *curPOs = str+*charsCount;
            break;
        case HOME:
            printf("");
            *curPOs = str;
            break;
        case DOWN:
            if(*curPOs+size < str+*charsCount){
                *curPOs+=size;
            }else{
                printf("No more lines below!");
            }
            break;
        case UP:
            if(*curPOs-size > str){
                *curPOs-=size;
            }else{
                printf("No more lines above!");
            }
            break;

    }
}

int calculateExtraSpaces(char* string, char* curPos, int line_size) {
    int spacesCount = 0, multEnterFlag = 0,EnterCount = 0;;
    for (int i = 0; &string[i] < curPos; i++) {
        if (string[i] == ENTER) {
            EnterCount++;
            if (multEnterFlag == 1) {
                spacesCount += line_size;
            } else {
                if ((i-EnterCount+spacesCount) % line_size != 0) {
                    spacesCount += line_size - ((i-EnterCount+spacesCount) % line_size);
                }
            }
            multEnterFlag = 1;
        } else {
            multEnterFlag = 0;
        }
    }
    return (EnterCount)?spacesCount-EnterCount-1:0;
}




