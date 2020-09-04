// A Bison parser, made by GNU Bison 3.4.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "AutoGenParser.hpp"


// Unqualified %code blocks.
#line 66 "src/lang/script/parser/AutoGenParser.yy"

#include "Parser.h"
#include "Lexer.h"
#include "yylex_function.h"

using namespace IAS;
using namespace Lang;
using namespace Model;
using namespace Script;
using namespace Parser;


#line 58 "src/lang/script/parser/AutoGenParser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 152 "src/lang/script/parser/AutoGenParser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   AutoGenParser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   AutoGenParser :: AutoGenParser  (::IAS::Lang::Script::Parser::Parser& myParser_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      myParser (myParser_yyarg)
  {}

   AutoGenParser ::~ AutoGenParser  ()
  {}

   AutoGenParser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
   AutoGenParser ::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
    , location (std::move (that.location))
  {}
#endif

  template <typename Base>
   AutoGenParser ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
   AutoGenParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
   AutoGenParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  bool
   AutoGenParser ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
   AutoGenParser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_type.
   AutoGenParser ::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
   AutoGenParser ::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

   AutoGenParser ::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

   AutoGenParser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
   AutoGenParser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
   AutoGenParser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
   AutoGenParser ::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
   AutoGenParser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   AutoGenParser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   AutoGenParser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   AutoGenParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   AutoGenParser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   AutoGenParser ::symbol_number_type
   AutoGenParser ::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

   AutoGenParser ::stack_symbol_type::stack_symbol_type ()
  {}

   AutoGenParser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   AutoGenParser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
   AutoGenParser ::stack_symbol_type&
   AutoGenParser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   AutoGenParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
      case 76: // T_SYMBOL
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 386 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      case 77: // T_STRING
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 392 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      case 78: // T_INTEGER
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 398 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      case 79: // T_LONG
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 404 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      case 80: // T_FLOAT
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 410 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      case 81: // T_BOOLEAN
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 416 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      case 82: // T_NULL
#line 240 "src/lang/script/parser/AutoGenParser.yy"
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 422 "src/lang/script/parser/AutoGenParser.cpp"
        break;

      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
   AutoGenParser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
   AutoGenParser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   AutoGenParser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   AutoGenParser ::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   AutoGenParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   AutoGenParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   AutoGenParser ::debug_level_type
   AutoGenParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   AutoGenParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   AutoGenParser ::state_type
   AutoGenParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
   AutoGenParser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   AutoGenParser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   AutoGenParser ::operator() ()
  {
    return parse ();
  }

  int
   AutoGenParser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 26 "src/lang/script/parser/AutoGenParser.yy"
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = new std::string("waisted");
}

#line 568 "src/lang/script/parser/AutoGenParser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, myParser));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 5:
#line 248 "src/lang/script/parser/AutoGenParser.yy"
    { myParser.addTypeDefinition((yystack_[0].value.pTypeDefinitionNode)); }
#line 693 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 6:
#line 249 "src/lang/script/parser/AutoGenParser.yy"
    {
    (yystack_[0].value.pProgramNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
	myParser.addProgram((yystack_[0].value.pProgramNode));
}
#line 702 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 7:
#line 254 "src/lang/script/parser/AutoGenParser.yy"
    {
  myParser.addNamespaceAlias((yystack_[0].value.pNamespaceAliasNode));
}
#line 710 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 8:
#line 259 "src/lang/script/parser/AutoGenParser.yy"
    {  myParser.open((yystack_[1].value.pQualifiedNameNode)->getQualifiedName());
           	 IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Free((yystack_[1].value.pQualifiedNameNode));
           	 }
#line 718 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 9:
#line 264 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval));
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 726 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 10:
#line 269 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[2].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[8].value.sval)); _SVAL_DELETE((yystack_[8].value.sval));
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[6].value.sval)); _SVAL_DELETE((yystack_[6].value.sval)); }
#line 735 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 11:
#line 275 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval));
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[1].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 743 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 12:
#line 280 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[1].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[7].value.sval)); _SVAL_DELETE((yystack_[7].value.sval));
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); }
#line 752 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 13:
#line 287 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 758 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 14:
#line 290 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 764 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 15:
#line 292 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode); }
#line 770 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 16:
#line 293 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();  }
#line 776 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 17:
#line 295 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[2].value.pTypeDefinitionNode); (yylhs.value.pTypeDefinitionNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 782 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 18:
#line 296 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();}
#line 788 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 19:
#line 298 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 794 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 20:
#line 299 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval));
												                _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 801 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 21:
