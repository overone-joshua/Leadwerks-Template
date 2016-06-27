#ifndef _DBJOURNAL_MODE_HPP_
    #define _DBJOURNAL_MODE_HPP_

#pragma once

typedef enum
{
    JOURNAL_MODE_DELETE = 0,
    JOURNAL_MODE_TRUNCATE = 1 << 0,
    JOURNAL_MODE_PERSIST = 1 << 1,
    JOURNAL_MODE_MEMORY = 1 << 2,
    JOURNAL_MODE_WAL = 1 << 3,
    JOURNAL_MODE_OFF = 1 << 4,

} DbJournalMode; // < end enum.

#endif _DBJOURNAL_MODE_HPP_
