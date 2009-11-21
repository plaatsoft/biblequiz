.rodata
.balign 32
.globl pic42length
.globl pic42data

pic42length:	.long	picdataend - pic42data
pic42data:
.incbin "../images/logo5.jpg"
picdataend:


