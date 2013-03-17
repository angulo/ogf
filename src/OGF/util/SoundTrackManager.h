/*
 * SoundTrackManager.h -- Basic sound resource manager header file
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

#ifndef __SOUND_TRACK_MANAGER_H__
#define __SOUND_TRACK_MANAGER_H__

#include <OGRE/Ogre.h>

#include "../core/LogFactory.h"
#include "SoundTrack.h"

namespace OGF {
	
	class SoundTrackManager : public Ogre::ResourceManager, public Ogre::Singleton<SoundTrackManager> {

		protected:
			
			Ogre::Resource *createImpl(const Ogre::String &name, Ogre::ResourceHandle handle,
				const Ogre::String &group, bool isManualLoad, Ogre::ManualResourceLoader *manualLoader,
				const Ogre::NameValuePairList* createParams);

		public:
			
			SoundTrackManager();
			virtual ~SoundTrackManager();

			static SoundTrackManager &getSingleton();
			static SoundTrackManager *getSingletonPtr();

			virtual SoundTrackPtr load(const Ogre::String &name, const Ogre::String &group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	};
};

#endif
