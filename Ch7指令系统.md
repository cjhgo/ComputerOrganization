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
**$|\underline{\overline{操作码字段}}|\underline{\overline{操作数的地址码字段}}|$**
操作数的地址码
指令中存放的是操作数的地址码,通过地址码访存得到操作数
**操作数是目的,地址码是手段**


#####操作码
操作码用来指明该指令所要完成的操作

+ 位数反应机器允许的指令条数
+ 固定长度操作码
+ 变长操作码
	- 扩展操作码技术
		- **<u>扩展方案是不唯一的,</u>**
	- 让使用频率高的指令占用短操作码,缩短经常使用的指令的译码时间
+ 固定长度与可变长度的问题,,????????

#####例7.1
$假设指令字长为16位,操作数的地址码为6位,指令有零地址,一地址,二地址三地址格式\\\
(1)设操作码固定,若零地址指令有P种,一地址指令有Q种,则二地址指令最多几种,?\\\
(2)采用扩展操作码技术,若二地址指令有X种,零地址指令有Y种,则一地址指令最多几种,?$

+ (1)我的理解有问题
课本这样解答:地址码6位,指令字长16位,则二地址指令中操作码位数为4位
这4位操作码可有2^4=16种操作.一地址指令Q种,零地址指令P种,则二地址指令有16-P-Q种
	- 我不理解,为什么一共只有16种指令,答案就是条件说`操作码固定`啊
	即,无论是零地址,一地址还是二地址指令,它们中的操作码的位数都是一样的
		+ 所以问题就是如何确定操作码的位数,答案就是按4
		+ 我想的是,
			- 16位的指令,4位操作码,那,一地址指令地址用去6位,剩下的6位怎么安排呢,?
+ (2)这个问题,理解的关键就是`不是用一位操作码,而是用一种操作码,做下一类型的特征码`
	- 二地址指令操作码最短4位,一地址指令操作码10位,零地址指令操作码16位
		+ 每一类相比前一类`扩展`了6位;前一类每少一种,后一类就可以多2^6种
		+ 一地址指令的前4位不能和二地址指令的4位任意操作码重复,后6位任取
		+ 零地址指令的前10位不能和一地址指令的10位任意操作码重复,后6位任取		
	- 设一地址指令有M种,则有如下等式
	$[(2^4-X)\times 2^6 - M]\times 2^6=Y$
+ 从组合的观点看
	- 从二地址指令4位操作码的2^4组合中,取出2^4-X个给一地址指令
	- $零地址指令的16位操作码的前10位有2^{10}种组合,其中M中用给了一地址指令\\\
	二地址指令占去X\times 2^6(因为以二地址操作码开头的都不能用了\\\
	剩下[2^{10}-M-X\times 2^6]\times 2^6=Y)$
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
	- 确实只需要用一个操作数的指令:如`如一个寄存器内容增1或减1运算的指令`
	- 需呀两个操作的指令,使用约定好的操作数:如`i/o类指令,可以只在指令中指明该外设地址`
	另一个操作数事先约定好
