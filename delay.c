#include "delay.h"

void Delay_1ms_core_plus(unsigned char ix, unsigned char jx, unsigned char kx)	//@11.0592MHz
{
	unsigned char data i, j;
	
	//0.9ms
	_nop_();
	i = 2;
	/**153 - 1 ：补偿函数传参调用开销；
		152 - 1：补偿kx循环将nop前置多出来的两周期；
		151 - 1：补偿IX = 0时，KX循环多运行的2周期*/
	j = 150; 
	do
	{
		while (--j);
	} while (--i);
	
	// ====================================================
	// 动态时序补偿级 (Dynamic Timing Compensation)
	// 每圈严格消耗 4 个机器周期，用于 1:1 动态对冲外层 ix 大循环+jx自减为0时带来的累积误差，
	// 从而在全延时范围内（2ms ~ 65025ms）实现软件指令级“零线性累积误差”。
	// ====================================================
	/** 使用do-while让编译器将while(--k)优化到2周期 */
	do 
	{
		_nop_();
		_nop_();
	} while(--kx);
	
	//ms - 2
	do
	{
		while (--jx)
		{
			_nop_();
			i = 2;
			j = 198;	//199 - 1；补偿外层jx自减不等于0时产生的2周期误差
			do
			{
				while (--j);
			} while (--i);
		}
	} while (--ix);
	
}