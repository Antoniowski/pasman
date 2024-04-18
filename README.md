# pasman, an easy local cli password manager

pasman is an easy way to storage your password locally using your terminal

## How to setup

First clone this repo on your pc using the git clone comand:

```
git clone https://github.com/Antoniowski/pasman
```

or the GitHub CLI commnad:

```
gh repo clone Antoniowski/pasman
```

Then open the terminal and navigate to the folder where you cloned the repo and use make to create the executable.
And that's it, now you just need to use the following comand to start using pasman

```
./pasman
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

