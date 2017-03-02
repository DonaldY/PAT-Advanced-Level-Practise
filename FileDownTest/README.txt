version - 2.1
更改函数位置，将联系紧密的函数放在一起，增加可读性。



详细分步骤：http://blog.csdn.net/fanfan4569/article/details/56287336
主要功能：多线程下载，支持断点下载
缺陷：
    1、代码整洁：
	  ①DownUtils 的 构造器 仍待改进
	  ②DownThread 的 RandomAccessFile 冗余，
		tempFileName 与 tempFile 抉择麻烦导致冗余，不知怎么简化。
    2、ExecutorsService 线程池的使用，感觉麻烦了(无法更好控制线程)
	导致，最后监听线程下载进度（进度条）受阻。（后来想到：每个线程下载完部分则传给
	DownUtils的接口，接口里对变量进行增，这要放锁。（但我(。??)ノ））
		

可完善功能：
1、监听线程进度
2、调用setBreakPoint()
3、clean code吧
4、忘了，。。。
	