#ifndef MY_MATH_H__
#define MY_MATH_H__

#include "defs.h"

#ifndef KEIL_5

//============================变长参数宏==================================
#define GET_ARGS_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_ARGS(...) (GET_ARGS_COUNT(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#endif
/**==========表达式类型(E_)==============*/

#define GT(A, B) ((A) > (B))
#define LT(A, B) ((A) < (B))
#define EQ(A, B) ((A) == (B))

#define GE(A, B) ((A) >= (B))
#define LE(A, B) ((A) <= (B))
#define NE(A, B) ((A) != (B))

//三目运算符
#define COND(C, T, F) ((C) ? (T) : (F))

#define CMP(A, B) (LT(A, B) ? -1 : (EQ(A, B) ? 0 : 1))

#define NOT_L(A) (!(A))

#define AND_L(A, B) ((A) && (B))

#define OR_L(A, B) ((A) || (B))

#define XOR_L(A, B) NE(NOT_L(A), NOT_L(B))

#define IN_RANGE(VAL, MIN_VAL, MAX_VAL) AND_L(GE(VAL, MIN_VAL), LE(VAL, MAX_VAL))

//检查位状态
#define CHK_BIT(X, N) (AND(SHR(X, N), 1))


//=========位运算符========

#define NOT(N) (~(N))

#define AND(A, B) ((A) & (B))

#define OR(A, B) ((A) | (B))

#define XOR(A, B) ((A) ^ (B))

#define SHL(X, N) ((X) << (N))

#define SHR(X, N) ((X) >> (N))

#define _B(N)					(1 << (N))

//X第N位置1
#define SET_BIT(X, N)	(OR(X, SHL(1, N)))

//X第N位置0
#define CLR_BIT(X, N) (AND(X, NOT(SHL(1, N))))

//X第N位反转
#define TOG_BIT(X, N) (XOR(X, SHL(1, N)))

//=============BIT 批处理==========
// 置位 (任意N位置 1)
#define SET_BITS3(X, N1, N2, N3)         ((X) |= MASK3(N1, N2, N3))
#define SET_BITS4(X, N1, N2, N3, N4)     ((X) |= MASK4(N1, N2, N3, N4))

// 清零 (任意几个位置 0)
#define CLEAR_BITS3(X, N1, N2, N3)       ((X) &= ~MASK3(N1, N2, N3))
#define CLEAR_BITS4(X, N1, N2, N3, N4)   ((X) &= ~MASK4(N1, N2, N3, N4))

// 取反 (任意几个位状态翻转)
#define TOGGLE_BITS3(X, N1, N2, N3)      ((X) ^= MASK3(N1, N2, N3))
#define TOGGLE_BITS4(X, N1, N2, N3, N4)  ((X) ^= MASK4(N1, N2, N3, N4))

//============TYPE BIT 宏================
#define SET_BITS(B1, B2) (BITP(B1), BITV(B2))


//=========通用运算符========

#define MAX(A, B) (GT(A, B) ? (A) : (B))
#define MAX3(A, B, C) R3_(MAX, A, B, C)

#define MIN(A, B) (LT(A, B) ? (A) : (B))
#define MIN3(A, B, C) R3_(MIN, A, B, C)

#define ADD(A, B) ((A) + (B))
#define ADD3(A, B, C) R3_(ADD, A, B, C)

#define SUB(A, B) ((A) - (B))
#define SUB3(A, B, C) R3_(SUB, A, B, C)

#define DIFF(A, B) (GT(A, B) ? SUB(A, B) : SUB(B, A))

#define SAT_SUB(A, B) (GE(A, B) ? SUB(A, B) : 0)

#define MUL(A, B) ((A) * (B))
#define MUL3(A, B, C) R3_(MUL, A, B, C)

#define DIV(A, B) ((A) / (B))
#define DIV3(A, B, C) R3_(DIV, A, B, C)

