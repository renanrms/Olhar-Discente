/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicTypes.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_TYPES_H
#define DIC_TYPES_H "@(#)dicTypes.h $Revision: 1.1 $"

#include "dicConst.h"

typedef enum {dicEnglish, dicPortuguese, dicLanguagesAmount} dicLanguageType;

typedef enum {dicDes, dicMd5 = 1, dicSha256 = 5, dicSha512 = 6} dicCryptAlgorithms;

typedef unsigned long long dicUserIdentifierType;

typedef enum
{
	dicAdministrator = 1,
	dicTeacher,
	dicTeacher_administrator,
	dicStudent,
	dicStudent_administrator,
	dicStudent_teacher,
	dicStudent_teacher_administrator,
	dicUserProfilesAmountMoreOne,
} dicUserProfileType;

typedef struct dicUserData
{
	dicUserIdentifierType userId;
	dicUserProfileType profile;
	char nickname [DIC_NICKNAME_MAX_LENGTH + 1];
	char password [DIC_PASSWORD_MAX_LENGTH + 1];
	char passwordConfirmation [DIC_PASSWORD_MAX_LENGTH + 1];
	char username [DIC_USERNAME_MAX_LENGTH + 1];
	char usernameConfirmation [DIC_USERNAME_MAX_LENGTH + 1];
	char email [DIC_EMAIL_MAX_LENGTH + 1];
	char emailConfirmation [DIC_EMAIL_MAX_LENGTH + 1];
	struct dicUserData *next;
	struct dicUserData *previous; 
} dicUserDataType;

typedef enum
{
	dicLanguageArgument,
	dicCurrentUserNicknameArgument,
	dicNicknameArgument,
	dicUsernameArgument,
	dicUsernameConfirmationArgument,
	dicEmailArgument,
	dicEmailConfirmationArgument,
	dicProfileArgument,
	dicFriendEmailArgument
} dicArgumentNameType;


#endif 

/*$RCSfile: dicTypes.h,v $*/
