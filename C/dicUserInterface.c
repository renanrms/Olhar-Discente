/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicUserInterface.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdlib.h>

#include "dicUserInterface.h"
#include "dicTypes.h"

char *dicUserProfileStrings [dicLanguagesAmount][dicUserProfilesAmountMoreOne - 1] =
{
   {
      "administrator",
      "teacher",
      "administrator_teacher",
      "student",
      "administrator_student",
      "teacher_student",
      "administrator_teacher_student"
   },
   {
      "administrador",
      "professor",
      "administrador_professor",
      "estudente",
      "adminstrador_estudante",
      "professor_estudante",
      "adminstrador_professor_estudante"
   }
};

char *dicCliUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      NULL,
      NULL,
      /*Web and Ncurses fields*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      /*Web links and Ncurses options*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      /*Web and Ncurses buttons*/
      NULL,
      NULL,
      NULL,
      /*Event and notification massages*/
      "Operation was successful",
      "For Help",
      "Successfully authenticated user"
   },
   {
      NULL,
      NULL,
      /*Web and Ncurses fields*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      /*Web links and Ncurses options*/
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      /*Web and Ncurses buttons*/
      NULL,
      NULL,
      NULL,
      /*Event and notification massages*/
      "Operação realizada com sucesso",
      "Para ver a ajuda",
      "Usuário autenticado com sucesso"
   }
};

char *dicNcursesUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "English",
      "Portuguese",
      /*Web and Ncurses fields*/
      "Login",
      "Password",
      "Password confirmation",
      "Temporary password",
      "Username",
      "Username confirmation",
      "E-mail",
      "E-mail confirmation",
      /*Web links and Ncurses options*/
      "Contact us",
      "License",
      "Home",
      "Reset password",
      "Create an account",
      "Help",
      /*Web and Ncurses buttons*/
      "Sign In",
      "Send",
      "Register",
      /*Event and notification massages*/
      "Operation was successful",
      "For Help",
      "Successfully authenticated user"
   },
   {
      "Englês",
      "Português",
      /*Web and Ncurses fields*/
      "Usu&aacuterio",
      "Senha",
      "Confirmação de senha",
      "Senha temporária",
      "Nome completo",
      "Confirmação do nome",
      "E-mail",
      "Confirmação do e-mail",
      /*Web links and Ncurses options*/
      "Contacte-nos",
      "Licença",
      "Tela Principal",
      "Reiniciar senha",
      "Criar uma conta",
      "Ajuda",
      /*Web and Ncurses buttons*/
      "Entrar",
      "Enviar",
      "Cadastrar",
      /*Event and notification massages*/
      "Operação realizada com sucesso",
      "Para ver a ajuda",
      "Usuário autenticado com sucesso"
   }
};

char *dicWebUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "English",
      "Portugu&ecircs",
      /*Web and Ncurses fields*/
      "Login",
      "Password",
      "Password confirmation",
      "Temporary password",
      "Username",
      "Confirmation",
      "E-mail",
      "Confirmation",
      /*Web links and Ncurses options*/
      "Contact us",
      "License",
      "Home",
      "Forgot my password",
      "Create an account",
      "Help",
      /*Web and Ncurses buttons*/
      "Sign In",
      "Send",
      "Register",
      /*Event and notification massages*/
      "Operation was successful",
      "For Help",
      "Successfully authenticated user"
   },
   {
      "English",
      "Portugu&ecircs",
      /*Web and Ncurses fields*/
      "Usu&aacuterio",
      "Senha",
      "Confirma&ccedil&atildeo de senha",
      "Senha tempor&aacuteria",
      "Nome completo",
      "Confirma&ccedil&atildeo",
      "E-mail",
      "Confirma&ccedil&atildeo",
      /*Web links and Ncurses options*/
      "Contacte-nos",
      "Licen&ccedila",
      "P&aacutegina Principal",
      "Esqueci minha senha",
      "Criar uma conta",
      "Ajuda",
      /*Web and Ncurses buttons*/
      "Entrar",
      "Enviar",
      "Cadastrar",
      /*Event and notification massages*/
      "Opera&ccedil&atildeo realizada com sucesso",
      "Para ver a ajuda",
      "Usu&aacuterio autenticado com sucesso"
   }
};

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
DicGetUserProfileString (dicUserProfileType dicUserProfile, dicLanguageType dicLanguage)
{
   return dicUserProfileStrings [dicLanguage][dicUserProfile - 1];
}

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
DicGetCliUserInterfaceMessage (dicUserInterfaceMessageType dicUserInterfaceMessage, dicLanguageType dicLanguage)
{
   return dicCliUserInterfaceMessages [dicLanguage][dicUserInterfaceMessage];
}

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
DicGetNcursesUserInterfaceMessage (dicUserInterfaceMessageType dicUserInterfaceMessage, dicLanguageType dicLanguage)
{
   return dicNcursesUserInterfaceMessages [dicLanguage][dicUserInterfaceMessage];
}

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
DicGetWebUserInterfaceMessage (dicUserInterfaceMessageType dicUserInterfaceMessage, dicLanguageType dicLanguage)
{
   return dicWebUserInterfaceMessages [dicLanguage][dicUserInterfaceMessage];
}


/*$RCSfile: dicUserInterface.c,v $*/
