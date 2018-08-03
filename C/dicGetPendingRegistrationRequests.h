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

#ifndef DIC_GETPENDINGREGISTRATIONREQUESTS_H
#define DIC_GETPENDINGREGISTRATIONREQUESTS_H "@(#)dicGetPendingRegistrationRequests.h $Revision$"

#include "dicErrors.h"
#include "dicTypes.h"

/*
 * dicErrorType
 * DicGetPendingRegistrationRequests (dicUserDataType**);
 *
 * Arguments:
 * dicUserDataType** - pointer to pointer to first element of requesting users linked list (O)
 *
 * Returned values:
 * dicOk - registration request was approved successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicRequestingUsersFileNotExist - the requesting users file not exist
 * dicUsersFileNotExist - the users file not exist
 *
 * Description:
 * This function gives back a double linked list of requesting users with all your data.
 * (If there are't requestings, gives back NULL)
 */
dicErrorType
DicGetPendingRegistrationRequests (dicUserDataType**);

#endif 

/*$RCSfile$*/
