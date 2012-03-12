//
// Telescope - graphical task switcher
//
// (c) Ilya Skriblovsky, 2010
// <Ilya.Skriblovsky@gmail.com>
//

// $Id: DBus.h 174 2011-02-28 17:17:05Z mitrandir $

// DBus - class for dealing with D-Bus

#ifdef DBUS

#ifndef __TELESCOPE__DBUS_H
#define __TELESCOPE__DBUS_H

#include <dbus/dbus.h>

#include <X11/Xlib.h>

#include "XIdleTask.h"

class XEventLoop;
class TeleWindow;
class LauncherWindow;

class DBus: public XIdleTask
{
    public:
        static Atom DBUS_MESSAGE;
        enum DBusMessageType
        {
            DBusMessageShow,
            DBusMessageHide
        };

    private:
        static DBus * _instance;

        XEventLoop *_eventLoop;
        TeleWindow *_teleWindow;
        LauncherWindow *_launcherWindow;

        DBusConnection *_conn;

        DBusObjectPathVTable _telescopeVTable;
        DBusObjectPathVTable _launcherVTable;

        static void telescope_unregister(
            DBusConnection *conn,
            DBus *self
        );
        static DBusHandlerResult telescope_message(
            DBusConnection *conn,
            DBusMessage *msg,
            DBus *self
        );

        static void launcher_unregister(
            DBusConnection *conn,
            DBus *self
        );
        static DBusHandlerResult launcher_message(
            DBusConnection *conn,
            DBusMessage *msg,
            DBus *self
        );


        static void sendDBusMessageToWindow(Display *dpy, Window window, DBusMessageType msg);


        bool _dispatchOnIdle;
        static void dispatchStatusChanged(DBusConnection *conn, DBusDispatchStatus status, void *data);

        void onIdle();

    public:
        DBus(XEventLoop *eventLoop, TeleWindow *teleWindow, LauncherWindow *launcherWindow);
        virtual ~DBus();

        static DBus * instance() { return _instance; }
        DBusConnection * getConnection() { return _conn; }
};

#endif

#endif
