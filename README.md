# pasman, an easy local cli password manager

pasman is an easy way to storage your password locally using your terminal

## How to setup

You can download pasman last version at this [link] or alternatively you can compile it yourself from the source code.

If you choose the latter then firstly clone this repo on your pc using the git clone command:

```
git clone https://github.com/Antoniowski/pasman
```

or the GitHub CLI command:

```
gh repo clone Antoniowski/pasman
```

Then, open the terminal and navigate to the folder where you cloned the repo and use make to create the executable.
If you cannot use the make command you can manually compile files by using the following instructions:
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

Another thing that will be asked is a path to a folder that will be used to create a pasman folder that will contain all the encrypted files.

## Reset and Export

To reset the program and create a new profile you just need to delete the config.txt file that can be found in the pasman/ folder at the path that has been specified during the initialization.

N.B. Deleting the config file and run the program again will automatically delete the pass.txt file where the passwords are saved.

You can also export your file so that you can use them into another machine. You just need to copy your config and pass files into your new
computer (in the folder that you have spacified during the init) and you are ready to go.