#line 301 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval));
												 (yylhs.value.pDeclarationNode)->setIsArray(true);
												 _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 809 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 22:
#line 304 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval));
																  (yylhs.value.pDeclarationNode)->setIsArray(true);
												                  _SVAL_DELETE((yystack_[6].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 817 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 23:
#line 309 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pNamespaceAliasNode) = IAS_DFT_FACTORY<Dec::NamespaceAliasNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval));
					_SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 824 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 24:
#line 313 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[3].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[2].value.pParametersNode)); }
#line 830 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 25:
#line 316 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[4].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[3].value.pParametersNode),(yystack_[2].value.pDeclarationNode)); }
#line 836 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 26:
#line 319 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[5].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[4].value.pParametersNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE_StringList((yystack_[1].value.pStringList));}
#line 842 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 27:
#line 322 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[6].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[5].value.pParametersNode),(yystack_[4].value.pDeclarationNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE_StringList((yystack_[1].value.pStringList));}
#line 848 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 28:
#line 324 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval));
  (yylhs.value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  _SVAL_DELETE((yystack_[0].value.sval));
}
#line 858 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 29:
#line 329 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));
  (yylhs.value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  _SVAL_DELETE((yystack_[2].value.sval));
  _SVAL_DELETE((yystack_[0].value.sval));
}
#line 869 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 30:
#line 336 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval));
  (yylhs.value.pDeclarationNode)->setIsArray(true);
  (yylhs.value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  _SVAL_DELETE((yystack_[0].value.sval));
}
#line 880 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 31:
#line 342 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));
  (yylhs.value.pDeclarationNode)->setIsArray(true);
  (yylhs.value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  _SVAL_DELETE((yystack_[2].value.sval));
  _SVAL_DELETE((yystack_[0].value.sval));
}
#line 892 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 32:
#line 350 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pParametersNode) = (yystack_[1].value.pParametersNode); }
#line 898 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 33:
#line 351 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();  }
#line 904 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 34:
#line 353 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pParametersNode) = (yystack_[2].value.pParametersNode);
  (yystack_[0].value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode));
}
#line 914 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 35:
#line 358 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();
  (yystack_[0].value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode));
 }
