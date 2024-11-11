#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define COLUMN_USERNAME_SIZE 32

typedef struct
{
   int id;

   char username[COLUMN_USERNAME_SIZE];

    } ROW;


 #define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE 5
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)


typedef struct
{
    ROW rows[TABLE_MAX_ROWS];
    size_t num_rows;
} TABLE;




    