/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicFunctions.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "dicGetUsers.h"
#include "dicUserInterface.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicConfig.h"
#include "dicConst.h"
#include "dicTypes.h"

/* 
 * dicLanguageType
 * DicGetLanguageIndex (const char*);
 *
 * Arguments:
 * const char* - string of language (I)
 *
 * Returned value:
 * dicEnglish - english language (if string differs from other languages)
 * dicPortuguese - portuguese language (if string is dicPortuguese)
 *
 * Description:
 * This function returns the language corresponds to string.
 */
dicLanguageType
DicGetLanguageIndex (const char *dicLanguageString)
{
   if (!strcmp (dicLanguageString, "dicPortuguese"))
      return dicPortuguese;
   else
      return dicEnglish;
}

/*
 * dicUserProfileType
 * DicGetUserProfileIndex (const char*);
 *
 * Arguments:
 * const char* - string of profile in any implemented language (ex.: "administrator", "estudante"...)
 *
 * Returned values:
 * dicUserProfileType - profile corresponding to string
 *
 * Description:
 * This function returns the profile corresponding to string.
 * dicUserProfilesAmountMoreOne indicates invalid profile string.
 */
dicUserProfileType
DicGetUserProfileIndex (const char *dicProfileString)
{
   dicUserProfileType dicUserProfileIndex = 1;
   dicLanguageType dicLanguage;

   while (dicUserProfileIndex < dicUserProfilesAmountMoreOne)
   {
      dicLanguage = 0;
      while (dicLanguage < dicLanguagesAmount)
      {
         if (!strcmp (dicProfileString, DicGetUserProfileString (dicUserProfileIndex, dicEnglish)) || !strcmp (dicProfileString, DicGetUserProfileString (dicUserProfileIndex, dicPortuguese)))
            return dicUserProfileIndex;
         dicLanguage++;
      }
      dicUserProfileIndex++;
   }

   return dicUserProfilesAmountMoreOne;
}

/*
 * char*
 * DicGetAbsolutFileName (const char*, const char*);
 * 
 * Arguments:
 * const char* - directory (I)
 * const char* - file name (I)
 *
 * Returned value:
 * char* - Absolute file name
 *
 * Description:
 * This function returns the concatenation between directory and file name.
 * It does not change the received strings.
 */
char*
DicGetAbsolutFileName (const char* dicDirectory, const char* dicFileName)
{
	extern char dicFilePath [DIC_FILE_PATH_MAX_LENGTH + 1];
	
	snprintf (dicFilePath, DIC_FILE_PATH_MAX_LENGTH + 1, "%s%s", dicDirectory, dicFileName);

	return dicFilePath;
}

/*
 * dicErrorType
 * DicCheckStringField (const char*, const char*,  size_t, size_t);
 * 
 * Arguments:
 * const char* - input string (I)
 * const char* - valid caracters string (I)
 * size_t - minimum length (I)
 * size_t - maximum length (I)
 *
 * Returned value:
 * dicOk - valid string
 * dicInvalidCaracter - string contains invalid caracter
 * dicInvalidLength - string length is out of range
 * dicInvalidArgument - input string or valid caracters string is pointer to NULL
 *
 * Description:
 * This function Checks if the input string is valid.
 */
dicErrorType
DicCheckStringField (const char* dicString, const char* dicValidCaracters,  size_t dicMinimunLength, size_t dicMaximunLength)
{
   unsigned dicStringIndex = 0;
   unsigned dicValidCaractersIndex;

   if (dicString == NULL || dicValidCaracters == NULL)
      return dicInvalidArgument;

   while (dicString [dicStringIndex] != DIC_EOS)
   {
      dicValidCaractersIndex = 0;

      while (1)
      {
         if (dicString [dicStringIndex] == dicValidCaracters [dicValidCaractersIndex])
            break;

         if (dicValidCaracters [dicValidCaractersIndex] == DIC_EOS)
            return dicInvalidCaracter;

         dicValidCaractersIndex++;
      }

      dicStringIndex++;
   }

   if ((dicStringIndex >= dicMinimunLength) && (dicStringIndex <= dicMaximunLength))
      return dicOk;
   else 
      return dicInvalidLength;
}

/*
 * dicErrorType
 * DicCheckNickname (const char*, const char*,  size_t, size_t);
 * 
 * Arguments:
 * const char* - Nickname (I)
 * const char* - valid caracters of Nickname (I)
 * size_t - minimum length (I)
 * size_t - maximum length (I)
 *
 * Returned value:
 * dicOk - valid Nickname
 * dicInvalidNickname - more or less than one occourrence of point or invalid length or character
 * dicInvalidArgument - Nickname or valid caracters string is pointer to NULL
 *
 * Description:
 * This function Checks if the Nickname is valid. 
 */
