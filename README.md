# NP_2023

### Using Git and Github

1. Install git on your machine using 

```sudo apt install git``` .

2. Make sure **no directory named NP_2023** in your workspace directory .

3. Clone this repo using the following command, then this repo will be cloning into your workspace named NP_2023.

```git clone https://github.com/JYYehlouis/NP_2023``` 

4. Open your terminal and cd to this directory, set your personal info with 

```git config --local user.name "<Yourname>" && git config --local user.email "<YourEmail>"``` .

5. Set up your depository as origin, using 

```git remote add origin https://github.com/JYYehlouis/NP_2023.git```

6. For personal convenience, I recommend using this command next, 

```git remote set-url origin https://<YourGithubUsername>:<YourToken>@github.com/JYYehlouis/NP_2023.git```

7. Before working on this repo, it is a good habit to check if you are using the latest repo, using the command below to update all your files.

```git fetch origin && git pull```
8. Using the following command if you have to work on some specific branch,

```git switch <branch-name>```

9. After working on this repo, you will have to commit this changes, using the following commands, and the ```<message>``` is used to tell others what you changed.

```git add . && git commit -m "<message>"```

10. Using the following command after point 8, this will help you upload you changes, and you have to push the branch correctly on the name (usually the same as you see using ```git status```). 

```git push -u origin <branch-name>```

### Compilation

```g++ -O2 -L"\usr\include\SFML" -lsfml-graphics -lsfml-window -lsfml-system```

### Current status

1. Interface is almost complete, but we have to make sure that every click is not always be counted. Is it possible to calculate that given a specific region, the thing will be placed on the intersection if the clicl is valid.

2. The connection between the interface and the client.

3. Maybe we should have a menu that we can enter the player information (not complete), the menu of the online users (not complete), and the one that 2 players are playing (almost complete)

### Complete (git log to see the progress)

- 

- 

- 
