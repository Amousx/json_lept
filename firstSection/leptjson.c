#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;

static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    if(*c->json =='\0'){
        v->type = LEPT_NULL;
        return LEPT_PARSE_OK;
    }
    else if(*c->json == ' '){
        lept_parse_whitespace(c);
        if(*c->json == '\0') return LEPT_PARSE_INVALID_VALUE;
        else{
            v->type = LEPT_NULL;
            return LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
}

static int lept_parse_root_not_singular(lept_context* c, lept_value* v){
    while(*c->json != ' ' || *c->json != '\0'){
        c->json++;
    }
    
    if(*c->json == ' '){
        lept_parse_whitespace(c);
    }
    if(*c->json == '\0') return LEPT_PARSE_INVALID_VALUE;
    v->type = LEPT_NULL;
    return LEPT_PARSE_ROOT_NOT_SINGULAR;
}

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);    //空
        case '\0': return LEPT_PARSE_EXPECT_VALUE;  //纯空白
        //default:   return LEPT_PARSE_INVALID_VALUE; //其他情况
        default: return lept_parse_root_not_singular(c,v);
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    return lept_parse_value(&c, v);
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}