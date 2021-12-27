#!/bin/bash

python3 asset_helper.py --mode=encrypt -i ../assets/characters.png -o ../assets/characters_encrypted.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/player_attack.png -o ../assets/player_attack_encrypted.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/spritesheet.png -o ../assets/spritesheet_encrypted.png --key=ASSET_KEY
