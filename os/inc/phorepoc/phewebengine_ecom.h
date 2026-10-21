// Copyright The Phorepoc Authors
// SPDX-License-Identifier: Apache-2.0

// phewebengine_ecom.h -- the Symbian (C++) side of the engine seam: the ECom interface an engine package implements.
//
// An engine package carries one ECom plug-in DLL. Its registration resource declares an implementation of interface
// PHE_WEBENGINE_ECOM_IFACE_UID (phewebengine.h); the implementation factory returns a CPheWebEnginePlugin whose Api() is the
// engine's PheWebEngineApi table. The frontend lists implementations without loading them (REComSession::ListImplementationsL),
// and instantiates the chosen one with CPheWebEnginePlugin::NewL on the first navigation.
//
// Header only; this is the one place the seam touches e32. Keep phewebengine.h free of it.
#ifndef PHE_WEBENGINE_ECOM_H
#define PHE_WEBENGINE_ECOM_H

#include <e32base.h>
#include <ecom/ecom.h>
#include <phorepoc/phewebengine.h>

class CPheWebEnginePlugin : public CBase
	{
public:
	// the frontend: load the DLL of implementation aImpl and return its plug-in object (the caller deletes it)
	static CPheWebEnginePlugin* NewL(TUid aImpl)
		{
		TAny* p = REComSession::CreateImplementationL(aImpl, _FOFF(CPheWebEnginePlugin, iDtorKey));
		return reinterpret_cast<CPheWebEnginePlugin*>(p);
		}
	virtual ~CPheWebEnginePlugin()
		{
		REComSession::DestroyedImplementation(iDtorKey);
		}
	// the engine's function table (PheWebEngineGetApi(PHE_WEBENGINE_VERSION)); NULL when the engine does not support the version
	virtual const PheWebEngineApi* Api() = 0;
private:
	TUid iDtorKey;
	};

#endif
