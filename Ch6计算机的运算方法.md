viewport:width=device-width,initial-scale=1

目录

[TOC]

##Ch6计算机的运算方法
###无符号数和有符号数
###数的定点表示和浮点表示
在计算机中,小数点不用专门的器件表示,而是按照约定的方式标出
共有两种方法表示小数点的存在,即定点表示和浮点表示
####定点表示
+ 纯小数:小数点位于数符位和第一数值位之间
+ 纯整数:小数点位于数值位之后

处理非纯小数
处理非纯整数
都要乘上一个比例因子
####浮点表示
$$N=S \times r^j\\\
S:尾数,决定了表示精度\\\
r:基数\\\
j:阶码,决定了表示范围$$


**<u>浮点数的位数确定后,合理分配阶码和尾数的位数直接影响
浮点数的表示范围和精度</u>**


+ 为了提高数据精度,以及便于浮点数的比较
规定**<u>浮点数的尾数用纯小数形式</u>**
+ **<u>规格化数:尾数最高位为1的浮点数</u>**
浮点数表示成规格化形式后,精度最高
+ 浮点数的表示形式
![floatpoint][0]
	

- m位的阶码表示范围


	
+ 浮点数的表示范围
	+ 浮点数能表示的
	$最大的正数A (1-2^{-n})\times 2^{(2^m-1)}\\\
	最小的正数B 2^{-n}\times 2^{-(2^{m}-1)}\\\
	最大的负数-B\\\
	最小的负数-A$
		- 规格化后,浮点数能表示的A不变,B变
	- 不是能表示的最小的数,是最小的正数
	浮点数当然能表示零,但是
		+ $\underline{在0和B ,及-B到0之间,有很多数无法用浮点数表示}$
			- 因为它们的阶码小于最小阶码
			这叫`下溢`
			**产生下溢时机器,机器将尾数各位强置为零,按机器零处理**
				+ 举例比如
				阶码最小是-12,即小数点最多左移12位
				$0$
				而一个数要小数点左移-15,即阶码为-15 < -12,
				产生下溢
					- $机器能表示的最小正数是0.\underbrace{000...001}\_{n}\\\
					那么0.\underbrace{000...00001}\_{>n,比如n+5},就没法表示$
		+ $\underline{在B和+\infty,及-\infty到-B之间,有很多数无法用浮点数表示}$
			- 因为他们的阶码大于最大阶码
			这叫`上溢`
			**产生上溢时机器停止运算,进行中断溢出处理**
				+ 举例比如
![floatoverflow][3]				
+ 浮点数的规格化
	- $尾数左移一位相当于乘了2,阶码部分要乘2^{-1}抵销,即\\\
	尾数左移,阶码减一\\\
	尾数右移一位相当于乘了2^{-1},阶码要乘2抵销,即\\\
	尾数右移,阶码加一$
		+ **<u>区分尾数移动和,小数点移动</u>**
	- 规格化后,浮点数能表示的最小正数是
	$0.1000\cdots \times 2^{-Max_{阶码}} = ...$
	最大负数相应变化,最大正数和最小负数不变
####定点数和浮点数的比较
![floatsample][1]
$$阶符,阶码数值部分;数符.尾数数值部分$$
**十进制分数怎样化成二进制小数,快速**
$ \frac{53}{512},并不能主观的看出来\\\
要义:\times \frac{256}{256},256怎样来的,512的一半\\\
= \frac{53}{512} \times \frac{256}{256}\\\
= \frac{53}{256} \times \frac{256}{512}\\\
= \frac{53}{256} \times \frac{1}{2}\\\
= ...\\\
即,乘 \frac{1}{2}
当算到了 \frac{21}{32}时,这样算\\\
= \frac{16+4+1}{32}$

**关于机器零**

+ 机器零有两种情况
	- 尾数为0
		+ 尾数为0,阶码无论多少,这个数都是0
	- (尾数虽不为零),但是产生了下溢
		+ 阶码小于或等于最小阶码,等于也算,,
+ 机器零的写法
	- 尾数补码表示,阶码补码表示时,
	机器零这么写:$1,000..0;0.000...0$
	- 尾数补码表示,阶码移码表示时,
	机器零这么写:$0,000...0;0.000...0$
		+ 这种写法的机器零
		是全零,有利于简化机器的判零电路
