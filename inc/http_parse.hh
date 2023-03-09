#ifndef HTTP_PARSE_H
#define HTTP_PARSE_H
enum class CHECK_STATE { PREQUESTLINE, HEADER, CONTENT };

enum class LINE_STATUS { LINE_OK, LINE_BAD, LINE_OPEN };

enum class HTTP_CODE {
    NO_REQUEST,
    GET_REQUEST,
    BAD_REQUEST,
    FORBIDDEN_REQUEST,
    INTERNAL_ERROR,
    CLOSED_CONNECTION
};

#define BUFFER_SIZE 4096

class http_parse{

private:
    LINE_STATUS parse_line();
};

#endif