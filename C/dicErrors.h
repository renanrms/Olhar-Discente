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

#ifndef DIC_ERRORS_H
#define DIC_ERRORS_H "@(#)dicErrors.h $Revision$"

#include "dicTypes.h"

typedef enum
{
	dicOk,
	dicInvalidSuboption,
	dicInvalidOption,
	dicHasRequiredArguments,
	dicHaveNotPermission,
	dicHelpNotFound,
	dicLicenseNotFound,
	dicInvalidCaracter,
	dicInvalidLength,
	dicOverPoint,
	dicNoPoint,
	dicOverArroba,
	dicNoArroba,
	dicEmptyUsername,
	dicEmptyLastName,
	dicOverLengthNames,
	dicInvalidEmailConfirmation,
	dicUserEmailAlreadyRegistered,
	dicInvalidPasswordConfirmation,
	dicIcorrectPassword,
	dicInvalidArgument,
	dicEmptyUsersFile,
	dicUsersFileNotExist,
	dicNicknameNotExist,
	dicErrorCodesAmount
} dicErrorType;


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
DicGetCliErrorMessage (dicErrorType, dicLanguageType);

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
DicGetNcursesErrorMessage (dicErrorType, dicLanguageType);

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
DicGetWebErrorMessage (dicErrorType, dicLanguageType);

#endif 

/*$RCSfile$*/
