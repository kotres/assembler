/**************************************************************************//**
 *\file  assembler.h
 *\brief Assembler structure and functions.
 *
 *\author Michel Kuhlburger
 *
 *\date 26/01/2018
******************************************************************************/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "sourceCode.h"
#include "label.h"

#define MAXIMUM_LINE_LENGTH 256


/**************************************************************************//**
 * \struct Assembler
 * \brief struct used for assembling source code file.
 *
 * Assembler is the struct that contains all the information necessairy to
 * assemble a source code file given to the programm.
 ******************************************************************************/

struct Assembler
{
    struct SourceCode *source_code;/**< A list of all the source code needed to be assembled. */
    uint32_t location_counter;/**< Used for counting the address of the instuction beeing assembled. */
    struct Label *labels;/**< A list of all the labels found in the source code. */
};

/**************************************************************************//**
 * \fn void assemblerInitialise(struct Assembler *assembler)
 * \brief Initializes all the Assembler members to 0 or NULL.
 * \param[in] assembler Pointer to assembler being initialized.
******************************************************************************/

void assemblerInitialise(struct Assembler *assembler);

/**************************************************************************//**
 * \fn int assemblerAssemble(struct Assembler *assembler,const char *source_file_name)
 * \brief Assembles the source code file into binary.
 * \param[in] assembler Pointer to assembler used for assembly.
 * \param[in] source_file_name Name of the source code file to be assembled
 * \return 0 if file could be assembled and -1 if not.
******************************************************************************/

int assemblerAssemble(struct Assembler *assembler,const char *source_file_name);

/**************************************************************************//**
 * \fn int assemblerLoadSourceCode(struct Assembler *assembler,const char *source_file_name)
 * \brief Loads the source code file contents into the assembler's source code list.
 * \param[in] assembler Pointer to assembler used for assembly.
 * \param[in] source_file_name Name of the source code file to be loaded.
 * \return 0 if file could be loaded and -1 if not.
******************************************************************************/

int assemblerLoadSourceCode(struct Assembler *assembler,const char *source_file_name);

/**************************************************************************//**
 * \fn int assemblerFindLabels(struct Assembler *assembler)
 * \brief Finds all the labels in the source code list.
 * \param[in] assembler Pointer to assembler used for assembly.
 * \return -1 if an error occured and 0 if not (even if no labels were found).
******************************************************************************/

int assemblerFindLabels(struct Assembler *assembler);

int assemblerDetermineLines(struct Assembler *assembler);

int assemblerResolveLabelValues(struct Assembler *assembler);

void assemblerDestroy(struct Assembler *assembler);

#endif
