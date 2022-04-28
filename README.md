# Sistemsko_programiranje

## NZ1
Napraviti program koji će za zadani uređaj (C:, D:, ...) obići cijelu strukturu direktorija počevši od korijenskog direktorija te ispisati koliko se direktorija nalazi na svakoj razini. Nulta razina je ona u kojoj je korijenski direktorij i tu rezultat treba biti 1. Svi ostali rezultati za svaku iduću razinu ovise o samoj strukturi poddirektorija. Rezultat ispisati za svaku razinu, npr.

Razina 0: 1 direktorija

Razina 1: 7 direktorija

Razina 2: 32 direktorija

... itd. koliko god razina ima


## NZ8
Proučiti FTP protokol te s obzirom na njega napraviti jednostavni FTP klijent koji je u stanju:

- spojiti se na određeni FTP server (IP adresu i uobičajeni port je 21)

- autentificirati korisnika (korisničko ime, lozinka)

- omogućiti korisniku spuštanje datoteke iz defaultnog direktorija na serveru (nije potrebno ugraditi mijenjanje direktorija), tako da klijent zada ime tražene datoteke.

Program isprobati s bilo kojim FTP serverom ili instalirati vlastiti (npr. program Quick 'n Easy FTP Server omogućava postavljanje jednostavnog Windows FTP servera)