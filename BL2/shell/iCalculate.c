#include "iCalculate.h"
#include "iMath.h"
#include "shell.h"
#include "stdio.h"

Data stack1[MAXSIZE];
int top1 = -1;
Data stack2[MAXSIZE];
int top2 = -1;

unsigned char rePriRank(unsigned char op){
    
    if(op > iCend && op <= iO1sub)
        return 1;
    else if(op > iO1sub && op <= iO1mul)
        return 2;
    else if(op > iO1mul && op <= iO2end)
        return 3;
    else
        return 0;
    
}

void infix2postfix(Data *express, int n){
    
    Data *p = express;
    int i = 0;
    
    for(i = 0; i < n ; ++i){
        //p[i] is number or const
        if(p[i].flag == 0 || p[i].flag == 2 || p[i].flag == 3){
            stack1[++top1].data = p[i].data;
            stack1[top1].flag = p[i].flag;
        }
        //p[i] is operation
        else{
            //if op is '(' or the stack2 is empty, begin to push.
            if(p[i].data == iO3lb || top2 == -1){
                stack2[++top2].data = p[i].data;
                stack2[top2].flag = p[i].flag;
            }
			//if op is method function , begin to push.
			else if( (unsigned char)p[i].data > iO1end && (unsigned char)p[i].data < iO2end ){
				stack2[++top2].data = p[i].data;
                stack2[top2].flag = p[i].flag;
			}
            //if priority of element that will push is higher than the top of stack, just push.
            else if(top2 > -1 && (rePriRank((unsigned char)p[i].data) > rePriRank((unsigned char)stack2[top2].data))){
                stack2[++top2].data = p[i].data;
                stack2[top2].flag = p[i].flag;
            }
			
			//if op is ')' , begin to pop until op is stack2[top2].data = '('.
            else if(p[i].data == iO3rb){
                while(stack2[top2].data != iO3lb){
                    stack1[++top1].data = stack2[top2].data;
                    stack1[top1].flag = stack2[top2--].flag;
                }
                top2--;
            }
            else{
                while(top2 > -1 && (rePriRank((unsigned char)p[i].data) <= rePriRank((unsigned      \
                            char)stack2[top2].data))){
                    stack1[++top1].data = stack2[top2].data;
                    stack1[top1].flag = stack2[top2--].flag;
                }
                stack2[++top2].data = p[i].data;
                stack2[top2].flag = p[i].flag;
            }
        }    
    }
	
    while(top2 > -1){
        stack1[++top1].data = stack2[top2].data;
        stack1[top1].flag = stack2[top2--].flag;
    }
    
}

double iCalculatePost(){
    
    int i = 0;
	Data a,b;
    double c;
    unsigned char f;
	
	ErrorFlag = 0;
    for(i = 0; i <= top1; ++i){
        if(stack1[i].flag == 0 || stack1[i].flag == 2 || stack1[i].flag == 3){
            stack2[++top2].data = stack1[i].data;
            stack2[top2].flag = stack1[i].flag;
        }
        else{
            if(stack1[i].data > iO1end && stack1[i].data < iO2end ){
                a.data = stack2[top2].data;
				a.flag = stack2[top2--].flag;	
				b.data = 0;
				b.flag = 0;
				iDealNum(a, b, stack1[i].data, &c, &f);
            }
            else{
                a.data = stack2[top2].data;
                a.flag = stack2[top2--].flag;
                b.data = stack2[top2].data;
                b.flag = stack2[top2--].flag;
				iDealNum(b, a, stack1[i].data, &c, &f);
            }
            stack2[++top2].data = c;
            stack2[top2].flag = f;   
        }
    }
	
    if(stack2[top2].flag == 2) return stack2[top2].data * PI;
	else if(stack2[top2].flag == 3) return stack2[top2].data * E; 
	else return stack2[top2].data; 

}

double iOperate(double a,double b, unsigned char op, unsigned char flag){

    if(op > iCend && op <= iO1mul)
        switch(op){
            case iO1add : return (a+b);
            case iO1sub : return (a-b);
            case iO1mul : return (a*b);
            case iO1div : {
				if(b == 0){
					ErrorFlag = DIVERROR;
					return 0;
				}
				return (a/b/1.0);
			}
		}
    else{
        switch(op){
            case iO1xd : return iPowOfInt(a, (int)b);
            case iO1xf : return iPowOfDbl(a, b);
            case iO2sin : return iSin(a, flag);
            case iO2cos : return iCos(a, flag);
            case iO2tan : return iTan(a, flag);
            case iO2arcsin : return iArcsin(a);
            case iO2arccos : return iArccos(a);
            case iO2arctan : return iArctan(a);
            case iO2ex : return iExp(a);
            case iO2ln : return iLn(a, flag);
            case iO2sqrt : return iSqrt(a);
            case iO2sqrt3 : return iSqrt3(a);
            case iO2fac : return iFactorial((unsigned int)a);
        }
    }
   
}

