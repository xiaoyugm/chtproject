//Sequence.h
//#define	 SEQNUM	16
//#define  MAXWAITLEN 20

//#define   MAXPOINT 15000
//#define   BLOCKSIZE 1000
//#define   MAXBLOCK 15 
//#define   MAXSTEP   1

//点的类型
/*
#define ICO 	     0
#define A50 	     1
#define MCA 	     2
#define MC8 	     3
#define C3  	     4
#define B1  	     5
#define B21 	     6
#define B20_B30      7
#define B34  	     8
#define B38  	     9
#define B2   	     10
#define B3   	     11
#define B22  	     12
#define B23  	     13
#define B25  	     14
#define B48  	     15
#define D1	     16
#define D10  	     17
#define D11  	     18
#define SUB_ST       19
#define TIME_P	     20*/
/*
#define  MAXADDR     128
#define MAXTRUNCK    8
#define MAXCOMMAND   2000
#define HIGHCOMMAND  1000
#define MEDIUMCOMMAND   500
#define  MINCOMMAND     100*/
/* 
typedef struct {
  UINT Data16;
  BYTE Pstate;
}aValue;
*/
/*
typedef struct trigSEQ {
  WORD   Point,Seq;
  int   Condition;
  BYTE PntStat;
 } TRIG;
*/
/*  typedef struct tagDAYTIME {
  int    Hour;
  int    Minute;
  int    Month;
  int    Day;
  char    Daily;
  char    Active;
  UINT    Seqnum;
  } DAYTIME;*/
/*  
  typedef struct tagSTACK {
	WORD	seqnum;
	BYTE    seqevent;
//	BYTE	depth;
//    BYTE	id;
  } STACK;*/
/*
  typedef struct tagSEQSTACK {
	STACK   seqstack[5];//4个可以执行的东西 
	BYTE	ptr;    
	BYTE    depth; //added by ljh
  } SEQSTACK;
*/
/*  
 typedef struct  tagCOMMAND1{
 
  int   command_type; 
  char  Para1[8];
  char  Para2[8];
  char  Para3[8];
  char  Para4[8];  
  } COMMAND1;*/
/*  typedef struct tagNSEQ {
  WORD    SPUnum;     //时序号
  BOOL    SPUhold;    //是否刮起
  BYTE    SPUprori;   //优先级
  int    num_of_command;

//   COMMAND1 command[2000];   //动态开辟 
  COMMAND1 *command;
  } NSEQ;
*/
/*  
typedef struct {
  char H, Apc, P1_2,P3_4, Srf, Prt,Inscan;//Rng, Unt,
  BYTE Alm, Dly;//,Pstate;
//  DOUBLEBYTE Data;
  char desc[18];
}aPoint;
typedef struct {
  char type;
  BYTE pointnum,cmdnum;
  int  startpoint,scan_seq;
}TRUNKADDR;
typedef struct {
  BYTE Xmits,Errs,Responses,Id,Data;
}TRUNKSTATUS;*/