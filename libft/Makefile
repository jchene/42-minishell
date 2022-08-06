# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 00:39:01 by anguinau          #+#    #+#              #
#    Updated: 2022/08/06 11:38:58 by anguinau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME			=	libft.a
SRCSDIR			=	srcs
INCLUDESDIR		=	includes
OBJSDIR			=	objs
CFLAGS			=	-Wall -Wextra -Werror -g #-fsanitize=address
CC				=	gcc
RM				=	rm -rf

SRCS			=	$(shell find $(SRCSDIR) -type f -name "*.c")
INCLUDES		=	$(shell find $(INCLUDESDIR) -type f -name "*.h")
OBJS			=	$(subst $(SRCSDIR),$(OBJSDIR),$(SRCS:.c=.o))

INDEX			=	0
BUILD_SIZE		=	$(shell ls srcs | wc -l)

_STOP			=	\e[0m
_RED			=	\e[91m
_YELLOW			=	\e[93m
_GREEN			=	\e[92m
E_BAR			=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[                              ]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)


# Bar displayer

define update_bar =
	progress =	$(shell echo "$(INDEX) * 35 / $(BUILD_SIZE)" | bc)
	ifeq ($(progress), 0)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)                                 $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)0%]$(_STOP)
	else ifeq ($(progress), 1)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)o                                $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)3%]$(_STOP)
	else ifeq ($(progress), 2)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)oo                               $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)6%]$(_STOP)
	else ifeq ($(progress), 3)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)ooo                              $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)9%]$(_STOP)
	else ifeq ($(progress), 4)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)oooo                             $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)12%$(_STOP)]
	else ifeq ($(progress), 5)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)ooooo                            $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)15%$(_STOP)]
	else ifeq ($(progress), 6)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)oooooo                           $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)18%$(_STOP)]
	else ifeq ($(progress), 7)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)ooooooo                          $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)21%$(_STOP)]
	else ifeq ($(progress), 8)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)oooooooo                         $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)24%$(_STOP)]
	else ifeq ($(progress), 9)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)ooooooooo                        $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)27%$(_STOP)]
	else ifeq ($(progress), 10)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_RED)oooooooooo                       $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_RED)30%$(_STOP)]
	else ifeq ($(progress), 11)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)ooooooooooo                      $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)33%$(_STOP)]
	else ifeq ($(progress), 12)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)oooooooooooo                     $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)36%$(_STOP)]
	else ifeq ($(progress), 13)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)ooooooooooooo                    $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)39%$(_STOP)]
	else ifeq ($(progress), 14)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)oooooooooooooo                   $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)42%$(_STOP)]
	else ifeq ($(progress), 15)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)ooooooooooooooo                  $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)45%$(_STOP)]
	else ifeq ($(progress), 16)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)oooooooooooooooo                 $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)48%$(_STOP)]
	else ifeq ($(progress), 17)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)ooooooooooooooooo                $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)51%$(_STOP)]
	else ifeq ($(progress), 18)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)oooooooooooooooooo               $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)54%$(_STOP)]
	else ifeq ($(progress), 19)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)ooooooooooooooooooo              $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)57%$(_STOP)]
	else ifeq ($(progress), 20)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)oooooooooooooooooooo             $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)60%$(_STOP)]
	else ifeq ($(progress), 21)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)ooooooooooooooooooooo            $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)63%$(_STOP)]
	else ifeq ($(progress), 22)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_YELLOW)oooooooooooooooooooooo           $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_YELLOW)66%$(_STOP)]
	else ifeq ($(progress), 23)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)ooooooooooooooooooooooo          $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)69%$(_STOP)]
	else ifeq ($(progress), 24)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)oooooooooooooooooooooooo         $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)72%$(_STOP)]
	else ifeq ($(progress), 25)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)ooooooooooooooooooooooooo        $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)75%$(_STOP)]
	else ifeq ($(progress), 26)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)oooooooooooooooooooooooooo       $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)78%$(_STOP)]
	else ifeq ($(progress), 27)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)ooooooooooooooooooooooooooo      $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)81%$(_STOP)]
	else ifeq ($(progress), 28)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)oooooooooooooooooooooooooooo     $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)84%$(_STOP)]
	else ifeq ($(progress), 29)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)ooooooooooooooooooooooooooooo    $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)87%$(_STOP)]
	else ifeq ($(progress), 30)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)oooooooooooooooooooooooooooooo   $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)90%$(_STOP)]
	else ifeq ($(progress), 31)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)ooooooooooooooooooooooooooooooo  $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)93%$(_STOP)]
	else ifeq ($(progress), 32)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)oooooooooooooooooooooooooooooooo $(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)96%$(_STOP)]
	else ifeq ($(progress), 33)
		E_BAR	=	$(_RED)-$(_YELLOW)-$(_GREEN)>$(_STOP)[$(_GREEN)ooooooooooooooooooooooooooooooooo$(_STOP)]$(_GREEN)<$(_YELLOW)-$(_RED)-$(_STOP)[$(_GREEN)100%$(_STOP)]
	endif
endef


# Rules

all				:	$(NAME)

$(NAME)			:	$(OBJSDIR) $(OBJS)
					@ar rcs $(NAME) $(OBJS)
					@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
					@$(eval BUILD_SIZE=$(shell echo $$(($(BUILD_SIZE)+1))))
					@echo -ne '	                                                \r'
					@echo -e '	$(NAME) $(_GREEN)created$(_STOP).'
					@echo -e '	[$(_GREEN)100%$(_STOP)]'
					@$(eval $(call update_bar))

$(OBJSDIR)		:
					@mkdir $(OBJSDIR)
					@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
					@$(eval BUILD_SIZE=$(shell echo $$(($(BUILD_SIZE)+1))))
					@echo -ne '	                                                \r'
					@echo -e '	objs directory $(_GREEN)created$(_STOP).'
					@echo -ne '	$(E_BAR)\r'
					@$(eval $(call update_bar))

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c $(INCLUDES)
					@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -include $(INCLUDES)
					@mv $(SRCSDIR)/*.o $(OBJSDIR)
					@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
					@echo -ne '	                                                \r'
					@echo -e '	$@ $(_GREEN)created$(_STOP).'
					@echo -ne '	$(E_BAR)\r'
					@$(eval $(call update_bar))

ifeq	($(shell ls | grep objs), objs)
clean			:
					@$(RM) $(OBJSDIR)
					@echo -ne '	                                                \r'
					@echo -e '	objs directory $(_GREEN)removed$(_STOP).'
endif

fclean			:	clean
					@$(RM) $(NAME)
					@echo -ne '	                                                \r'
					@echo -e '	$(NAME) $(_GREEN)removed$(_STOP).'

re				:	fclean all

.PHONY			:	all bonus clean fclean re
