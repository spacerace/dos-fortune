all:
	bcc -Md -ansi -0 -O -I./include/ -V -W -o fortune.com fortune.c
	ls -al fortune.com
	
upx:	all
	upx -9 fortune.com
	
dosbox:
	dosbox
	
