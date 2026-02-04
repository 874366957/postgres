/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_BASE_YY_PREPROC_H_INCLUDED
# define YY_BASE_YY_PREPROC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int base_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SQL_ALLOCATE = 258,            /* SQL_ALLOCATE  */
    SQL_AUTOCOMMIT = 259,          /* SQL_AUTOCOMMIT  */
    SQL_BOOL = 260,                /* SQL_BOOL  */
    SQL_BREAK = 261,               /* SQL_BREAK  */
    SQL_CARDINALITY = 262,         /* SQL_CARDINALITY  */
    SQL_CONNECT = 263,             /* SQL_CONNECT  */
    SQL_COUNT = 264,               /* SQL_COUNT  */
    SQL_DATETIME_INTERVAL_CODE = 265, /* SQL_DATETIME_INTERVAL_CODE  */
    SQL_DATETIME_INTERVAL_PRECISION = 266, /* SQL_DATETIME_INTERVAL_PRECISION  */
    SQL_DESCRIBE = 267,            /* SQL_DESCRIBE  */
    SQL_DESCRIPTOR = 268,          /* SQL_DESCRIPTOR  */
    SQL_DISCONNECT = 269,          /* SQL_DISCONNECT  */
    SQL_FOUND = 270,               /* SQL_FOUND  */
    SQL_FREE = 271,                /* SQL_FREE  */
    SQL_GET = 272,                 /* SQL_GET  */
    SQL_GO = 273,                  /* SQL_GO  */
    SQL_GOTO = 274,                /* SQL_GOTO  */
    SQL_IDENTIFIED = 275,          /* SQL_IDENTIFIED  */
    SQL_INDICATOR = 276,           /* SQL_INDICATOR  */
    SQL_KEY_MEMBER = 277,          /* SQL_KEY_MEMBER  */
    SQL_LENGTH = 278,              /* SQL_LENGTH  */
    SQL_LONG = 279,                /* SQL_LONG  */
    SQL_NULLABLE = 280,            /* SQL_NULLABLE  */
    SQL_OCTET_LENGTH = 281,        /* SQL_OCTET_LENGTH  */
    SQL_OPEN = 282,                /* SQL_OPEN  */
    SQL_OUTPUT = 283,              /* SQL_OUTPUT  */
    SQL_REFERENCE = 284,           /* SQL_REFERENCE  */
    SQL_RETURNED_LENGTH = 285,     /* SQL_RETURNED_LENGTH  */
    SQL_RETURNED_OCTET_LENGTH = 286, /* SQL_RETURNED_OCTET_LENGTH  */
    SQL_SCALE = 287,               /* SQL_SCALE  */
    SQL_SECTION = 288,             /* SQL_SECTION  */
    SQL_SHORT = 289,               /* SQL_SHORT  */
    SQL_SIGNED = 290,              /* SQL_SIGNED  */
    SQL_SQLERROR = 291,            /* SQL_SQLERROR  */
    SQL_SQLPRINT = 292,            /* SQL_SQLPRINT  */
    SQL_SQLWARNING = 293,          /* SQL_SQLWARNING  */
    SQL_START = 294,               /* SQL_START  */
    SQL_STOP = 295,                /* SQL_STOP  */
    SQL_STRUCT = 296,              /* SQL_STRUCT  */
    SQL_UNSIGNED = 297,            /* SQL_UNSIGNED  */
    SQL_VAR = 298,                 /* SQL_VAR  */
    SQL_WHENEVER = 299,            /* SQL_WHENEVER  */
    S_ADD = 300,                   /* S_ADD  */
    S_AND = 301,                   /* S_AND  */
    S_ANYTHING = 302,              /* S_ANYTHING  */
    S_AUTO = 303,                  /* S_AUTO  */
    S_CONST = 304,                 /* S_CONST  */
    S_DEC = 305,                   /* S_DEC  */
    S_DIV = 306,                   /* S_DIV  */
    S_DOTPOINT = 307,              /* S_DOTPOINT  */
    S_EQUAL = 308,                 /* S_EQUAL  */
    S_EXTERN = 309,                /* S_EXTERN  */
    S_INC = 310,                   /* S_INC  */
    S_LSHIFT = 311,                /* S_LSHIFT  */
    S_MEMPOINT = 312,              /* S_MEMPOINT  */
    S_MEMBER = 313,                /* S_MEMBER  */
    S_MOD = 314,                   /* S_MOD  */
    S_MUL = 315,                   /* S_MUL  */
    S_NEQUAL = 316,                /* S_NEQUAL  */
    S_OR = 317,                    /* S_OR  */
    S_REGISTER = 318,              /* S_REGISTER  */
    S_RSHIFT = 319,                /* S_RSHIFT  */
    S_STATIC = 320,                /* S_STATIC  */
    S_SUB = 321,                   /* S_SUB  */
    S_VOLATILE = 322,              /* S_VOLATILE  */
    S_TYPEDEF = 323,               /* S_TYPEDEF  */
    CSTRING = 324,                 /* CSTRING  */
    CVARIABLE = 325,               /* CVARIABLE  */
    CPP_LINE = 326,                /* CPP_LINE  */
    IP = 327,                      /* IP  */
    IDENT = 328,                   /* IDENT  */
    UIDENT = 329,                  /* UIDENT  */
    FCONST = 330,                  /* FCONST  */
    SCONST = 331,                  /* SCONST  */
    USCONST = 332,                 /* USCONST  */
    BCONST = 333,                  /* BCONST  */
    XCONST = 334,                  /* XCONST  */
    Op = 335,                      /* Op  */
    ICONST = 336,                  /* ICONST  */
    PARAM = 337,                   /* PARAM  */
    TYPECAST = 338,                /* TYPECAST  */
    DOT_DOT = 339,                 /* DOT_DOT  */
    COLON_EQUALS = 340,            /* COLON_EQUALS  */
    EQUALS_GREATER = 341,          /* EQUALS_GREATER  */
    LESS_EQUALS = 342,             /* LESS_EQUALS  */
    GREATER_EQUALS = 343,          /* GREATER_EQUALS  */
    NOT_EQUALS = 344,              /* NOT_EQUALS  */
    ABORT_P = 345,                 /* ABORT_P  */
    ABSENT = 346,                  /* ABSENT  */
    ABSOLUTE_P = 347,              /* ABSOLUTE_P  */
    ACCESS = 348,                  /* ACCESS  */
    ACTION = 349,                  /* ACTION  */
    ADD_P = 350,                   /* ADD_P  */
    ADMIN = 351,                   /* ADMIN  */
    AFTER = 352,                   /* AFTER  */
    AGGREGATE = 353,               /* AGGREGATE  */
    ALL = 354,                     /* ALL  */
    ALSO = 355,                    /* ALSO  */
    ALTER = 356,                   /* ALTER  */
    ALWAYS = 357,                  /* ALWAYS  */
    ANALYSE = 358,                 /* ANALYSE  */
    ANALYZE = 359,                 /* ANALYZE  */
    AND = 360,                     /* AND  */
    ANY = 361,                     /* ANY  */
    ARRAY = 362,                   /* ARRAY  */
    AS = 363,                      /* AS  */
    ASC = 364,                     /* ASC  */
    ASENSITIVE = 365,              /* ASENSITIVE  */
    ASSERTION = 366,               /* ASSERTION  */
    ASSIGNMENT = 367,              /* ASSIGNMENT  */
    ASYMMETRIC = 368,              /* ASYMMETRIC  */
    ATOMIC = 369,                  /* ATOMIC  */
    AT = 370,                      /* AT  */
    ATTACH = 371,                  /* ATTACH  */
    ATTRIBUTE = 372,               /* ATTRIBUTE  */
    AUTHORIZATION = 373,           /* AUTHORIZATION  */
    BACKWARD = 374,                /* BACKWARD  */
    BEFORE = 375,                  /* BEFORE  */
    BEGIN_P = 376,                 /* BEGIN_P  */
    BETWEEN = 377,                 /* BETWEEN  */
    BIGINT = 378,                  /* BIGINT  */
    BINARY = 379,                  /* BINARY  */
    BIT = 380,                     /* BIT  */
    BOOLEAN_P = 381,               /* BOOLEAN_P  */
    BOTH = 382,                    /* BOTH  */
    BREADTH = 383,                 /* BREADTH  */
    BY = 384,                      /* BY  */
    CACHE = 385,                   /* CACHE  */
    CALL = 386,                    /* CALL  */
    CALLED = 387,                  /* CALLED  */
    CASCADE = 388,                 /* CASCADE  */
    CASCADED = 389,                /* CASCADED  */
    CASE = 390,                    /* CASE  */
    CAST = 391,                    /* CAST  */
    CATALOG_P = 392,               /* CATALOG_P  */
    CHAIN = 393,                   /* CHAIN  */
    CHAR_P = 394,                  /* CHAR_P  */
    CHARACTER = 395,               /* CHARACTER  */
    CHARACTERISTICS = 396,         /* CHARACTERISTICS  */
    CHECK = 397,                   /* CHECK  */
    CHECKPOINT = 398,              /* CHECKPOINT  */
    CLASS = 399,                   /* CLASS  */
    CLOSE = 400,                   /* CLOSE  */
    CLUSTER = 401,                 /* CLUSTER  */
    COALESCE = 402,                /* COALESCE  */
    COLLATE = 403,                 /* COLLATE  */
    COLLATION = 404,               /* COLLATION  */
    COLUMN = 405,                  /* COLUMN  */
    COLUMNS = 406,                 /* COLUMNS  */
    COMMENT = 407,                 /* COMMENT  */
    COMMENTS = 408,                /* COMMENTS  */
    COMMIT = 409,                  /* COMMIT  */
    COMMITTED = 410,               /* COMMITTED  */
    COMPRESSION = 411,             /* COMPRESSION  */
    CONCURRENTLY = 412,            /* CONCURRENTLY  */
    CONDITIONAL = 413,             /* CONDITIONAL  */
    CONFIGURATION = 414,           /* CONFIGURATION  */
    CONFLICT = 415,                /* CONFLICT  */
    CONNECTION = 416,              /* CONNECTION  */
    CONSTRAINT = 417,              /* CONSTRAINT  */
    CONSTRAINTS = 418,             /* CONSTRAINTS  */
    CONTENT_P = 419,               /* CONTENT_P  */
    CONTINUE_P = 420,              /* CONTINUE_P  */
    CONVERSION_P = 421,            /* CONVERSION_P  */
    COPY = 422,                    /* COPY  */
    COST = 423,                    /* COST  */
    CREATE = 424,                  /* CREATE  */
    CROSS = 425,                   /* CROSS  */
    CSV = 426,                     /* CSV  */
    CUBE = 427,                    /* CUBE  */
    CURRENT_P = 428,               /* CURRENT_P  */
    CURRENT_CATALOG = 429,         /* CURRENT_CATALOG  */
    CURRENT_DATE = 430,            /* CURRENT_DATE  */
    CURRENT_ROLE = 431,            /* CURRENT_ROLE  */
    CURRENT_SCHEMA = 432,          /* CURRENT_SCHEMA  */
    CURRENT_TIME = 433,            /* CURRENT_TIME  */
    CURRENT_TIMESTAMP = 434,       /* CURRENT_TIMESTAMP  */
    CURRENT_USER = 435,            /* CURRENT_USER  */
    CURSOR = 436,                  /* CURSOR  */
    CYCLE = 437,                   /* CYCLE  */
    DATA_P = 438,                  /* DATA_P  */
    DATABASE = 439,                /* DATABASE  */
    DAY_P = 440,                   /* DAY_P  */
    DEALLOCATE = 441,              /* DEALLOCATE  */
    DEC = 442,                     /* DEC  */
    DECIMAL_P = 443,               /* DECIMAL_P  */
    DECLARE = 444,                 /* DECLARE  */
    DEFAULT = 445,                 /* DEFAULT  */
    DEFAULTS = 446,                /* DEFAULTS  */
    DEFERRABLE = 447,              /* DEFERRABLE  */
    DEFERRED = 448,                /* DEFERRED  */
    DEFINER = 449,                 /* DEFINER  */
    DELETE_P = 450,                /* DELETE_P  */
    DELIMITER = 451,               /* DELIMITER  */
    DELIMITERS = 452,              /* DELIMITERS  */
    DEPENDS = 453,                 /* DEPENDS  */
    DEPTH = 454,                   /* DEPTH  */
    DESC = 455,                    /* DESC  */
    DETACH = 456,                  /* DETACH  */
    DICTIONARY = 457,              /* DICTIONARY  */
    DISABLE_P = 458,               /* DISABLE_P  */
    DISCARD = 459,                 /* DISCARD  */
    DISTINCT = 460,                /* DISTINCT  */
    DO = 461,                      /* DO  */
    DOCUMENT_P = 462,              /* DOCUMENT_P  */
    DOMAIN_P = 463,                /* DOMAIN_P  */
    DOUBLE_P = 464,                /* DOUBLE_P  */
    DROP = 465,                    /* DROP  */
    EACH = 466,                    /* EACH  */
    ELSE = 467,                    /* ELSE  */
    EMPTY_P = 468,                 /* EMPTY_P  */
    ENABLE_P = 469,                /* ENABLE_P  */
    ENCODING = 470,                /* ENCODING  */
    ENCRYPTED = 471,               /* ENCRYPTED  */
    END_P = 472,                   /* END_P  */
    ENFORCED = 473,                /* ENFORCED  */
    ENUM_P = 474,                  /* ENUM_P  */
    ERROR_P = 475,                 /* ERROR_P  */
    ESCAPE = 476,                  /* ESCAPE  */
    EVENT = 477,                   /* EVENT  */
    EXCEPT = 478,                  /* EXCEPT  */
    EXCLUDE = 479,                 /* EXCLUDE  */
    EXCLUDING = 480,               /* EXCLUDING  */
    EXCLUSIVE = 481,               /* EXCLUSIVE  */
    EXECUTE = 482,                 /* EXECUTE  */
    EXISTS = 483,                  /* EXISTS  */
    EXPLAIN = 484,                 /* EXPLAIN  */
    EXPRESSION = 485,              /* EXPRESSION  */
    EXTENSION = 486,               /* EXTENSION  */
    EXTERNAL = 487,                /* EXTERNAL  */
    EXTRACT = 488,                 /* EXTRACT  */
    FALSE_P = 489,                 /* FALSE_P  */
    FAMILY = 490,                  /* FAMILY  */
    FETCH = 491,                   /* FETCH  */
    FILTER = 492,                  /* FILTER  */
    FINALIZE = 493,                /* FINALIZE  */
    FIRST_P = 494,                 /* FIRST_P  */
    FLOAT_P = 495,                 /* FLOAT_P  */
    FOLLOWING = 496,               /* FOLLOWING  */
    FOR = 497,                     /* FOR  */
    FORCE = 498,                   /* FORCE  */
    FOREIGN = 499,                 /* FOREIGN  */
    FORMAT = 500,                  /* FORMAT  */
    FORWARD = 501,                 /* FORWARD  */
    FREEZE = 502,                  /* FREEZE  */
    FROM = 503,                    /* FROM  */
    FULL = 504,                    /* FULL  */
    FUNCTION = 505,                /* FUNCTION  */
    FUNCTIONS = 506,               /* FUNCTIONS  */
    GENERATED = 507,               /* GENERATED  */
    GLOBAL = 508,                  /* GLOBAL  */
    GRANT = 509,                   /* GRANT  */
    GRANTED = 510,                 /* GRANTED  */
    GREATEST = 511,                /* GREATEST  */
    GROUP_P = 512,                 /* GROUP_P  */
    GROUPING = 513,                /* GROUPING  */
    GROUPS = 514,                  /* GROUPS  */
    HANDLER = 515,                 /* HANDLER  */
    HAVING = 516,                  /* HAVING  */
    HEADER_P = 517,                /* HEADER_P  */
    HOLD = 518,                    /* HOLD  */
    HOUR_P = 519,                  /* HOUR_P  */
    IDENTITY_P = 520,              /* IDENTITY_P  */
    IF_P = 521,                    /* IF_P  */
    IGNORE_P = 522,                /* IGNORE_P  */
    ILIKE = 523,                   /* ILIKE  */
    IMMEDIATE = 524,               /* IMMEDIATE  */
    IMMUTABLE = 525,               /* IMMUTABLE  */
    IMPLICIT_P = 526,              /* IMPLICIT_P  */
    IMPORT_P = 527,                /* IMPORT_P  */
    IN_P = 528,                    /* IN_P  */
    INCLUDE = 529,                 /* INCLUDE  */
    INCLUDING = 530,               /* INCLUDING  */
    INCREMENT = 531,               /* INCREMENT  */
    INDENT = 532,                  /* INDENT  */
    INDEX = 533,                   /* INDEX  */
    INDEXES = 534,                 /* INDEXES  */
    INHERIT = 535,                 /* INHERIT  */
    INHERITS = 536,                /* INHERITS  */
    INITIALLY = 537,               /* INITIALLY  */
    INLINE_P = 538,                /* INLINE_P  */
    INNER_P = 539,                 /* INNER_P  */
    INOUT = 540,                   /* INOUT  */
    INPUT_P = 541,                 /* INPUT_P  */
    INSENSITIVE = 542,             /* INSENSITIVE  */
    INSERT = 543,                  /* INSERT  */
    INSTEAD = 544,                 /* INSTEAD  */
    INT_P = 545,                   /* INT_P  */
    INTEGER = 546,                 /* INTEGER  */
    INTERSECT = 547,               /* INTERSECT  */
    INTERVAL = 548,                /* INTERVAL  */
    INTO = 549,                    /* INTO  */
    INVOKER = 550,                 /* INVOKER  */
    IS = 551,                      /* IS  */
    ISNULL = 552,                  /* ISNULL  */
    ISOLATION = 553,               /* ISOLATION  */
    JOIN = 554,                    /* JOIN  */
    JSON = 555,                    /* JSON  */
    JSON_ARRAY = 556,              /* JSON_ARRAY  */
    JSON_ARRAYAGG = 557,           /* JSON_ARRAYAGG  */
    JSON_EXISTS = 558,             /* JSON_EXISTS  */
    JSON_OBJECT = 559,             /* JSON_OBJECT  */
    JSON_OBJECTAGG = 560,          /* JSON_OBJECTAGG  */
    JSON_QUERY = 561,              /* JSON_QUERY  */
    JSON_SCALAR = 562,             /* JSON_SCALAR  */
    JSON_SERIALIZE = 563,          /* JSON_SERIALIZE  */
    JSON_TABLE = 564,              /* JSON_TABLE  */
    JSON_VALUE = 565,              /* JSON_VALUE  */
    KEEP = 566,                    /* KEEP  */
    KEY = 567,                     /* KEY  */
    KEYS = 568,                    /* KEYS  */
    LABEL = 569,                   /* LABEL  */
    LANGUAGE = 570,                /* LANGUAGE  */
    LARGE_P = 571,                 /* LARGE_P  */
    LAST_P = 572,                  /* LAST_P  */
    LATERAL_P = 573,               /* LATERAL_P  */
    LEADING = 574,                 /* LEADING  */
    LEAKPROOF = 575,               /* LEAKPROOF  */
    LEAST = 576,                   /* LEAST  */
    LEFT = 577,                    /* LEFT  */
    LEVEL = 578,                   /* LEVEL  */
    LIKE = 579,                    /* LIKE  */
    LIMIT = 580,                   /* LIMIT  */
    LISTEN = 581,                  /* LISTEN  */
    LOAD = 582,                    /* LOAD  */
    LOCAL = 583,                   /* LOCAL  */
    LOCALTIME = 584,               /* LOCALTIME  */
    LOCALTIMESTAMP = 585,          /* LOCALTIMESTAMP  */
    LOCATION = 586,                /* LOCATION  */
    LOCK_P = 587,                  /* LOCK_P  */
    LOCKED = 588,                  /* LOCKED  */
    LOGGED = 589,                  /* LOGGED  */
    LSN_P = 590,                   /* LSN_P  */
    MAPPING = 591,                 /* MAPPING  */
    MATCH = 592,                   /* MATCH  */
    MATCHED = 593,                 /* MATCHED  */
    MATERIALIZED = 594,            /* MATERIALIZED  */
    MAXVALUE = 595,                /* MAXVALUE  */
    MERGE = 596,                   /* MERGE  */
    MERGE_ACTION = 597,            /* MERGE_ACTION  */
    METHOD = 598,                  /* METHOD  */
    MINUTE_P = 599,                /* MINUTE_P  */
    MINVALUE = 600,                /* MINVALUE  */
    MODE = 601,                    /* MODE  */
    MONTH_P = 602,                 /* MONTH_P  */
    MOVE = 603,                    /* MOVE  */
    NAME_P = 604,                  /* NAME_P  */
    NAMES = 605,                   /* NAMES  */
    NATIONAL = 606,                /* NATIONAL  */
    NATURAL = 607,                 /* NATURAL  */
    NCHAR = 608,                   /* NCHAR  */
    NESTED = 609,                  /* NESTED  */
    NEW = 610,                     /* NEW  */
    NEXT = 611,                    /* NEXT  */
    NFC = 612,                     /* NFC  */
    NFD = 613,                     /* NFD  */
    NFKC = 614,                    /* NFKC  */
    NFKD = 615,                    /* NFKD  */
    NO = 616,                      /* NO  */
    NONE = 617,                    /* NONE  */
    NORMALIZE = 618,               /* NORMALIZE  */
    NORMALIZED = 619,              /* NORMALIZED  */
    NOT = 620,                     /* NOT  */
    NOTHING = 621,                 /* NOTHING  */
    NOTIFY = 622,                  /* NOTIFY  */
    NOTNULL = 623,                 /* NOTNULL  */
    NOWAIT = 624,                  /* NOWAIT  */
    NULL_P = 625,                  /* NULL_P  */
    NULLIF = 626,                  /* NULLIF  */
    NULLS_P = 627,                 /* NULLS_P  */
    NUMERIC = 628,                 /* NUMERIC  */
    OBJECT_P = 629,                /* OBJECT_P  */
    OBJECTS_P = 630,               /* OBJECTS_P  */
    OF = 631,                      /* OF  */
    OFF = 632,                     /* OFF  */
    OFFSET = 633,                  /* OFFSET  */
    OIDS = 634,                    /* OIDS  */
    OLD = 635,                     /* OLD  */
    OMIT = 636,                    /* OMIT  */
    ON = 637,                      /* ON  */
    ONLY = 638,                    /* ONLY  */
    OPERATOR = 639,                /* OPERATOR  */
    OPTION = 640,                  /* OPTION  */
    OPTIONS = 641,                 /* OPTIONS  */
    OR = 642,                      /* OR  */
    ORDER = 643,                   /* ORDER  */
    ORDINALITY = 644,              /* ORDINALITY  */
    OTHERS = 645,                  /* OTHERS  */
    OUT_P = 646,                   /* OUT_P  */
    OUTER_P = 647,                 /* OUTER_P  */
    OVER = 648,                    /* OVER  */
    OVERLAPS = 649,                /* OVERLAPS  */
    OVERLAY = 650,                 /* OVERLAY  */
    OVERRIDING = 651,              /* OVERRIDING  */
    OWNED = 652,                   /* OWNED  */
    OWNER = 653,                   /* OWNER  */
    PARALLEL = 654,                /* PARALLEL  */
    PARAMETER = 655,               /* PARAMETER  */
    PARSER = 656,                  /* PARSER  */
    PARTIAL = 657,                 /* PARTIAL  */
    PARTITION = 658,               /* PARTITION  */
    PARTITIONS = 659,              /* PARTITIONS  */
    PASSING = 660,                 /* PASSING  */
    PASSWORD = 661,                /* PASSWORD  */
    PATH = 662,                    /* PATH  */
    PERIOD = 663,                  /* PERIOD  */
    PLACING = 664,                 /* PLACING  */
    PLAN = 665,                    /* PLAN  */
    PLANS = 666,                   /* PLANS  */
    POLICY = 667,                  /* POLICY  */
    POSITION = 668,                /* POSITION  */
    PRECEDING = 669,               /* PRECEDING  */
    PRECISION = 670,               /* PRECISION  */
    PRESERVE = 671,                /* PRESERVE  */
    PREPARE = 672,                 /* PREPARE  */
    PREPARED = 673,                /* PREPARED  */
    PRIMARY = 674,                 /* PRIMARY  */
    PRIOR = 675,                   /* PRIOR  */
    PRIVILEGES = 676,              /* PRIVILEGES  */
    PROCEDURAL = 677,              /* PROCEDURAL  */
    PROCEDURE = 678,               /* PROCEDURE  */
    PROCEDURES = 679,              /* PROCEDURES  */
    PROGRAM = 680,                 /* PROGRAM  */
    PUBLICATION = 681,             /* PUBLICATION  */
    QUOTE = 682,                   /* QUOTE  */
    QUOTES = 683,                  /* QUOTES  */
    RANGE = 684,                   /* RANGE  */
    READ = 685,                    /* READ  */
    REAL = 686,                    /* REAL  */
    REASSIGN = 687,                /* REASSIGN  */
    RECURSIVE = 688,               /* RECURSIVE  */
    REF_P = 689,                   /* REF_P  */
    REFERENCES = 690,              /* REFERENCES  */
    REFERENCING = 691,             /* REFERENCING  */
    REFRESH = 692,                 /* REFRESH  */
    REINDEX = 693,                 /* REINDEX  */
    RELATIVE_P = 694,              /* RELATIVE_P  */
    RELEASE = 695,                 /* RELEASE  */
    RENAME = 696,                  /* RENAME  */
    REPEATABLE = 697,              /* REPEATABLE  */
    REPLACE = 698,                 /* REPLACE  */
    REPLICA = 699,                 /* REPLICA  */
    RESET = 700,                   /* RESET  */
    RESPECT_P = 701,               /* RESPECT_P  */
    RESTART = 702,                 /* RESTART  */
    RESTRICT = 703,                /* RESTRICT  */
    RETURN = 704,                  /* RETURN  */
    RETURNING = 705,               /* RETURNING  */
    RETURNS = 706,                 /* RETURNS  */
    REVOKE = 707,                  /* REVOKE  */
    RIGHT = 708,                   /* RIGHT  */
    ROLE = 709,                    /* ROLE  */
    ROLLBACK = 710,                /* ROLLBACK  */
    ROLLUP = 711,                  /* ROLLUP  */
    ROUTINE = 712,                 /* ROUTINE  */
    ROUTINES = 713,                /* ROUTINES  */
    ROW = 714,                     /* ROW  */
    ROWS = 715,                    /* ROWS  */
    RULE = 716,                    /* RULE  */
    SAVEPOINT = 717,               /* SAVEPOINT  */
    SCALAR = 718,                  /* SCALAR  */
    SCHEMA = 719,                  /* SCHEMA  */
    SCHEMAS = 720,                 /* SCHEMAS  */
    SCROLL = 721,                  /* SCROLL  */
    SEARCH = 722,                  /* SEARCH  */
    SECOND_P = 723,                /* SECOND_P  */
    SECURITY = 724,                /* SECURITY  */
    SELECT = 725,                  /* SELECT  */
    SEQUENCE = 726,                /* SEQUENCE  */
    SEQUENCES = 727,               /* SEQUENCES  */
    SERIALIZABLE = 728,            /* SERIALIZABLE  */
    SERVER = 729,                  /* SERVER  */
    SESSION = 730,                 /* SESSION  */
    SESSION_USER = 731,            /* SESSION_USER  */
    SET = 732,                     /* SET  */
    SETS = 733,                    /* SETS  */
    SETOF = 734,                   /* SETOF  */
    SHARE = 735,                   /* SHARE  */
    SHOW = 736,                    /* SHOW  */
    SIMILAR = 737,                 /* SIMILAR  */
    SIMPLE = 738,                  /* SIMPLE  */
    SKIP = 739,                    /* SKIP  */
    SMALLINT = 740,                /* SMALLINT  */
    SNAPSHOT = 741,                /* SNAPSHOT  */
    SOME = 742,                    /* SOME  */
    SPLIT = 743,                   /* SPLIT  */
    SOURCE = 744,                  /* SOURCE  */
    SQL_P = 745,                   /* SQL_P  */
    STABLE = 746,                  /* STABLE  */
    STANDALONE_P = 747,            /* STANDALONE_P  */
    START = 748,                   /* START  */
    STATEMENT = 749,               /* STATEMENT  */
    STATISTICS = 750,              /* STATISTICS  */
    STDIN = 751,                   /* STDIN  */
    STDOUT = 752,                  /* STDOUT  */
    STORAGE = 753,                 /* STORAGE  */
    STORED = 754,                  /* STORED  */
    STRICT_P = 755,                /* STRICT_P  */
    STRING_P = 756,                /* STRING_P  */
    STRIP_P = 757,                 /* STRIP_P  */
    SUBSCRIPTION = 758,            /* SUBSCRIPTION  */
    SUBSTRING = 759,               /* SUBSTRING  */
    SUPPORT = 760,                 /* SUPPORT  */
    SYMMETRIC = 761,               /* SYMMETRIC  */
    SYSID = 762,                   /* SYSID  */
    SYSTEM_P = 763,                /* SYSTEM_P  */
    SYSTEM_USER = 764,             /* SYSTEM_USER  */
    TABLE = 765,                   /* TABLE  */
    TABLES = 766,                  /* TABLES  */
    TABLESAMPLE = 767,             /* TABLESAMPLE  */
    TABLESPACE = 768,              /* TABLESPACE  */
    TARGET = 769,                  /* TARGET  */
    TEMP = 770,                    /* TEMP  */
    TEMPLATE = 771,                /* TEMPLATE  */
    TEMPORARY = 772,               /* TEMPORARY  */
    TEXT_P = 773,                  /* TEXT_P  */
    THEN = 774,                    /* THEN  */
    TIES = 775,                    /* TIES  */
    TIME = 776,                    /* TIME  */
    TIMESTAMP = 777,               /* TIMESTAMP  */
    TO = 778,                      /* TO  */
    TRAILING = 779,                /* TRAILING  */
    TRANSACTION = 780,             /* TRANSACTION  */
    TRANSFORM = 781,               /* TRANSFORM  */
    TREAT = 782,                   /* TREAT  */
    TRIGGER = 783,                 /* TRIGGER  */
    TRIM = 784,                    /* TRIM  */
    TRUE_P = 785,                  /* TRUE_P  */
    TRUNCATE = 786,                /* TRUNCATE  */
    TRUSTED = 787,                 /* TRUSTED  */
    TYPE_P = 788,                  /* TYPE_P  */
    TYPES_P = 789,                 /* TYPES_P  */
    UESCAPE = 790,                 /* UESCAPE  */
    UNBOUNDED = 791,               /* UNBOUNDED  */
    UNCONDITIONAL = 792,           /* UNCONDITIONAL  */
    UNCOMMITTED = 793,             /* UNCOMMITTED  */
    UNENCRYPTED = 794,             /* UNENCRYPTED  */
    UNION = 795,                   /* UNION  */
    UNIQUE = 796,                  /* UNIQUE  */
    UNKNOWN = 797,                 /* UNKNOWN  */
    UNLISTEN = 798,                /* UNLISTEN  */
    UNLOGGED = 799,                /* UNLOGGED  */
    UNTIL = 800,                   /* UNTIL  */
    UPDATE = 801,                  /* UPDATE  */
    USER = 802,                    /* USER  */
    USING = 803,                   /* USING  */
    VACUUM = 804,                  /* VACUUM  */
    VALID = 805,                   /* VALID  */
    VALIDATE = 806,                /* VALIDATE  */
    VALIDATOR = 807,               /* VALIDATOR  */
    VALUE_P = 808,                 /* VALUE_P  */
    VALUES = 809,                  /* VALUES  */
    VARCHAR = 810,                 /* VARCHAR  */
    VARIADIC = 811,                /* VARIADIC  */
    VARYING = 812,                 /* VARYING  */
    VERBOSE = 813,                 /* VERBOSE  */
    VERSION_P = 814,               /* VERSION_P  */
    VIEW = 815,                    /* VIEW  */
    VIEWS = 816,                   /* VIEWS  */
    VIRTUAL = 817,                 /* VIRTUAL  */
    VOLATILE = 818,                /* VOLATILE  */
    WAIT = 819,                    /* WAIT  */
    WHEN = 820,                    /* WHEN  */
    WHERE = 821,                   /* WHERE  */
    WHITESPACE_P = 822,            /* WHITESPACE_P  */
    WINDOW = 823,                  /* WINDOW  */
    WITH = 824,                    /* WITH  */
    WITHIN = 825,                  /* WITHIN  */
    WITHOUT = 826,                 /* WITHOUT  */
    WORK = 827,                    /* WORK  */
    WRAPPER = 828,                 /* WRAPPER  */
    WRITE = 829,                   /* WRITE  */
    XML_P = 830,                   /* XML_P  */
    XMLATTRIBUTES = 831,           /* XMLATTRIBUTES  */
    XMLCONCAT = 832,               /* XMLCONCAT  */
    XMLELEMENT = 833,              /* XMLELEMENT  */
    XMLEXISTS = 834,               /* XMLEXISTS  */
    XMLFOREST = 835,               /* XMLFOREST  */
    XMLNAMESPACES = 836,           /* XMLNAMESPACES  */
    XMLPARSE = 837,                /* XMLPARSE  */
    XMLPI = 838,                   /* XMLPI  */
    XMLROOT = 839,                 /* XMLROOT  */
    XMLSERIALIZE = 840,            /* XMLSERIALIZE  */
    XMLTABLE = 841,                /* XMLTABLE  */
    YEAR_P = 842,                  /* YEAR_P  */
    YES_P = 843,                   /* YES_P  */
    ZONE = 844,                    /* ZONE  */
    FORMAT_LA = 845,               /* FORMAT_LA  */
    NOT_LA = 846,                  /* NOT_LA  */
    NULLS_LA = 847,                /* NULLS_LA  */
    WITH_LA = 848,                 /* WITH_LA  */
    WITHOUT_LA = 849,              /* WITHOUT_LA  */
    MODE_TYPE_NAME = 850,          /* MODE_TYPE_NAME  */
    MODE_PLPGSQL_EXPR = 851,       /* MODE_PLPGSQL_EXPR  */
    MODE_PLPGSQL_ASSIGN1 = 852,    /* MODE_PLPGSQL_ASSIGN1  */
    MODE_PLPGSQL_ASSIGN2 = 853,    /* MODE_PLPGSQL_ASSIGN2  */
    MODE_PLPGSQL_ASSIGN3 = 854,    /* MODE_PLPGSQL_ASSIGN3  */
    UMINUS = 855                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 589 "preproc.y"

	double		dval;
	char	   *str;
	int			ival;
	struct when action;
	struct index index;
	int			tagname;
	struct this_type type;
	enum ECPGttype type_enum;
	enum ECPGdtype dtype_enum;
	struct fetch_desc descriptor;
	struct su_symbol struct_union;
	struct prep prep;
	struct exec exec;
	struct describe describe;

#line 681 "preproc.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE base_yylval;
extern YYLTYPE base_yylloc;

int base_yyparse (void);


#endif /* !YY_BASE_YY_PREPROC_H_INCLUDED  */
