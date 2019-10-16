// 
// 
// 

#include "myLCD.h"
#include <LiquidCrystal.h>

const int rs = 3, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
myLCD::myLCD()
{
	//设置LCD要显示的列数、行数，即2行16列
	lcd.begin(1, 1);
}

void myLCD::show(int i)
{
	lcd.setCursor(0, 0);
	lcd.print(i);
	currentNum = i;
}

void myLCD::clear()
{
	lcd.clear();
	currentNum = -1;
}
