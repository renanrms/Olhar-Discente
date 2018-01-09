/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef DIC_USERINTERFACE_H
#define DIC_USERINTERFACE_H "@(#)dicUserInterface.h $Revision$"

#include "dicTypes.h"

typedef enum 
{
   dicEnglishMessage,
   dicPortugueseMessage,
   dicLoginMessage,
   dicPasswordMessage,
   dicSignInButtonMessage,
   dicForgotMyPasswordMessage,
   dicTermsOfUseMessage,
   dicCreateAnAccountMessage,
   dicHelpMessage,
   dicContactUsMessage,
   dicFullNameMessage,
   dicFullNameConfirmationMessage,
   dicEmailMessage,
   dicEmailConfirmationMessage,
   dicRegisterButtonMessage,
   dicHomeMessage,
   dicSendButtonMessage,
   dicInvalidSuboption,     /*CLI message*/
   dicUserInterfaceMessagesAmount
} dicUserInterfaceMessageType;


/* 
 * char *
 * DicGetCliUserInterfaceMessage (dicUserInterfaceMessageType, dicLanguageType);
 *
 * Arguments:
 * dicUserInterfaceMessageType - message code (I)
 * dicLanguageType - message language (I)
 *
 * Returned value:
 * char * - message
 *
 * Description:
 * This function gives a message for CLI user interface.
 */
char *
DicGetCliUserInterfaceMessage (dicUserInterfaceMessageType, dicLanguageType);

/* 
 * char *
 * DicGetNcursesUserInterfaceMessage (dicUserInterfaceMessageType, dicLanguageType);
 *
 * Arguments:
 * dicUserInterfaceMessageType - message code (I)
 * dicLanguageType - message language (I)
 *
 * Returned value:
 * char * - message
 *
 * Description:
 * This function gives a message for Ncurses user interface.
 */
char *
DicGetNcursesUserInterfaceMessage (dicUserInterfaceMessageType, dicLanguageType);

/* 
 * char *
 * DicGetWebUserInterfaceMessage (dicUserInterfaceMessageType, dicLanguageType);
 *
 * Arguments:
 * dicUserInterfaceMessageType - message code (I)
 * dicLanguageType - message language (I)
 *
 * Returned value:
 * char * - message
 *
 * Description:
 * This function gives a message for web user interface.
 */
char *
DicGetWebUserInterfaceMessage (dicUserInterfaceMessageType, dicLanguageType); 

#endif 

/*$RCSfile$*/
