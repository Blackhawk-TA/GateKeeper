#!/bin/bash

python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/characters.png -o ../assets/characters.png --key=ASSET_KEY
python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/player_attack.png -o ../assets/player_attack.png --key=ASSET_KEY
python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/spritesheet.png -o ../assets/spritesheet.png --key=ASSET_KEY
python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/knight_attack.png -o ../assets/knight_attack.png --key=ASSET_KEY
