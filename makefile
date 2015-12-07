client.o: client.c board.o game.o server.o game_client.o client_old.o
	gcc client.c board.o game.o game_client.c -o client.o 
	
client_old.o: client_old.c board.o game.o game_server.o
	gcc client_old.c board.o game.o game_server.c -o client_old.o 
	
server.o: server.c board.o game.o game_server.o
	gcc server.c board.o game.o game_server.c -o server.o 
	
clean:
	rm -f *.o

game_server.o: game_server.c 
	gcc -c game_server.c -o game_server.o
    
game_client.o: game_client.c
	gcc -c game_client.c -o game_client.o
    
game.o: board.o game.c
	gcc -c game.c board.o -o game.o 
	
board.o: board.c
	gcc -c board.c -o board.o 

