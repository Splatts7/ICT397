/**
* @class GameAssetFactory
* @brief Parameterized factory method used for game asset creation
* @author Jack Matters
* @version 01 - Started, implemented from lecture notes
* @date 18/04/2017
*/

#ifndef GAMEASSETFACTORY_H
#define GAMEASSETFACTORY_H

#include <string>
#include "GameObject.h"

class GameAssetFactory
{
	public:

		/**
		* @brief Create a pointer to a GameObject of type 'type'
		* @param type - Type of GameObject to create
		* @return GameObject - pointer to the GameObject created
		*/
		GameObject* Create(std::string type);
};

#endif