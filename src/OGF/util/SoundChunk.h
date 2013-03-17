/*
 * SoundChunk.h -- Basic sound resource header file
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

#ifndef __SOUND_CHUNK_H__
#define __SOUND_CHUNK_H__

#include <SDL/SDL_mixer.h>
#include <Ogre.h>

#include "../core/LogFactory.h"

namespace OGF {
	
	class SoundChunk : public Ogre::Resource {
		
		protected:
			
			virtual void loadImpl();
			virtual void unloadImpl();
			size_t calculateSize() const;

			Mix_Chunk *_playableSource;
			Ogre::String _path;
		
		public:
			
			static std::string RESOURCE_TYPE;

			SoundChunk(Ogre::ResourceManager *resourceManager, const Ogre::String &name,
				const Ogre::ResourceHandle handle, const Ogre::String &group,
				const bool &manualLoad = 0, Ogre::ManualResourceLoader *manualLoader = 0);
			virtual ~SoundChunk();

			void play();
	};

	class SoundChunkPtr : public Ogre::SharedPtr<SoundChunk> {
		
		public:
			
			SoundChunkPtr();
			explicit SoundChunkPtr(SoundChunk *instancePtr);
			SoundChunkPtr(const SoundChunkPtr &instance);
			SoundChunkPtr(const Ogre::ResourcePtr &resourcePtr);

			SoundChunkPtr & operator= (const Ogre::ResourcePtr &resourcePtr);
	};
};

#endif
