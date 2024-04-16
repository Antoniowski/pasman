# pasman, a easy local cli password manager

pasman is an easy way to storage your password locally using your terminal.

## How to setup

First clone this repo on your pc using the git clone comand

```
git clone https://github.com/Antoniowski/pasman
```

or the GitHub CLI commnad

```
gh repo clone Antoniowski/pasman
```

Then open the terminal and navigate to the folder where you cloned the repo and use make to create the executable.
And that's it, now you just need to use the following comand to start using pasman

```
./pasman
```

## First Init

When you open pasman for the first time, a short initialization will begin.
During it you will be asked to choose an username, a password and a key. The key will be used to login (in combo with your password obviously) and, in particular, to encrypt both your info and your passwords.

Another thing that will be asked is a path to a folder that will be used to create another one named pasman that will contain the encrypted files.

## How to reset

To reset the program and create a new profile you just need to delete the config.txt file that can found in the pasman/ folder at the path that has been specified during the init. 

N.B. Deleting the config file and run the program again will automatically delete the pass.txt file where the passwords are saved.


