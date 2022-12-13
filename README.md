# HUST_OS_LAB
HUST操作系统实验（上传了加粗部分）
## 实验一
1）用NASM编写MBR引导程序，在BOCHS虚拟机中测试。  
2）在Linux（建议Ubuntu或银河麒麟或优麒麟）下裁剪和编译Linux内核，并启用
新内核。（其他发行版本也可以）  
3）为Linux内核（建议Ubuntu或银河麒麟或优麒麟）增加2个系统调用，并启用
新的内核，并编写应用程序测试。（其他发行版本也可以）  
***4）在Linux （建议Ubuntu或银河麒麟或优麒麟） 或Windows下，编写脚本或批
处理。脚本参数1个：指定目录。脚本的作用是把指定目录中的全部文件的文件名
加后缀，后缀是执行脚本时的日期和时分。例如：文件名“test”变成“test-
2022-11-21-20-42”.***  

[前三个子任务参考](https://ziyikee-github-io.vercel.app/2021/11/25/OS%E5%AE%9E%E9%AA%8C%E6%9C%80%E7%BB%88%E7%89%88/#HUST%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F%E5%AE%9E%E9%AA%8C%E4%B8%80)(需挂梯子）
## 实验二
***1）在Linux/Windows下创建2个线程A和B，循环输出数据或字符串。  
2）在Liunx下创建（fork）一个子进程，实验wait/exit函数***  
3）在Windows/Linux下，利用线程实现并发画圆画方。   
***4）在Windows或Linux下利用线程实现“生产者-消费者”同步控制  
5）在Linux下利用信号机制(signal)实现进程通信***  
6）在Windows或Linux下模拟哲学家就餐，提供死锁和非死锁解法。  
7）研读Linux内核并用printk调试进程创建和调度策略的相关信息。  
## 实验四
***1）Windows/Linux模拟实现FIFO或LRU页面淘汰算法。***  
2）Linux下利用/proc/pid/pagemap技术计算某个变量或函数虚拟地址对
应的物理地址等信息。  
3）研读并修改Linux内核的缺页处理函数do_no_page 或页框分配函数
get_free_page，并用printk打印调试信息。注意：需要编译内核  
4）编写一个Linux内核模块，并完成模块的安装/卸载等操作。  
***5）编写Linux驱动程序（字符类型或杂项类型）并编程应用程序测试。
功能：write几个整数进去，read出其和或差或最大值。***  
6）编写Linux驱动程序（字符类型或杂项类型）并编程应用程序测试。
功能：有序读和写内核缓冲区，可以重复读，可以覆盖写。返回实际读写
字节数。  

[任务一参考](https://blog.csdn.net/qq_45740212/article/details/113366246)
[任务五参考](https://blog.csdn.net/hanp_linux/article/details/90474432)
