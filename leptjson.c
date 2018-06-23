#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

#define EXPECT(c,ch) \
        do { \
            assert(*c->json == (ch));\
            c->json++;\
        } while(0)

typedef struct{
    const char* json;
} lept_context;

static void lept_parse_whitespace(lept_context* c){
    const char *p = c->json;
    while (*p == ' '|| *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c,lept_node* v){
    EXPECT(c,'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK; 
}

static int lept_parse_value(lept_context* c,lept_node* v){
    switch (*c->json){
        case 'n':  return lept_parse_null(c,v);
        case '\0':  return LEPT_PARSE_EXPECT_VALUE;
        default:    return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_node* v,const char* json){
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c,v);
}

lept_type lept_get_type(const lept_node *v)
{
    assert(v != NULL);
    return v->type;
}