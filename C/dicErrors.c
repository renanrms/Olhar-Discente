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

#include "dicErrors.h"
#include "dicTypes.h"

char *DicCliErrorMessages [dicLanguagesAmount][dicErrorCodesAmount] = 
{
   {
      "Ok",
      "File error",
      ""
   },
   {
      "Sucesso",
      "Erro relacionado com arquivo",
      ""
   }
};

char *DicNcursesErrorMessages [dicLanguagesAmount][dicErrorCodesAmount] = 
{
   {
      "Ok",
      "File error",
      ""
   },
   {
      "Sucesso",
      "Erro relacionado com arquivo",
      ""
   }
};


char *DicWebErrorMessages [dicLanguagesAmount][dicErrorCodesAmount] = 
{
   {
      "Ok",
      "sorry, the file containing the help in this language was not found.",
      "sorry, the file containing the license in this language was not found."
   },
   {
      "Sucesso",
      "Desculpe, o arquivo que cont&eacutem a ajuda neste idioma n&atildeo foi encontrado.",
      "Desculpe, o arquivo que cont&eacutem a licensa neste idioma n&atildeo foi encontrado."
   }
};


/* 
 * char *
 * DicGetCliErrorMessage (dicErrorType, dicLanguageType);
 *
 * Arguments:
 * dicErrorType - Error code (I)
 * dicLanguageType - Language of error mensage (I)
 *
 * Returned value:
 * char * - error mensage
 * 
 * Description:
 * This function gives the error mensage for CLI
 */
char *
DicGetCliErrorMessage (dicErrorType dicError, dicLanguageType dicLanguage)
{
   return DicCliErrorMessages [dicLanguage][dicError];
}

/*
 * char *
 * DicGetNcursesErrorMessage (dicErrorType, dicLanguageType);
 *
 * Arguments:
 * dicErrorType - Error code (I)
 * dicLanguageType - Language of error mensage (I)
 *
 * Returned value:
 * char * - error mensage
 *
 * Description:
 * This function gives the error mensage for Ncurses interface
 */
char *
DicGetNcursesErrorMessage (dicErrorType dicError, dicLanguageType dicLanguage)
{
   return DicNcursesErrorMessages [dicLanguage][dicError];
}

/*
 * char *
 * DicGetWebErrorMessage (dicErrorType, dicLanguageType);
 *
 * Arguments:
 * dicErrorType - Error code (I)
 * dicLanguageType - Language of error mensage (I)
 *
 * Returned value:
 * char * - error mensage
 *
 * Description:
 * This function gives the error mensage for web interface
 */
char *
DicGetWebErrorMessage (dicErrorType dicError, dicLanguageType dicLanguage)
{
   return DicWebErrorMessages [dicLanguage][dicError];
}

/*$RCSfile$*/
