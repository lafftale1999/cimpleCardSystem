# CuperAdCcreen
Individual assignment for my class "C / C++ Programming". The objective was to simulate an access system where we can dynamically Create, Read, Update and Delete cards in the system. I also tried to emulate an encryption system (without any prior knowledge in cryptography) to create a sense of security for the program.

## Key features
Reads the .txt-file with cards in it.  
Allocates the list of cards on the heap.  
User are able to dynamically:
* scan card
* show all cards
* change card access
* create new card
* delete card

Every card has a unique key and map for encrypting/decrypting their access. The map is randomly generated and is used to map the key when checking access.

## Prerequisites
**Operating System** Makefile is tuned for Windows/Linux.  
**Programming Languages** C and Makefile.  
**Compiler** GCC.  
**Libraries** C Standard libraries.  
