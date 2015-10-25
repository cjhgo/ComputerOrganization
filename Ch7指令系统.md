viewport:width=device-width,initial-scale=1

目录

[TOC]

#[计算机组成原理](...)
##Ch7指令系统
指令系统的分类
常见寻址方式
指令格式
设计指令系统时应考虑的各种因素
###1.机器指令
####指令的一般格式
**$|\underline{\overline{操作码字段}}|\underline{\overline{地址码字段}}|$**
**$|\underline{\overline{操作码字段}}|\underline{\overline{操作数字段}}|$**
操作数的地址码

#####操作码
操作码用来指明该指令所要完成的操作

+ 位数反应机器允许的指令条数
+ 固定长度与可变长度的问题,,????????
扩展操作码技术
#####地址码
地址码用来指出该指令源操作数的地址,结果的地址,下一条指令的地址

+ 四地址指令
$|\underline{\overline{OP}}|\underline{\overline{A_1第一操作数地址}}|
\underline{\overline{A_2第二操作数地址}}|
\underline{\overline{A_3结果存放地址}}|\underline{\overline{A_4下一条指令地址}}|$
	- 四次访存
		+ 取指令一次
		+ 取第一操作数一次
		+ 取第二操作数一次
		+ 存结果一次	
+ 三地址指令$|\underline{\overline{OP}}|\underline{\overline{A_1}}|\underline{\overline{A_2}}|
\underline{\overline{A_3}}|$
	- 把后续指令地址隐含在程序计数器PC中,省去$A_4字段$,直接寻址范围扩大
	- 依然是四次访存
+ 二地址指令$|\underline{\overline{OP}}|\underline{\overline{A_1}}|\underline{\overline{A_2}}|$
	- $A_1或A_2$既用来表示操作数地址,也用来表示结果存放地址,省去$A_4字段$,直接寻址范围扩大
	- $(A_1)OP(A_2) \rightarrow A_1/A_2$:4次访存
	- $(A_1)OP(A_2) \rightarrow ACC$:3次访存
		- 存结果不用访存
+ 一地址指令$|\underline{\overline{OP}}|\underline{\overline{A_1}}|$
	- 用ACC既存放操作数,也用来存放运算结果,省去一个操作数字段,直接寻址范围扩大
	- $(A_1)OP(ACC) \rightarrow ACC$:2次访存
		- 取指令访存一次
		- 取操作数访存一次
+ 零地址指令$|\underline{\overline{OP}}|$
	- 操作数地址隐含在退栈指针中

**结论**:用硬件资源承担地址码可扩大寻址范围

操作码是寄存器的情况,不用访存	
####指令字长

+ $操作码长度+操作数地址长度\times操作数地址个数=指令长度$
+ 指令字长:操作码+操作数位数
+ 机器字长:CPU内寄存器的位数
+ 存储字长:基本存储单元一个字的位数