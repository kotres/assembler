/**************************************************************************//**
 *\file  label.h
 *\brief label structure and functions.
 *
 *\author Michel Kuhlburger
 *
 *\date 26/01/2018
******************************************************************************/


#ifndef LABEL_H
#define LABEL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

/**************************************************************************//**
 * \struct Label
 * \brief Node for making label lists.
 *
 * Label is a list node type struct that contains the name of an assembly label
 * and it's corresponding value.
 ******************************************************************************/

struct Label
{
    uint32_t address;/**< The value of the label. */
    char *name;/**< The name of the label. */
    struct Label *next;/**< pointer to the next label node. */
};

/**************************************************************************//**
 * \fn int labelInitialize(struct Label **label,uint32_t address,const char* name)
 * \brief Initalizes a NULL label pointer into the first node of a label list.
 * \param[in] label Pointer to a NULL label pointer.
 * \param[in] address Address value of the label.
 * \param[in] name name of the label.
 * \return 0 if label could be initialized, -1 if an error occured.
******************************************************************************/

int labelInitialize(struct Label **label,uint32_t address,const char* name);

/**************************************************************************//**
 * \fn int labelPushBack(struct Label *label, uint32_t address, const char *name)
 * \brief Initalizes a label node at the end of a label list.
 * \param[in] label A non NULL label pointer.
 * \param[in] address Address value of the label.
 * \param[in] name name of the label.
 * \return 0 if label could be initialized, -1 if an error occured.
******************************************************************************/

int labelPushBack(struct Label *label, uint32_t address, const char *name);

/**************************************************************************//**
 * \fn struct Label* labelFindLabel(struct Label *label,const char *name)
 * \brief Finds a label in the list by its name.
 * \param[in] label A non NULL label pointer.
 * \param[in] name Name of the label to be found.
 * \return A pointer to the first corresponding label if it was found or NULL if not.
******************************************************************************/

struct Label* labelFindLabel(struct Label *label,const char *name);

/**************************************************************************//**
 * \fn struct Label* labelEnd(struct Label *label)
 * \brief Returns a pointer to the end of the label list.
 * \param[in] label A non NULL label pointer.
 * \param[in] name Name of the label to be found.
 * \return A pointer to the last label of the list or NULL if an empty list was given.
******************************************************************************/

struct Label* labelEnd(struct Label *label);

/**************************************************************************//**
 * \fn void labelPrintLabels(struct Label *label)
 * \brief prints all the names of the labels in the list given.
 * \param[in] label A label pointer.
******************************************************************************/

void labelPrintLabels(struct Label *label);

/**************************************************************************//**
 * \fn labelDestroy(struct Label *label)
 * \brief Destroys a label list by freeing all the ressources alloced to it.
 * \param[in] label A label pointer.
******************************************************************************/

void labelDestroy(struct Label *label);

#endif
