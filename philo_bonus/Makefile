CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

TARGET = philo_bonus

SRCS = philo_bonus.c sem_utils_bonus.c \
		ph_setup_bonus.c ph_execution_bonus.c \
		ph_actions_bonus.c utils_bonus.c

OBJS = $(SRCS:.c=.o)

HEADER = philo_bonus.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re