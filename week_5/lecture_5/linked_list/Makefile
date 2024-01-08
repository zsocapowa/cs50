# Define the C compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any libraries to link
LIBS = -lcs50

# Phony targets
.PHONY: tree linked_list

tree:
	$(CC) $(CFLAGS) -o $@ tree.c $(LIBS)

linked_list:
	$(CC) $(CFLAGS) -o $@ linked_list.c $(LIBS)