#define DIV_ROUND_UP(A, B) (DIV(SUB(ADD(A, B), 1), B))

#define REM(A, B) ((A) % (B))

#define MOD(A, B) (REM(ADD(REM(A, B), B), B))

#define MUL_DIV(A, B, C) DIV(MUL(A,B),C)

#define MID(A, B, C) (MIN(MAX((A), (B)), MAX(MIN((A), (B)), (C))))


#define CLAMP(VAL, MIN_VAL, MAX_VAL) (MIN(MAX(MIN_VAL, VAL), MAX_VAL))

#define ARRAY_SIZE(ARR) DIV(sizeof(ARR), sizeof(ARR[0]))
	
#ifndef TICK_RATE
#define TICK_RATE(X, T) SUB(DIV(ADD(X, T), T), 1)
#endif


//=============================TYPE UNIT 宏===============================
//获得值
#define GET_NUNIT(X)				XGLUB(V_, X)

//获得单位名字
#define GET_UNIT_NAME(X) 		XGLUB(U_, X)

//从单位名字获得单位大小
#define UN_V(U_NAME) 				XGLUB(_, U_NAME)

//获得单位大小
#define GET_UNIT_DEF(X) 		XGLUB(_, XGLUB(U_, X))
	
//将单位A转为单位B
#define TRANS_UNIT(X, UB_NAME) \
	UB_NAME( \
		COND(GE(GET_UNIT_DEF(X),  UN_V(UB_NAME)), \
						MUL(GET_NUNIT(X), DIV(GET_UNIT_DEF(X), UN_V(UB_NAME))), \
						DIV(GET_NUNIT(X), DIV(UN_V(UB_NAME), GET_UNIT_DEF(X)))	\
		) \
	)

//X的单位转换为较小的那个
#define TRANS_UNIT_MIN(X, UN2)	\
	XGLUB(GET_UNIT_NAME(X), XGLUB(_, XGLUB(UN2, _MIN))) (\
		MUL(GET_NUNIT(X), COND(LE(GET_UNIT_DEF(X), UN_V(UN2)), 1UL, DIV(GET_UNIT_DEF(X), UN_V(UN2)))) \
	)

//缩放倍率
#define SCALE_RATIO(A, B) \
	DIV( \
		GET_NUNIT(TRANS_UNIT_MIN(A, GET_UNIT_NAME(B))), \
		GET_NUNIT(TRANS_UNIT_MIN(B, GET_UNIT_NAME(A)))	\
	)


/**========代码块类型(C_)========*/
#define MOV(REG, VAL) \
do { \
	(REG) = (VAL); \
} while (0)

#define MOV_OP(REG, OP) \
do { \
	(REG) = (OP); \
} while (0)

#define RMW(REG, OP, VAL) \
do { \
	MOV(REG, OP(REG, VAL)); \
} while (0)

#define REG_SET_BIT(REG, N) \
do { \
	MOV_OP(REG, SET_BIT(REG, N)); \
} while (0)

#define REG_CLR_BIT(REG, N) \
do { \
	MOV_OP(REG, CLR_BIT(REG, N)); \
} while (0)

#define REG_TOG_BIT(REG, N) \
do { \
	MOV_OP(REG, TOG_BIT(REG, N)); \
} while (0)

// 基础自增
#define INC(REG) \
do { \
	RMW(REG, ADD, 1); \
} while(0)

//基础自减
#define DEC(REG) \
do { \
	RMW(REG, SUB, 1); \
} while(0)

// 自增+N
#define INC_N(REG, STEP) \
do { \
	RMW(REG, ADD, STEP); \
} while(0)

//自减-N
#define DEC_N(REG, STEP) \
do { \
	RMW(REG, SUB, STEP); \
} while(0)



/** =========执行流(F_)=========== */
//自增+运算
#define INC_OP(A, OP) \
do{ \
	INC(A); \
	OP; \
}while (0)

