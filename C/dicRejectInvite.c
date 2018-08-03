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

#include "dicAcceptInvite.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicTypes.h"
#include "dicConst.h"
#include "dicConfig.h"
#include "Libraries/sendmail.h"

/*
 * dicErrorType
 * DicRejectInvite (char*, char*);
 *
 * Arguments:
 * char* - password of invited user (I)
 * char* - nickname of invited user (I)
 *
 * Returned values:
 * dicOk - invite was rejected successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotInvitedUser - if user is not invited or your invite has expired
 * dicIcorrectPassword - user authentication failed
 *
 * Description:
 * This function rejects a invite to register in the system if user was invited,
 * your invite is not expired and your password is correct.
 */
dicErrorType
DicRejectInvite (char *dicInvitedPassword, char *dicInvitedNickname)
{
	FILE *dicInvitedUsersFile;
	FILE *dicInvitedUsersFile_Temp;
	FILE *dicUsersFile;
	FILE *dicUsersFile_Temp;

	char dicUsersFileLineCopy [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char dicUsersFileLine [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char *validation;
	size_t dicReadBytes;
	unsigned char dicFoundInvitedUser = 0; /*flag variable*/

	dicUserIdentifierType dicUserId;
	dicUserIdentifierType dicUserInvitedId;
	char dicUserEmail [DIC_EMAIL_MAX_LENGTH]
	char dicFirstName [DIC_USERNAME_MAX_LENGTH + 1];
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];
	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH];
	time_t dicAbsoluteValidityTime;

	dicErrorType dicReturnCode;

	if (dicPassword == NULL || dicInvitedUser == NULL)
		return dicInvalidArgument;

	dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");
	dicUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"), "w");

	/*obtain data of invited user*/
	while (1)
	{
		if (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
		{
			strcpy (dicUsersFileLineCopy, dicUsersFileLine);

			dicUserInvitedId = strtoul (strtok (dicUsersFileLine, ":"), &validation, 10);

			/*if found user, verifys the password*/
			if (!strcmp (strtok (NULL, ":"), dicInvitedNickname))
			{
				dicTokenPointer = strtok (NULL, ":");
				/*if password is empty*/
				if (*(dicTokenPointer - 1) == ':')
				{
					strcpy (dicFirstName, strtok (NULL, ":")); /*receives the full name*/
					strcpy (dicUserEmail, strtok (NULL, ":"));
					strtok (dicFirstName, " ");

					break;
				}
				else
				{
					fclose (dicUsersFile);
					fclose (dicUsersFile_Temp);
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
					return dicUserAlreadyRegistered;
				}
			}
			else /*if is not the shared user, copy this line*/
			{
				fprintf (dicUsersFile_Temp, "%s", dicUsersFileLineCopy);
			}
		}
		else /*final of file. user not found*/
		{
			fclose (dicUsersFile);
			fclose (dicUsersFile_Temp);
			remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
			return dicNotInvitedUser;
		}
	}

	dicInvitedUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME), "r");
	dicInvitedUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"), "w");

	/*copy from invited users file to pemporary file and search the userId corresponding to nickname*/
	while (1)
	{
		/*<validity><userId><encoded password>*/
		fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicInvitedUsersFile);
		fread (&(dicUserId), sizeof (dicUserIdentifierType), 1, dicInvitedUsersFile);
		dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicInvitedUsersFile);
		dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;

		/*final of file*/
		if (dicReadBytes != sizeof (time_t) + sizeof (dicUserIdentifierType) + DIC_PASSWORD_MAX_LENGTH*sizeof (char))
		{
			/*not found user. Indicates that user is in other pendent state*/
			if (!dicFoundInvitedUser)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicInvitedUsersFile);
				fclose (dicInvitedUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
				return dicNotInvitedUser;
			}
			else
				break;
		}

		/*found user. This line is not copy*/
		if (dicUserId == dicUserInvitedId)
		{
			dicFoundInvitedUser = 1;
			/*invite is expired*/
			if (time (NULL) > dicAbsoluteValidityTime)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicInvitedUsersFile);
				fclose (dicInvitedUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
				return dicNotInvitedUser;
			}
			if (DicCheckPassword (dicInvitedPassword, dicEncodedPassword) != dicOk)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicInvitedUsersFile);
				fclose (dicInvitedUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
				return dicIcorrectPassword;
			}
		}
		else /*not is the user invited. Copy data for temporary file*/
		{
			fwrite (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicInvitedUsersFile_Temp);
			fwrite (&(dicUserId), sizeof (dicUserIdentifierType), 1, dicInvitedUsersFile_Temp);
			fwrite (dicEncodedPassword, sizeof (char), DIC_HASH_SHA512_LENGTH, dicInvitedUsersFile_Temp);
		}
	}

	/*close the files and deletes the invited users file*/
	fclose (dicInvitedUsersFile);
	fclose (dicInvitedUsersFile_Temp);
	remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME));
	/*rename temporary file created*/
	rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"),
	        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME));

	/*copy the rest of users file for temporary file*/
	while (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
	{
		fprintf (dicUsersFile_Temp, "%s", dicUsersFileLine);
	}

	/*close the files and deletes the users file*/
	fclose (dicUsersFile);
	fclose (dicUsersFile_Temp);
	remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));
	/*rename temporary file created */
	rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"),
	        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));

	/*create message*/
	sprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	        "Hi, ", dicFirstName, "!\n\n",
	        "You rejected the invite at Olhar Discente with success and your all data are deleted.\n\n\n\n",
	        "If want to know the site access: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
	        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
	        "-------------------------------------------------------\n\n\n",
	        "Olá, ", dicFirstName, "!\n\n",
	        "Você rejeitou seu convite de cadastramento em Olhar Discente com sucesso e todos os seus dado foram deletados.\n\n\n\n",
	        "Caso queira conhecer melhor o site acesse aqui: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
	        "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
	        );

	/*Send email to new user*/
	sendMail (
		DIC_SMTP_CLIENT_DOMAIN,
		DIC_SMTP_SERVER_FULL_HOSTNAME,
		DIC_SMTP_SERVER_PORT,
		DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
		dicUserEmail, /*To*/
		NULL, /*cc*/
		NULL, /*bcc*/
		"Olhar Discente - User Registered successfully", /*Subject*/
		dicEmailBody,   /*Body*/
		NULL  /*Attatchement*/
	);

	return dicOk;
}

/*$RCSfile$*/