####IEEE754
![IEEE754][2]
IEEE754的短实数和长实数的尾数规格化有一位隐藏位
临时实数不采用隐藏位方案
举例
$178.125_{10}\\\
=1011 0010.001\\\
\overset{按照之前的约定}=0.1011 0010 001 \times 2^{-1000_2},尾数是一个纯小数\\\
\overset{采用隐藏位}= 1.011 0010 001 \times 2^{-111_2},尾数非纯小数$
###浮点四则运算
####浮点加减运算
1. 对阶:**小阶向大阶看齐**
	+ 小阶向大阶看齐,小阶要变大,尾数就要变小
	尾数变小就要右移
		- **尾数右移可能发生数码丢失,影响精度**
	+ 如果让大阶向小阶看齐,大阶变小,大阶的尾数就要变大
	即要左移,左移之后得到的尾数就不再是纯小数了
	所以,小阶向大阶看齐
2. 尾数求和
	+ 按定点数加减法运算即可
3. 规格化:$规格化要求尾数是这样的形式:\pm.1....\\\
即 \frac{1}{2} \leqslant |S| \leqslant 1$
	+ **如果采用双符号位的补码**
	$S>0, [S]_补=00.1....\\\
	S<0,[S]_补=11.0.....
	可见,当尾数的最高数值位和符号位不同时,即为规格化形式$
		- 两种特殊情况
			+ $S= -\frac{1}{2},[S]_补=11.100...\\\
			按规则,规定,用补码表示的-\frac{1}{2}不是规格化数$
			+ $S= -1,[S]_补=11.000...\\\
			按规则,规定,用补码表示的-1是规格化数$
	+ 结果按规则不是规格化数时,需要规格化
		- 左规:符号位和最高数值位相同不符合规则
		- 右规:尾数发生溢出,尾数之和绝对值大于1,
		表现为双符号位两位值不同
4. 舍入:对阶和右规过程中,尾数右移低位丢失,引起误差,影响精度
为此可用舍入法来提高尾数的精度
	+ `0舍1入法`
	+ `恒置1法`
5. 溢出判断

####浮点乘除法运算

###定点运算

###算术逻辑单元

http://segmentfault.com/a/1190000004090283
http://w3schools.invisionzone.com/index.php?showtopic=48625
https://www.quora.com/Why-is-0-1+0-2-not-equal-to-0-3-in-most-programming-languages
http://stackoverflow.com/questions/588004/is-floating-point-math-broken
http://stackoverflow.com/questions/5852056/why-does-alert321-alert-false
http://www.exploringbinary.com/hexadecimal-floating-point-constants/
http://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
http://floating-point-gui.de/

https://www.ics.uci.edu/~eppstein/161/960227.html


https://www.baidu.com/s?wd=%E7%BA%BF%E6%80%A7%E6%8E%A2%E6%B5%8B%E5%86%8D%E6%95%A3%E5%88%97%E6%B3%95%20%E6%9F%A5%E6%89%BE%E5%A4%B1%E8%B4%A5&rsv_spt=1&rsv_iqid=0xdcdfaf9100023aa7&issp=1&f=8&rsv_bp=0&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_enter=1&rsv_sug3=31&rsv_sug1=17&sug=%E7%BA%BF%E6%80%A7%E6%8E%A2%E6%B5%8B%E5%86%8D%E6%95%A3%E5%88%97%E6%B3%95&rsv_n=1&rsv_t=af664Tpw7e%2Fy%2F9ProyMdLm3oRmdBPbz7RtggOWpIkwPGbu9hTq4rNPoIuANECfyUlEj3&rsv_sug2=0&inputT=13206&rsv_sug4=13206

http://www.cskaoyan.com/thread-160179-1-1.html

[0]:http://cjhgo.sinaapp.com/CS/ComputerOrganization/images/floatpoint.gif
[1]:http://cjhgo.sinaapp.com/CS/ComputerOrganization/images/floatsample.gif
[2]:http://cjhgo.sinaapp.com/CS/ComputerOrganization/images/IEEE754.gif
[3]:http://cjhgo.sinaapp.com/CS/ComputerOrganization/images/floatoverflow.gif