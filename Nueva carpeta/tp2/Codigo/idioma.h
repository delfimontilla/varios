#ifndef IDIOMA__H
#define IDIOMA__H

#include "config.h"

#if defined LANG_SPANISH
#include "spanish.h"

#elif defined LANG_ENGLISH
#include "english.h"

#else 
#include "spanish.h"

#endif

#endif