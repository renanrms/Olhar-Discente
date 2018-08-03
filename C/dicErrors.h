/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicErrors.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_ERRORS_H
#define DIC_ERRORS_H "@(#)dicErrors.h $Revision: 1.1 $"

#include "dicTypes.h"

typedef enum
{
	dicOk,
	dicInvalidArgument,
	dicNoOptionEntered,
	dicInvalidOption,
	dicInvalidSuboption,
	dicInvalidProfile,
	dicHasRequiredArguments,
	dicHaveNotPermission,
	dicHelpNotFound,
	dicLicenseNotFound,
	dicInvalidCaracter,
	dicInvalidLength,
	dicInvalidNickname,
	dicInvalidEmail,
	dicInvalidUsername,
	dicEmptyUsername,
	dicEmptyLastName,
	dicOverLengthNames,
	dicInvalidEmailConfirmation,
	dicUserEmailAlreadyRegistered,
	dicUserEmailNotFound,
	dicInvalidPassword,
	dicInvalidPasswordConfirmation,
	dicIncorrectPassword,
	dicEmptyUsersFile,
	dicUsersFileNotExist,
	dicRequestingUsersFileNotExist,
	dicNicknameNotExist,
	dicUserAlreadyRegistered,
	dicNotInvitedUser,
	dicNotPermitedProfileRequest,
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

/*$RCSfile: dicErrors.h,v $*/
