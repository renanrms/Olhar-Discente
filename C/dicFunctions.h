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

#ifndef DIC_FUNCTIONS_H
#define DIC_FUNCTIONS_H "@(#)dicFunctions.h $Revision$"

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
 * dicOverPoint - more than one occurrence of point
 * dicNoPoint - no occurrence of point
 * dicInvalidCaracter - Nickname contains invalid caracter
 * dicInvalidLength - Nickname length is out of range
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
 * dicOverArroba - more than one occurrence of arroba
 * dicNoArroba - no occurrence of arroba
 * dicInvalidCaracter - Email contains invalid caracter
 * dicInvalidLength - Email length is out of range
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
 * dicEmptyUsername - username is empty
 * dicEmptyLastName - there isn't last name
 * dicOverLengthNames - one or more names are very large
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function creates a first nickname option in the form <first name>.<last name>
 * and a sencond nickname option in the form <first name>.<penultimate name>.
 * In case of the username to contain only one last name the second option is a empty string. 
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
 * dicInvalidPasswordLength - password length is out of range
 * dicInvalidPasswordCaracter - invalid caracter in password
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
 * dicInvalidPasswordLength - password length is out of range
 * dicInvalidPasswordCaracter - invalid caracter in password
 * dicInvalidArgument - one of the arguments is pointer to NULL
 *
 * Description:
 * This function verifys the correspondece between a plain password and a encoded password.
 */
dicErrorType
DicCheckPassword (char*, char*);

#endif 

/*$RCSfile$*/
