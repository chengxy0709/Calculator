#include "iMath.h"

//After define, some function may enhance their computational,accuracy, 
//but computational efficiency will become lower
#define SUPEREXP

unsigned char ErrorFlag = 0 ;

//a double number be divided exactly by another double number
double doubleMod(double x,double y){
    char flag = 0;
    
	//record x's sign
    if(x>0) flag = 0;
    else flag = 1;
    
    x = iAbs(x);
    while( x >= y ){
        x = x - y;
    }
    
	//add x's sign
    if(!flag) return x;
    else return (0-x);
}

//sin(x) = x - (x^3)/3! + (x^5)/5! .....
double iSin(double x,int flag){
    
    double p = x; //molecule
    double q = 1.0; //denominator
    double result = 0;
    int i = 1;
    
    //calculate with PI
    if(flag != 0){
        x = doubleMod(x,2);
		//judge x whether is a unique value
        if(x == 0 || x == -1 || x == 1)
            return 0;
        else if(x == 0.5 || x == -1.5)
            return 1;
        else if(x == 1.5 || x == -0.5)
            return -1;
		//alter x with x * PI
        else{
            p = x * PI;
            x = p;
        }
    }
	//calculate without PI
    else{
        x = doubleMod(x,2*PI);
        p = x;
    }
    //taylor expansion
    for(i = 1; i < 11; ++i){
        result = result + (p / q);
        p = p * x * x;
        q = 0 - q * (2 * i + 1) * (2 * i);
    }
    
    return result;
        
} 

//arcsin(x) = x+1/6*x^3+3/40*x^5+5/112*x^7+35/1152*x^9
double iArcsin(double x){
    
    double p = x; //molecule
    double q[5]; //denominator
    double result = 0;
    int i = 1;
    
	//judge x whether is in domain of definition
    if(x > 1 || x < -1){
        ErrorFlag = VALOUTRANGEERROR;
        return 0;
    }
	//judge x whether is a unique value
    else if( x == -1 )
        return -90;
    else if( x == 1)
        return 90;
    else if(x == 0)
        return 0;
    else if(x == 0.5)
        return 30;
    else if(x == -0.5)
        return -30;
    
	//taylor coefficient
    q[0] = 1.0;q[1] = 1.0 / 6;q[2] = 3.0 / 40;
    q[3] = 5.0 / 112;q[4] = 35.0 / 1152;
	//taylor expansion
    for(i = 0; i < 5; ++i){
        result = result + (p * q[i]);
        p = p * x * x;
    }
    
	//return angle result
    return (result / (2 * PI)) * 360;
        
} 


#ifndef SUPEREXP
	//transform iCos to iSin
    double iCos(double x, int flag){
    
        if(flag != 0)
            return iSin(x+0.5, flag);
        else
            return iSin(x+PI/2, flag);
    
    }
#else 
    //cos(x) = 1 - (x^2)/2! + (x^4)/4! .....
    double iCos(double x, int flag){
    
        double p = 1.0; //molecule
        double q = 1.0; //denominator
        double result = 0;
        int i = 1;
    
        //calculate with PI
        if(flag != 0){
            x = doubleMod(x,2);
			//judge x whether is a unique value
            if(x == 0.5 || x == 1.5 || x == -0.5 || x == -1.5 )
                return 0;
            else if(x == 0)
                return 1;
            else if(x == -1 || x == 1)
                return -1;
			//alter x with x * PI
            else{
                p = 1.0;
                x = x * PI;
            }
        }
		//calculate without PI
        else{
            x = doubleMod(x,2*PI);
            p = 1.0;
        }
		//taylor expansion
        for(i = 1; i < 11; ++i){
            result = result + (p / q);
            p = p * x * x;
            q = 0 - q * (2 * i ) * (2 * i - 1);
        }
    
        return result;
    
    }
#endif

//arccos（x）＝1/2*pi-x-1/6*x^3-3/40*x^5-5/112*x^7-35/1152*x^9
double iArccos(double x){
    
    double p = x; //molecule
    double q[5]; //denominator
    double result = 0;
    int i = 1;
    
	//judge x whether is in domain of definition
    if(x > 1 || x < -1){
        ErrorFlag = VALOUTRANGEERROR;
        return 0;
    }
	//judge x whether is a unique value
    else if( x == -1 )
        return 180;
    else if( x == 1)
        return 0;
    else if(x == 0)
        return 90;
    else if(x == 0.5)
        return 60;
    else if(x == -0.5)
        return 120;
    
	//taylor coefficient
    q[0] = 1.0;q[1] = 1.0 / 6;q[2] = 3.0 / 40;
    q[3] = 5.0 / 112;q[4] = 35.0 / 1152;
	//taylor expansion
    for(i = 0; i < 5; ++i){
        result = result + (p * q[i]);
        p = p * x * x;
    }
    
	//return angle result
    return ((0.5*PI-result) / (2 * PI)) * 360;
        
}  

