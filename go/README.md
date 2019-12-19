# go语言计算并输出平方数
## 原程序
```
package main
import("fmt" 
"time")
func counter(out chan<- int){
	for x:=0;x<100;x++{
		out<-x
		time.Sleep(200 * time.Millisecond)
	}
	close(out)
}
func squarer(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}
func printer(in<-chan int){
	for v:=range in{
		fmt.Print(v)
		fmt.Print(" ")
		time.Sleep(300 * time.Millisecond)
	}
}
func main(){
	naturals:=make(chan int)
	squares:=make(chan int)

	go counter(naturals)
	go squarer(squares,naturals)
	printer(squares)
}
```
三个goroutine：
第一个goroutine叫做counter，产生
一个自然数序列，发送到下一个
goroutine；
第二个goroutine叫做squarer，计算
每个数的平方，发送到下一个
goroutine；
第三个goroutine叫做printer，接收
值并输出它们。
## 题目
假设生成一个自然数需要200毫秒的时间，对自然数
取平方需要500毫秒的时间，而输出一个自然数需要
300毫秒的时间，请修改上一页的程序，让输出所有
数字所需时间最小。  
– 提示一：可以用time.Sleep(200 * time.Millisecond)来模拟时
间消耗了200毫秒；  
– 要求一：在goroutine的阻塞时间最小同时，请尽量减少内存
花费；  
– 要求二：请说明你的程序输出每一个数字所需的时间是多少。  
- 要求三：counter只能一个线程
## 改后的代码
```
package main
import("fmt" 
"time")

func counter(out chan<- int){
	for x:=0;x<100;x++{
		out<-x
		time.Sleep(200 * time.Millisecond)
	}
	close(out)
}
func squarer(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}
func squarer1(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}
func squarer2(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}

func printer(in<-chan int){
	for v:=range in{
		fmt.Print(v)
		fmt.Print(" ")
		time.Sleep(300 * time.Millisecond)
	}
}
func printer1(in<-chan int){
	for v:=range in{
		fmt.Print(v)
		fmt.Print(" ")
		time.Sleep(300 * time.Millisecond)
	}
}
func main(){
	naturals:=make(chan int,3)
	squares:=make(chan int,3)

	go counter(naturals)
	go squarer(squares,naturals)
	go squarer1(squares,naturals)
	go squarer2(squares,naturals)
	go printer1(squares)
	printer(squares)
}
```
## 说明
由于counter goroutine只能开一个，所以开三个squarer使其处理时间小于counter；此时counter为瓶颈，开两个printer使其处理时间也小于counter；所以最后counter为瓶颈。200ms*100=20s，最终输出时间略长于20s。
## 结果
```
[Running] go run "d:\homework\程序设计作业\go\main.go"
0 1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361 400 441 484 529 576 625 676 729 784 841 900 961 1024 1089 1156 1225 1296 1369 1444 1521 1600 1681 1764 1849 1936 2025 2116 2209 2304 2401 2500 2601 2704 2809 2916 3025 3136 3249 3364 3481 3600 3721 3844 3969 4096 4225 4356 4489 4624 4761 4900 5041 5184 5329 5476 5625 5776 5929 6084 6241 6400 6561 6724 6889 7056 7225 7396 7569 7744 7921 8100 8281 8464 8649 8836 9025 9216 9409 9604 9801 
[Done] exited with code=0 in 22.04 seconds
```
所以最终平均输出时间为22.04/100=220.4ms。
