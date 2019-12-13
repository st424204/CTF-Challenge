

all: read_flag app

app: app.c
	gcc -no-pie -fno-stack-protector -o app app.c
read_flag: read_flag.c
	gcc read_flag.c -o read_flag

install:
	echo "FLAG{aaaaaaaaaaaaaaaaaaaaa}" > flag
	apt install apparmor-profiles
	chown root:root flag
	chmod 0400 flag
	chmod +s read_flag
	rm /usr/bin/read_flag
	ln -s `pwd`/read_flag /usr/bin/
	aa-autodep read_flag
	aa-enforce read_flag

clean:
	rm app read_flag flag

