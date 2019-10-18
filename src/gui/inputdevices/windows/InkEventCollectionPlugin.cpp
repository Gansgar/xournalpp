//
// Created by Georg Friedrich on 10/14/2019.
//

#ifdef WIN32

#include <windows.h>

#include <iostream>

#include "InkEventCollectionPlugin.h"
#include "Win8PointerInputApi.h"

GdkFilterReturn filter(GdkXEvent *xevent, GdkEvent *event, gpointer data) {
    MSG *msg = (MSG*) xevent;

    g_warning("Got msg");
    if (msg->message == 0x0245)
        g_warning("Got a pen message");

    return GDK_FILTER_CONTINUE;
}

#endif