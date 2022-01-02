#!/bin/bash

python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/characters.png -o ../assets/characters.png --key=ASSET_KEY
python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/spritesheet.png -o ../assets/spritesheet.png --key=ASSET_KEY
python3 asset_helper.py --mode=decrypt -i ../assets/encrypted/attack_animations.png -o ../assets/attack_animations.png --key=ASSET_KEY
