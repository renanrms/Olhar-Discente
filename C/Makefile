# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# EEL270 - Computacao II - Turma 2016/1
# Prof. Marcelo Luiz Drumond Lanza
#
# $Author$
# $Date$
# $Log$
#

CC = gcc
LD = gcc

CFLAGS = -Wall -ansi
LFLAGS = -Wall -ansi

DIC_ROOT = /users/renan.passos/private/EEL270/2016-1/DIC
DIC_WEB_ROOT = /users/renan.passos/public/html/DIC

DIC_HTMLTOC_OBJS = dicHtmlToC.o
DIC_MAIN_OBJS = dicCgiMain.o dicUserInterface.o dicFunctions.o 
DIC_SHOWREQUESTREGISTRATIONFORM_OBJS = dicCgiShowRequestRegistrationForm.o dicUserInterface.o dicFunctions.o
DIC_SHOWREQUESTPASSWORDRESETFORM_OBJS = dicCgiShowRequestPasswordResetForm.o dicUserInterface.o dicFunctions.o
DIC_SHOWWEBHELP_OBJS = dicCgiShowWebHelp.o dicUserInterface.o dicFunctions.o dicErrors.o
DIC_SHOWLICENSE_OBJS = dicCgiShowLicense.o dicUserInterface.o dicFunctions.o dicErrors.o

HTMLTOC = dicHtmlToC

CGIS = dicMain.cgi\
       dicShowRequestRegistrationForm.cgi\
       dicShowRequestPasswordResetForm.cgi\
       dicShowWebHelp.cgi\
       dicShowLicense.cgi

EXECS = $(HTMLTOC)\
        $(CGIS)

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(EXECS)

clean:
	rm -f *.o $(EXECS)


dicHtmlToC: $(DIC_HTMLTOC_OBJS)
	$(LD) $(LFLAGS) -o $@ $(DIC_HTMLTOC_OBJS)

dicMain.cgi: $(DIC_MAIN_OBJS)
	$(LD) $(LFLAGS) -o $@ $(DIC_MAIN_OBJS) -L./Libraries -lmlcgi

dicShowRequestRegistrationForm.cgi: $(DIC_SHOWREQUESTREGISTRATIONFORM_OBJS)
	$(LD) $(LFLAGS) -o $@ $(DIC_SHOWREQUESTREGISTRATIONFORM_OBJS) -L./Libraries -lmlcgi

dicShowRequestPasswordResetForm.cgi: $(DIC_SHOWREQUESTPASSWORDRESETFORM_OBJS)
	$(LD) $(LFLAGS) -o $@ $(DIC_SHOWREQUESTPASSWORDRESETFORM_OBJS) -L./Libraries -lmlcgi

dicShowWebHelp.cgi: $(DIC_SHOWWEBHELP_OBJS)
	$(LD) $(LFLAGS) -o $@ $(DIC_SHOWWEBHELP_OBJS) -L./Libraries -lmlcgi

dicShowLicense.cgi: $(DIC_SHOWLICENSE_OBJS)
	$(LD) $(LFLAGS) -o $@ $(DIC_SHOWLICENSE_OBJS) -L./Libraries -lmlcgi


install:
	make uninstall

	mkdir $(DIC_ROOT)/Binaries
	mkdir $(DIC_ROOT)/Data
	mkdir $(DIC_ROOT)/Data/Cookies
	mkdir $(DIC_WEB_ROOT)
	mkdir $(DIC_WEB_ROOT)/CGIs
	mkdir $(DIC_WEB_ROOT)/HTML

	cp $(DIC_ROOT)/Sources/C/dicMain.cgi $(DIC_WEB_ROOT)/CGIs/dicMain.cgi
	cp $(DIC_ROOT)/Sources/C/dicShowRequestRegistrationForm.cgi $(DIC_WEB_ROOT)/CGIs/dicShowRequestRegistrationForm.cgi
	cp $(DIC_ROOT)/Sources/C/dicShowRequestPasswordResetForm.cgi $(DIC_WEB_ROOT)/CGIs/dicShowRequestPasswordResetForm.cgi
	cp $(DIC_ROOT)/Sources/C/dicShowWebHelp.cgi $(DIC_WEB_ROOT)/CGIs/dicShowWebHelp.cgi
	cp $(DIC_ROOT)/Sources/C/dicShowLicense.cgi $(DIC_WEB_ROOT)/CGIs/dicShowLicense.cgi

	cp $(DIC_ROOT)/Sources/HTML/dicWebHelp_en-us.html $(DIC_WEB_ROOT)/HTML/dicWebHelp_en-us.html
	cp $(DIC_ROOT)/Sources/HTML/dicWebHelp_pt-br.html $(DIC_WEB_ROOT)/HTML/dicWebHelp_pt-br.html
	cp $(DIC_ROOT)/Sources/HTML/dicLicense_en-us.html $(DIC_WEB_ROOT)/HTML/dicLicense_en-us.html
	cp $(DIC_ROOT)/Sources/HTML/dicLicense_pt-br.html $(DIC_WEB_ROOT)/HTML/dicLicense_pt-br.html
	cp $(DIC_ROOT)/Sources/HTML/index_en-us.html $(DIC_WEB_ROOT)/HTML/index_en-us.html
	cp $(DIC_ROOT)/Sources/HTML/index_pt-br.html $(DIC_WEB_ROOT)/HTML/index_pt-br.html

uninstall:
	rm -rf $(DIC_ROOT)/Binaries
	rm -rf $(DIC_ROOT)/Data
	rm -rf $(DIC_WEB_ROOT)

#
#Modelos de link-edicao, compilacao de biblioteca e link-edicao com biblioteca
#
#aula0101: $(AULA0101OBJS)
#	$(LD) $(LFLAGS) -o $@ $?
#
#libmatematica.a: $(LIBMATEMATICAOBJS)
#	ar -r $@ $?
#
#aula0304a: $(AULA0304AOBJS)
#	$(LD) $(LFLAGS) -o $@ $? -L. -lmatematica
#


#$RCSfile$