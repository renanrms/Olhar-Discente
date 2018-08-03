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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dicGetUsers.h"
#include "dicAddUser.h"
#include "dicConfig.h"
#include "dicErrors.h"
#include "dicConst.h"
#include "dicTypes.h"
#include "dicFunctions.h"
#include "Libraries/sendmail.h"

dicErrorType
DicAddUser (dicUserDataType *dicUserData)
{
	FILE *dicUsersFile;

	char dicFirstNickname [DIC_NICKNAME_MAX_LENGTH + 1];
	char dicSecondNickname [DIC_NICKNAME_MAX_LENGTH + 1];
	char dicGeneratedPassword [DIC_PASSWORD_MAX_LENGTH + 1];
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];

	unsigned dicNicknameExist = 0;
	unsigned dicReturnCode = 0;

	size_t dicUsernameLength;

	dicUserDataType *dicFirstUser;
	dicUserDataType *dicAdmin = NULL;

	dicUserIdentifierType dicUserIdentifierIndex = 0;
		
	/*Check email*/
	if(DicCheckEmail (dicUserData->email, DIC_EMAIL_CARACTERS, DIC_EMAIL_MIN_LENGTH, DIC_EMAIL_MAX_LENGTH) != 0 )
		return dicInvalidEmail;
	
	if(strcmp (dicUserData->email, dicUserData->emailConfirmation) != 0)
		return dicInvalidEmailConfirmation;	

	/*Check/encode password*/
	dicReturnCode = DicEncodePasswordWithSpecificAlgorithm (dicUserData->password, dicSha512, dicEncodedPassword);
	if(dicReturnCode != dicOk)
		return dicReturnCode;

	if(strcmp (dicUserData->password, dicUserData->passwordConfirmation) != 0)
		return dicInvalidPasswordConfirmation;

	/*Check username*/
	dicUsernameLength = strlen (dicUserData->username);
	if((dicUsernameLength < DIC_USERNAME_MIN_LENGTH) || (dicUsernameLength > DIC_USERNAME_MAX_LENGTH))
		return dicInvalidUsername;

	/*Create nickname*/
	dicReturnCode = DicCreateNickname (dicUserData->username, dicFirstNickname, dicSecondNickname);
	if(dicReturnCode != dicOk)
		return dicReturnCode;

	dicUsersFile = fopen (DIC_USERS_DATABASE_FILE, "r");

	if (dicUsersFile == NULL) /*if the data file does note exist, the function adds the firt user (administrator) with userId = 0*/
	{			
		dicUserData->userId = 0;
		dicUserData->profile = dicAdministrator;
		dicUserData->nickname = dicFirstNickname;

		dicUsersFile = fopen (DIC_USERS_DATABASE_FILE, "w");

		/*userId:nickname:password:profile:username:email\n*/
		fprintf (dicUsersFile, "%llu:%s:%s:%i:%s:%s\n", 
			     dicUserData->userId,
		        dicUserData->nickname,
			     dicUserData->password,
			     dicUserData->profile,
			     dicUserData->username,
			     dicUserData->email);
	}
	else /*If the file exists the function should verify if will operate in the next two options*/
	{
		dicUsersFile = fopen (DIC_USERS_DATABASE_FILE, "a");

		if(strlen (dicUserData->password) != 0) /*empty password indicates that user is pendent or locked*/
		{
			/*Check nickname and email in database*/		
			dicReturnCode = DicGetUsers (&dicFirstUser);		
			if(dicReturnCode != dicOk)
				return dicReturnCode;

			dicAdmin = dicFirstUser;
			
			while(dicFirstUser != NULL)
			{
				/*nickname already exist*/
				if(!strcmp (dicFirstUser->nickname, dicUserData->nickname))
					dicNicknameExist = 1;

				/*email already exist*/
				if(!strcmp (dicFirstUser->email, dicUserData->email))
					return dicUserEmailAlreadyRegistered;

				dicUserIdentifierIndex = dicFirstUser->userId;
				dicFirstUser = dicFirstUser->next;	
			}

			if (dicNicknameExist)
				strcpy (dicUserData->nickname, dicSecondNickname);

			/*free the linked list*/	
			DicFreeUsersLinkedList (dicFirstUser);
			/*increment one to userId*/
			dicUserData->userId = dicUserIdentifierIndex + 1;	
			/*encode password*/
			DicEncodePasswordWithSpecificAlgorithm (dicUserData->password, dicSha512, dicUserData->password);	

			fprintf (dicUsersFile, "%llu:%s:%s:%i:%s:%s\n", 
				dicUserData->userId,
				dicUserData->nickname,
				dicUserData->password, 
				dicSimpleUser, /*Simple User = 1*/
				dicUserData->username,
				dicUserData->email
		 		);

			/*Send email to user*/
			sendMail (
				DIC_SMTP_CLIENT_DOMAIN,
				DIC_SMTP_SERVER_FULL_HOSTNAME,
				DIC_SMTP_SERVER_PORT,
				dicAdmin->email, /*From Admin*/
				dicUserData->email, /*To*/
				NULL, /*cc*/
				NULL, /*bcc*/
				"User of Olhar Discente Registered successfully ", /*Subject*/
				"You was registered successfully at Olhar Discente.\n",   /*Body*/
				NULL  /*Attatchement*/
			);
		}
		else
		{
			/*
		 	 * Now we're assuming that the function receives an empty password,
 		 	 * so must be generated a random password and sent to user email 
 		 	 */
		
			/*Create a temporary password with 16 random characters*/
         DicCreateRandomString(DIC_TEMP_PASSWORD_CHARACTERS, 16, dicGeneratedPassword);
		
			/*Encode the password created*/
			DicEncodePasswordWithSpecificAlgorithm(dicGeneratedPassword, dicSha512, dicUserData->password);	
		
			/*Open users.abeyances*/


			/*send email with link to confirm registration*/



		}

	}


	return dicOk;
}

/*$RCSfile$*/
