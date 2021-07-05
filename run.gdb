# run.gdb
target remote localhost:3333
monitor reset halt
load
break mainprog
