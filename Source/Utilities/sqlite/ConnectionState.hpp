#ifndef _CONNECTION_STATE_HPP_
    #define _CONNECTION_STATE_HPP_

#pragma once

typedef enum
{
    CONNECTION_CLOSED = 0 << 0,
    CONNECTION_OPEN = 0 << 1,
    CONNECTION_CONNECTING= 0 << 2,
    CONNECTION_EXECUTING = 0 << 3,
    CONNECTION_FETCHING = 0 << 4,
    CONNECTION_BROKEN = 0 << 5,
    CONNECTION_CLOSING = 0 << 6

}  ConnectionState; // < end enum.

#endif _CONNECTION_STATE_HPP_