/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef CUBEPL1SCANNER_H
#define CUBEPL1SCANNER_H

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL                                         \
    cubeplparser::CubePL1Parser::token_type                             \
    cubeplparser::CubePL1Scanner::lex(                          \
        cubeplparser::CubePL1Parser::semantic_type * yylval,             \
        cubeplparser::CubePL1Parser::location_type * yylloc              \
        )
#endif

#ifndef __FLEX_LEXER_H
//#define yyFlexLexer Cube3FlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include "CubePL1Parser.h"

namespace cubeplparser
{
/** Scanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to CubeparserFlexLexer. However we change the context of the generated
 * yylex() function to be contained within the Scanner class. This is required
 * because the yylex() defined in yyFlexLexer has no parameters. */
class CubePL1Scanner : public yyFlexLexer
{
public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    CubePL1Scanner( std::istream*        arg_yyin = 0,
                    std::ostream*        arg_yyout = 0,
                    CubePL1ParseContext* parseContext = NULL );

    /** Required for virtual functions */
    virtual
    ~CubePL1Scanner();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated bison parser then
     * calls this virtual function to fetch new tokens. */
    virtual CubePL1Parser::token_type
    lex(
        CubePL1Parser::semantic_type* yylval,
        CubePL1Parser::location_type* yylloc
        );

private:

    CubePL1ParseContext* parseContext;
};
} // namespace parser

#endif // SCANNER_H
