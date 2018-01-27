/**************************************************************************//**
 *\file  sourceCode.h
 *\brief Source code structure and functions.
 *
 *\author Michel Kuhlburger
 *
 *\date 26/01/2018
******************************************************************************/

#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "label.h"

/**************************************************************************//**
 * \enum SourceCodeType
 * \brief Used for describing the type of line a Source code node is.
*/
enum SourceCodeType{
    label_type,/**< The source code node contains a label.*/
    label_dependent_code_type,/**< An instruction that has a label parameter.*/
    position_dependent_code_type,/**< The instruction's value depends on its half word position.*/
    static_code_type,/**< An instruction that doesn't have a label parameter.*/
    org_type,/**< An org directive overwriting the assembler's location counter.*/
    not_determined_type/**< The line type hasn't been determined yet.*/
};

/**************************************************************************//**
 * \struct SourceCode
 * \brief Node for making source code lists.
 *
 * SourceCode is a list node type struct that contains the original source code string and
 * all the necessairy data to process it.
 ******************************************************************************/

struct SourceCode
{
    char *line;/**< The original source code line contained in a source code file, used for user messages. */
    char *clean_line;/**< A processed version of line used for assmbling. */
    unsigned int line_number;/**< The line number of line in the original source code file. */
    struct SourceCode *next_line;/**< A pointer to the next node. */

    unsigned int binary_size;/**< The size in half words of the processed line.*/
    uint16_t *binary_data;/**< The binary data of the processed line.*/
    enum SourceCodeType type;/**< The type of source code line.*/
    struct Label *label;/**< Pointer to the label needed to process the line (NULL if no label is required)*/
    uint32_t instruction_label_value;/**< Value of the label used when processing the line*/

};

enum ProcessorInstructions{
    ALU_instruction,
    SHIFT_instruction,
    LOAD_instruction,
    LODL_instruction,
    MOV_instruction,
    MUL_instruction,
    BR_instruction,
    BRL_instruction,
    HALT_instruction,
    INT_instruction,
    NOP_instruction,
    PUSH_instruction,
    POP_instruction,
    STOR_instruction,
    INVALID_instruction
};

/**************************************************************************//**
 * \fn int sourceCodeInitialise(struct SourceCode **code,const char* line,unsigned int line_number)
 * \brief Initalizes a NULL source code pointer into the first node of a source code list.
 * \param[in] code Pointer to a NULL source code pointer.
 * \param[in] line String of line retrieved from source file.
 * \param[in] line_number Number of the line in the source file.
 * \return 0 if source code could be initialized, -1 if an error occured.
******************************************************************************/

int sourceCodeInitialise(struct SourceCode **code,const char* line,unsigned int line_number);

/**************************************************************************//**
 * \fn int sourceCodePushBack(struct SourceCode *code,const char* line,unsigned int line_number)
 * \brief Creates a new source code node and puts it at the back of the list pointed by *code.
 * \param[in] code A non NULL source code pointer.
 * \param[in] line String of line retrieved from source file.
 * \param[in] line_number Number of the line in the source file.
 * \return 0 if source code node could be initialized, -1 if an error occured.
******************************************************************************/

int sourceCodePushBack(struct SourceCode *code,const char* line,unsigned int line_number);

/**************************************************************************//**
 * \fn void sourceCodeDestroy(struct SourceCode *code)
 * \brief destroys source code list by freeing all alloced data assigned to it.
 * \param[in] code A non NULL source code pointer.
******************************************************************************/

void sourceCodeDestroy(struct SourceCode *code);

/**************************************************************************//**
 * \fn sourceCodePrint(struct SourceCode *code)
 * \brief Prints to screen all the data contained in a source code list.
 * \param[in] code A non NULL source code pointer.
******************************************************************************/

void sourceCodePrint(struct SourceCode *code);

/**************************************************************************//**
 * \fn void sourceCodeCleanLine(const char *line)
 * \brief Cleans a line string for later processing.
 * Cleans a line string by removing all whitespace,
 *  comments and converting all lower case caracters to upper case.
 * \param[in] line A non NULL string of the line to be cleaned.
******************************************************************************/

void sourceCodeCleanLine(const char *line);

/**************************************************************************//**
 * \fn void sourceCodeRemoveWhitespace(const char *line)
 * \brief Removes all whitespace from a string.
 * \param[in] line A non NULL string of the string where the whitespace will be removed.
******************************************************************************/

void sourceCodeRemoveWhitespace(const char *line);

/**************************************************************************//**
 * \fn void sourceCodeConvertToUpperCase(const char *line)
 * \brief Converts all lower case characters of a string to uper case.
 * \param[in] line A non NULL string of the string where the whitespace will be removed.
******************************************************************************/

void sourceCodeConvertToUpperCase(const char *line);

int sourceCodeDetermineDirective(struct SourceCode *source_code_iterator);

int sourceCodeEncodeInstruction(struct SourceCode *source_code_iterator,uint32_t position);

int sourceCodeEncodeALUInstruction(struct SourceCode *source_code_iterator, unsigned char opcode, char *parameters);

enum ProcessorInstructions sourceCodeDetermineInstructionType(char **line_ptr, unsigned char *opcode);

unsigned char sourceCodeDetermineRegister(char **line_ptr);

int sourceCodeDetermineImmediate(char** line_ptr,uint32_t *immediate);

#endif
