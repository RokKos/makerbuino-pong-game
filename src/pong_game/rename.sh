#! /bin/bash
#Script that deletes unecesary binaries, renames and moves binaries that Arduino IDE created

game_name=PONG2P.HEX

rm pong_game.ino.with_bootloader.standard.hex
mv pong_game.ino.standard.hex $game_name
mv $game_name ../../bin