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

#include "dicFunctions.h"
#include "dicTypes.h"
#include "string.h"

/* 
 * dicLanguageType
 * DicGetLanguageIndex (char *);
 *
 * Arguments:
 * char * - string of language ("dicEnglish" ou "dicPortuguese") (I)
 *
 * Returned value:
 * dicEnglish - english language
 * dicPortuguese - portuguese language
 *
 * Description:
 * This function returns the language corresponds to string.
 */
dicLanguageType
DicGetLanguageIndex (char *dicLanguageString)
{
   if (!strcmp (dicLanguageString, "dicPortuguese"))
      return dicPortuguese;
   else
      return dicEnglish;
}


/*$RCSfile$*/