void iDealNum(Data a, Data b,unsigned char op, double *c, unsigned char *flag){
    
    //normal number
    if(a.flag == 0 && b.flag == 0){
        //two operator
        if(op > iCend && op < iO1end){
            //if x^n's n is a interger, use the function that pow for int
            if(op == iO1xf && (b.data - (int)b.data) == 0)
                *c = iOperate(a.data,(int)b.data, iO1xd, 0);
            else
                *c = iOperate(a.data,b.data,op, 0);
        }
        //one operator
        else{
            *c = iOperate(a.data,0,op, 0);
        }
        *flag = 0;
    }
    //a is unique number and b is normal number
    else if(a.flag != 0 && b.flag == 0){
           if(op > iCend && op < iO1end){
               if(op == iO1mul || op == iO1div){
                   *c = iOperate(a.data , b.data, op, 0);
                   *flag = a.flag;
               }
               else{
                   if(a.flag == 2)
                       *c = iOperate(a.data * PI , b.data, op, 0);
                   else
                       *c = iOperate(a.data * E , b.data, op, 0);
                   *flag = 0;
               }
           }
           else{
               if(a.flag == 2 && (op >= iO2sin && op <= iO2tan))
                   *c = iOperate(a.data, 0, op, 1);    
               else if(a.flag == 3 && op == iO2ln)
                   *c = iOperate(a.data,0,op,1);
               else{
                   if(a.flag == 2)
                       *c = iOperate(a.data * PI , 0, op, 0);
                   else
                       *c = iOperate(a.data * E , 0, op, 0);
               }
               *flag = 0;
           }
    }
	//a is normal number and b is unique number
    else if(a.flag == 0 && b.flag != 0){
        if(op > iCend && op < iO1end){
           if(op == iO1mul || op == iO1div){
               *c = iOperate(a.data , b.data, op, 0);
               *flag = b.flag;
           }
           else{
                   if(b.flag == 2)
                       *c = iOperate(a.data , b.data * PI, op, 0);
                   else
                       *c = iOperate(a.data , b.data * E, op, 0);
                   *flag = 0;
           }
       }
    }
	//a is unique number and b is unique number
    else{
        if(op > iCend && op < iO1end){
           if((op == iO1add || op == iO1sub) && a.flag == b.flag){
               *c = iOperate(a.data , b.data, op, 0);
               *flag = a.flag;
           }
           else{
               if(a.flag == 2 && b.flag == 3)
                   *c = iOperate(a.data * PI , b.data * E, op, 0);
               else
                   *c = iOperate(a.data * E , b.data * PI, op, 0);
               *flag = 0;
           }
       }
       else{
               if(a.flag == 2 && (op >= iO2sin || op <= iO2tan))
                   *c = iOperate(a.data, 0, op, 1);    
               else if(a.flag == 3 && op == iO2ln)
                   *c = iOperate(a.data,0,op,1);
               else{
                   if(a.flag == 2)
                       *c = iOperate(a.data * PI , 0, op, 0);
                   else
                       *c = iOperate(a.data * E , 0, op, 0);
               }
               *flag = 0;
       }
    }
    
}

int str2express(char *s, int n, Data *express){
    char f = 0;
    int i,k;
    double a,t;
    for(i = 0,k = 0; i < n; ++k){
        a = 0;
        t = 0.1;
        f = 0;
		//transform series of number to a number
        if( s[i] >= iN0 && s[i] < iNend ){
            while(i < n && s[i] >= iN0 && s[i] < iNend){
                if(f == 0)
                    a = a * 10 + s[i];
                else{
                    a = a + t * s[i];
                    t = t * 0.1;
                }
                ++i;
                if(s[i] == iUpoint){
                    ++i;
                    f = 1;
                }
            }
            express[k].data = a;
            express[k].flag = 0;
        }
        else if( s[i] == iUpi ){
            express[k].data = 1;
            express[k].flag = 2;
            ++i;
        }
        else if( s[i] == iUe ){
            express[k].data = 1;
            express[k].flag = 3;
            ++i;
        }
		else if( s[i] == iUans ){
            express[k].data = result;
            express[k].flag = 0;
            ++i;
        }
		else if( s[i] == iUalt ){
            express[k].data = 0;
            express[k].flag = 5;
            ++i;
        }
        else if(s[i] > iCend && s[i] < iO3end){
            express[k].data = s[i];
            express[k].flag = 1;
            ++i;
        }
    }
	return k;
}


