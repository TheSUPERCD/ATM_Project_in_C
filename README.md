# The ATM Project Documentation

# Programmer :
	Chayan Deb.
	B.Tech Electrical Engineering.
	3rd Semester.
	IIT Palakkad.
	July-Dec 2019.
	

# Description: 
This C-Program can be used as an ATM machine driver and offers almost all the functionalities of a real ATM machine 
with end to end user data encryption. The user data as well as the system data that gets saved in the operation period of the ATM 
machine gets saved in the specific text files in an encrypted format that uses top-of-the-line RSA encryption method.
This RSA encryption ensures no data can be extracted from the files unless the security password can be guessed.
This program uses two python scripts that runs when the files are to be encrypted or decrypted. These scripts are used because 
standard C-language does not allow storing big data-type numbers. That's why Python had to be used.
The python script PrivateKeyGen.py allows the user to pick any n and a public key and this script computes the private key for the 
decryption of the messege.


	PrivateKeyGen.py : This Python script generates the private key for given any public key given the prime factors p and q of the
	number n. This script can be used for generating a unique private key for your unique  public key. But be sure to use smaller 
	numbers.


# System Requirements: 
Windows OS with python interpreter installed.
