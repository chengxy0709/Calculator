/*
 *    Filename : iCalculate.h
 *
 *    Description : including some methods of dealing with the string of infix expression
 *                          and calculating these expression.
*/
#ifndef __iCALCULATE_H__
#define __iCALCULATE_H__

//(0-9)'s number of sequence
#define iN0 0
#define iN1 1
#define iN2 2
#define iN3 3
#define iN4 4
#define iN5 5
#define iN6 6
#define iN7 7
#define iN8 8
#define iN9 9
#define iNend 10
//unique symbol's number of sequence
#define iUpoint  11
#define iUe        12
#define iUpi       13
#define iUans    14
#define iUalt    15
#define iUend    16
//control symbol's number of sequence
#define iCleft    17
#define iCright  17
#define iCdown 18
#define iCup      19
#define iCclear  20
#define iCdel     21
#define iCend    22
//operate of two eyes symbol's number of sequence
#define iO1add  23
#define iO1sub  24
#define iO1div  25
#define iO1mul   26
#define iO1xd    27
#define iO1xf     28
#define iO1end  29
//operate of one eyes symbol's number of sequence
#define iO2sin  30
#define iO2cos  31
#define iO2tan  32
#define iO2arcsin   33
#define iO2arccos  34
#define iO2arctan  35
#define iO2ex  36
#define iO2ln  37
#define iO2sqrt   38
#define iO2sqrt3  39
#define iO2fac  40
#define iO2end    41
//unique operate symbol's number of sequence
#define iO3lb  42
#define iO3rb  43
#define iO3end 44

//operator's data structure
typedef struct Data{
    double data;
    unsigned char flag;
}Data;
 
//Double stack method
//operator's stack
#define MAXSIZE 20
extern Data stack1[MAXSIZE];
extern int top1;
extern Data stack2[MAXSIZE];
extern int top2;
 
//return a rank of priority of operator
unsigned char rePriRank(unsigned char op);
//the infix's array will be changed to become postfix's array by the function 
void infix2postfix(Data *express, int n);

//calculate the postfix's value
double iCalculatePost();

//method of operator
double iOperate(double a,double b, unsigned char op, unsigned char flag);
//calculate two operator by op
void iDealNum(Data a, Data b,unsigned char op, double *c, unsigned char *flag);

//transform input string to operator's data
int str2express(char *s, int n, Data *express);

#endif

