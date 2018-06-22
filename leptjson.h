#include<stdio.h>

typedef enum{
    LEPT_NULL,
    LEPT_TRUE,
    LEPT_FALSE
}lept_type;

typedef struct{
    lept_type type;
}lept_node;

typedef enum{
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
}lept_error_type;

int lept_parse(lept_node * v,const char* json);

lept_type lept_get_type(const lept_node* v);