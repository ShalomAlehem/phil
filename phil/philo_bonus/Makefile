# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 10:53:57 by dpowdere          #+#    #+#              #
#    Updated: 2021/09/18 15:08:12 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus
SRCS := \
  philo_bonus.c \
  clean_up.c \
  configure.c \
  eat.c \
  error.c \
  get_number.c \
  get_semname.c \
  philosopher.c \
  satiety_controller.c \
  state_notify.c \
  time.c \
  wait_for.c

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
