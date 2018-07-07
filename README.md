# MAKERbuino Pong Game

![PONG GIF][gif]

[![MIT License][license-badge]](https://github.com/RokKos/makerbuino-pong-game/blob/master/LICENSE)

### Table of Contents

* **[About](#about)**
* **[Resources](#resources)**
* **[Trying out the Game](#trying-out-the-game)**
* **[Building Project](#building-project)**
* **[License](#license)**

## About

This is 8-bit pong game for MAKERbuino. I am making this game just to get to know the platform. Expect more games like this in future.

So this is basically remaking of one of earliest games called Pong. You can read more on [wiki](https://en.wikipedia.org/wiki/Pong). But there is a twist I am doing this on a game console called [MAKERbuino](https://www.makerbuino.com/). This game is for two players and can be played locally on one console.

## Resources
So first we need some basic documentation. 
For this, we can turn on MAKERbuino [Getting Started guide](https://www.makerbuino.com/coding-getting-started/). Here you will find all the instructions to start coding.

Then when you start to code and get into the details this two reference pages: [Arduino](https://www.arduino.cc/reference/en/) and [GAMEbuino](https://www.makerbuino.com/reference/) will help you out.

And you call also check this [tutorial](https://www.makerbuino.com/coding-pong/) which was the inspiration for this project. 

Arduino also provides the IDE for coding, building the project and exporting the project. You can found IDE [here](https://www.arduino.cc/en/Main/Software). But I personally don't use it. See the [Building Project]() paragraph for this.
 
I also found this [helpful site](http://digole.com/tools/PicturetoC_Hex_converter.php) for converting/exporting .bmp images to C HEX array so that you can include pictures in your game.

## Building Project

So I am really a fan of a terminal and VS Code. This is the reason why I abandoned Arduino IDE. In my opinion, it just took many clicks to export your project and rename it like says in [documentation](https://www.makerbuino.com/coding-getting-started/). So I created the [script](https://github.com/RokKos/makerbuino-pong-game/blob/master/src/pong_game/rename.sh) that automates this process. This script builds the project from .ino files and then deletes all unused build outputs and then renames it to the name_of_the_game.HEX. Usage of the script:
``` bash
cd src/pong_game/
chmod +x rename.sh
./rename.sh
```

TODO: implement continuous integration with [Travic CI](https://travis-ci.org/) or [PlatformIO](https://platformio.org/)

## Trying out the Game

There are 3 ways how to try out the game:
1. You can clone the repository and then upload the program to your MAKERbuino
2. You can download only [HEX file](https://github.com/RokKos/makerbuino-pong-game/blob/master/bin/PONG2P.HEX) and then copy it to the SD card and put SD card to the MAKERbuino
3. You can again download [HEX file](https://github.com/RokKos/makerbuino-pong-game/blob/master/bin/PONG2P.HEX) and try it in [online emulator](http://simbuino4web.ppl-pilot.com/).


## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/RokKos/makerbuino-pong-game/blob/master/LICENSE) file for details.

[license-badge]:    https://img.shields.io/badge/license-MIT-007EC7.svg "MIT Lincense"
[gif]: https://github.com/RokKos/makerbuino-pong-game/blob/master/screenshots/PONG2P_gif.gif