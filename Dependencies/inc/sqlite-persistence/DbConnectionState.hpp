#ifndef _CONNECTION_STATE_HPP_
    #define _CONNECTION_STATE_HPP_

#pragma once

typedef enum
{
    CONNECTION_CLOSED = 0,
    CONNECTION_OPEN = 1 << 0,
    CONNECTION_CONNECTING = 1 << 1,
    CONNECTION_EXECUTING = 1 << 2,
    CONNECTION_FETCHING = 1 << 3,
    CONNECTION_BROKEN = 1 << 4,
    CONNECTION_CLOSING = 1 << 5

} DbConnectionState; // < end enum.

#endif _CONNECTION_STATE_HPP_