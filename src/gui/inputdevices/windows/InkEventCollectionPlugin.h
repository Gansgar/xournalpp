//
// Created by Georg Friedrich on 10/14/2019.
//
#pragma once

#include <glib.h>
#include <gdk/gdk.h>

#ifdef WIN32

GdkFilterReturn filter(GdkXEvent *xevent, GdkEvent *event, gpointer data);

#endif
