/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicGetPendingRegistrationRequestsPerUser.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dicGetPendingRegistrationRequestsPerUser.h"
#include "dicGetUsers.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicTypes.h"
#include "dicConst.h"
#include "dicConfig.h"

/*
 * dicErrorType
 * DicGetPendingRegistrationRequestsPerUser (char*, dicUserDataType**);
 *
 * Arguments:
 * char* - responsible user nickname
 * dicUserDataType** - pointer to pointer to first element of requesting users linked list (O)
 *
 * Returned values:
 * dicOk - registration request was approved successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicRequestingUsersFileNotExist - the requesting users file not exist
 * dicUsersFileNotExist - the users file not exist
 * dicNicknameNotExist - the responsible user received not exist
 *
 * Description:
 * This function gives back a double linked list of register requestings of responsible user with all your data.
 * (If there are't requestings in your responsability, gives back NULL)
 */
dicErrorType
DicGetPendingRegistrationRequestsPerUser (char *dicResponsibleNickname, dicUserDataType **dicFirstRequestingUser)
{
	FILE *dicRequestingUsersFile;

	dicUserDataType *dicUser;
	dicUserDataType *dicFirstUser;
	dicUserDataType *dicRequestingUser;

	time_t dicAbsoluteValidityTime;
	dicUserIdentifierType dicUserId1;
	dicUserIdentifierType dicUserId2;
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];

	dicUserIdentifierType dicResponsibleUserId;

	unsigned char dicFoundResponsibleUser = 0;

	char *validation;
	size_t dicReadBytes;

	dicErrorType dicReturnCode;


	if (dicResponsibleNickname == NULL || dicFirstRequestingUser == NULL)
		return dicInvalidArgument;

	dicReturnCode = DicGetUsers (&dicFirstUser);
	if (dicReturnCode != dicOk)
		return dicReturnCode;

	dicUser = dicFirstUser;

	while (dicUser != NULL)
	{
		if (!strcmp (dicUser->nickname, dicResponsibleNickname))
		{
			dicFoundResponsibleUser = 1;
			dicResponsibleUserId = dicUser->userId;
			break;
		}
		dicUser = dicUser->next;
	}
	if (!dicFoundResponsibleUser)
		return dicNicknameNotExist;

	*dicFirstRequestingUser = NULL;
	dicRequestingUser = NULL;

	dicRequestingUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_REQUESTING_USERS_DATA_FILENAME), "r");
	if (dicRequestingUsersFile == NULL)
		return dicRequestingUsersFileNotExist;

	/*<validity><userId><encoded password>*/
	fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicRequestingUsersFile);
	fread (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
	fread (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
	dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicRequestingUsersFile);
	dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;

	/*obtains the list of not expired requests*/
	while (dicReadBytes == sizeof (time_t) + 2*sizeof (dicUserIdentifierType) + DIC_PASSWORD_MAX_LENGTH*sizeof (char))
	{
		/*if request is not expired*/
		if ((time (NULL) <= dicAbsoluteValidityTime) && (dicUserId2 == dicResponsibleUserId))
		{
			if (dicRequestingUser != NULL)
			{
				dicRequestingUser->next = malloc (sizeof (dicUserDataType));
				dicRequestingUser = dicRequestingUser->next;
			}
			else
			{
				dicRequestingUser = malloc (sizeof (dicUserDataType));
				dicRequestingUser->previous = NULL
			}

			dicRequestingUser->userId = dicUserId1;
			strcpy (dicRequestingUser->password, dicEncodedPassword);

			/*if is the first not expired request*/
			if (*dicFirstRequestingUser == NULL)
				*dicFirstRequestingUser = dicRequestingUser;
		}

		/*<validity><userId><encoded password>*/
		fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicRequestingUsersFile);
		fread (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
		fread (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
		dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicRequestingUsersFile);
		dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;
	}
	fclose (dicRequestingUsersFile);
	dicRequestingUser->next = NULL;

	dicUser = dicFirstUser;
	/*obtain data of requesting users*/
	while (dicUser != NULL)
	{
		dicRequestingUser = *dicFirstRequestingUser;
		while (dicRequestingUser != NULL)
		{
			if (dicRequestingUser->userId == dicUser->userId)
			{
				strcpy (dicRequestingUser->nickname, dicUser->nickname);
				dicRequestingUser->profile = dicUser->profile;
				strcpy (dicRequestingUser->username, dicUser->username);
				strcpy (dicRequestingUser->email, dicUser->email);
			}

			dicRequestingUser = dicRequestingUser->next;
		}

		dicUser = dicUser->next;
	}

	dicUser = dicFirstUser;
	while (dicUser != NULL)
	{
		dicUser = dicUser->next;
		free (dicUser->previous);
	}

	return dicOk;
}

/*$RCSfile: dicGetPendingRegistrationRequestsPerUser.c,v $*/
