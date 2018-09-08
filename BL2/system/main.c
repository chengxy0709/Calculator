
#include "stdio.h"
#include "led.h"
#include "uart.h"
#include "interrupt.h"
#include "key.h"
#include "lcd.h"
#include "s5pv210io.h"
#include "shell.h"

void main(){
	
	Led_init();
	uart_init();
	Lcd_init();
	Shell_init();
	//key_iinit(ALL);
	//system_init_exception();
	//intenable_init(INT_LEFT);
	//intenable_init(INT_DOWN);
	//intenable_init(INT_ELSE);
	//intSetAdd(INT_LEFT,isr_key_left );
	//intSetAdd(INT_DOWN,isr_key_down );
	//intSetAdd(INT_ELSE,isr_key_else );
    while(1){
		//接收命令
		puts_s("S5PV210#");
		gets_s(CmdStr);
		puts_s("\n");
		//解析命令
		if(AnalyCmd(CmdStr))
			//执行命令
			ExeCmd();
	}
	
	
}
void isr_key_left(void){
	
	printf("LEFT\n");
	int_clearflag(LEFT);
	
}
void isr_key_down(void){
	
	printf("DOWN\n");
	int_clearflag(DOWN);
	
}
void isr_key_else(void){
	
	if( check_int() == UP )
		printf("UP\n");
	else if( check_int() == RIGHT )
		printf("RIGHT\n");
	else if( check_int() == BACK )
		printf("BACK\n");
	else if( check_int() == MENU )
		printf("MENU\n");
	else
		printf("NOKEY\n");
	int_clearflag(ALL);
	
}

int raise(int signum){
	
	return 0;
	
}