dicErrorType
DicCheckNickname (const char* dicNickname, const char* dicValidCaracters,  size_t dicMinimunLength, size_t dicMaximunLength)
{
   unsigned dicNicknameIndex = 0;
   unsigned dicValidCaractersIndex;
   unsigned dicPointsCount = 0;

   if (dicNickname == NULL || dicValidCaracters == NULL)
      return dicInvalidArgument;

   while (dicNickname [dicNicknameIndex] != DIC_EOS)
   {
      dicValidCaractersIndex = 0;

      if (dicNickname [dicNicknameIndex] == '.')
      {
         dicPointsCount++;
      }
      else
      {
         while (1)
         {
            if (dicNickname [dicNicknameIndex] == dicValidCaracters [dicValidCaractersIndex])
               break;

            if (dicValidCaracters [dicValidCaractersIndex] == DIC_EOS)
               return dicInvalidNickname;

            dicValidCaractersIndex++;
         }
      }

      dicNicknameIndex++;
   }

   if (dicPointsCount != 1)
      return dicInvalidNickname;

   if ((dicNicknameIndex >= dicMinimunLength) && (dicNicknameIndex <= dicMaximunLength))
      return dicOk;
   else 
      return dicInvalidNickname;
}

/*
 * dicErrorType
 * DicCheckEmail (const char*, const char*,  size_t, size_t);
 * 
 * Arguments:
 * const char* - Email (I)
 * const char* - valid caracters of Email (I)
 * size_t - minimum length (I)
 * size_t - maximum length (I)
 *
 * Returned value:
 * dicOk - valid Email
 * dicInvalidEmail - more or less than one occourrence of point or invalid length or character
 * dicInvalidArgument - Email or valid caracters string is pointer to NULL
 *
 * Description:
 * This function Checks if the Email is valid. 
 */
dicErrorType
DicCheckEmail (const char* dicEmail, const char* dicValidCaracters,  size_t dicMinimunLength, size_t dicMaximunLength)
{
   unsigned dicEmailIndex = 0;
   unsigned dicValidCaractersIndex;
   unsigned dicArrobasCount = 0;

   if (dicEmail == NULL || dicValidCaracters == NULL)
      return dicInvalidArgument;

   while (dicEmail [dicEmailIndex] != DIC_EOS)
   {
      dicValidCaractersIndex = 0;

      if (dicEmail [dicEmailIndex] == '@')
      {
         dicArrobasCount++;
      }
      else
      {
         while (1)
         {
            if (dicEmail [dicEmailIndex] == dicValidCaracters [dicValidCaractersIndex])
               break;

            if (dicValidCaracters [dicValidCaractersIndex] == DIC_EOS)
               return dicInvalidEmail;

            dicValidCaractersIndex++;
         }
      }

      dicEmailIndex++;
   }

   if (dicArrobasCount != 1)
      return dicInvalidEmail;

   if ((dicEmailIndex >= dicMinimunLength) && (dicEmailIndex <= dicMaximunLength))
      return dicOk;
   else 
      return dicInvalidEmail;
}

/*
 * dicErrorType
 * DicCreateRandomString (const char*, size_t, char*);
 * 
 * Arguments:
 * const char* - valid caracters string (I)
 * size_t - string length (I)
 * char* - output string (O)
 *
 * Returned values:
 * dicOk - string created successfully
 * dicInvalidArgument - valid caracters string or output string is pointer to NULL or valid caracters string is empty
 *
 * Description:
 * This function creates a random string.
 */
dicErrorType
DicCreateRandomString (const char *dicValidCaracters, size_t dicLength, char *dicCreatedString)
{
   unsigned dicCreatedStringIndex = 0;   
   unsigned dicValidCaractersIndex;

   if (dicValidCaracters[0] == DIC_EOS || dicValidCaracters == NULL || dicCreatedString == NULL)
      return dicInvalidArgument;

   srand (time(NULL));

   dicValidCaractersIndex = strlen (dicValidCaracters);
   while (dicCreatedStringIndex < dicLength)
   {
      dicCreatedString [dicCreatedStringIndex] = dicValidCaracters [rand() % dicValidCaractersIndex];
      dicCreatedStringIndex++;
   }

   dicCreatedString [dicCreatedStringIndex] = DIC_EOS;

   return dicOk;
}

