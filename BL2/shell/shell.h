#include "iCalculate.h"

#ifndef _S5PV210IO_H
#define _S5PV210IO_H

#define CMD_MAX_LENGTH 10
#define CMD_MAX_NUMBER 50

extern double result; // calculated result

extern int row;
#define Tab 10

extern char CmdStr[CMD_MAX_LENGTH*CMD_MAX_NUMBER+1]; //cmd string's buffer
extern char CmdSym[CMD_MAX_NUMBER+1]; //buffer that cmd to symbol
extern Data express[CMD_MAX_NUMBER+1]; // buffer that symbol to infix express

int Shell_init( void );
int AnalyCmd(char *cmdstr);
int ExeCmd();
void iDisplay(double num);
int iCheckMatch( char *str );

#endif