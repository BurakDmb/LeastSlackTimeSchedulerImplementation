# LeastSlackTimeSchedulerImplementation
A basic least-slack-time scheduler implementation in c for time shared systems.

This project was a assignment for my BIL395-Programming Languages class.

To run, follow these commands in unix terminal:
```
git clone https://github.com/BurakDmb/LeastSlackTimeSchedulerImplementation.git ~/Desktop/LSTS
cd ~/Desktop/LSTS
```
Compile and link using the command below and output to the file named 'LSTS'
```
gcc main.c -o LSTS
```
Lastly, run it with this command
```
./LSTS
```

Also if you have cmake, you can follow these steps too,

After that, you need to clone my project to your computer(On this example, the code below will download the code to your desktop, in the directory named Interpreter)

```
git clone https://github.com/BurakDmb/LeastSlackTimeSchedulerImplementation.git ~/Desktop/LSTS
cd ~/Desktop/LSTS
```
After that, create a temporary build folder to build project. Then, enter that folder
```
mkdir cmake-build-debug
cd cmake-build-debug
```
Lastly, run these commands to build and run the interpreter
```
cmake ..
make
./LSTS
```
Or if you are using [CLion, A cross-platform IDE for C and C++](https://www.jetbrains.com/clion/) You can simply use the Import Project from Sources and run project from ide. You can easily build and run the project from the CLion


