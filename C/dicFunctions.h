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

#ifndef DIC_FUNCTIONS_H
#define DIC_FUNCTIONS_H "@(#)dicFunctions.h $Revision$"

#include "dicTypes.h"

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
DicGetLanguageIndex (char *);

#endif 

/*$RCSfile$*/
