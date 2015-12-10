#ifndef TYPE
#define TYPE

#include <QString>

#define HEADER_INCLUDE  0
#define HEADER_NON      1

#define STUDENT     1
#define PROFESSOR   2
#define DONCARE     3

#define POST_LOGIN  1
#define POST_USER   2
#define POST_CLASS  3
#define GET_USER    4
#define GET_CHAT    5
#define POST_CHAT   6
#define POST_REGISTER_REPORT    7
#define GET_REPORTLIST          8
#define GET_SUMMIT_LIST         9
#define POST_SUMMIT             10

#define SERVER_ADD "http://203.255.43.246:3000"
//#define SERVER_ADD "http://www.naver.com"

// 사용자 url
#define URL_STUDENT     "/student"
#define URL_PROFESSOR   "/professor"

// 로그인 url
#define URL_LOGIN       "/login"

// 유저정보 url
#define URL_USER        "/users"

// 채팅 url
#define URL_CHAT        "/chat"

// 리포트 등록 url
#define URL_REGISTER    "/report"

// 등록한 리포트 목록 요청 url
#define URL_SUMMIT_LIST "/report/submit/list"

#define URL_SUMMIT      "/report/submit"



//QString log_para[2] = {"student","passwd"};

#endif // TYPE

