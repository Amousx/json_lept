#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum{
    LEPT_NULL,
    LEPT_TRUE,
    LEPT_FALSE,
    LEPT_NUMEBR,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
}lept_type;

typedef struct{
    lept_type type;
}lept_value;    //tree struct ,just like the node

typedef enum{
    LEPT_PARSE_OK = 0,                   //正常返回
    LEPT_PARSE_EXPECT_VALUE,             //json只有空白
    LEPT_PARSE_INVALID_VALUE,            //非其他情况
    LEPT_PARSE_ROOT_NOT_SINGULAR         //空白之后还有词
}lept_error_type;    //enum return types

int lept_parse(lept_value * v,const char* json);

lept_type lept_get_type(const lept_value* v);   //return the type of the node

#endif     /*LEPTJSON_H__*/