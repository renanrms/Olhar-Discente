/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicDisapproveRegistrationRequest.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_DISAPPROVEREGISTRATIONREQUEST_H
#define DIC_DISAPPROVEREGISTRATIONREQUEST_H "@(#)dicDisapproveRegistrationRequest.h $Revision: 1.1 $"

#include "dicErrors.h"

/*
 * dicErrorType
 * DicDisapproveRegistrationRequest (char*, char*);
 *
 * Arguments:
 * char* - nickname of responsible user (I)
 * char* - nickname of requesting (I)
 *
 * Returned values:
 * dicOk - registration request was disapproved successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotRequestingUser - user is not requesting or your requesting has expired
 * dicNotResponsibleUser - user is nor the responsible for this request
 *
 * Description:
 * This function disapproves a registration request if the data received corresponds to requesting user
 * and your responsible user and the request is not expired, and then send an email for the requesting.
 */
dicErrorType
DicDisapproveRegistrationRequest (char*, char*);

#endif 

/*$RCSfile: dicDisapproveRegistrationRequest.h,v $*/
