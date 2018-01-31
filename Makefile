obj-win = ws.o functions.o win.o
obj-linux = ws.o functions.o linux.o

ws-linux : $(obj-linux)
	gcc -o ws $(obj-linux)

ws-win : $(obj-win)
	gcc -o ws $(obj-win)

ws.o : ws.c ws.h
	gcc -c -g ws.c

functions.o : ./functions/functions.c ./functions/functions.h
	gcc -c -g ./functions/functions.c

functions : ./functions/functions.c ./functions/functions.h
	gcc -c -g ./functions/functions.c win.o

linux.o : ./platform/linux.c ./platform/platform.h
	gcc -c -g ./platform/linux.c

win.o : ./platform/win.c ./platform/platform.h
	gcc -c -g ./platform/win.c

clean-all : 
	rm ws $(obj-linux) $(obj-win)

clean-o :
	rm $(obj-linux) $(obj-win)