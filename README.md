# Snake PvP Game
### About Game

Snake Pvp Game is a 1v1 game where the each player starts in an opposite corner of the play field and then attempt to survive as long as possible without hitting the other players tail or their own tail.

The player who survives the longest wins that round and the player which wins the most rounds, wins the game.

###### This game was created for an embedded programing assignment for the ence260 course at the Univercity of Canterbury

## Installation/Setup

To begin with you need to install the AVR compilation tools, to do this, put the command below into your terminal:

```bash
sudo apt-get install git gcc-avr binutils-avr avr-libc dfu-programmer
```
Then in your terminal, navigate to where you wish to locate the UC funkit software library and enter to command below into your terminal:

```bash
git clone https://eng-git.canterbury.ac.nz/rmc84/ence260-ucfk4.git
```

Then move the files from this directory ``(ence260-2022/group_132)`` into the folder `assignment/final` in the UC funkit software library.

Extra documentaion of the UC funkit software library can be found at [UC FunKit Wiki](http://ecewiki.elec.canterbury.ac.nz/mediawiki/index.php/UCFK4)

To then upload the program to the funkits, you must connect the funkits via USB to your PC and run the following command in the terminal when in your `assignment/final` directory:

```bash
make program
```

## How to Play

1. To begin the game, face the IR blasters (the side opposite the reset button) of each of the funkits towards each other
2. Then on one of the funkits press the Nav Switch and then the button (near the IR blaster) down
3. After the funkits connect to each other, the game will start. Each users payer will be the on in the corner near the Nav switch
4. Now each player can use the Nav switch to dirrect their snake in any dirrection

The goal of the game is to make your snake not hit the body of either players snake for as long as it take to outlast your opponent. Once one of the players has hit a snake body, the round will end and the player which didn't have a collision will gain a point and then a new round will start. The player that has won the most round when the players finish playing, **Wins the game.**


## Authors:

cfi29 (Caleb Fitzgerald)

**and**

tfl33 (Thomas Fleming - [Online Portfolio](https://www.flemingkin.co.nz/Thomas))

## Contributing

We welcome pull requests. Please initiate an issue to discuss your modifications before making any major ones.

## License

[The Unlicense](https://choosealicense.com/licenses/unlicense/)
