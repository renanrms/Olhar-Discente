/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicUserInterface.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_USERINTERFACE_H
#define DIC_USERINTERFACE_H "@(#)dicUserInterface.h $Revision: 1.1 $"

#include "dicTypes.h"

typedef enum 
{
   dicEnglishMessage,
   dicPortugueseMessage,
   /*Web and Ncurses fields*/
   dicLoginMessage,
   dicPasswordMessage,
   dicPasswordConfirmationMessage,
   dicTempPasswordMessage,
   dicUserNameMessage,
   dicUserNameConfirmationMessage,
   dicEmailMessage,
   dicEmailConfirmationMessage,
   /*Web links and Ncurses options*/
   dicContactUsMessage,
   dicTermsOfUseMessage,
   dicHomeMessage,
   dicForgotMyPasswordMessage,
   dicCreateAnAccountMessage,
   dicHelpMessage,
   /*Web and Ncurses buttons*/
   dicSignInButtonMessage,
   dicSendButtonMessage,
   dicRegisterButtonMessage,
   /*Event and notification massages*/
   dicSuccessMessage,
   dicForHelpMessage,
   dicCorrectAuthenticateMessage,
   /*Number of messages*/
   dicUserInterfaceMessagesAmount
} dicUserInterfaceMessageType;


/*
 * char *
 * DicGetUserProfileString (dicUserProfileType, dicLanguageType);
 *
 * Arguments:
 * dicUserProfileType - profile
 * dicLanguageType - language
 *
 * Returned values:
 * char * - profile string
 *
 * Description:
 * This function returns the string of the profile in a language.
 */
char *
DicGetUserProfileString (dicUserProfileType, dicLanguageType);

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

/*$RCSfile: dicUserInterface.h,v $*/
