#! /bin/bash
#Script that deletes unecesary binaries, renames and moves binaries that Arduino IDE created

game_name=PONG2P.HEX
game_binary=pong_game.ino.hex
#This command compiles sketch into hex file
#/home/rokkos/arduino-1.8.5/arduino-builder -compile -logger=machine -hardware /home/rokkos/arduino-1.8.5/hardware -tools /home/rokkos/arduino-1.8.5/tools-builder -tools /home/rokkos/arduino-1.8.5/hardware/tools/avr -built-in-libraries /home/rokkos/arduino-1.8.5/libraries -libraries /home/rokkos/Arduino/libraries -fqbn=arduino:avr:uno -ide-version=10805 -build-path /home/rokkos -warnings=none -build-cache /tmp/arduino_cache_966880 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avr-gcc.path=/home/rokkos/arduino-1.8.5/hardware/tools/avr -prefs=runtime.tools.arduinoOTA.path=/home/rokkos/arduino-1.8.5/hardware/tools/avr -prefs=runtime.tools.avrdude.path=/home/rokkos/arduino-1.8.5/hardware/tools/avr -verbose /home/rokkos/Documents/C/makerbuino-pong-game/src/pong_game/pong_game.ino


/home/rokkos//arduino-1.8.5/arduino  --pref build.path=/home/rokkos/Documents/C/makerbuino-pong-game/bin  --verify /home/rokkos/Documents/C/makerbuino-pong-game/src/pong_game/pong_game.ino

cd /home/rokkos/Documents/C/makerbuino-pong-game/bin

#This command removes all file except one
shopt -s extglob 
rm -rf -- !($game_binary) 
mv pong_game.ino.hex $game_name