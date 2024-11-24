#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//Normal :
#define TAB 9
#define ENTER 13
#define ESC 27
#define BACKSPACE 8



#define EXTENDED -32
#define HOME 71
#define UP 72
#define LEFT 75
#define RIGHT 77
#define END 79
#define DOWN 80
#define DELETE 83




void gotoxy( int, int);
void textattr(int);

void getSize(int* size);
void cleanConsole();
void color_space(int,int);
void resetColorat(int,int);
void resetColor();
void getCursorToStart(int,int);
void moveCursor(int,int);
void print_finaltxt(char*,int,int,int,int,int); //string,number of chars,size of colored area, x of coor_startpoint, y of coor_startpoint
void handleEXETENDEDkeys(char*,char**,int*,int);//string,pointer to curpos pointer,pointer to number of chars,num of chars in a line


int main()
{
    int size =50;
    int lines = 3;
    /* /////////////////////////////////////////////get the size then clean console;
    getSize(&size);
    cleanConsole();
    */
    //size++; //add 1 for null terminator

    char* string;
    string = malloc(size *lines* sizeof(char));
    int chars_count= 0;
    char ch;
    char* currPos;
    currPos = string;

    //positioning variables
    int start_x =30,start_y=3;

    do{
        int curX = (currPos-string)%size +start_x;
        int curline = (currPos-string)/size + start_y;
        print_finaltxt(string,chars_count,size,start_x,start_y,lines);
        moveCursor(curX,curline);
        ch = getch();
        cleanConsole();
        if(ch == EXTENDED){
            handleEXETENDEDkeys(string,&currPos,&chars_count,size);

        }else if(ch == BACKSPACE){
            if(currPos == string){
                printf("There's nothing before cursor to delete");
            }else{
                for(int i=chars_count;i>currPos-string;i--){
                    string[i+1]=string[i];
                }
                chars_count--;
                currPos--;
            }
        }else if(ch!= TAB && chars_count<size*lines-2){
            if(currPos-string < chars_count){
                for(int i=chars_count;i>currPos-string;i--){
                    *(string+i)= *(string+i-1);
                }
                *(currPos)=ch;
                currPos++;
                chars_count++;
            }else{
                *(currPos) = ch;
                currPos++;
                chars_count++;
            }
        }else if (chars_count>= size*lines-2){
            printf("You reached to maximum allowed number of chars \n");
        }

    }while(ch!= TAB);
    cleanConsole();
    printf("your final message is : ");
    print_finaltxt(string,chars_count,size,start_x,start_y,lines);
    resetColorat(0,start_y+lines);


    return 0;
}


void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void textattr(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void getSize(int* size){
    printf("Please enter the legth of your message : ");
    scanf("%d",size);
    printf("\n");
}

void cleanConsole(){
    system("cls");
}

void color_space(int pos_x,int pos_y){
    gotoxy(pos_x,pos_y);
    textattr(0x37);
}

void resetColorat(int x, int y){
    gotoxy(x,y);
    textattr(0x07);
}

void resetColor(){
    textattr(0x07);
}

void getCursorToStart(int x,int y){
    gotoxy(x,y);
}

void moveCursor(int x,int y){
    gotoxy(x,y);
}

/**
* print_finaltxt - function prints the txt design(background color,...)
* @string - our text
* @charsCount - number of chars in our text
* @size - our region size (maximum number of chars allowed)
*
*start point coor :
* @start_x - x value of start point
* @start_y - y value of start point
*/
void print_finaltxt(char* string,int charsCount,int size,int start_x,int start_y,int lines){
    color_space(start_x,start_y);
    int curLine = 0;
        for(int i=0;i<charsCount;i++){
            printf("%c",*(string+i));
            //printf("i = %d , size = %d",i,size);
            if(i%size == 0 && i>0){
                curLine++;
                color_space(start_x,start_y+curLine);
            }
        }
        for(int i = charsCount;i<size*lines;i++){
            printf(" ");
            if(i%(size) == 0 && i>0){
                curLine++;
                color_space(start_x,start_y+curLine);
            }
        }
        //printing empty line
        curLine++;
        moveCursor(start_x,start_y+curLine);
        for(int i = 0;i<size;i++){
            printf(" ");
            if(i%size == 0 && i>0){
                curLine++;
                color_space(start_x,start_y+curLine);
            }
        }
        resetColor();
}
/**
* handling_moves - function that handle left & right cursor moves
* @str: pointer to our text
* @charsCount: number of chars in our text
*
*/
void handleEXETENDEDkeys(char* str,char** curPOs,int* charsCount,int size){
    char ch = getch();
    switch(ch){
        case RIGHT:
            if(*curPOs == str+*charsCount){
                printf("Your cursor is in the end of text already, you can't go right !!!");
                break;
            }
            (*curPOs)++;
            break;
        case LEFT:
             if(*curPOs == str){
                printf("Your cursor is in the start of text already, you can't go left !!!");
                break;
            }
            (*curPOs)--;
            printf(" inside move cursor %c",**curPOs);
            break;
        case DELETE:
            if(*charsCount == 0 || (*(curPOs)-str)==*charsCount){
                printf("No thing behind cursor to delete !!!");
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
                printf("NO lines after that one !!!");
            }
            break;
        case UP:
            if(*curPOs-size > str){
                *curPOs-=size;
            }else{
                printf("NO lines before that one !!!");
            }
            break;

    }
}