+ 零地址指令$|\underline{\overline{OP}}|$
指令字中没有地址码,(不代表不需要操作数
	- 不需要操作数的零地址指令:如`停机`,`空操作`这类指令
	- 需要操作数的零地址指令,使用约定好的操作数:如`子程序返回`,`中断返回`这类指令
	**<u>操作数地址隐含在堆栈指针中</u>**

**结论**:用硬件资源承担地址码可扩大寻址范围

操作码是寄存器的情况,不用访存	
####指令字长

+ $操作码长度+操作数地址长度\times操作数地址个数=指令长度$
+ 指令字长:操作码+操作数位数
+ 机器字长:CPU内寄存器的位数
+ 存储字长:基本存储单元一个字的位数
###2.操作数类型和操作类型
####操作数类型

+ 地址
+ 数字
+ 字符
+ 逻辑数据
####数据(操作数,而非指令字)在存储器中的存放方式:数据的解释方式

+ 边界对齐的问题
+ 两种字节序的问题

内存中是一条条指令;
指令时操作码+操作数
**<u>大端,小端字节序值得是指令中的操作数作为一个数据
当它的位数超过一个字节成为多字节数时,在内存中的存放顺序
而不是整条指令作为一个多字节数据在内存中的存放顺序</u>**

数据才讲大端,小端

+ 取指令时,指令的操作码显然要放在一条指令的最开始处,
这样才能识别出指令的类型
进而 判断取多长的字节 成为一条指令
	- <u>即,给定一个地址,从此地址开始首先读到的必须是操作码</u>
+ 取数据时,同样给定一个地址,首先读到的字节
	- 也许是数据的低字节,则此时为小端模式
	- 也许是数据的高字节,则此时为大端模式
+ 取指令时,根据操作码判断处读取多少个连续的字节
取操作数时,必须知道类型信息,即操作数时一个字,半个字,还是两个字
(这些类型信息可以通过指令涉及的寄存器的位数来约定,等等)


####操作类型

+ 数据传送
+ 算术逻辑操作
+ 移位
+ 转移
	- 无条件转移
	- 条件转移
	- 调用与返回
		+ 过程调用
		+ 系统调用
		+ 子程序调用
	- 陷阱与陷阱指令
+ 输入输出
+ 其他:等待,停机,空操作,开中断,关中断,置条件码,.....
+ 非数值处理指令:字符串传送,字符串比较,字符串查询,...
###3.寻址方式
寻址方式:确定本条指令的数据地址以及下一条将要执行的指令地址的方法
####指令寻址
+ 顺序寻址:程序计数器PC加1,自动形成下一条指令的地址
+ 跳跃寻址:通过转移类指令实现
####数据寻址
在指令中设置一字段指明属于哪一种寻址方式
指令的地址码往往不代表操作数的真实地址,称为形式地址,记为A
操作数的真实地址称为有效地址,记为EA,由**寻址方式和形式地址**共同确定

#####1.立即寻址:立即数
操作数本身就在指令字内
立即数,立即寻址特征#

+ 优点,只要取出指令就立即获得操作数,指令执行阶段不必访存
+ 缺点,位数限制了立即数的范围
#####2.直接寻址:EA=A
形式地址就是真实地址

+ 位数限制了寻址范围
#####3.隐含寻址:不显式给出地址码
指令不明显的给出操作数地址,操作数地址隐含在操作码或寄存器中
#####4.间接寻址EA=(A)
形式地址指出操作数有效地址所在的存储单元地址

+ 优点1:扩大了操作数的寻址范围,因为形式地址位数通常小于指令字长,而存储字长可与指令字长相等,能表示更高的地址
	+ 多次间址,可以用存储字的首位来标识,同时首位就不再是EA的组成部分
+ 优点2:便于编制程序.
	- 通过间址,虽然每次返回到不同的地址单元但可以用相同的指令表示,进而这样的指令可以写成子程序
+ 缺点:要两次或多次访存
#####5.寄存器寻址:EA=R_i
地址码给出寄存器编号,操作数在寄存器中
#####6.寄存器间接寻址:EA=(R_i)
地址码给出寄存器编号,真实地址在寄存器中
比间接寻址少访存一次
#####7.基址寻址:EA=A+(BR)
有效地址=形式地址+基址寄存器中的内容(基地址)

+ 基址寄存器
	- 隐式基址寄存器,专用基址寄存器,用户不必明显指出,由指令寻址特征位反映出
	- 显式基址寄存器,用户明确指出通用寄存器中的某个寄存器作基址寄存器
+ 可扩大操作数的寻址范围:首地址+偏移量	
#####8.变址寻址:EA=A+(IX)
有效地址=形式地址+变址寄存器内容之和

+ 基址寻址主要用于为程序或数据分配存储空间,故基址寄存器内容通常由操作系统或管理程序确定,
	- 程序执行过程中,基址寄存器不变,A可变
+ 变址寻址中,变址寄存器内容由用户设定,
	- 程序执行过程中,A不变,变址寄存器其值可变,
	- 主要用于处理**数组问题**:A为首地址,IX是不断变化的下标

基址寻址和变址寻址都可以扩大操作数的寻址范围,**<u>当寄存器位数足够时</u>**
方法就是段偏移
如果,没有采用段偏移的手段,而是直接相加,那就没有扩大操作数的寻址范围
也就是说,只能能扩大,是否扩大,看具体条件和手段


#####9.相对寻址:EA=(PC)+A
用于转移类指令,**转移地址不固定**,随PC值变化而变

+ 对应编写**浮动程序**特别有利,
	- 程序无论在主存哪段区域都可以正确运行
#####不同寻址方式的配合使用
+ 基址变址寻址
+ 相对间址寻址,,,
#####10.堆栈寻址
+ 堆栈用寄存器组来实现,硬堆栈
+ 堆栈用主存一部分空间做堆栈,软堆栈

#####例7.2
$设相对寻址的转移指令占用3个字节,第一字节为操作码,\\\
第二三字节为相对位移量(补码表示),且数据在存储器中采用以低字节地址为字地址的方式\\\
每当cpu从存储器中取出一个字节时,自动完成加一操作\\\
(1)若PC当前值为240_{10},要求转移到290_{10},\\\
则转移指令的第二,三字节的机器代码是什么?$

+ 首先,计算
	- $转移指令执行完毕后PC=243,目标地址290,\\\
	所以偏移量为+47,用16位补码表示为002FH$
+ 我犯的错误就是把整条指令当成一个数据然后按小端模式存放,得到了`2F00OP`
然后查看指令的第二,三字节的内容
	- 实际上是把指令操作码放在第一个字节,接下来,
	将操作数按小端模式存放在接下来的两个字节中,得到`OP2F00`
	得到正确答案
		- 第二个字节为2FH
		- 第三个字节为00H
	- 我是如何意识到错误的,
		+ 看到百度知道上一个人说:[`从第二个字节开始存放这个数据/位移量`](http://zhidao.baidu.com/question/173281794.html)
		突然顿悟,大小端规则限制的是这些操作数的存放方式
		而非整个指令
堆栈寻址可以看做是一种隐含寻址,因为它的操作数是由堆栈指针隐式给出的
堆栈寻址也可以看做是一种间接寻址,如果SP这个堆栈指针是个寄存器的话,SP存放在操作数的有效地址
###4.指令格式(设计)举例
+ 确定指令格式时应从以下这些方面考虑
	- 操作类型
	- 数据类型
	- 指令格式:指令字长,操作码位数,地址码位数,地址个数,,
	指令字长和操作码位数是否可变
	- 寻址方式:
	- 寄存器个数:寄存器的多少直接影响指令的执行时间
+ 指令格式举例:体现了上边哪些方面
	- PDP-8
		+ 指令字长统一12位
	- PDP-11
	- IBM 360
	- Intel 8086
####指令格式设计
#####例7.4-7.7
+ 通过有几种寻址方式来判断寻址特征位有几位
+ 通过寄存器个数来判断地址码为寄存器位数有几位
+ 关于扩展寻址空间的方法
	- 采用间址寻址:例7.7(3)
	- 扩展指令长度,从而扩展地址码长度:例7.5(2)
	- 基址寄存器作段号,段偏移:例7.7(2)
###5.RISC技术
用20%的简单指令的组合来实现不常用的80%的那些指令功能

精简指令集
减少指令的执行周期数
$$程序执行时间P=I\times C \times T$$
由于精简了指令集,RISC中的I比CISC多,
但是RISC中的大多数指令仅用1个左右的机器周期完成
并RISC的每个机器周期的执行时间也小于CISC

####RISC技术的主要特点
+ 用20%实现另外的80%
+ 指令长度固定,格式种类少,寻址方式种类少
+ 只有store/load指令访存
+ CPU中有多个通用寄存器
	- 减少访存
+ 采用流水线技术,大部分指令在一个时钟周期内完成
+ 控制器采用组合逻辑,不用微程序
+ 优化的编译技术
