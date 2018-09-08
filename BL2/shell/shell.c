#include "shell.h"
#include "stdio.h"
#include "lcd.h"
#include "iCalculate.h"
#include "iMath.h"
#include "iDrawWave.h"

char CmdStr[CMD_MAX_LENGTH*CMD_MAX_NUMBER+1]={0};
char CmdSym[CMD_MAX_NUMBER+1]={0};
Data express[CMD_MAX_NUMBER+1];
#define CMDNUM 14
const char iCmd[CMDNUM][CMD_MAX_LENGTH] = {"e","pi","ans","sin","cos","tan","arcsin","arccos","arctan","exp","ln","sqrt","curt","fac"};

const char helpText[] = {"-------------instructions--------------\n\
\tThe shell serves as calculator.\n\
Usage : \n\
\tsin function : sin [argument]\n\
\tcos function : cos [argument]\n\
\ttan function : tan [argument]\n\
\tarcsin function : arcsin [argument]\n\
\tarccos function : arccos [argument]\n\
\tarctan function : arctan [argument]\n\
\texp function : exp [argument]\n\
\tln function : ln [argument]\n\
\tsqrt function : sqrt [argument]\n\
\tcurt function : curt [argument]\n\
\tfactorial function : fac [argument]\n\n\
Someelse operation:\n\
\t + : [op1] + [op2]\n\
\t / : [op1] / [op2]\n\
\t - : [op1] - [op2]\n\
\t * : [op1] * [op2]\n\
\t ^ : [op1] ^ [op2]\n\n\
Some const:\n\
\tPi : pi\n\
\tThe base of the natural log : e\n\
\tThe result that last calculated : ans\n\n\
There are some examples as follows.\n\
\teg1 : sin 1 + 2.25 / 3\n\
\teg2 : 1 + sin ( pi / 2 ) * 2 - 2\n\
\teg3 : sin cos fac 2 + 2\n\n\
Note : The expression should be composed by these\n \
      that operators are Separated by spaces.\n\
-----------------------------\n\n\
"};

double result = 0;

int showflag;
//0: express
//1: wave
int row;

int iStrcmp(const char *str1,const char *str2){
     
     char *p = str1;
     char *q = str2;
     
     while(*p && *q){
         if(*p != *q) return 0;
         ++p;
         ++q;
     }
     if(*p == '\0' && *q == '\0') return 1;
     else return 0;
     
 }
 
static int strcpy_s(char *str1,char *str2){
	
	volatile char *pstr1 = str1;
	volatile char *pstr2 = str2;
	
	while( *pstr1 ){
		*pstr2 = *pstr1;
		pstr1++;
		pstr2++;
	}
	*pstr2 = '\0';
	return 1;
	
}

int iCmd2symbol(char *cmdstr, char *symbolstr){
     
     char *text = cmdstr;
     char tempstr[10] = {0};
     int i = 0,count = 0;
     
     while(*text){
         if(*text == ' '){
             ++text;
             continue;
         }
         if(*text >= '0' && *text <= '9')
             *symbolstr = *text - '0';
         else if(*text == '.')
             *symbolstr = iUpoint;
         else if(*text == '+')
             *symbolstr = iO1add;
         else if(*text == '-')
             *symbolstr = iO1sub;
         else if(*text == '*')
             *symbolstr = iO1mul;
         else if(*text == '/')
             *symbolstr = iO1div;
         else if(*text == '^')
             *symbolstr = iO1xf;
         else if(*text == '(')
             *symbolstr = iO3lb;
         else if(*text == ')')
             *symbolstr = iO3rb;
		 else if(*text == '$')
             *symbolstr = iUalt;
         else{
             i = 0;
             while(*text >= 'a' && *text <= 'z'){
                 tempstr[i] = *text;
                 ++i;
                 ++text;
                 if(i >= 9) return -1;
             }
             tempstr[i] = '\0';    
			 //printf("%s\n",tempstr);
             for(i = 0; i < CMDNUM; ++i){
                 if(iStrcmp(iCmd[i],tempstr))
                     break;
             }
             if(i >= CMDNUM) 
                 return -1;
             else{
				 if(i == 0) *symbolstr = iUe;
                 else if(i == 1) *symbolstr = iUpi;
                 else if(i == 2) *symbolstr = iUans;
                 else *symbolstr = iO2sin + i - 3;
             }
			 --text;
         }
         if(*text) ++text;
         ++symbolstr;
         ++count;
     }
     
     return count;
     
}

static int CleanArray(char *array ,int length){
	
	char *parray = array;
	
	while(length--){
		*parray = 0;
		parray++;
	}
	
}

