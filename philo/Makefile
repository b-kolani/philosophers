CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

TARGET = philo

SRCS = philo.c \
       time_utils.c \
       string_utils.c \
       resrcs_management.c \
       fork_utils.c \
       ph_setup.c \
       lock_management.c \
       ph_execution.c \
       ph_actions.c \

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

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