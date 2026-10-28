# webengine

This is the plug-in interface between [Phorepoc](https://github.com/Phorepoc)'s browser and the engine that draws the
pages. The browser app, `phebrowser` in [core](https://github.com/Phorepoc/core), doesn't know which engine it's
running. It talks to whichever one is installed through this one C header, and the engine talks back the same way.

That means engines can come and go independently of the browser. [webkit-symbian](https://github.com/Phorepoc/webkit-symbian)
is one, a NetSurf port could be another, and you can install them from Catalogue instead of having them built into the
ROM.

## How it works

Everything is in `os/inc/phorepoc/phewebengine.h`. It's plain C with UTF-16 strings, and it doesn't include any
Symbian or engine headers, so both sides can use it without pulling in each other's code.

An engine fills in a table of function pointers, `PheWebEngineApi`, and exports `PheWebEngineGetApi` to hand it over.
It can also register as an ECom plug-in with interface `0xE7016B01`. The browser lists the installed engines and loads
the one you pick.

The interface can grow without breaking anyone. `PHE_WEBENGINE_VERSION` and the table's `size` field tell the browser
which version it's talking to. New functions only ever go at the end, and a function an engine doesn't provide is left
NULL. Optional features, such as find in page, snapshots, zoom, downloads, private windows and saving the session, are
advertised as bits in `caps`.

## Using it

Add this repository to `PHOREPOC_ADAPTATIONS` when you build, and the header becomes available to every component as
`<phorepoc/phewebengine.h>`.

## License

Apache-2.0.
