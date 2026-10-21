# phewebengine

The C interface between the [Phorepoc](https://github.com/Phorepoc) browser frontend (`phebrowser`, in
[core](https://github.com/Phorepoc/core)) and a web engine: [webkit-symbian](https://github.com/Phorepoc/webkit-symbian), a
NetSurf port, or any other. One header, plain C, UTF-16 strings, no Symbian and no engine headers.

| path | what |
|---|---|
| `os/inc/phorepoc/phewebengine.h` | the interface: events, `PheWebEngineApi` (a table of function pointers), capability bits, `PheWebEngineGetApi` |

An engine package implements the table and exports `PheWebEngineGetApi` (or registers an ECom implementation of interface
`0xE7016B01`); the frontend lists installed engines and loads the chosen one at run time. Neither side includes the other's
code: both include this header. Engines are installed from the app store, not shipped in the ROM.

The header is versioned (`PHE_WEBENGINE_VERSION`, and the table's `size` field: new entries are appended, a missing entry is
NULL). Features are advertised in `caps` (find, snapshot, zoom, downloads, private views, suspend, session state).

## Using it

The repository is a layer, like the adaptations: add it to `PHOREPOC_ADAPTATIONS` and its `os/` (so `os/inc/phorepoc/`) is laid
over core's OS tree; the include-tree export publishes it as `<phorepoc/phewebengine.h>`.

## Licence

Apache-2.0 (`LICENSE`, `NOTICE`, `AUTHORS`).
