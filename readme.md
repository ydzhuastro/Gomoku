# Gomoku

A naive terminal Gomoku game just for fun. 
一款简易的命令行五子棋游戏。

This code was written during my undergraduate study as a part of my homework. I will make an English version in the near future. 英文版本开发中。

## build the code 代码编译
+ Mac user please run the followings in the Terminal / Mac用户请在终端中运行
  ```
  $ ./build.sh
  ```
  
  Or 或者
  ```
  $ clang++ -Xclang -fopenmp -o go main.cc -lomp
  ```
+ Linux
  ```
  $ g++ -fopenmp -o go main.cc -lomp
  ```
## run the code 运行
```
$ ./go
```
Have fun!
