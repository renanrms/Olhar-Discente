/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicShowCliHelp.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "dicShowCliHelp.h"
#include "dicFunctions.h"
#include "dicConfig.h"
#include "dicConst.h"
#include "dicErrors.h"
#include "dicTypes.h"

void
DicShowCliHelp (dicLanguageType dicLanguage)
{
	FILE *dicCliHelpFile;
	char dicTextLine [DIC_TEXT_PARAGRAPH_MAX_LENGTH + 1];

	if (dicLanguage == dicEnglish)
	{
		dicCliHelpFile = fopen ("./dicCliHelp_en-us.txt", "r");
	}
	else
	{
		dicCliHelpFile = fopen ("./dicCliHelp_pt-br.txt", "r");
	}

	if (dicCliHelpFile == NULL)
		printf ("%s\n", DicGetCliErrorMessage (dicHelpNotFound, dicLanguage));
	else
	{
		printf ("--help ------------------------------------------------------\n");
		while (fgets (dicTextLine, DIC_TEXT_PARAGRAPH_MAX_LENGTH + 1, dicCliHelpFile) != NULL)
			printf ("%s", dicTextLine);
		printf ("\n--help ------------------------------------------------------\n");
	}
}

/*$RCSfile: dicShowCliHelp.c,v $*/
