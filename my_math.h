#ifndef MY_MATH_H__
#define MY_MATH_H__

#ifndef KEIL_5

//============================变长参数宏==================================
#define GET_ARGS_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_ARGS(...)  (GET_ARGS_COUNT(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#endif

//==============胶水宏==================
#define GLUB(A, B) A##B
#define XGLUB(A, B) GLUB(A, B)

/** 
=================运算类型：M_ ===========================
===================值类型：V_ ===========================
===================表达式：E_ ===========================
===================代码块：C_ ===========================
===================执行流：F_ ===========================
=================类型约束: T_ ===========================
*/

//=========类型转换====================
#define CA(T, V) ((T)(V))
#define CAP(T, OP, V) (CA(T, OP(CA(T, V))))
#define CAP2(T, OP, V1, V2) 	CA(T, OP(CA(T, V1), CA(T, V2)))
#define CAP3(T, OP, V1, V2, V3) CA(T, OP(CA(T, V1), CA(T, V2), CA(T, V3)))
#define CAP4(T, OP, V1, V2, V3, V4) CA(T, OP(CA(T, V1), CA(T, V2), CA(T, V3), CA(T, V4)))
#define CAP5(T, OP, V1, V2, V3, V4, V5) CA(T, OP(CA(T, V1), CA(T, V2), CA(T, V3), CA(T, V4), CA(T, V5)))
#define U8(V) CA(u8, V)

//=========位运算符========

#define NOT(N) (~(N))
#define NOT_T(T, N) CAP(T, NOT, N)

#define AND(A, B) ((A) & (B))
#define AND_T(T, A, B) CAP2(T, AND, A, B)

#define OR(A, B) ((A) | (B))
#define OR_T(T, A, B) CAP2(T, OR, A, B)

#define XOR(A, B) ((A) ^ (B))
#define XOR_T(T, A, B) CAP2(T, XOR, A, B)

#define SHL(X, N) ((X) << (N))
#define SHL_T(T, X, N) (CA(T, SHL(CA(T, X), N)))

#define SHR(X, N) ((X) >> (N))
#define SHR_T(T, X, N) (CA(T, SHR(CA(T, X), N)))


//=============项目实施运算符=============

//X第N位置1
#define SET_BIT(X, N)	(OR(X, SHL(1, N)))

//X第N位置0
#define CLR_BIT(X, N) (AND(X, NOT(SHL(1, N))))

//X第N位反转
#define TOG_BIT(X, N) (XOR(X, SHL(1, N)))

//=========通用运算符========

#define MAX(A, B) (GT(A, B) ? (A) : (B))
#define MAX_T(T, A, B) CAP2(T, MAX, A, B)

#define MIN(A, B) (LT(A, B) ? (A) : (B))
#define MIN_T(T, A, B) CAP2(T, MIN, A, B)

#define ADD(A, B) ((A) + (B))
#define ADD_T(T, A, B) CAP2(T, ADD, A, B)

#define SUB(A, B) ((A) - (B))
#define SUB_T(T, A, B) CAP2(T, SUB, A, B)

#define DIFF(A, B) (GT(A, B) ? SUB(A, B) : SUB(B, A))
#define DIFF_T(T, A, B) (GT(A, B) ? SUB_T(T, A, B) : SUB_T(T, B, A))

#define SAT_SUB(A, B) (GE(A, B) ? SUB(A, B) : 0)
#define SAT_SUB_T(T, A, B) (GE(A, B) ? SUB_T(T, A, B) : CA(T, 0))

#define MUL(A, B) ((A) * (B))
#define MUL_T(T, A, B) CAP2(T, MUL, A, B)

#define DIV(A, B) ((A) / (B))
#define DIV_T(T, A, B) CAP2(T, DIV, A, B)

#define DIV_ROUND_UP(A, B) (DIV(SUB(ADD(A, B), 1), B))
#define DIV_ROUND_UP_T(T, A, B) CAP2(T, DIV_ROUND_UP, A, B)

#define REM(A, B) ((A) % (B))
#define REM_T(T, A, B) CAP2(T, REM, A, B)

#define MOD(A, B) (REM(ADD(REM(A, B), B), B))
#define MOD_T(T, A, B) CAP2(T, MOD, A, B)

#define MUL_DIV(A, B, C) DIV(MUL(A,B),C)
#define MUL_DIV_T(T, A, B, C) CAP3(T, MUL_DIV, A, B, C)

#define CLAMP(VAL, MIN_VAL, MAX_VAL) (LT(VAL, MIN_VAL) ? MIN_VAL : (LT(VAL, MAX_VAL) ? VAL : MAX_VAL))
#define CLAMP_T(T, VAL, MIN_VAL, MAX_VAL) CAP3(T, CLAMP, VAL, MIN_VAL, MAX_VAL)

#define ARRAY_SIZE(ARR) DIV(sizeof(ARR), sizeof(ARR[0]))
	
#ifndef TICK_RATE
#define TICK_RATE(X, T) SUB(DIV(ADD(X, T), T), 1)
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
#define AND_L3(A, B, C) AND_L(AND_L(A, B), C)

#define OR_L(A, B) ((A) || (B))
#define OR_L3(A, B, C) OR_L(OR_L(A, B), C)

#define XOR_L(A, B) NE(NOT_L(A), NOT_L(B))

#define IN_RANGE(VAL, MIN_VAL, MAX_VAL) AND_L(GE(VAL, MIN_VAL), LE(VAL, MAX_VAL))


//========项目实施表达式==============

//检查位状态
#define BIT_CHK(X, N) (AND(SHR(X, N), 1))


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



#endif