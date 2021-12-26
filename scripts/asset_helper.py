#!/usr/bin/python

import getopt
import os
import sys

from cryptography.fernet import Fernet
from dotenv import load_dotenv


def main(argv):
	mode = ""
	key_env = ""
	key_gen = False
	input_file = ""
	output_file = ""

	try:
		opts, args = getopt.getopt(argv, "hm:i:o:k:", ["mode=", "input=", "output=", "key=", "keygen"])
	except getopt.GetoptError:
		print("./asset-helper.py --mode=encrypt -i <input_file> -o <output_file> --keygen")
		print("./asset-helper.py --mode=decrypt -i <input_file> -o <output_file> --key=<env var>")
		sys.exit(2)

	for opt, arg in opts:
		if opt == '-h':
			print("./asset-helper.py --mode=encrypt -i <input_file> -o <output_file> --keygen")
			print("./asset-helper.py --mode=decrypt -i <input_file> -o <output_file> --key=<env var>")
			sys.exit()
		elif opt in ("-i", "--input"):
			input_file = arg
		elif opt in ("-o", "--output"):
			output_file = arg
		elif opt in ("-m", "--mode"):
			mode = arg
		elif opt in ("-k", "--key"):
			key_env = arg
		elif opt in "--keygen":
			key_gen = True

	if key_gen:
		key = Fernet.generate_key().decode("utf-8")
		print(key)
	else:
		load_dotenv()
		key = os.environ[key_env]

	if mode == "encrypt":
		encrypt(key, input_file, output_file)
	elif mode == "decrypt":
		decrypt(key, input_file, output_file)
	else:
		print("Invalid mode")


def encrypt(key, input_file, output_file):
	with open(input_file, "rb") as file:
		original = file.read()

	fernet = Fernet(key)
	encrypted = fernet.encrypt(original)

	with open(output_file, "wb") as encrypted_file:
		encrypted_file.write(encrypted)


def decrypt(key, input_file, output_file):
	with open(input_file, "rb") as encrypted_file:
		encrypted = encrypted_file.read()

	fernet = Fernet(key)
	decrypted = fernet.decrypt(encrypted)

	with open(output_file, "wb") as decrypted_file:
		decrypted_file.write(decrypted)


main(sys.argv[1:])
