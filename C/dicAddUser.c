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
#include <time.h>

#include "dicGetUsers.h"
#include "dicAddUser.h"
#include "dicConfig.h"
#include "dicErrors.h"
#include "dicConst.h"
#include "dicTypes.h"
#include "dicFunctions.h"
#include "Libraries/sendmail.h"

/*
 * dicErrorType
 * DicAddUser (dicUserDataType*);
 *
 * Arguments:
 * dicUserDataType - structure containing username, password (empty or not) and confirmation, email and profile (I)
 *
 * Returned values:
 * dicOk - user was added successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicInvalidNickname - nickname is invalid
 * dicInvalidEmail - email is invalid
 * dicInvalidEmailConfirmation - email confirmation differs from email
 * dicUserEmailAlreadyRegistered - email is already registered
 * dicInvalidPassword - invalid password
 * dicInvalidPasswordConfirmation - password confirmation differs from password
 * dicInvalidUsername - username is invalid
 * dicIcorrectPassword - user authentication failed
 * dicEmptyLastName - username has only one name
 * dicOverLengthNames - very large names to create nickname
 *
 * Description:
 * This function verifys the validity of data, creates an nickname and
 * if it's the first user, register as administrator, 
 * else register with profile received and send an email to user.
 * If password is empty, an invite is send by email. 
 */
