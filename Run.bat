gcc ascii.c -o ascii.exe -Wall -std=c99 -O3
gcc feistel.c -o feistel.exe -Wall -std=c99 -O3
./ascii.exe < ascii_in.txt >> ascii_out.txt
./feistel.exe < ascii_out.txt >> feistel_out.txt