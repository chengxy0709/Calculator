/*
    *    filename : iMath.h 
    *    
    *    API : maths method
*/
#ifndef __iMath_H__
#define __iMath_H__

#define PI 3.141592653590
#define E  2.718281828459

//return x's absolute value
#define iAbs(x) (x>0) ? x : (0-x)

//calculate error flag
//ErrorFlag : 0 no error
//ErrorFlag : 1 division error
//ErrorFlag : 2 operator error or value out of range
extern unsigned char ErrorFlag;
#define NOERROR 0
#define DIVERROR 1
#define VALOUTRANGEERROR 2

//double number divided exactly 
//return a double that double x / double y
double doubleMod(double x,double y);

/*****************************trigonometric,function***********************************/

//math method that sin function 
//if flag = 0 ,iSin function will use x without const of pi to calculate
//else if flag = 1,it will use x with const of pi to calculate
//return double number that sin(x)
double iSin(double x,int flag); 

//math method that arcsin function 
//return double number that arcsin(x)
double iArcsin(double x);

//math method that cos function 
//if flag = 0 ,iCos function will use x without const of pi to calculate
//else if flag = 1,it will use x with const of pi to calculate
//return double number that cos(x)
double iCos(double x, int flag);

//math method that arccos function 
//return double number that arccos(x)
double iArccos(double x);

//math method that tan function 
//if flag = 0 ,iTan function will use x without const of pi to calculate
//else if flag = 1,it will use x with const of pi to calculate
//return double number that tan(x)
double iTan(double x, int flag);

//math method that arctan function 
//return double number that arctan(x)
double iArctan(double x );

/**************************trigonometric,function end************************************/

//math method that e^x function 
//return double number that exp(x)
double iExp(double x );

//math method that ln function 
//if flag = 0 ,iLn function will use x without const of e to calculate
//else if flag = 1,it will use x with const of e to calculate
//return double number that ln(x)
double iLn(double x,int flag);


//math method that x^y function 
//return double number that pow(x,n)
double iPowOfInt(double x, int n);		//n must be a integer
double iPowOfDbl(double x, double n);	//n may be a double

//math method that sqrt function 
//return double number that sqrt(x)
double iSqrt(double x);
//math method that curt function 
//return double number that curt(x)
double iSqrt3(double x);

//math method that factorial function 
//return integer number that x!
//x must be a integer
unsigned int iFactorial(unsigned int x);

#endif


