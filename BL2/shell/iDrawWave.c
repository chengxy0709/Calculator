#include "shell.h"
#include "stdio.h"
#include "lcd.h"
#include "iCalculate.h"
#include "iMath.h"

double waveData[1024] = {0};
int range_row;
int range_col;

int isPlot(char *str){
	
	char cmd[5] = {'p','l','o','t','\0'};
	char *p = str,*q = cmd;

	while(*p != '\0' && *q != '\0' ){
		if(*p != *q)
			return 0;
		p++;
		q++;
	}
	
	if(*q == '\0')
		return 1;
	else
		return 0;
	
}

int CalculateData(){
	
	int i = 0,j;
	int n,a;
	char *p = CmdStr+5;
	double max = 0;

/***************************************************/
	//get range_row's value
	range_row = 0;
	range_col = 0;
	//ignore space
	while(*p == ' ')
		p++;
	while(*p != ' '){
		if(*p < '0' || *p > '9')
			return 0;
		range_row = range_row*10 + (*p - '0');
		p++;
	}
	//ignore space
	while(*p == ' ')
		p++;
/***************************************************/
	
	a = iCmd2symbol(p,CmdSym);
	if(a == -1){
		printf("Input Error2 !\n");
		return 0 ;
	}
	
	for(i = 0; i < 1024; ++i){
			
		n = str2express(CmdSym, a, express);
		//alter '$' value 
		for( j = 0; j < n; ++j ){
			if( express[j].flag == 5 ){
				express[j].data = (range_row / 1024.0)*(i - 512);
				express[j].flag = 0;
			}
		}
		top1 = -1;
		top2 = -1;	
		infix2postfix( express, n);
		waveData[i] = iCalculatePost();
		printf(".");
		if( iAbs(waveData[i]) > max )
			max = iAbs(waveData[i]);
	}
	printf("\n");
	range_col = (int)(max + 1)*2;
	return 1;
	
}

void DrawWave(){
	
	int i;
	
	Draw_Rect(0,0,1024,600,BLACK);
	
	for(i = 0; i < 1024; ++i ){
		Draw_point(i,(int)(300 - (600 / range_col)*waveData[i]),RED);
	}
	
	Draw_String_8_16(0,0,BLUE,CmdStr);
	Draw_String_8_16(0,16,BLUE,"x'len: ");
	Draw_num_8_16(8*8,16,BLUE,range_row/2);
	Draw_String_8_16(0,32,BLUE,"y'len: ");
	Draw_num_8_16(8*8,32,BLUE,range_col/2);
	
	Draw_Line(0,300,1024,300,GREEN);
	Draw_Line(512,0,512,600,GREEN);
	
}