/*
 * dicErrorType
 * DicCreateNickname (const char*, char*, char*);
 * 
 * Arguments:
 * const char* - username (I)
 * char* - first nickname option (O)
 * char* - second nickname option (O)
 *
 * Returned values:
 * dicOk - nickname created successfully
 * dicEmptyUsername - username is empty
 * dicEmptyLastName - there's one name only
 * dicOverLengthNames - one or more names are very large
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function creates a first nickname option in the form <first name>.<last name>
 * and a sencond nickname option in the form <first name>.<penultimate name>.
 * In case of the username to contain only one last name the second option is a empty string. 
 * All generated nicknames contains only lower cases independently of the username.
 */
dicErrorType
DicCreateNickname (const char *dicUsername, char *dicNickname1, char *dicNickname2)
{
   char dicUsernameCopy [DIC_USERNAME_MAX_LENGTH];
   char *dicFirstName;
   char *dicMidleName;
   char *dicLastName = NULL;
   char *dicBuffer;
   int dicReturnCode;

   if (dicUsername == NULL || dicNickname1 == NULL || dicNickname2 == NULL)
      return dicInvalidArgument;

   strcpy (dicUsernameCopy, dicUsername);

   dicFirstName = strtok (dicUsernameCopy, " ");

   if (dicFirstName == NULL)
      return dicEmptyUsername;

   while ((dicBuffer = strtok (NULL, " ")) != NULL) /*returns NULL if there are't additional non empty strings*/
   {
      dicMidleName = dicLastName;
      dicLastName = dicBuffer;
   }

   if (dicLastName == NULL)
      return dicEmptyLastName;

   /*converts uper to lower case*/
   dicBuffer = dicFirstName;
   while (*dicBuffer != DIC_EOS)
   {
      if ((*dicBuffer > 'A') && (*dicBuffer < 'Z'))
         *dicBuffer += 'a' - 'A';
   }
   dicBuffer = dicLastName;
   while (*dicBuffer != DIC_EOS)
   {
      if ((*dicBuffer > 'A') && (*dicBuffer < 'Z'))
         *dicBuffer += 'a' - 'A';
   }
   dicBuffer = dicMidleName;
   while ((*dicBuffer != DIC_EOS) && (*dicBuffer != DIC_EOS))
   {
      if ((*dicBuffer > 'A') && (*dicBuffer < 'Z'))
         *dicBuffer += 'a' - 'A';
   }

   dicReturnCode = snprintf (dicNickname1, DIC_NICKNAME_MAX_LENGTH + 1, "%s.%s", dicFirstName, dicLastName);
   if (dicReturnCode < 0) /*Is the number of written valid caracters or negative error code*/
      return dicOverLengthNames;

   if (dicMidleName != NULL)
   {
      dicReturnCode = snprintf (dicNickname2, DIC_NICKNAME_MAX_LENGTH + 1, "%s.%s", dicFirstName, dicMidleName);
      if (dicReturnCode < 0)
         return dicOverLengthNames;
   }
   else
      *dicNickname2 = DIC_EOS;

   return dicOk;
}

/*
 * dicErrorType
 * DicGetCryptAlgorithm (const char*, dicCryptAlgorithms*);
 *
 * Arguments:
 * const char* - encoded password (I)
 * dicCryptAlgorithms* - hash algorithm (O)
 *
 * Returned values:
 * dicOk - algorithm obtained successfully
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function obtains the hash algorithm used in the password.
 */
dicErrorType
DicGetCryptAlgorithm (const char *dicEncryptedPassword, dicCryptAlgorithms *dicAlgorithm)
{
   if(dicEncryptedPassword == NULL || dicAlgorithm == NULL)
      return dicInvalidArgument;

/*
 * Md5 encrypted password -> $1$salt$rest
 * Sha256 encrypted password -> $5$salt$rest
 * Sha512 encrypted password -> $6$salt$rest
 * Des encrypted password -> <two digits salt><rest>
 */

   if(dicEncryptedPassword[0] != '$')
      *dicAlgorithm = dicDes;
   else
      *dicAlgorithm = (int) dicEncryptedPassword[1] - '0';

   return dicOk;
}

/*
 * dicErrorType
 * DicEncodePasswordWithSpecificAlgorithm (char*, dicCryptAlgorithms, char*);
 *
 * Arguments:
 * char* - plain password (I)
 * dicCryptAlgorithms - hash algorithm (I)
 * char* - encoded password (O)
 *
 * Returned values:
 * dicOk - Encrypted password successfully
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function encode a plain password with a specific algotithm and a aleatory salt.
 */
