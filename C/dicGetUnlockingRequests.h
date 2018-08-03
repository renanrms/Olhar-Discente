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

#ifndef DIC_GETUNLOCKINGREQUESTS_H
#define DIC_GETUNLOCKINGREQUESTS_H "@(#)dicGetUnlockingRequests.h $Revision$"

#include "dicTypes.h"
#include "dicErrors.h"

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
DicGetUnlockingRequests (dicNicknameListType**);

#endif 

/*$RCSfile$*/