//transform iTan to iSin/iCos
double iTan(double x, int flag){
    
        double a = iSin(x, flag);
        double b = iCos(x, flag);

		//judge denominator whether is zero
        if(b == 0){
            ErrorFlag = 1;
            return 0;
        }
        else
            return a / b;
    
}

//arctan(x) = x-1/3*x^3+1/5*x^5-1/7*x^7+1/9*x^9+ ....
double iArctan(double x ){
    
    double p = 0 - PI / 2;
    double q = PI / 2;
    double r = (p+q) / 2.0;
    int num = 30;
    double t = 0;
    
	if(x == 1)
		return 45;
	if(x == -1)
		return -45;
	
    while(t != x && num--){
        r = (p + q) / 2.0;
        t = iTan(r,0);
        if(t > x) q = r;
        else p = r;
    }
    
	//return angle result
    return (r / (2 * PI)) * 360;
    
}

//e^x = 1 + x + (x^2)/2! + ....
double iExp(double x ){
    
    double p = x;
    double q = 1.0;
    double result = 0;
    int i;
    
	if(x > 5) return (iExp(x - 5)*iExp(5));
	if(x < -5) return (iExp(x + 5)*iExp(-5));
	
    for(i = 1; i < 30; ++i){
        result = result + (p / q);
        p = p * x;
        q = q * (i + 1);
    }
    return (1+result);
       
}

//ln(1 + x) = x - x^2/2 + x^3/3 ......
double iLn(double x,int flag){
    
    double p = x;
    double q = 1.0;
    double result = 0;
    double t = 1;
    int i;
    
	if(flag == 1)
		if(x == 1) return 1;
		else x = E * x;
	
	
    if( x <= 0 ){
        ErrorFlag = VALOUTRANGEERROR;
        return 0;
    }
    else if(x <= 1.5 && x >= 0.5){
        x = x - 1;
        p = x;
    }
	else if(x > 1.5)
		return (iLn(x / 1.5, 0) + iLn(1.5 , 0));
    else{
        return (0 - iLn(1 / x , 0));
    }

    for(i = 1; i < 30; ++i){
        result = result + (p / q) * t;
        p = p * x;
        q = (q + 1);
        t = t * (-1);
    }
    return result;
    
}

//x^y = e^( ln(x) * y )
double iPowOfDbl(double x, double n) {
    
	if(n < 1 && n > -1 && x < 0){
		ErrorFlag = VALOUTRANGEERROR;
        return 0;
	}
	    
    return iExp( n * iLn(x,0) );
    
}

double iPowOfInt(double x, int n) {
    double y = 1;
    int z = iAbs(n);
    if(n == 0 || x == 1)
        return 1;
    if(x == -1 && n % 2 == 0)
        return 1;
    else if(x == -1 && n % 2 != 0)
        return -1;
	//if n is too big
    if(n >= 100 || n <= -100){
        ErrorFlag = VALOUTRANGEERROR;
        return 0;
    }
    while(z > 1){
        if(z % 2 != 0){
             y = y * x;
             z++;  
        }
        else{
             x = x * x;
             z = z / 2;
        }
    }
    if(n > 0)
        return x/y;
    else
        return 1.0/(x/y);           
}

double iSqrt(double x){
    
    double result;
    
    if(x < 0){
        ErrorFlag = VALOUTRANGEERROR;
        return 0;
    }
    
	result = iPowOfDbl(x, 0.5);
    
	if(result - (int)result < 0.000001)
		return (int)result;
	else
		return	result;
	
}

double iSqrt3(double x){
    
    int flag = (x >= 0)?0:1;
    double result;
    
    x = iAbs(x);
	result = iPowOfDbl(x, 1.0/3);
	
	if(result - (int)result < 0.000001)
		if(flag) return 0 - (int)result;
		else return (int)result;
	else
		if(flag) return 0 - result;
		else return result;
    
}

unsigned int iFactorial(unsigned int x){
    
    unsigned int result = 1;
    while(x>0){
        result = result * x;
        --x;
    }
    return result;
    
}

//iMath file endl

