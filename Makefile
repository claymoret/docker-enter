all: importenv

importenv: importenv.c
	gcc importenv.c -o importenv

clean:
	rm -f importenv

install:
	cp docker-enter importenv /usr/local/bin
