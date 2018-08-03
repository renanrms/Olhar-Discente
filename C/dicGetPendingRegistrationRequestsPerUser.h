/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicGetPendingRegistrationRequestsPerUser.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_GETPENDINGREGISTRATIONREQUESTSPERUSER_H
#define DIC_GETPENDINGREGISTRATIONREQUESTSPERUSER_H "@(#)dicGetPendingRegistrationRequestsPerUser.h $Revision: 1.1 $"

#include "dicErrors.h"
#include "dicTypes.h"

/*
 * dicErrorType
 * DicGetPendingRegistrationRequestsPerUser (char*, dicUserDataType**);
 *
 * Arguments:
 * char* - responsible user nickname
 * dicUserDataType** - pointer to pointer to first element of requesting users linked list (O)
 *
 * Returned values:
 * dicOk - get requestings successfully
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
DicGetPendingRegistrationRequestsPerUser (char*, dicUserDataType**);

#endif 

/*$RCSfile: dicGetPendingRegistrationRequestsPerUser.h,v $*/
