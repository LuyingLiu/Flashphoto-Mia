Coding Style    {#style}
============
Names and Order of Includes:

For the header files, we use google style to include those files. The standard
order is: Related header, C library, C++ library, other libraries' .h,
your project's .h. All of a project's header files should be listed as
descendants of the project's source directory without use of UNIX directory
shortcuts . (the current directory) or .. (the parent directory). For example,
`google-awesome-project/src/base/logging.h` should be included as:
    #include "base/logging.h"
In `dir/foo.cc or dir/foo_test.cc`, whose main purpose is to implement or test
the stuff in `dir2/foo2.h`, order your includes as follows:
*    1. dir2/foo2.h.
*    2. A blank line
*    3. C system files.
*    4. C++ system files.
*    5. A blank line
*    6. Other libraries' .h files.
*    7. Your project's .h files.
Another example, the includes in `google-awesome-project/src/foo/internal/fooserver.cc`
might look like this:

    #include "foo/server/fooserver.h"

    #include <sys/types.h>
    #include <unistd.h>
    #include <vector>

    #include "base/basictypes.h"
    #include "base/commandlineflags.h"
    #include "foo/server/bar.h"

All of the classes should be in the `image_tool` snamespace.

General Naming Rules:

Names should be descriptive; avoid abbreviation.

Give as descriptive a name as possible, within reason. Do not use abbreviations
that are ambiguous or unfamiliar to readers outside your project, and do not
abbreviate by deleting letters within a word. Abbreviations that would be
familiar to someone outside your project with relevant domain knowledge are OK.
As a rule of thumb, an abbreviation is probably OK if it's listed in Wikipedia.
Here are good examples:

    int price_count_reader;    // No abbreviation.
    int num_errors;            // "num" is a widespread convention.
    int num_dns_connections;   // Most people know what "DNS" stands for.
    int lstm_size;             // "LSTM" is a common machine learning abbreviation.

These are bad examples:

    int n;                     // Meaningless.
    int nerr;                  // Ambiguous abbreviation.
    int n_comp_conns;          // Ambiguous abbreviation.
    int wgc_connections;       // Only your group knows what this stands for.
    int pc_reader;             // Lots of things can be abbreviated "pc".
    int cstmr_id;              // Deletes internal letters.
    FooBarRequestInfo fbri;    // Not even a word.

Note that certain universally-known abbreviations are OK, such as i for an
iteration variable and T for a template parameter.

For some symbols, names should start with a capital letter and to have a capital
letter for each new word (a.k.a. "Camel Case" or "Pascal case"). When
abbreviations or acronyms appear in such names, prefer to capitalize the
abbreviations or acronyms as single words (i.e StartRpc(), not StartRPC()).

File Names:

Filenames should be all lowercase and can include underscores. Examples of
acceptable file names:

    my_useful_class.cc
    my_useful_class_test.cc

C++ files should end in .cc and header files should end in .h.

Do not use filenames that already exist in /usr/include, such as db.h.

In general, make your filenames very specific. For example, use `http_server_logs.h`
rather than logs.h. A very common case is to have a pair of files called, e.g.,
`foo_bar.h` and `foo_bar.cc`, defining a class called FooBar.

Type Names:

Type names start with a capital letter and have a capital letter for each new
word, with no underscores: MyExcitingClass, MyExcitingEnum.

The names of all types — classes, structs, type aliases, enums, and type
template parameters — have the same naming convention. Type names should
start with a capital letter and have a capital letter for each new word.
No underscores. For example:

    // classes and structs
    class UrlTable { ...
    class UrlTableTester { ...
    struct UrlTableProperties { ...

    // enums
    enum UrlTableErrors { ...

Variable Names:

The names of variables (including function parameters) and data members are all
lowercase, with underscores between words. Data members of classes (but not
structs) additionally have trailing underscores. For instance: `a_local_variable`,
`a_struct_data_member`, `a_class_data_member_`.

*    Common Variable names:

For example:

    string table_name;  // OK - uses underscore.
    string tablename;   // OK - all lowercase.
    string tableName;   // Bad - mixed case.

*    Class Data Members:

Data members of classes, both static and non-static, are named like ordinary
nonmember variables, but with a trailing underscore.

    class TableInfo {
      ...
     private:
      string table_name_;  // OK - underscore at end.
      string tablename_;   // OK.
      static Pool<TableInfo>* pool_;  // OK.
    };

*    Struct Data Members:

Data members of structs, both static and non-static, are named like ordinary
nonmember variables. They do not have the trailing underscores that data members
in classes have.

    struct UrlTableProperties {
      string name;
      int num_entries;
      static Pool<UrlTableProperties>* pool;
    };

*    Function Names:

Regular functions have mixed case; accessors and mutators may be named like
variables.

Ordinarily, functions should start with a capital letter and have a capital
letter for each new word. Here are some examples:

    AddTableEntry()
    DeleteUrl()
    OpenFileOrDie()

Accessors and mutators (get and set functions) may be named like variables.
These often correspond to actual member variables, but this is not required.
For example, `int count()` and `void set_count(int count)`.

Comments:

The following rules describe what you should comment and where. But remember:
while comments are very important, the best code is self-documenting. Giving
sensible names to types and variables is much better than using obscure names
that you must then explain through comments.

*    Comment Style:

Use either the `//` or `/* */` syntax. If you want your comments auto generated
by oxygen, use `///` or `/** */`.

*    File Comments:

Start each file with license boilerplate.

Legal Notice and Author Line: Every file should contain license boilerplate. In
our project, we use styles like ` Copyright (c) 2015-2018 Daniel Keefe, TAs, &
Regents of the University of Minnesota.`

If you make significant changes to a file with an author line, consider deleting
the author line. New files should usually not contain copyright notice or author
line.

*   Class Comments:

Every non-obvious class declaration should have an accompanying comment that
describes what it is for and how it should be used. Typically, you should use a
single file for each class.

    // Iterates over the contents of a GargantuanTable.
    // Example:
    //    GargantuanTableIterator* iter = table->NewIterator();
    //    for (iter->Seek("foo"); !iter->done(); iter->Next()) {
    //      process(iter->key(), iter->value());
    //    }
    //    delete iter;
    class GargantuanTableIterator {
      ...
    };

The class comment should provide the reader with enough information to know how
and when to use the class, as well as any additional considerations necessary to
correctly use the class. Document the synchronization assumptions the class makes,
if any. If an instance of the class can be accessed by multiple threads, take
extra care to document the rules and invariants surrounding multithreaded use.

The class comment is often a good place for a small example code snippet
demonstrating a simple and focused usage of the class.

When sufficiently separated (e.g. .h and .cc files), comments describing the use
of the class should go together with its interface definition; comments about
the class operation and implementation should accompany the implementation of
the class's methods.

*   Function Comments:

Declaration comments describe use of the function (when it is non-obvious);
comments at the definition of a function describe operation.

Function Declarations: Almost every function declaration should have comments
immediately preceding it that describe what the function does and how to use it.
These comments may be omitted only if the function is simple and obvious
(e.g. simple accessors for obvious properties of the class). The comment
describes the function. Normally, you need to describe: What the inputs and
outputs are. For class member functions: whether the object remembers reference
arguments beyond the duration of the method call, and whether it will free them
or not. If the function allocates memory that the caller must free. Whether any
of the arguments can be a null pointer. If there are any performance
implications of how a function is used. If the function is re-entrant. What are
its synchronization assumptions?

When documenting function overrides, focus on the specifics of the override
itself, rather than repeating the comment from the overridden function. In many
of these cases, the override needs no additional documentation and thus no
comment is required.

When commenting constructors and destructors, just document what constructors do
with their arguments (for example, if they take ownership of pointers), and what
cleanup the destructor does. If this is trivial, just skip the comment. It is
quite common for destructors not to have a header comment.

*   Class Data Members:

The purpose of each class data member (also called an instance variable or member
variable) must be clear. If there are any invariants (special values,
relationships between members, lifetime requirements) not clearly expressed by
the type and name, they must be commented. However, if the type and name suffice
(`int num_events_;`), no comment is needed.

*   Global Variables:
All global variables should have a comment describing what they are, what they
are used for, and (if unclear) why it needs to be global. For example:

*   Explanatory Comments:

Tricky or complicated code blocks should have comments before them.

*   Line Comments:

Lines that are non-obvious should get a comment at the end of the line. These
end-of-line comments should be separated from the code by 2 spaces.

Citations:
Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html
