/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
#include <stdlib.h>

#include "dicTypes.h"
#include "dicShowCliHelp.h"
#include "dicFunctions.h"
#include "dicConst.h"
#include "dicConfig.h"

void
DicShowCliHelp (dicLanguageType dicLanguage)
{
	FILE *dicCliHelpFile;
	char dicTextLine [DIC_TEXT_PARAGRAPH_MAX_LENGTH + 1];

	if (dicLanguage == dicEnglish)
	{
		dicCliHelpFile = fopen (DicGetAbsolutFileName (DIC_PRIVATE_ROOT_DIRECTORY, "Binaries/dicCliHelp_en-us.txt"), "r");
	}
	else
	{
		dicCliHelpFile = fopen (DicGetAbsolutFileName (DIC_PRIVATE_ROOT_DIRECTORY, "Binaries/dicCliHelp_pt-br.txt"), "r");
	}

	while (fgets (dicTextLine, DIC_TEXT_PARAGRAPH_MAX_LENGTH + 1, dicCliHelpFile) != NULL)
		printf ("%s", dicTextLine);
}

/*$RCSfile$*/
