#!/bin/bash

python3 asset_helper.py --mode=encrypt -i ../assets/characters.png -o ../assets/encrypted/characters.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/spritesheet.png -o ../assets/encrypted/spritesheet.png --key=ASSET_KEY
python3 asset_helper.py --mode=encrypt -i ../assets/attack_animations.png -o ../assets/encrypted/attack_animations.png --key=ASSET_KEY
