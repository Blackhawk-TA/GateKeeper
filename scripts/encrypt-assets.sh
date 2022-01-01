#!/bin/bash

python3 asset_helper.py --mode=encrypt -i ../assets/characters.png -o ../assets/encrypted/characters.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/player_attack.png -o ../assets/encrypted/player_attack.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/spritesheet.png -o ../assets/encrypted/spritesheet.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/knight_attack.png -o ../assets/encrypted/knight_attack.png --key=ASSET_KEY
