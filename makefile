Input = main.cpp GetFromFile.cpp
Out = Main
CC = g++
Links = `pkg-config --cflags --libs gtk+-2.0` 
GTK+: $(Input)
	$(CC) $(Input) -o $(Out) $(Links)
