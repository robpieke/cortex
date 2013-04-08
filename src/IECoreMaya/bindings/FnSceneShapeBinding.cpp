//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2013, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of Image Engine Design nor the names of any
//       other contributors to this software may be used to endorse or
//       promote products derived from this software without specific prior
//       written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "boost/python.hpp"

#include <cassert>

#include "maya/MFnDependencyNode.h"

#include "IECore/SceneInterface.h"

#include "IECoreMaya/bindings/FnSceneShapeBinding.h"
#include "IECoreMaya/StatusException.h"
#include "IECoreMaya/SceneShapeInterface.h"

using namespace IECoreMaya;
using namespace boost::python;

static IECore::SceneInterfacePtr sceneInterface( MFnDependencyNode *fnDN )
{
	assert( fnDN );
	MPxNode *userNode = fnDN->userNode();
	SceneShapeInterface *sc = dynamic_cast<SceneShapeInterface *>( userNode );
	assert( sc );
	IECore::ConstSceneInterfacePtr scnInterface = sc->getSceneInterface();
	return const_cast<IECore::SceneInterface*>( scnInterface.get() );
}

static list childrenNames( MFnDependencyNode *fnDN )
{
	assert( fnDN );
	MPxNode *userNode = fnDN->userNode();
	SceneShapeInterface *sc = dynamic_cast<SceneShapeInterface *>( userNode );
	assert( sc );
	std::vector<IECore::InternedString> names = sc->childrenNames();
	
	list result;
	for( std::vector<IECore::InternedString>::const_iterator it = names.begin(); it!=names.end(); it++ )
	{
		result.append( (*it).value() );
	}
			
	return result;
}

void IECoreMaya::bindFnSceneShape()
{

	def( "_sceneShapeSceneInterface", &sceneInterface );
	def( "_sceneShapeChildrenNames", &childrenNames );

}