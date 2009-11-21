.rodata
.balign 32
.globl xml2length
.globl xml2data

xml2length:	.long	xmldataend - xml2data
xml2data:
.incbin "../xml/english.xml"
xmldataend:


