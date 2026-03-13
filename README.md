# Pasman, An Easy Local Cli Password Manager

<p align="center">
  <img src="./pasman_img.png" alt="Trax"/>
</p>

<p align="center">
  <a href="https://ko-fi.com/P5P11VSMXF"><img src="https://ko-fi.com/img/githubbutton_sm.svg"/></a>
</p>

Pasman is an easy way to storage your password locally using your terminal

## How to setup

You can download pasman latest version [here](https://github.com/Antoniowski/pasman/releases) or alternatively you can compile it yourself from the source code.

If you choose the latter then firstly clone this repo on your pc using the git clone command:

```
git clone https://github.com/Antoniowski/pasman
```

or the GitHub CLI command:

```
gh repo clone Antoniowski/pasman
```

Then, open the terminal and navigate to the folder where you cloned the repo and use <code>make</code> to create the executable or just use the <code>install.sh</code> script. <br/>
If you cannot use the <code>make</code> command you can manually compile files by using the following instructions:
```
g++ -c ./src/PasswordHandler/passwordhandler.cpp
g++ -c ./src/TextHandler/texthandler.cpp
g++ -c ./src/Utility/utility.cpp
g++ -c ./src/main.cpp
g++ texthandler.o passwordhandler.o utility.o main.o -o pasman
```
And that's it, now you just need to use ./pasman to open the program or, if on Windows, start pasman.exe.

N.B. If you are on Mac you need to specify the C++ version to the compiler. To do so, add the std flag to the g++
commands as follows:

```
g++ -std=c++20  -c ./src/PasswordHandler/passwordhandler.cpp
g++ -std=c++20 -c ./src/TextHandler/texthandler.cpp
g++ -std=c++20 -c ./src/Utility/utility.cpp
g++ -std=c++20 -c ./src/main.cpp
g++ -std=c++20 texthandler.o passwordhandler.o utility.o main.o -o pasman
```

## Initialization

When you open pasman for the first time, a short initialization will begin.
During it you will be asked to choose an username, a password and a key. The key will be used to login (in combo with your password obviously) and, in particular, to encrypt both your info and your passwords.

## Reset and Export

To reset the program and create a new profile you just need to delete the exfls file that will be create in the same folder where the program is.

N.B. Deleting the exfls file and run the program again will automatically delete all the content in the sqlite database.

You can also export your database so that you can use them into another machine. You just need to initialize pasman on the new machine using the same key used on the old one and then 
copy your localdata.db file into your new computer in the same folder of the program.