static int Str2Num(char *str){
	
	int num=0;
	
	while(*str){
		num = num*10 + (*str-'0');
		str++;
	}
	
	return num;
	
}

int Shell_init( void ){
	
	int i = 0;
	
	CleanArray(CmdStr ,CMD_MAX_LENGTH*CMD_MAX_NUMBER+1);
	CleanArray(CmdSym ,CMD_MAX_NUMBER+1);
	
	for(i = 0; i < CMD_MAX_NUMBER+1; ++i){
		express[i].data = 0;
		express[i].flag = 0;
	}
	
	puts_s("\nCalculator's shell\n");
	
	row = 0;
	ErrorFlag = 0;
	result = 0;
	showflag = 0;
	
}
int AnalyCmd(char *cmdstr){
	
	int a,n,i;
	
	if( ! iCheckMatch( CmdStr )){
		printf("Input Error1 !\n");
		return 0;
	}
	if( iStrcmp( CmdStr,"help") ){
		printf(helpText);
		return 0;
	}
	if(isPlot(cmdstr)){
		if(CalculateData()){
			DrawWave();
			showflag = 1;
		}
		return 0;
	}
	a = iCmd2symbol(CmdStr,CmdSym);
    if(a == -1){
		printf("Input Error2 !\n");
		return 0 ;
	}
	else{
		/*for(i = 0; i < a; ++i){
			printf("%d\n",CmdSym[i]);
		}*/
		top1 = -1;
		top2 = -1;	
		n = str2express(CmdSym, a, express);
		infix2postfix( express, n);			
	}
	
	return 1;
	
}

int iCheckMatch( char *str ){
    
    char stack[20] = {0};
    int top = -1;
    
    while(*str){
        if(*str == '(' )
            stack[++top] = *str;
        else if(*str == ')')
            --top;
        ++str;
    }    
    
    if(top == -1) return 1;
    else return 0;

}

void iDisplay(double num){
    
    char disint[15] = {0};
    char disfloat[10] = {0};
    int integer;
    int i,j,col,flag;
    char temp;
	
	
	if(num < 0){
		flag = 1;
		num = iAbs(num);
	}else
		flag = 0;
	
	col = 0;
	integer = (int)num;
    num = num - (int)num;
	num = num + 0.0000000001;
	
    for(i = 0; integer > 0 ; ++i){
        disint[i] = integer % 10 + '0';
        integer = integer / 10;
    }
	col = i;
    disint[i] = '\0';
    for(j = 0; j < i/2; ++j){
        temp = disint[i - j - 1];
        disint[i - j - 1] = disint[j];
        disint[j] = temp;
    }
    for(i = 0; i < 9 ; ++i){
        disfloat[i] = (int)(num * 10) + '0';
        num = (num * 10) - (int)(num * 10);
    }
    disfloat[i] = '\0';
    for(i = i - 1; i >= 0 ; --i){
        if(disfloat[i] == '0')
            disfloat[i] = '\0';
        else
            break;
    }
	/********************display*********************/
	if( row == 0 )
		Draw_Rect(0,560,10,600,BLACK);
	else
		Draw_Rect(0,row - 40,10,row,BLACK);
	Draw_Rect(0,row,10,row + 40,WHITE);
	Draw_Rect(10,row,1024,row + 40,BLACK);
	
	Draw_String_8_16(Tab+0,row,GREEN,CmdStr);
	row += 20;
	
	if(flag){
		Draw_String_8_16(Tab+0,row,BLUE,"-");
		col += 1;
	}
	
	if(disint[0] != '\0')
		Draw_String_8_16(Tab+flag*8,row,BLUE,disint);
	else{
		Draw_String_8_16(Tab+flag*8,row,BLUE,"0");
		col += 1;
	}
    if(disfloat[0] != '\0'){
		Draw_String_8_16(Tab+col*8,row,BLUE,".");
		Draw_String_8_16(Tab+(col+1)*8,row,BLUE,disfloat);
	}
    row += 20;
	if(row >= 600)
		row = 0;
	/****************end display*********************/
}


int ExeCmd(){
	
	printf("calculating\n");
	result = iCalculatePost();
	if(ErrorFlag == 0){
		printf("\n---------------------\n");
		if(showflag == 1){
			row = 0;
			showflag = 0;
			Draw_Rect(0,0,1024,600,BLACK);
		}
		iDisplay(result);
	}
	else if(ErrorFlag == 1){
		printf("\n-------DIVERROR-------\n");
	}
	else if(ErrorFlag == 2){
		printf("\n---VALOUTRANGEERROR---\n");
	}
	
	return 1;
	
}