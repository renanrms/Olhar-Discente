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

#ifndef DIC_TYPES_H
#define DIC_TYPES_H "@(#)dicTypes.h $Revision$"

#include "dicConst.h"

typedef enum {dicEnglish, dicPortuguese, dicLanguagesAmount} dicLanguageType;

typedef unsigned long long dicUserIdentifierType;

typedef enum
{
	administrator=1,
	teacher,
	teacher_administrator,
	student,
	student_administrator,
	student_teacher,
	student_teacher_administrator
} dicUserProfileType;

typedef struct dicUserData
{
	dicUserIdentifierType userIdentifier;
	dicUserProfileType perfil;
	char nickname [DIC_NICKNAME_MAX_LENGTH + 1];
	char password [DIC_PASSWORD_MAX_LENGTH + 1];
	char passwordConfirmation [DIC_PASSWORD_MAX_LENGTH + 1];
	char username [DIC_FULLNAME_MAX_LENGTH + 1];
	char usernameConfirmation [DIC_FULLNAME_MAX_LENGTH + 1];
	char email [DIC_EMAIL_MAX_LENGTH + 1];
	char emailConfirmation [DIC_EMAIL_MAX_LENGTH + 1];
	struct dicUserData *next;
	struct dicUserData *previous; 
} dicUserDataType;

typedef enum
{
	dicLanguageArgument,
	dicNicknameArgument,
	dicUsernameArgument,
	dicUsernameConfirmationArgument,
	dicEmailArgument,
	dicEmailConfirmationArgument
} dicArgumentNameType;


#endif 

/*$RCSfile$*/