#line 924 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 36:
#line 364 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementsListNode) = (yystack_[1].value.pStatementsListNode); }
#line 930 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 37:
#line 366 "src/lang/script/parser/AutoGenParser.yy"
    {
(yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode);
(yystack_[1].value.pStatementNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
(yylhs.value.pStatementsListNode)->addStatement((yystack_[1].value.pStatementNode));
 }
#line 940 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 38:
#line 371 "src/lang/script/parser/AutoGenParser.yy"
    {
  (yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode);
  (yystack_[1].value.pDeclarationNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
  (yylhs.value.pStatementsListNode)->addDeclaration((yystack_[1].value.pDeclarationNode));
}
#line 950 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 39:
#line 376 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementsListNode) = IAS_DFT_FACTORY<Stmt::StatementsListNode>::Create(); }
#line 956 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 40:
#line 378 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 962 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 41:
#line 379 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 968 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 42:
#line 381 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval));     (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[4].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 974 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 43:
#line 383 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[6].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 980 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 44:
#line 386 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementsListNode); }
#line 986 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 45:
#line 387 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); (yylhs.value.pStatementNode)->setSourceLocation(myParser.getLexer()->getCachedLocation()); }
#line 992 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 46:
#line 388 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 998 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 47:
#line 389 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1004 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 48:
#line 390 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1010 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 49:
#line 391 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1016 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 50:
#line 392 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1022 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 51:
#line 393 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1028 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 52:
#line 394 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1034 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 53:
#line 395 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1040 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 54:
#line 396 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1046 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 55:
#line 397 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1052 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 56:
#line 398 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1058 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 57:
#line 399 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1064 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 58:
#line 400 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1070 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 59:
#line 401 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1076 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 60:
#line 402 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1082 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 61:
#line 404 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::AssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1088 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 62:
#line 405 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ConditionalAssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pXPathAccessNode)); }
#line 1094 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 63:
#line 406 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::MergeNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1100 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 64:
#line 408 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLeftSideNode) = IAS_DFT_FACTORY<Stmt::LeftSideNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1106 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 65:
#line 415 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1112 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 66:
#line 416 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::AdditionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1118 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 67:
#line 417 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SubtractionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1124 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 68:
#line 419 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1130 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 69:
#line 420 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::MultiplyNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1136 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 70:
#line 421 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DivisionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1142 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 71:
#line 422 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ModuloNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1148 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 72:
#line 424 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1154 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 73:
#line 426 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1160 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 74:
#line 427 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPath::XPathExprNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1166 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 75:
#line 429 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = (yystack_[1].value.pExprNode); }
#line 1172 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 76:
#line 430 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_INTEGER,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1178 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 77:
#line 431 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_LONG,*(yystack_[0].value.sval));    _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1184 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 78:
#line 432 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_FLOAT,*(yystack_[0].value.sval));   _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1190 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 79:
#line 433 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_STRING,*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1196 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 80:
#line 434 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_BOOLEAN,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1202 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 81:
#line 435 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_NULL,*(yystack_[0].value.sval));    _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1208 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 82:
#line 437 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1214 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 83:
#line 439 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval), (yystack_[0].value.pStatementsListNode)); _SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 1220 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 84:
#line 442 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CastNode>::Create((yystack_[3].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1226 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 85:
#line 445 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPathOrValueNode>::Create((yystack_[3].value.pXPathAccessNode),(yystack_[1].value.pExprNode)); }
#line 1232 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 86:
#line 448 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CondValueNode>::Create((yystack_[5].value.pLogicalExprNode),(yystack_[3].value.pExprNode),(yystack_[1].value.pExprNode)); }
#line 1238 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 87:
#line 450 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::FunCallNode>::Create((yystack_[1].value.pQualifiedNameNode), (yystack_[0].value.pExprListNode)); }
#line 1244 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 88:
#line 451 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CopyOfNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1250 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 89:
#line 452 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DetachNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1256 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 90:
#line 453 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::NegativeNode>::Create((yystack_[0].value.pExprNode)); }
#line 1262 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 91:
#line 454 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SizeOfNode>::Create((yystack_[1].value.pXPathAccessNode));}
#line 1268 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 92:
#line 455 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNode>::Create((yystack_[1].value.pExprNode));}
#line 1274 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 93:
#line 456 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNSNode>::Create((yystack_[1].value.pExprNode));}
#line 1280 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 94:
#line 457 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::StrLenNode>::Create((yystack_[1].value.pExprNode));}
#line 1286 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 95:
#line 459 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1292 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 96:
#line 461 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalDiffNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1298 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 97:
#line 462 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1304 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 98:
#line 463 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1310 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 99:
#line 464 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1316 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 100:
#line 465 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1322 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 101:
#line 468 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsTypeNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1328 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 102:
#line 471 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsInstanceNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1334 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 103:
#line 473 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1340 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 104:
#line 474 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = (yystack_[1].value.pLogicalExprNode); }
#line 1346 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 105:
#line 475 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalNotNode>::Create((yystack_[0].value.pLogicalExprNode)); }
#line 1352 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 106:
#line 476 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsSetNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1358 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 107:
#line 477 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsNullNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1364 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 108:
#line 479 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1370 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 109:
#line 480 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalAndNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1376 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 110:
#line 482 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1382 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 111:
#line 483 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalOrNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1388 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 112:
#line 485 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1394 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 113:
#line 488 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
								IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNode>::Create(
										(*((yystack_[0].value.pXPathNode)->getElements().begin()))->getName()),(yystack_[0].value.pXPathNode));}
#line 1402 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 114:
#line 492 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
						IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNode>::Create((yystack_[2].value.pExprNode)),(yystack_[0].value.pXPathNode)); }