//运算+自增
#define OP_INC(OP, A) \
do{ \
	OP; \
	INC(A); \
}while (0)

//自减+运算
#define DEC_OP(A, OP) \
do{ \
	DEC(A); \
	OP; \
}while (0)

//运算+自减
#define OP_DEC(OP, A) \
do{ \
	OP; \
	DEC(A); \
}while (0)
//====================================================
//====================================================
//自增N+运算
#define INCN_OP(A, STEP, OP) \
do{ \
	INC_N(A, STEP); \
	OP; \
}while (0)

//运算+自增N
#define OP_INCN(OP, A, STEP) \
do{ \
	OP; \
	INC_N(A, STEP); \
}while (0)

//自减N+运算
#define DECN_OP(A, STEP, OP) \
do{ \
	DEC_N(A, STEP); \
	OP; \
}while (0)

//运算+自减N
#define OP_DECN(OP, A, STEP) \
do{ \
	OP; \
	DEC_N(A, STEP); \
}while (0)

//=========================条件跳转==============================
//如果条件满足，则A，否则B
#define IFF(E, TC, FC) \
do { \
	if(E) {TC;} \
	else 	{FC;} \
} while (0)

#define IFFT(T, E, TC, FC) \
do { \
	T _safe_expr = (E); \
	if(_safe_expr) {TC;} \
	else 	{FC;} \
} while (0)

#define IFF_RET(E, RET_VAL) \
do { \
    if (E) { return (RET_VAL); } \
} while (0)

#define IFFT_RET(T, E, RET_VAL) \
do { \
    T _safe_expr = (E); \
    if (_safe_expr) { return (RET_VAL); } \
} while (0)

#define IFF_BREAK(E) \
do { \
    if (E) { break; } \
} while (0)

#define IFFT_BREAK(T, E) \
do { \
    T _safe_expr = (E); \
    if (_safe_expr) { break; } \
} while (0)

#define IFF2(E1, E2, T1C, T2C, FC) \
do { \
    if (E1) { T1C; } \
    else if (E2) { T2C; } \
    else { FC; } \
} while (0)

#define IFFT2(T, E1, E2, T1C, T2C, FC) \
do { \
    T _safe_expr1 = (E1); \
    T _safe_expr2 = (E2); \
    if (_safe_expr1) { T1C; } \
    else if (_safe_expr2) { T2C; } \
    else { FC; } \
} while (0)

//========================循环===============================

//表达式展开
#define GTT(VAR, I, AIM, STEP) \
	for(VAR = (I); GT(VAR, AIM); VAR = ADD(VAR, STEP)) 

#define LTT(VAR, I, AIM, STEP) \
	for(VAR = (I); LT(VAR, AIM); VAR = ADD(VAR, STEP)) 

#define EQQ(VAR, I, AIM, STEP)	\
	for(VAR = (I); EQ(VAR, AIM); VAR = ADD(VAR, STEP)) 

#define GEE(VAR, I, AIM, STEP) \
	for(VAR = (I); GE(VAR, AIM); VAR = ADD(VAR, STEP)) 

#define LEE(VAR, I, AIM, STEP) \
	for(VAR = (I); LE(VAR, AIM); VAR = ADD(VAR, STEP)) 
	
#define NEE(VAR, I, AIM, STEP) \
	for(VAR = (I); NE(VAR, AIM); VAR = ADD(VAR, STEP)) 


#define FORR(EE, CODE) \
do { \
	EE { \
		CODE; \
	} \
} while (0)

#define WHILEE(EE, CODE) \
do { \
	while (EE) { \
		CODE; \
	} \
} while (0)

#define DOO(CODE, EE) \
do { \
	do { \
		CODE; \
	} while (EE); \
} while (0)




/** 
=================运算类型：M_ ===========================
===================值类型：V_ ===========================
===================表达式：E_ ===========================
===================代码块：C_ ===========================
===================执行流：F_ ===========================
=================类型约束: T_ ===========================
*/

#endif