dicErrorType
DicAddUser (dicUserDataType *dicUserData)
{
	FILE *dicUsersFile;
	FILE *dicInvitedUsersFile;

	char dicFirstName [DIC_USERNAME_MAX_LENGTH + 1];
	char dicFirstNickname [DIC_NICKNAME_MAX_LENGTH + 1];
	char dicSecondNickname [DIC_NICKNAME_MAX_LENGTH + 1];
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];

	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH + 1];

	size_t dicUsernameLength;

	time_t dicAbsoluteValidityTime;

	dicErrorType dicReturnCode = 0;

	dicUserDataType *dicRegisteredUser;
		
	/*Check email*/
	dicReturnCode = DicCheckEmail (dicUserData->email, DIC_EMAIL_CARACTERS, DIC_EMAIL_MIN_LENGTH, DIC_EMAIL_MAX_LENGTH);
	if(dicReturnCode != dicOk)
		return dicReturnCode;
	if(strcmp (dicUserData->email, dicUserData->emailConfirmation) != 0)
		return dicInvalidEmailConfirmation;	

	/*Check password*/
	if (strlen (dicUserData->password) != 0)
	{
		dicReturnCode = DicCheckStringField (dicUserData->password, DIC_PASSWORD_CARACTERS, DIC_PASSWORD_MIN_LENGTH, DIC_PASSWORD_MAX_LENGTH);
		if (dicReturnCode != dicOk)
			return dicInvalidPassword;
	}
	if(strcmp (dicUserData->password, dicUserData->passwordConfirmation))
		return dicInvalidPasswordConfirmation;

	/*Check username*/
	dicReturnCode = DicCheckStringField (dicUserData->username, DIC_USERNAME_CARACTERS, DIC_USERNAME_MIN_LENGTH, DIC_USERNAME_MAX_LENGTH);
	if(dicReturnCode != dicOk)
		return dicInvalidUsername;

	/*Create nickname*/
	dicReturnCode = DicCreateNickname (dicUserData->username, dicFirstNickname, dicSecondNickname);
	if(dicReturnCode != dicOk)
		return dicReturnCode;

	dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");

	if (dicUsersFile == NULL) /*if the data file does note exist, the function adds the firt user (administrator) with userId = 0*/
	{			
		dicUserData->userId = 0;
		dicUserData->profile = dicAdministrator;
		dicUserData->nickname = dicFirstNickname;

		/*encode password*/
		DicEncodePasswordWithSpecificAlgorithm (dicUserData->password, dicSha512, dicEncodedPassword);

		dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "w");

		/*userId:nickname:password:profile:username:email\n*/
		fprintf (dicUsersFile, "%llu:%s:%s:%i:%s:%s\n", 
			     dicUserData->userId,
		         dicUserData->nickname,
			     dicEncodedPassword,
			     dicUserData->profile,
			     dicUserData->username,
			     dicUserData->email);

		fclose (dicUsersFile);
	}
	else /*If the file exists the function should verify if will creat or invite a new user*/
	{
		strcpy (dicFirstName, dicUser->username);
		strtok (dicFirstName, " ");

		/*open users data file*/
		dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "a");

		/*first user*/
		dicReturnCode = DicGetUsers (&dicRegisteredUser);		
		if(dicReturnCode != dicOk)
			return dicReturnCode;

		/*Check nickname and email in file*/		
		while(dicRegisteredUser != NULL)
		{
			/*nickname already exist*/
			if(!strcmp (dicRegisteredUser->nickname, dicUserData->nickname))
				strcpy (dicUserData->nickname, dicSecondNickname);

			/*email already exist*/
			if(!strcmp (dicRegisteredUser->email, dicUserData->email))
				return dicUserEmailAlreadyRegistered;

			dicUserData->userId = dicRegisteredUser->userId;
			dicRegisteredUser = dicRegisteredUser->next;
		}

		dicUserData->userId++;

		if(strlen (dicUserData->password) != 0) /*if no empty password creates a new user*/
		{
			/*Check and encode password*/
			dicReturnCode = DicEncodePasswordWithSpecificAlgorithm (dicUserData->password, dicSha512, dicEncodedPassword);	
			if(dicReturnCode != dicOk)
				return dicReturnCode;

			fprintf (dicUsersFile, "%llu:%s:%s:%i:%s:%s\n", 
						dicUserData->userId,
						dicUserData->nickname,
						dicEncodedPassword, 
						dicUserData->profile, 
						dicUserData->username,
						dicUserData->email);

			fclose (dicUsersFile);

			sprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			        "Welcome, ", dicFirstName, "!\n\n",
			        "You was registered at Olhar Discente with this e-mail.\n\n\n",
			        "You are reistered as ", dicUserData->username, " and your login data are:\n\n",
			        "\tNickname: ", dicUserData->nickname,
			        "\n\tPassword: ", dicUserData->password,
			        "\n\n\nVisit us in here: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
			        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
			        "-------------------------------------------------------\n\n\n",
			        "Bem-vindo, ", dicFirstName, "!\n\n",
			        "Você foi registrado em Olhar Discente com este e-mail.\n\n\n",
			        "Você está registrado como ", dicUserData->username, " e seus dados de login são:\n\n",
			        "\tApelido: ", dicUserData->nickname,
			        "\n\tSenha: ", dicUserData->password,
			        "\n\n\nAcesse aqui: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
			        "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
			        );

			/*Send email to new user*/
			sendMail (
				DIC_SMTP_CLIENT_DOMAIN,
				DIC_SMTP_SERVER_FULL_HOSTNAME,
				DIC_SMTP_SERVER_PORT,
				DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
				dicUserData->email, /*To*/
				NULL, /*cc*/
				NULL, /*bcc*/
				"Olhar Discente - User Registered successfully", /*Subject*/
				dicEmailBody,   /*Body*/
				NULL  /*Attatchement*/
			);
		}
		else
		{
			/*Create a temporary password with 16 random characters*/
        	DicCreateRandomString(DIC_TEMP_PASSWORD_CHARACTERS, DIC_TEMP_PASSWORD_LENGTH, dicUserData->password);

			/*Encode the password created*/
			DicEncodePasswordWithSpecificAlgorithm(dicUserData->password, dicSha512, dicEncodedPassword);

			/*userId:nickname::profile:username:email\n*/
			fprintf (dicUsersFile, "%llu:%s::%i:%s:%s\n", 
			         dicUserData->userId,
			         dicUserData->nickname,
			         dicUserData->profile,
			         dicUserData->username,
			         dicUserData->email);

			fclose (dicUsersFile);

			/*open invited users file*/
			dicInvitedUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME), "a");

			dicAbsoluteValidityTime = time (NULL) + DIC_INVITE_EXPIRATION_TIME;
			/*<validity><userId><encoded password>*/
			fwrite (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicInvitedUsersFile);
			fwrite (&(dicUserData->userId), sizeof (dicUserIdentifierType), 1, dicInvitedUsersFile);
			fwrite (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicInvitedUsersFile);

			fclose (dicInvitedUsersFile);

			sprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			        "Hi, ", dicFirstName, "!\n\n",
			        "You was invited to register at Olhar Discente (teacher evaluate system) with this e-mail.\n\n\n",
			        "You are invited as ", dicUserData->username, " and your data are:\n\n",
			        "\tNickname: ", dicUserData->nickname,
			        "\n\tTemporary password: ", dicUserData->password,
			        "\nDo not worry about any errors in your name, you will be able to change it.\n\n\n",
			        "For accept access: ", DIC_WEB_SERVER_URL,
			        "CGIs/dicAcceptInviteForm.cgi?dicNickname=", dicUserData->nickname,
			        "&dicLanguage=dicEnglish\n",
			        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n",
			        "This invite expires in 72 hours if you do not accept.\n\n",
			        "For reject this invite access: ", DIC_WEB_SERVER_URL,
			        "CGIs/dicRejectInviteForm.cgi?dicLanguage=dicEnglish\n\n\n",
			        "-------------------------------------------------------\n\n\n",
			        "Olá, ", dicFirstName, "!\n\n",
			        "Você foi convidado a regstrar-se em Olhar Discente (sistema de avaliação de docentes) com este e-mail.\n\n\n",
			        "Você está convidado como ", dicUserData->username, " e seus dados são:\n\n",
			        "\tApelido: ", dicUserData->nickname,
			        "\n\tSenha temporária: ", dicUserData->password,
			        "\nNão se preocupe com eventuais erros no seu nome, você poderá corrigi-los futuramente.\n\n\n",
			        "Para aceitar o convite acesse: ", DIC_WEB_SERVER_URL,
			        "CGIs/dicAcceptInviteForm.cgi?dicNickname=", dicUserData->nickname,
			        "&dicLanguage=dicPortuguese\n",
			        "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n",
			        "Este convite expira em 72 horas se você não aceitá-lo.\n\n",
			        "Para rejeitá-lo acesse: ", DIC_WEB_SERVER_URL,
			        "CGIs/dicRejectInviteForm.cgi?dicLanguage=dicEnglish\n"
			        );

			/*Send invite email*/
			sendMail (
				DIC_SMTP_CLIENT_DOMAIN,
				DIC_SMTP_SERVER_FULL_HOSTNAME,
				DIC_SMTP_SERVER_PORT,
				DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
				dicUserData->email, /*To*/
				NULL, /*cc*/
				NULL, /*bcc*/
				"Olhar Discente - Invite to Register", /*Subject*/
				dicEmailBody,   /*Body*/
				NULL  /*Attatchement*/
			);

		}

	}


	return dicOk;
}

/*$RCSfile$*/
