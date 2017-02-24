
APP = user

all:
	gcc -o $(APP) user.c -pthread -Wall

clean:
	rm -f $(APP)
