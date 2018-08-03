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

char *dicUserProfileStrings [dicLanguagesAmount][dicUserProfilesAmountMoreOne - 1] =
{
   {
      "administrator",
      "teacher",
      "teacher_administrator",
      "student",
      "student_administrator",
      "student_teacher",
      "student_teacher_administrator"
   },
   {
      "administrador",
      "professor",
      "professor_administrador",
      "estudente",
      "estudente_administrador",
      "estudente_professor",
      "estudente_professor_administrador"
   }
};

char *dicCliUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "",
      "",
      "",
      "Password: ",
      "Password confirmation: ",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "For help",
      "User successfully created"
   },
   {
      "",
      "",
      "",
      "Senha",
      "Confirmacao de senha",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "Para ver a ajuda",
      "Usuario criado com sucesso"
   }
};

char *dicNcursesUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      ""
   },
   {
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      ""
   }
};

char *dicWebUserInterfaceMessages [dicLanguagesAmount][dicUserInterfaceMessagesAmount] =
{
   {
      "English",
      "Portugu&ecircs",
      "Login",
      "Password",
      "Password confirmation",
      "Sign In",
      "Forgot my password",
      "License",
      "Create an account",
      "Help",
      "Contact us",
      "User name",
      "User name confirmation",
      "E-mail",
      "E-mail confirmation",
      "Register",
      "Home",
      "Send",
      "",
      "",
      "",
      "",
      ""
   },
   {
      "English",
      "Portugu&ecircs",
      "Usu&aacuterio",
      "Senha",
      "Confirma&ccedil&atildeo de senha",
      "Entrar",
      "Esqueci minha senha",
      "Licen&ccedila",
      "Cadastrar",
      "Ajuda",
      "Contacte-nos",
      "Nome de usu&aacuterio",
      "Confirma&ccedil&atildeo do nome de usu&aacuterio",
      "E-mail",
      "Confirma&ccedil&atildeo do E-mail",
      "Cadastrar",
      "P&aacutegina Principal",
      "Enviar"
      "",
      "",
      "",
      "",
      ""
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


/*$RCSfile$*/
