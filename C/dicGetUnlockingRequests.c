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
#include <string.h>
#include <time.h>

#include "dicGetUnlockingRequests.h"
#include "dicGetUsers.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicConfig.h"
#include "dicConst.h"
#include "dicTypes.h"


/*
 * dicErrorType
 * DicGetUnlockingRequests (dicNicknameListType**);
 *
 * Arguments:
 * dicNicknameListType** - pointer to pointer to first element of unlocking users nickname linked list (O)
 *
 * Returned values:
 * dicOk - get unlocking requests successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUnlockingUsersFileNotExist - the unlocking users file not exist
 * dicUsersFileNotExist - the users file not exist
 *
 * Description:
 * This function gives back a linked list of unlocking users with your nicknames.
 * (If there are't unlock requests, gives back NULL)
 */
dicErrorType
DicGetUnlockingRequests (dicNicknameListType **dicFirstNickname)
{
	FILE *dicUnlockingUsersFile;

	struct dicUserIdentifiers
	{
		dicUserIdentifierType userId;
		struct dicUserIdentifiers *next;
	};

	struct dicUserIdentifiers *dicIdentifiers = NULL;
	struct dicUserIdentifiers *dicFirstIdentifier = NULL;
	struct dicUserIdentifiers *dicIdentifierPrevious;

	dicNicknameListType *dicNicknames = NULL;

	dicUserDataType *dicUser;
	dicUserDataType *dicFirstUser;

	time_t dicAbsoluteValidityTime;
	dicUserIdentifierType dicUserId;

	size_t dicReadBytes;

	dicErrorType dicReturnCode;


	if (dicFirstNickname == NULL)
		return dicInvalidArgument;

	dicUnlockingUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_UNLOCKING_USERS_DATA_FILENAME), "r");
	if (dicUnlockingUsersFile == NULL)
		return dicUnlockingUsersFileNotExist;

	/*<validity><userId>*/
	fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicUnlockingUsersFile);
	dicReadBytes = fread (&(dicUserId), sizeof (dicUserIdentifierType), 1, dicUnlockingUsersFile);

	/*obtains the list of not expired requests*/
	while (dicReadBytes == sizeof (time_t) + sizeof (dicUserIdentifierType))
	{
		/*if unlocking request is not expired*/
		if (time (NULL) <= dicAbsoluteValidityTime)
		{
			if (dicIdentifiers != NULL)
			{
				dicIdentifiers->next = malloc (sizeof (dicUserDataType));
				dicIdentifiers = dicIdentifiers->next;
			}
			else
			{
				dicIdentifiers = malloc (sizeof (dicUserDataType));
			}

			dicIdentifiers->userId = dicUserId;

			/*if is the first not expired request*/
			if (dicFirstIdentifier == NULL)
				dicFirstIdentifier = dicIdentifiers;
		}

		/*<validity><userId>*/
		fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicUnlockingUsersFile);
		dicReadBytes = fread (&(dicUserId), sizeof (dicUserIdentifierType), 1, dicUnlockingUsersFile);
	}
	fclose (dicUnlockingUsersFile);
	dicIdentifiers->next = NULL;

	dicReturnCode = DicGetUsers (&dicFirstUser);
	if (dicReturnCode != dicOk)
		return dicReturnCode;

	*dicFirstNickname = NULL;

	dicUser = dicFirstUser;
	/*obtain data of requesting users*/
	while (dicUser != NULL)
	{
		dicIdentifiers = dicFirstIdentifier;
		while (dicIdentifiers != NULL)
		{
			if (dicIdentifiers->userId == dicUser->userId)
			{
				if (dicNicknames != NULL)
				{
					dicNicknames->next = malloc (sizeof (dicNicknameListType));
					dicNicknames = dicNicknames->next;
				}
				else
				{
					dicNicknames = malloc (sizeof (dicNicknameListType));
					*dicFirstNickname = dicNicknames;
				}

				strcpy (dicNicknames->nickname, dicUser->nickname);
			}

			dicIdentifiers = dicIdentifiers->next;
		}

		dicUser = dicUser->next;
	}

	dicUser = dicFirstUser;
	while (dicUser != NULL)
	{
		dicUser = dicUser->next;
		free (dicUser->previous);
	}

	dicIdentifiers = dicFirstIdentifier;
	while (dicIdentifiers != NULL)
	{
		dicIdentifierPrevious = dicIdentifiers;
		dicIdentifiers = dicIdentifiers->next;
		free (dicIdentifierPrevious);
	}

	return dicOk;
}

/*$RCSfile$*/
