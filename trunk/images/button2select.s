.rodata
.balign 32
.globl pic5length
.globl pic5data

pic5length:	.long	picdataend - pic5data
pic5data:
.incbin "../images/button2select.png"
picdataend:


