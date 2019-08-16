/*
 * key_intf.h
 * element 5 key generator 
 * constant declarations
 *
 * DO NOT MODIFY
 */

/* possible exit codes */
#define ERC_SUCCESS	00
#define ERC_SUCCESS_BIN	01

#define ERC_ERROR 	10
#define ERC_MEMORY	11
#define ERC_FILE_IO	12
#define ERC_BAD_ARGS    13
#define ERC_BAD_INPUT   14
#define ERC_EXPIRED     15
#define ERC_INTERNAL    16

/* possible values for language_id */
#define liEnglish       1
#define liGerman        2
#define liPortuguese    3
#define liSpanish       4
#define liItalian       5
#define liFrench        6
