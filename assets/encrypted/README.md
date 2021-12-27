# Encrypted Assets

The assets within this folder are encrypted to prevent a violation of the asset licensing.

To encrypt them, the correct key is needed as an environment variable named `ASSET_KEY`.\
The `./scripts/decrypt-assets.sh` and `./scripts/encrypt-assets.sh` helpers can be used to handle de-/encryption.

The actual decryption and encryption is performed by the `./scripts/asset_helper.py` script.

