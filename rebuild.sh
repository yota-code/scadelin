#!/usr/bin/env zsh

setopt ERR_EXIT

gcc -g -std=gnu99 -c --save-temps matmul_test/matmul_test.c -I scadelin --include scadelin/scadelin_glue.h -o matmul_test.o
gcc -g -std=gnu99 -c --save-temps scadelin/scadelin_mat.c -L scadelin -o scadelin_mat.o
gcc -g -std=gnu99 -c --save-temps scadelin/scadelin_glue.c -L scadelin -o scadelin_glue.o
gcc -g -std=gnu99 --save-temps -I scadelin -I matmul_test matmul_main.c scadelin_mat.o scadelin_glue.o matmul_test.o -o matmul_main.exe

# ./matmul_main.exe

# nemiver ./matmul_main.exe