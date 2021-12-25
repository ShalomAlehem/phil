# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 13:10:07 by dpowdere          #+#    #+#              #
#    Updated: 2021/09/13 01:18:59 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
SRCS := \
  philo.c \
  clean_up.c \
  eat.c \
  error.c \
  get_number.c \
  philosopher.c \
  state_notify.c \
  time.c

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -MMD
LDLIBS := -lpthread

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

ifneq ($(findstring linux,$(shell $(CC) -dumpmachine)),)
  define ON_LINUX =

    We are on linux!

    Just a quick reminder on how to define
    a multiline variable value in Makefiles.

    See https://www.gnu.org/software/make/manual/html_node/Multi_002dLine.html

  endef
endif

ifdef ON_LINUX
  CPPFLAGS += -pthread
  LDFLAGS += -pthread
endif

ifdef DEBUG
  CC += -g3
endif

.PHONY: all clean debug fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

#%.o: %.c
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) -r $(NAME) *.dSYM core* vgcore*

re: fclean $(NAME)

debug: CC += -g3
debug: re

-include $(DEPS)
