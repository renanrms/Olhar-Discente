/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicFunctions.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_FUNCTIONS_H
#define DIC_FUNCTIONS_H "@(#)dicFunctions.h $Revision: 1.1 $"

#include "dicTypes.h"
#include "dicErrors.h"

/* 
 * dicLanguageType
 * DicGetLanguageIndex (cconst har*);
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
DicGetLanguageIndex (const char*);

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
 * dicUserProfilesAmount indicates invalid profile string.
 */
dicUserProfileType
DicGetUserProfileIndex (const char*);

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
DicGetAbsolutFileName (const char*, const char*);

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
DicCheckStringField (const char*, const char*,  size_t, size_t);

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
DicCheckNickname (const char*, const char*,  size_t, size_t);

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
DicCheckEmail (const char*, const char*,  size_t, size_t);

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
DicCreateRandomString (const char*, size_t, char*);

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
 * dicInvalidUsername - username is empty
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
DicCreateNickname (const char*, char*, char*);

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
DicGetCryptAlgorithm (const char*, dicCryptAlgorithms*);

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
DicEncodePasswordWithSpecificAlgorithm (char*, dicCryptAlgorithms, char*);

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
DicEncodePasswordWithSpecificSalt (char*, char*, char*);

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
DicCheckPassword (char*, char*);

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
 * If the users file is empty the function gives back a pointer to NULL.
 */
dicErrorType
DicAuthenticateUser (dicUserDataType*);

/* dicErrorType
 * DicWriteInBinaryFile (char, char*, time_t*, dicUserProfileType*, dicUserProfileType*, char*, char*, char*);
 *
 * Arguments:
 * char - sorting criterion, 'i' indicates the first user identifier argument and 't' indicates time argument (O)
 * char* - name of the binary file name (O)
 * time_t* - pointer to time (O)
 * dicUserProfileType* - pointer to first user identifier (O)
 * dicUserProfileType* - pointer to second user identifier (O)
 * char* - password string (O)
 * char* - email string (O)
 * char* - email change key string (O)
 *
 * Returned values:
 * dicOk - user writen successfully
 * dicInvalidArgument - file name argument is NULL pointer or sorting criterion is invalid or is incompatible with other arguments
 *
 * Description:
 * This function write in file all parameters (except the first and second) that are valid pointers
 * (differs from NULL) in the parameters order.
 * The sorting criterion 't' write the information at end of file and the 'i' write the information
 * before the first user that has a user identifier bigger than your.
 */
dicErrorType
DicWriteInBinaryFile (char, char*, time_t*, dicUserProfileType*, dicUserProfileType*, char*, char*, char*);

/*
 * dicErrorType
 * DicReadNextInformationInBinaryFile (FILE*, time_t*, dicUserProfileType*, dicUserProfileType*, char*, char*, char*);
 *
 * Arguments:
 * FILE* - file for read (I)
 * time_t* - pointer to time (I/O)
 * dicUserProfileType* - pointer to first user identifier (I/O)
 * dicUserProfileType* - pointer to second user identifier (I/O)
 * char* - password string (I/O)
 * char* - email string (I/O)
 * char* - email change key string (I/O)
 *
 * Returned values:
 * dicOk - information is read successfully
 * dicInvalidArgument - pointer to file argument is NULL
 * dicEndOfFile - end of file is encountered
 *
 * Description:
 * This function read from file all parameters (except the first) that are valid pointers (differs from NULL) in the parameters order.
 */
dicErrorType
DicReadNextInformationInBinaryFile (FILE*, time_t*, dicUserProfileType*, dicUserProfileType*, char*, char*, char*);

/*
 * dicErrorType
 * DicWriteNextInformationInBinaryFile (FILE*, time_t*, dicUserProfileType*, dicUserProfileType*, char*, char*, char*);
 *
 * Arguments:
 * FILE* - file for write (I)
 * time_t* - pointer to time (I)
 * dicUserProfileType* - pointer to first user identifier (I)
 * dicUserProfileType* - pointer to second user identifier (I)
 * char* - password string (I)
 * char* - email string (I)
 * char* - email change key string (I)
 *
 * Returned values:
 * dicOk - information is writen successfully
 * dicInvalidArgument - pointer to file argument is NULL
 *
 * Description:
 * This function write in file all parameters (except the first) that are valid pointers (differs from NULL) in the parameters order.
 */
dicErrorType
DicWriteNextInformationInBinaryFile (FILE*, time_t*, dicUserProfileType*, dicUserProfileType*, char*, char*, char*);

#endif 

/*$RCSfile: dicFunctions.h,v $*/