#line 1409 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 115:
#line 495 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathNode) = (yystack_[2].value.pXPathNode); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1415 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 116:
#line 497 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1421 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 117:
#line 500 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addHashIndexElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1427 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 118:
#line 502 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1433 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 119:
#line 504 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1439 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 120:
#line 507 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addHashIndexElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1445 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 121:
#line 509 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create("",(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); }
#line 1451 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 122:
#line 510 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create(*(yystack_[4].value.sval),(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); _SVAL_DELETE((yystack_[4].value.sval)); }
#line 1457 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 123:
#line 512 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WhileLoopNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1463 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 124:
#line 515 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[6].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1469 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 125:
#line 518 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[8].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[6].value.pExprNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1475 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 126:
#line 520 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1481 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 127:
#line 523 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[4].value.pLogicalExprNode),(yystack_[2].value.pStatementNode),(yystack_[0].value.pStatementNode)); }
#line 1487 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 128:
#line 525 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1493 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 129:
#line 527 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1499 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 130:
#line 528 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1505 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 131:
#line 529 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[1].value.pXPathAccessNode),(yystack_[0].value.pStatementsListNode)); }
#line 1511 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 132:
#line 530 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::DeleteNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1517 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 133:
#line 532 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create(); }
#line 1523 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 134:
#line 533 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create((yystack_[0].value.pExprNode)); }
#line 1529 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 135:
#line 536 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create((yystack_[0].value.pExprNode)); }
#line 1535 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 136:
#line 538 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::SortNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pQualifiedNameNode)); }
#line 1541 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 137:
#line 540 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IndexNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pXPathAccessNode));}
#line 1547 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 138:
#line 542 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::TryCatchNode>::Create((yystack_[1].value.pStatementsListNode),(yystack_[0].value.pCatchListNode));  }
#line 1553 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 139:
#line 543 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pCatchListNode) = (yystack_[1].value.pCatchListNode); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode));           }
#line 1559 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 140:
#line 544 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pCatchListNode) = IAS_DFT_FACTORY<Stmt::CatchListNode>::Create(); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode)); }
#line 1565 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 141:
#line 547 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pCatchNode) = IAS_DFT_FACTORY<Stmt::CatchNode>::Create((yystack_[2].value.pDeclarationNode),(yystack_[0].value.pStatementsListNode)); }
#line 1571 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 142:
#line 549 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create(); }
#line 1577 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 143:
#line 550 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprListNode)=(yystack_[1].value.pExprListNode); }
#line 1583 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 144:
#line 552 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprListNode)=(yystack_[2].value.pExprListNode); (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1589 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 145:
#line 553 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create();  (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1595 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 146:
#line 555 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStringList) = new StringList;}
#line 1601 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 147:
#line 556 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStringList)=(yystack_[1].value.pStringList); }
#line 1607 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 148:
#line 558 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStringList)=(yystack_[2].value.pStringList); (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 1613 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 149:
#line 559 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pStringList) = new StringList; (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1619 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 150:
#line 562 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pQualifiedNameNode)= IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1625 "src/lang/script/parser/AutoGenParser.cpp"
    break;

  case 151:
#line 563 "src/lang/script/parser/AutoGenParser.yy"
    { (yylhs.value.pQualifiedNameNode)=(yystack_[2].value.pQualifiedNameNode); (yylhs.value.pQualifiedNameNode)->addNextSymbol(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1631 "src/lang/script/parser/AutoGenParser.cpp"
    break;


#line 1635 "src/lang/script/parser/AutoGenParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   AutoGenParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
   AutoGenParser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short  AutoGenParser ::yypact_ninf_ = -194;

  const short  AutoGenParser ::yytable_ninf_ = -151;

  const short
   AutoGenParser ::yypact_[] =
  {
    -194,    34,  -194,   -56,   -56,    -7,    33,  -194,  -194,  -194,
    -194,  -194,  -194,   -38,   -14,    -5,    71,    49,  -194,   -11,
      31,    77,   109,  -194,    67,  -194,    46,  -194,  -194,   -10,
      79,    38,    91,   -15,    81,   140,  -194,   137,   330,   141,
     111,   144,   101,   118,  -194,    96,  -194,   123,    -2,  -194,
    -194,    15,    15,    15,   146,   146,    15,    15,   184,   421,
     146,   115,   166,   169,   170,    15,    15,   -56,   174,   177,
     178,   467,    63,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
     152,   153,  -194,  -194,  -194,     6,   155,  -194,   164,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,    51,   154,   156,    10,   165,   144,  -194,   225,
     205,   171,  -194,   206,   175,   228,    51,   229,   172,   146,
     146,   207,   216,   190,    32,    60,  -194,   155,  -194,  -194,
     220,   239,   235,  -194,   241,  -194,  -194,   237,    69,   246,
      94,   247,   200,   244,   217,    15,    15,    15,   184,  -194,
      51,    15,    15,    15,  -194,    15,    15,  -194,  -194,    15,
      15,    15,   208,   209,   231,   221,   218,  -194,  -194,  -194,
      61,  -194,   222,  -194,    -1,   211,  -194,   214,   226,   -56,
    -194,    15,    15,  -194,    11,    15,    15,   245,   254,    15,
      15,    15,    15,    15,    15,    15,    15,    15,    15,    15,
     146,   146,   407,   407,   256,   237,  -194,    15,   407,  -194,
     211,    15,    15,   227,   257,   260,   264,  -194,  -194,   267,
     268,   276,   261,   262,  -194,  -194,  -194,    48,   164,    76,
    -194,  -194,    66,   240,  -194,   242,  -194,  -194,   287,   259,
     263,     5,   265,  -194,   258,  -194,   303,  -194,   285,   289,
     211,   211,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,   307,   137,  -194,   311,
    -194,   295,   271,   297,   184,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,    15,    15,  -194,    15,  -194,  -194,     2,
    -194,   270,  -194,   272,   273,    15,  -194,  -194,   301,   306,
     407,   310,   407,  -194,    15,  -194,  -194,   299,   304,  -194,
     327,   296,  -194,  -194,  -194,   129,  -194,  -194,  -194,   184,
    -194,   323,  -194,  -194,   286,   288,    15,   407,  -194,  -194,
     305,  -194,   344,  -194,   302,   407,  -194,  -194
  };

  const unsigned char
   AutoGenParser ::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     3,     4,     5,
       7,     6,   150,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,   151,     0,    33,     0,    35,    39,     0,
       0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
      28,     0,     0,     0,    24,     0,    11,     0,     0,    34,
      36,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,    79,    76,    77,    78,    80,    81,    44,
       0,     0,    45,    46,    47,     0,     0,    64,   113,    50,
      49,    48,    51,    53,    54,    55,    56,    57,    59,    58,
      52,    60,     0,     0,     0,     0,     0,     0,    25,    18,
       0,     0,    23,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    68,    72,    73,   103,   108,
     110,   112,     0,    74,     0,   134,   135,     0,   118,     0,
       0,    72,     0,    74,     0,     0,     0,     0,   130,   132,
       0,     0,     0,     0,    90,     0,     0,    38,    37,     0,
       0,     0,     0,     0,     0,   128,    30,    29,   146,   149,
       0,    26,     0,    16,     0,     0,     9,     0,     0,     0,
      87,     0,     0,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   140,     0,     0,    75,
       0,     0,     0,     0,     0,     0,     0,   131,   129,     0,
       0,     0,     0,     0,    63,    61,    62,   118,   114,   115,
     142,   145,     0,     0,   147,     0,    27,    15,     0,     0,
      13,     0,    42,    41,   136,   137,     0,   104,     0,     0,
       0,     0,    95,    99,    97,   100,    98,    96,    66,    67,
      69,    70,    71,   109,   111,   123,   126,     0,   139,     0,
     121,     0,     0,     0,    82,    91,    88,    89,    92,    93,
      94,   119,   120,     0,     0,   143,     0,    31,   148,     0,
      17,     0,    12,     0,     0,     0,   106,   107,     0,     0,
       0,     0,     0,    84,     0,    85,    83,     0,     0,   144,
       0,    19,    14,    10,    43,     0,   101,   102,   127,     0,
     122,     0,   116,   117,     0,     0,     0,     0,   141,    86,
      21,    20,     0,   124,     0,     0,    22,   125
  };

  const short
   AutoGenParser ::yypgoto_[] =
  {
    -194,  -194,  -194,  -194,  -194,  -169,   125,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,   -18,  -194,   -33,  -193,  -194,  -194,
    -194,  -194,    57,   -43,   -62,   -52,    -6,  -194,   266,   180,
     183,   -48,   -35,   219,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   173,   -80,
    -194,   279,  -194,    -3
  };

  const short
   AutoGenParser ::yydefgoto_[] =
  {
      -1,     1,     7,     8,     9,   241,   111,   174,   239,    10,
      11,    31,    20,    26,    79,    38,    27,    81,    82,    83,
      84,    85,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   205,   206,   165,
     232,   106,   170,   116
  };

  const short
   AutoGenParser ::yytable_[] =
  {
      13,    14,    32,    87,    49,    80,   237,   134,   141,   265,
     266,   109,   142,    43,    45,   270,   115,   117,   118,   159,
      12,    39,    24,    19,   139,   143,    17,    25,    18,   113,
     148,   149,    86,   310,     2,   102,   180,    28,     3,     4,
     137,   271,     5,    16,    28,    86,    86,    86,   168,   247,
      17,    46,    60,    86,    61,    62,    63,    64,    21,    86,
      86,    68,    69,    29,   150,   154,    40,    70,   141,    15,
     218,   292,   184,    71,   114,   238,    30,     6,   311,   160,
     161,   298,   299,    42,    36,   143,   211,   169,   164,   195,
     196,    72,    73,    74,    75,    76,    77,    78,   207,   234,
    -150,   155,   109,   156,   285,   110,  -150,   318,    37,   320,
     214,   215,   216,   135,   136,    17,   155,   140,   156,   197,
     198,   199,   155,   235,   156,    23,   226,  -150,   286,   283,
     217,   284,   209,  -150,   333,   260,   261,   262,    34,    86,
      86,    86,   337,    35,   187,   188,   245,   326,    22,   327,
     248,   249,   258,   259,    33,    86,    41,    44,    47,   272,
     273,   189,   190,   191,   192,   193,   194,    87,    87,    48,
      24,   103,   269,    87,   104,    86,   244,   140,   107,    86,
      86,   105,   119,   120,   108,    61,    62,    63,    64,   112,
      28,   144,    68,    69,   121,   122,    86,    86,    70,   102,
     102,    86,    86,   145,    71,   102,   146,   147,   219,   220,
     221,   151,   222,   223,   152,   153,   224,   225,   157,   158,
     162,   231,    72,    73,    74,    75,    76,    77,    78,   163,
     166,   171,   173,   167,   301,   175,   177,   176,   178,   246,
     187,   188,   179,   181,   185,   182,   252,   253,   254,   255,
     256,   257,   321,   186,   200,   202,   306,   189,   190,   191,
     192,   193,   194,   203,   204,    87,   208,    87,    60,   230,
      61,    62,    63,    64,   201,   211,   210,    68,    69,   212,
     213,   233,   250,    70,   227,   229,   -87,   240,   236,    71,
     242,   251,    87,   267,    86,   275,    86,   102,   276,   102,
      87,   328,   277,   243,   274,   278,   279,    72,    73,    74,
      75,    76,    77,    78,   280,   281,   289,   287,   282,   288,
     295,    86,    17,   296,   102,   290,   291,   297,   294,    86,
     300,   302,   102,   303,   304,   305,    28,    50,   313,   316,
     307,   308,    51,   309,   317,    52,    53,   312,   319,    54,
     314,    55,   315,   322,    56,    57,    58,   324,    59,   325,
     323,   329,   330,    24,   335,   331,   293,    60,   334,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   268,   336,
     263,   228,    70,   332,   264,   183,   172,     0,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    78,    28,     0,     0,     0,     0,     0,    51,
       0,     0,    52,    53,     0,     0,    54,     0,    55,     0,
       0,    56,    57,    58,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,     0,     0,     0,    60,    70,
      61,    62,    63,    64,     0,    71,     0,    68,    69,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,    71,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,     0,     0,     0,     0,     0,   138,    73,    74,
      75,    76,    77,    78,    60,     0,    61,    62,    63,    64,
       0,     0,     0,    68,    69,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    73,    74,    75,    76,    77,    78
  };

  const short
   AutoGenParser ::yycheck_[] =
  {
       3,     4,    20,    38,    37,    38,     7,    55,    60,   202,
     203,     6,    60,    31,    29,   208,    51,    52,    53,    13,
      76,    31,    33,    37,    59,    60,    64,    38,    66,    31,
      65,    66,    38,    31,     0,    38,   116,     6,     4,     5,
      58,   210,     8,    10,     6,    51,    52,    53,    38,    38,
      64,    66,    37,    59,    39,    40,    41,    42,    63,    65,
      66,    46,    47,    32,    67,    71,    76,    52,   120,    76,
     150,    66,   120,    58,    76,    76,    45,    43,    76,    73,
      74,   250,   251,    45,    38,   120,    75,    77,    37,    57,
      58,    76,    77,    78,    79,    80,    81,    82,    29,    38,
      37,    53,     6,    55,    38,     9,    37,   300,    62,   302,
     145,   146,   147,    56,    57,    64,    53,    60,    55,    59,
      60,    61,    53,    62,    55,    76,   161,    64,    62,    53,
     148,    55,    38,    64,   327,   197,   198,   199,    29,   145,
     146,   147,   335,    76,    50,    51,   181,    18,    77,    20,
     185,   186,   195,   196,    77,   161,    77,    66,    77,   211,
     212,    67,    68,    69,    70,    71,    72,   202,   203,    29,
      33,    30,   207,   208,    63,   181,   179,   120,    77,   185,
     186,    37,    36,    37,    66,    39,    40,    41,    42,    66,
       6,    76,    46,    47,    48,    49,   202,   203,    52,   202,
     203,   207,   208,    37,    58,   208,    37,    37,   151,   152,
     153,    37,   155,   156,    37,    37,   159,   160,    66,    66,
      65,   164,    76,    77,    78,    79,    80,    81,    82,    65,
      76,    66,     7,    77,   267,    30,    30,    66,    63,   182,
      50,    51,    14,    14,    37,    73,   189,   190,   191,   192,
     193,   194,   304,    37,    34,    20,   274,    67,    68,    69,
      70,    71,    72,    22,    27,   300,    20,   302,    37,    38,
      39,    40,    41,    42,    35,    75,    29,    46,    47,    35,
      63,    63,    37,    52,    76,    76,    65,    76,    66,    58,
      76,    37,   327,    37,   300,    38,   302,   300,    38,   302,
     335,   319,    38,    77,    77,    38,    38,    76,    77,    78,
      79,    80,    81,    82,    38,    54,    29,    77,    56,    77,
      17,   327,    64,    38,   327,    66,    63,    38,    63,   335,
      23,    20,   335,    38,    63,    38,     6,     7,    66,    38,
     283,   284,    12,   286,    38,    15,    16,    77,    38,    19,
      77,    21,   295,    54,    24,    25,    26,    30,    28,    63,
      56,    38,    76,    33,    20,    77,   241,    37,    63,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   205,    77,
     200,   162,    52,   326,   201,   119,   107,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,     6,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    15,    16,    -1,    -1,    19,    -1,    21,    -1,
      -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    37,    52,
      39,    40,    41,    42,    -1,    58,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    37,    -1,    39,    40,    41,    42,
      -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82
  };

  const unsigned char
   AutoGenParser ::yystos_[] =
  {
       0,    84,     0,     4,     5,     8,    43,    85,    86,    87,
      92,    93,    76,   136,   136,    76,    10,    64,    66,    37,
      95,    63,    77,    76,    33,    38,    96,    99,     6,    32,
      45,    94,    97,    77,    29,    76,    38,    62,    98,    31,
      76,    77,    45,    97,    66,    29,    66,    77,    29,    99,
       7,    12,    15,    16,    19,    21,    24,    25,    26,    28,
      37,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      52,    58,    76,    77,    78,    79,    80,    81,    82,    97,
      99,   100,   101,   102,   103,   104,   109,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   136,    30,    63,    37,   134,    77,    66,     6,
       9,    89,    66,    31,    76,   115,   136,   115,   115,    36,
      37,    48,    49,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   114,   105,   105,    97,    76,   115,
     105,   108,   114,   115,    76,    37,    37,    37,   115,   115,
     136,    37,    37,    37,   109,    53,    55,    66,    66,    13,
      73,    74,    65,    65,    37,   132,    76,    77,    38,    77,
     135,    66,   134,     7,    90,    30,    66,    30,    63,    14,
     132,    14,    73,   111,   114,    37,    37,    50,    51,    67,
      68,    69,    70,    71,    72,    57,    58,    59,    60,    61,
      34,    35,    20,    22,    27,   130,   131,    29,    20,    38,
      29,    75,    35,    63,   115,   115,   115,    97,   132,   105,
     105,   105,   105,   105,   105,   105,   115,    76,   116,    76,
      38,   105,   133,    63,    38,    62,    66,     7,    76,    91,
      76,    88,    76,    77,   136,   115,   105,    38,   115,   115,
      37,    37,   105,   105,   105,   105,   105,   105,   106,   106,
     107,   107,   107,   112,   113,   100,   100,    37,   131,   115,
     100,    88,   108,   108,    77,    38,    38,    38,    38,    38,
      38,    54,    56,    53,    55,    38,    62,    77,    77,    29,
      66,    63,    66,    89,    63,    17,    38,    38,    88,    88,
      23,    99,    20,    38,    63,    38,    97,   105,   105,   105,
      31,    76,    77,    66,    77,   105,    38,    38,   100,    38,
     100,   108,    54,    56,    30,    63,    18,    20,    97,    38,
      76,    77,   105,   100,    63,    20,    77,   100
  };

  const unsigned char
   AutoGenParser ::yyr1_[] =
  {
       0,    83,    84,    84,    85,    85,    85,    85,    86,    87,
      87,    87,    87,    88,    88,    89,    89,    90,    90,    91,
      91,    91,    91,    92,    93,    93,    93,    93,    94,    94,
      94,    94,    95,    95,    96,    96,    97,    98,    98,    98,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   102,   103,   104,   105,   106,   106,   106,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   111,   111,   111,   112,   112,
     113,   113,   114,   115,   115,   116,   116,   116,   116,   116,
     116,   117,   117,   118,   119,   119,   120,   120,   121,   122,
     123,   123,   124,   125,   125,   126,   127,   128,   129,   130,
     130,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136
  };

  const unsigned char
   AutoGenParser ::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     1,     3,     7,
      10,     5,     9,     1,     3,     3,     2,     3,     0,     3,
       5,     5,     7,     6,     5,     6,     7,     8,     2,     4,
       4,     6,     3,     2,     3,     1,     3,     3,     3,     0,
       4,     6,     6,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     1,     1,     3,     3,     1,     3,
       3,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     4,     5,     5,     5,     7,     2,     4,     4,
       2,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     5,     5,     1,     3,     2,     4,     4,     1,     3,
       1,     3,     1,     1,     3,     3,     6,     6,     1,     4,
       4,     4,     6,     4,     8,    10,     4,     6,     2,     3,
       2,     3,     2,     1,     2,     2,     4,     4,     3,     2,
       1,     5,     2,     3,     3,     1,     2,     3,     3,     1,
       1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  AutoGenParser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "T_NONE", "\"IMPORT\"",
  "\"PROGRAM\"", "\"BEGIN\"", "\"END\"", "\"DEFINE\"", "\"EXTENSION\"",
  "\"ALIAS\"", "\"CALL\"", "\"SORT\"", "\"MERGE\"", "\"USING\"",
  "\"INDEX\"", "\"FOR\"", "\"TO\"", "\"STEP\"", "\"WHILE\"", "\"DO\"",
  "\"IF\"", "\"THEN\"", "\"ELSE\"", "\"RETURN\"", "\"THROW\"", "\"TRY\"",
  "\"CATCH\"", "\"WITH\"", "\"AS\"", "\"OF\"", "\"ARRAY\"", "\"RETURNS\"",
  "\"VAR\"", "\"AND\"", "\"OR\"", "\"NOT\"", "\"(\"", "\")\"", "\"NEW\"",
  "\"SIZEOF\"", "\"COPYOF\"", "\"DETACH\"", "\"CREATE\"", "\"DELETE\"",
  "\"EXTERNAL\"", "\"TYPE\"", "\"TYPENS\"", "\"ISSET\"", "\"ISNULL\"",
  "\"ISTYPE\"", "\"ISINSTANCE\"", "\"STRLEN\"", "\"[\"", "\"]\"", "\"[[\"",
  "\"]]\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\",\"", "\":\"",
  "\"::\"", "\".\"", "\";\"", "\"==\"", "\"<\"", "\"<=\"", "\">\"",
  "\">=\"", "\"<>\"", "\"= (assignment)\"", "\"?= (assignment)\"", "\"?\"",
  "T_SYMBOL", "T_STRING", "T_INTEGER", "T_LONG", "T_FLOAT", "T_BOOLEAN",
  "T_NULL", "$accept", "globals", "global", "import", "typeDefinition",
  "baseType", "typeDefinitionPropertiesEnclosed",
  "typeDefinitionProperties", "property", "namespaceDeclaration",
  "program", "programResult", "parametersListPar", "parametersList",
  "statementsListBeginEnd", "statementsList", "declaration", "statement",
  "assignment", "condassign", "merge", "lvalue", "expr", "exprTerm",
  "exprFactor", "exprPrimaryOrXPath", "exprPrimary", "relationalOper",
  "logicalExprPrimary", "logicalExprFactor", "logicalExprTerm",
  "logicalExpr", "xpathAccess", "xpath", "with", "whileLoop", "forLoop",
  "ifThenElse", "call", "external", "create", "delete", "return", "throw",
  "sort", "index", "tryCatch", "catchList", "catch", "exprListPar",
  "exprList", "externalParametersPar", "externalParameters", "qname", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
   AutoGenParser ::yyrline_[] =
  {
       0,   245,   245,   245,   247,   248,   249,   254,   258,   263,
     268,   274,   279,   286,   289,   292,   293,   295,   296,   298,
     299,   301,   304,   308,   312,   315,   318,   321,   324,   329,
     336,   342,   350,   351,   353,   358,   364,   366,   371,   376,
     378,   379,   380,   382,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   404,   405,   406,   408,   415,   416,   417,   419,   420,
     421,   422,   424,   426,   427,   429,   430,   431,   432,   433,
     434,   435,   437,   438,   441,   444,   447,   450,   451,   452,
     453,   454,   455,   456,   457,   459,   461,   462,   463,   464,
     465,   467,   470,   473,   474,   475,   476,   477,   479,   480,
     482,   483,   485,   488,   491,   495,   496,   499,   502,   503,
     506,   509,   510,   512,   514,   517,   520,   522,   525,   527,
     528,   529,   530,   532,   533,   536,   538,   540,   542,   543,
     544,   546,   549,   550,   552,   553,   555,   556,   558,   559,
     562,   563
  };

  // Print the state stack on the debug stream.
  void
   AutoGenParser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   AutoGenParser ::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

   AutoGenParser ::token_number_type
   AutoGenParser ::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
    };
    const unsigned user_token_number_max_ = 337;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

} // yy
#line 2353 "src/lang/script/parser/AutoGenParser.cpp"

#line 565 "src/lang/script/parser/AutoGenParser.yy"



void yy::AutoGenParser::error (const location_type& l,
                               const std::string& m)
{
  myParser.onAutoGenParserError(l, m);
}