dicErrorType
DicEncodePasswordWithSpecificAlgorithm (char *dicPassword, dicCryptAlgorithms dicAlgorithm, char *dicEncryptedPassword)
{
   char dicSalt [DIC_SALT_MAX_LENGTH + 1]; /*salt + EOS*/
   char dicCryptSalt [DIC_SALT_MAX_LENGTH + 5]; /* $digit$salt$ + EOS */

   if (dicPassword == NULL || dicEncryptedPassword == NULL)
      return dicInvalidArgument;

   if (dicAlgorithm == dicDes)
      DicCreateRandomString (DIC_BASE_64_CHARACTERS, 2, dicCryptSalt);
   else
   {
      DicCreateRandomString (DIC_BASE_64_CHARACTERS, DIC_SALT_MAX_LENGTH, dicSalt);
      snprintf (dicCryptSalt, DIC_SALT_MAX_LENGTH + 5, "$%i$%s$", dicAlgorithm, dicSalt);
   }

   strcpy (dicEncryptedPassword, crypt (dicPassword, dicCryptSalt));

   return dicOk;
}

/*
 * dicErrorType
 * DicEncodePasswordWithSpecificSalt (char*, char*, char*);
 *
 * Arguments:
 * char* - plain password (I)
 * char* - salt (in form $digit$salt$ or to digit for Des algorithm) (I)
 * char* - encoded password (O)
 *
 * Returned values:
 * dicOk - Encrypted password successfully
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function encode a plain password with a specific salt.
 * The hash algorithm is built-in the salt.
 */
dicErrorType
DicEncodePasswordWithSpecificSalt (char *dicPassword, char *dicSalt, char *dicEncryptedPassword)
{
   if (dicPassword == NULL || dicSalt == NULL || dicEncryptedPassword == NULL)
      return dicInvalidArgument;

   strcpy (dicEncryptedPassword, crypt (dicPassword, dicSalt));

   return dicOk;
}

/*
 * dicErrorType
 * DicCheckPassword (char*, char*);
 *
 * Arguments:
 * char* - plain password (I)
 * char* - encoded password (I)
 *
 * Returned values:
 * dicOk - correct password
 * dicIcorrectPassword - incorrect password
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function verifys the correspondece between a plain password and a encoded password.
 */
dicErrorType
DicCheckPassword (char *dicPassword, char *dicEncryptedPassword)
{
   char dicSalt [DIC_SALT_MAX_LENGTH + 1];
   dicCryptAlgorithms dicAlgorithm;

   if (dicPassword == NULL || dicEncryptedPassword == NULL)
      return dicInvalidArgument;

   DicGetCryptAlgorithm (dicEncryptedPassword, &dicAlgorithm);

   if (dicAlgorithm == dicDes)
      strncpy (dicSalt, dicEncryptedPassword, 2);
   else
      strncpy (dicSalt, dicEncryptedPassword, DIC_SALT_MAX_LENGTH + 4);

   if (strcmp (dicEncryptedPassword, crypt (dicPassword, dicSalt)))
      return dicOk;
   else
      return dicIncorrectPassword;
}

/*
 * dicErrorType
 * DicAuthenticateUser (dicUserDataType*);
 *
 * Arguments:
 * dicUserDataType* - pointer to dicUserDataType (I/O)
 *
 * Returned values:
 * dicOk - Correct login, user obtained successfully
 * dicInvalidArgument - received argument is NULL pointer
 * dicUsersFileNotExist - the users file not exist
 * dicNicknameNotExist - the nickname not exist
 * dicIncorrectPassword - the password is incorrect
 *
 * Description:
 * This function receives a pointer to dicUserDataType with plain password and nickname fields
 * and gives back the user identfier, username, email, and profile fields.
 * If the users file is empty the function gives back a ponter to NULL.
 */
dicErrorType
DicAuthenticateUser (dicUserDataType *dicUser)
{
   dicUserDataType *dicUserListElement;
   dicErrorType dicReturnCode;
   unsigned dicNicknameOccourrance = 0;

   if (dicUser == NULL)
      return dicInvalidArgument;

   dicReturnCode = DicGetUsers (&dicUserListElement);
   if (dicReturnCode != dicOk)
      return dicReturnCode;

   while (dicUserListElement != NULL)
   {
      if (!strcmp (dicUserListElement->nickname, dicUser->nickname))
      {
         if (!DicCheckPassword (dicUser->password, dicUserListElement->password))
         {
            dicUser->userId = dicUserListElement->userId;
            strcpy (dicUser->username, dicUserListElement->username);
            strcpy (dicUser->email, dicUserListElement->email);
            dicUser->profile = dicUserListElement->profile;
            return dicOk;
         }
         dicNicknameOccourrance++;
      }

      dicUserListElement = dicUserListElement->next;
   }

   if (dicNicknameOccourrance > 0)
      return dicIncorrectPassword;
   else
      return dicNicknameNotExist;
}

/*$RCSfile: dicFunctions.c,v $*/
