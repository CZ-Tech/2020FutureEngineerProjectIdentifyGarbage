// 
// 
// 

#include "myLCD.h"
#include <LiquidCrystal.h>

const int rs = 3, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal mylcd(rs, en, d4, d5, d6, d7);
myLCD::myLCD()
{
	//设置LCD要显示的列数、行数，即2行16列
	mylcd.begin(1, 1);
}

void myLCD::show(int i)
{
	mylcd.setCursor(0, 0);
	mylcd.print(i);
	currentNum = i;
}

void myLCD::clear()
{
	mylcd.clear();
	currentNum = -1;
}
