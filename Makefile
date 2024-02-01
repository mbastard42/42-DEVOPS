#	COMPILED LANGUAGES ] ===========================================================================	#
#	                                           [  CONFIG  ] ========================================	#
#	======================================================================================= [  LEAVE	#
#																										#
#	                                     [  NAME AND LOCATION  ] ===================================	#
BDIR	:=	bin/
NAME	:=	$(BDIR)ft_ping
#	                                           [  FILES  ] =========================================	#
FILE	:=	c
SDIR	:=	src/
COMP	:=	o
ODIR	:=	.obj/
#	                                          [  COMPILER  ] =======================================	#
CC		:=	gcc
CFLG	:=	-Wall -Wextra -Werror
LFLG	:=	-fsanitize=address
#																										#
#	============================================================================== [  MAKEFILE UTILS	#
#																										#
MAKEFLAGS	+=	--silent
RESET		:=	\033[0m
BOLD		:=	\033[1m
ITALIC		:=	\033[3m
GREY		:=	\033[90m
RED			:=	\e[0;31m
YELLOW		:=	\e[0;33m
GREEN		:=	\e[0;32m
#																										#
SRCS		:=	$(shell find $(SDIR) -name "*.$(FILE)")
OBJS		:=	$(subst $(SDIR),$(ODIR), ${SRCS:.$(FILE)=.$(COMP)})
#																										#
#	============================================================================== [  MAKEFILE RULES	#
#																										#
$(ODIR)%.$(COMP)	:	$(SDIR)%.$(FILE)
#																										#
	mkdir -p $(subst $(SDIR),$(ODIR), $(shell dirname $<)/)
	$(CC) $(CFLG) -c $< -o ${addprefix $(ODIR), ${<:$(SDIR)%.$(FILE)=%.$(COMP)}}
	echo "build\t\t$(YELLOW)compiled$(RESET)\t$(GREY)$(ODIR)${<:$(SDIR)%.$(FILE)=%.$(COMP)}$(RESET)"
#																										#
${NAME}				:	$(OBJS)
#																										#
	mkdir -p $(BDIR)
	$(CC) $(CFLG) $(LFLG) $(OBJS) -o $(NAME)
	echo "$(GREEN)build\t\tlinked\t\t$(BOLD)$(NAME)$(RESET)"
#																										#
print	:
#																										#
	echo "$(BOLD)RULE\t\tACTION\t\tTARGET$(RESET)"
#																										#
build	:	print ${NAME}
#																										#
clean	:	print
#																										#
	rm -rf $(ODIR)
	echo "$(GREY)clean$(RESET)\t\t$(RED)deleted$(RESET)\t\t$(ODIR)"
#																										#
fclean	:	print clean
#																										#
	rm -rf $(BDIR)
	echo "$(GREY)fclean$(RESET)\t\t$(RED)deleted$(RESET)\t\t$(BDIR)"
#																										#
.PHONY	:	print build clean fclean
#																										#
re		:	print fclean build
#																										#
all		:	print build clean
#																										#
#	                                       [  CUSTOM RULES  ] ======================================	#
#																										#
bonus	:	build																						#
#																										#
ping	:
#																										#
	tar -zxvf inetutils-2.0.tar.gz
	cd inetutils-2.0 && ./configure \
		--prefix=/usr				\
		--localstatedir=/var 		\
		--disable-logger     		\
		--disable-whois      		\
		--disable-rcp        		\
		--disable-rexec      		\
		--disable-rlogin     		\
		--disable-rsh        		\
		--disable-servers
	cd inetutils-2.0 && make && sudo make install
#																										#
.PHONY	:	re all bonus ping
#																										#
#	===================================================================================== [ MAKEFILE	#
