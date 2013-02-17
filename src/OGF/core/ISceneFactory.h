/*
 * ISceneFactory.h -- Scene factory interface header file.
 *
 * Copyright (C) 2013 Javier Angulo Luceron <javier.angulo1@gmail.com>
 * 
 * ogf is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ogf is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ISCENE_FACTORY_H__
#define __ISCENE_FACTORY_H__

#include "Scene.h"
#include "Types.h"

namespace OGF {
	
	class ISceneFactory {
		
		public:

			virtual ~ISceneFactory();
			virtual Scene * create(SceneId sceneId) = 0;
	};
};

#endif
