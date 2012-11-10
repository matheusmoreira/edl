# EDL

Easy Dynamic Loading

# What's this?

EDL aims to be a simple yet complete cross-platform interface to the various
platforms' dynamic loading facilities.

# What's this for?

It lets you load a shared library at runtime and access its functions and
variables without linking to it at compile time. You can use it to implement a
plugin system, for example.

# How do I install it?

Currently, there is no stable distribution. You must install from source:

    git clone git://github.com/matheusmoreira/edl.git

# How do I use it?

The most important structure is `edl_library`. It is an opaque structure, and
you use a pointer it to open a library by name and gain access to its functions
and data.

    double (*power)(double, double);
    edl_status status = EDL_FAILURE;
    edl_library * library = NULL;

    status = edl_library_create(&library);
    if (edl_status_is_failure(status)) { /* Could not allocate memory */ }

    status = edl_library_open(library, "libm.so");
    if (edl_status_is_failure(status)) { /* Could not find library */ }

Every function returns `edl_status`. All successful and error states are
enumerated. Check the function documentation to see which statuses it may
return. There are functions to check whether the status is successful or not.
Also, a function to obtain the name of the status as a `NULL`-terminated string
is provided for easy logging.

After opening the library, you can obtain the addresses of data or functions and
start using them.

    status = edl_library_get_function(library, "pow", (edl_function *) &power);
    if (edl_status_is_failure(status)) { /* Could not find function */ }

    printf("%f" "\n", power(2, 32));

After you are done with the library, don't forget to destroy it.

    status = edl_library_destroy(&library);
    if (edl_status_is_failure(status)) { /* Could not destroy library */ }

If given an open library, `edl_library_destroy` will close it for you before
destroying it. It will also set the `library` pointer to `NULL` automatically so
you don't have to worry about that.

# Alright. What else can it do?

With `edl_api` you can declare an entire API's worth of of function or data
pointers and link them all at once with a single function call.

    typedef void (*func)(int);

    func f;
    func g;
    func h;

    int * i;
    int * j;
    int * k;

    edl_api api = {
        .objects = (edl_api_object[]) {
            { "i", (edl_object *) &i },
            { "j", (edl_object *) &j },
            { "k", (edl_object *) &k },
            NULL
        },

        .functions = (edl_api_function[]) {
            { "f", (edl_function *) &f },
            { "g", (edl_function *) &g },
            { "h", (edl_function *) &h },
            { 0 }
        }
    };

    /* Later... */

    status = edl_api_initialize(&api, library);
    if (edl_status_is_failure(status)) { /* Could not initialize API */ }

    f(*i);
    g(*j);
    h(*k);

# What's the license?

EDL is free software released under the LGPLv3. You can dynamically link to this
library in free as well as in proprietary software.

# How do I contribute?

If you've found problems or would like to make suggestions,
[create a new issue][new-issue] and I'll take a look. Also, feel free to fork
the repository, fix it or add it yourself and send me a pull request if you'd
like.

 [new-issue]: https://github.com/matheusmoreira/edl/issues/new
