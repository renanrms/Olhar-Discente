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

#include "dicUserInterface.h"
#include "dicTypes.h"

char *dicCliUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "message 1",
      "message 2"
   },
   {
      "mensagem 1",
      "mensagem 2"
   }
};

char *dicNcursesUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "message 1",
      "message 2"
   },
   {
      "mensagem 1",
      "mensagem 2"
   }
};

char *dicWebUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "English",
      "Portugu&ecircs",
      "Login",
      "Password",
      "Sign In",
      "Forgot my password",
      "License",
      "Create an account",
      "Help",
      "Contact us",
      "Full name",
      "Full name confirmation",
      "E-mail",
      "E-mail confirmation",
      "Register",
      "Home",
      "Send"
   },
   {
      "English",
      "Portugu&ecircs",
      "Usu&aacuterio",
      "Senha",
      "Entrar",
      "Esqueci minha senha",
      "Licen&ccedila",
      "Cadastrar",
      "Ajuda",
      "Contacte-nos",
      "Nome completo",
      "Confirma&ccedil&atildeo do nome completo",
      "E-mail",
      "Confirma&ccedil&atildeo do E-mail",
      "Cadastrar",
      "P&aacutegina Principal",
      "Enviar"
   }
};


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


/*$RCSfile$*/
